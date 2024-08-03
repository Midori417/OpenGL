/**
* @file Particle.cpp
*/
#include "Particle.h"
#include "Debug.h"
#include "Time.h"
#include "Quaternion.h"
#include "ResouceManager.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* ���_�f�[�^�\����
	*/
	struct ParticleVertex
	{
		// ���W
		float x, y;

		// �e�N�X�`�����W
		float u, v;
	};

	/**
	* �摜�\���p�f�[�^���i�[����\����(float*16��=64�o�C�g)
	*/
	struct ParticleData
	{
		Matrix4x4 trasformMatrix;

		// �F�ƕs�����x
		Vector4 color;

		// �e�N�X�`�����W
		Texcoord texcoord;
	};

	/**
	* �R���X�g���N�^
	*/
	ParticleEmitter::ParticleEmitter(const ParticleEmitterParameter& ep,
		const ParticleParameter& pp, ParticleManager* pManager)
		:ep(ep), pp(pp), pManager(pManager), interval(1.0f / ep.emissionsPerSecond)
	{
		texture = ep.texture;
	}

	/**
	* �G�~�b�^�[�̊Ǘ����ɂ���p�[�e�B�N���̏�Ԃ��X�V����
	*
	* @param matView	�`��Ɏg�p����r���[�s��
	*/
	void ParticleEmitter::Update(const Matrix4x4& matView)
	{
		// �Ǘ��I�u�W�F�N�g�����ݒ�Ȃ牽�����Ȃ�
		if (!pManager)
		{
			return;
		}

		// ���Ԃ��o�߂�����
		timer += Time::DeltaTime();
		if (timer >= ep.duration)
		{
			if (ep.isLoop)
			{
				timer -= ep.duration;
				emissionTimer -= ep.duration;
			}
			else
			{
				timer = ep.duration;
			}
		}
		// �\�[�g�Ɏg���u���_����̐[�x�l�v���v�Z
		viewDepth = (matView * Vector4(ep.position, 1)).z;

		// �p�[�e�B�N���̕��o
		for (; timer - emissionTimer >= interval; emissionTimer += interval)
		{
			AddParticle();
		}

		// �p�[�e�B�N���̍X�V
		for (auto e : particles)
		{
			if (e->lifeTime <= 0)
			{
				continue;
			}
			e->lifeTime -= Time::DeltaTime();

			// ���x���v�Z
			const float t = e->GetLifeTimeRatio();
			Vector3 velocity = e->velocity.Interporate(t);

			// ���a�����̑��x���v�Z
			velocity += e->radialDirection * e->pp->radial.Interporate(t);

			// �d�͂ɂ������x�Ƒ��x���X�V
			// �����x
			e->gravityAccel += ep.gravity * Time::DeltaTime();
			// ���x
			e->gravitySpeed += e->gravityAccel * Time::DeltaTime();
			velocity.y += e->gravitySpeed;

			// ���W���X�V
			e->position += velocity * Time::DeltaTime();

			// �\�[�g�Ɏg���u���_����̐[�x�l�v���v�Z
			e->viewDepth = (matView * Vector4(e->position, 1)).z;
		}

		// ����ł���p�[�e�B�N�����폜
		auto itr = std::partition(particles.begin(), particles.end(),
			[](const Particle* p) {
				return !p->IsDead();
			});
		for (auto i = itr; i != particles.end(); ++i)
		{
			pManager->DeallocateParticle(*i);	// �p�[�e�B�N����ԋp
		}
		particles.erase(itr, particles.end());

		// �p�[�e�B�N�����\�[�g
		std::sort(particles.begin(), particles.end(),
			[](const Particle* a, const Particle* b) {
				return a->viewDepth < b->viewDepth;
			});
	}

	/**
	* �p�[�e�B�N����ǉ�����
	*/
	void ParticleEmitter::AddParticle()
	{
		// �p�[�e�B�N�����m�ۂł��Ȃ���Ή������Ȃ�
		Particle* particle = pManager->AllocateParticle();
		if (!particle)
		{
			return;
		}

		// ���[�J�����o���W���v�Z
		Vector4 position = Vector4(0, 0, 0, 1);
		switch (ep.shape)
		{
		case ParticleEmitterShape::Sphere:
		{
			const float cosTheta = pManager->RandomFloat(-1, 1);
			const float sinTheta = Mathf::Sqrt(1 - cosTheta * cosTheta);
			const float phi = pManager->RandomFloat(0, 2 * Mathf::PI);
			// �e�̑̐ς̌���4/3��^����A���a���Ƃ̕��o�p�x�͔��w�̂R�捪�ŋ��߂���
			// thickness��3�悷�邱�ƂŁA3�捪���Ƃ������ŏ��l��thickness�ƈ�v����
			const float t = ep.sphere.thickness;
			const float r0 = pManager->RandomFloat(1 - t * t * t, 1);
			const float r = std::cbrt(r0) * ep.sphere.radius;
			position.x = r * sinTheta * Mathf::Cos(phi);
			position.y = r * sinTheta * Mathf::Sin(phi);
			position.z = r * cosTheta;
			break;
		}
		case ParticleEmitterShape::Box:
			position.x = pManager->RandomFloat(-ep.box.size.x, ep.box.size.x);
			position.y = pManager->RandomFloat(-ep.box.size.y, ep.box.size.y);
			position.z = pManager->RandomFloat(-ep.box.size.z, ep.box.size.z);
			break;
		}

		Vector3 pos;
		Matrix3x3 mRot;
		Vector3 scale;
		Matrix4x4::Decompose(ep.objTransform, pos, scale, mRot);

		Quaternion rot = Quaternion::RotationMatrixToQuaternion(mRot).Inverse();

		// �p�[�e�B�N���̃����o�[�ϐ���������
		particle->pp = &pp;
		particle->lifeTime = pp.lifeTime;
		particle->position = ep.position + rot * Vector3(position);
		particle->radialDirection = Vector3(particle->position - ep.position).Normalized();
		particle->gravityAccel = 0;
		particle->gravitySpeed = 0;
		particle->viewDepth = 0;

		// ���������_���W����0�łȂ���΁A�ړ������Ƀ����_����������
		if (ep.radomizeDirection)
		{
			// �ړ������������_��������s����v�Z
			const float randomRanage = Mathf::PI * ep.radomizeDirection;
			const Quaternion rotRandom = Quaternion::EulerToQuaternion(Vector3(
				pManager->RandomFloat(-randomRanage, randomRanage),
				pManager->RandomFloat(-randomRanage, randomRanage),
				pManager->RandomFloat(-randomRanage, randomRanage)));
			rot = rot * rotRandom;	// ��]�ƃ����_��������

			// ���a�����������_����
			particle->radialDirection = Vector3(rotRandom * particle->radialDirection);
		}
		// ���x�x�N�g������]
		particle->velocity.start = Vector3(rot * pp.velocity.start);
		particle->velocity.end = Vector3(rot * pp.velocity.end);

		// �^�C������1��葽���ꍇ�A�����_���Ƀ^�C����I������
		if (ep.tiles.x > 1 || ep.tiles.y > 1)
		{
			const Vector2 invTiles = 1.0f / ep.tiles;
			const int u = pManager->RandomInt(0, static_cast<int>(ep.tiles.x) - 1);
			const int v = pManager->RandomInt(0, static_cast<int>(ep.tiles.y) - 1);
			particle->texcoord.uv.x = static_cast<float>(u) * invTiles.x;
			particle->texcoord.uv.y = static_cast<float>(v) * invTiles.y;
			particle->texcoord.size.x = invTiles.x;
			particle->texcoord.size.y = invTiles.y;
		}

		// �G�~�b�^�[�̊Ǘ����X�g�Ƀp�[�e�B�N����ǉ�
		particles.push_back(particle);
	}

	/**
	* �p�[�e�B�N���Ǘ��I�u�W�F�N�g���쐬����
	*
	* @param maxParticleCount �\���\�ȃp�[�e�B�N���̍ő吔
	*/
	ParticleManagerPtr ParticleManager::Create(size_t maxParticleCount)
	{
		return std::make_shared<ParticleManager>(maxParticleCount);
	}

	/**
	* �R���X�g���N�^
	*
	* @param maxParticleCount �\���\�ȃp�[�e�B�N���̍ő吔
	*/
	ParticleManager::ParticleManager(size_t maxParticleCount)
		:maxParticleCount(maxParticleCount)
	{
		const ParticleVertex vertexData[] = {
			{-0.5f,-0.5f, 0, 1},
			{ 0.5f,-0.5f, 1, 1},
			{ 0.5f, 0.5f, 1, 0},
			{-0.5f, 0.5f, 0, 0},
		};
		vbo = RenderingSystem::BufferObject::Create(sizeof(vertexData), vertexData);

		const GLushort indexData[] = { 0, 1, 2, 2, 3, 0 };
		ibo = RenderingSystem::BufferObject::Create(sizeof(indexData), indexData);

		vao = RenderingSystem::VertexArrayObject::Create();

		glBindVertexArray(*vao);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
			(const void*)offsetof(ParticleVertex, u));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		ssbo = RenderingSystem::MappedBufferObject::Create(maxParticleCount * sizeof(ParticleData),
			GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);

		// �K�v�ȃ������̈���m��
		emitters.reserve(100);
		particles.resize(maxParticleCount);

		// ���g�p�p�[�e�B�N�����X�g���쐬
		freeParticles.resize(maxParticleCount);
		auto itr = particles.end();
		for (auto& e : freeParticles)
		{
			--itr;
			e = &*itr;
		}

		// ������������
		std::random_device rd;
		randomEngine.seed(rd());

		shader = ResouceSystem::ResouceManager::GetInstance()->GetShader(DefalutShader::Particle);
	}

	/**
	* �f�X�g���N�^
	*/
	ParticleManager::~ParticleManager()
	{
		// �S�ẴG�~�b�^�[����}�l�[�W���[�̃A�h���X����������
		for (auto& e : emitters)
		{
			e->pManager = nullptr;
		}
	}

	/**
	* �p�[�e�B�N���̏�Ԃ��X�V����
	*
	* @param matView �`��Ɏg�p����r���[�s��
	*/
	void ParticleManager::Update(const Matrix4x4& matView)
	{
		if (emitters.empty())
		{
			return;
		}

		// �G�~�b�^�[�̍X�V
		for (auto& e : emitters)
		{
			e->Update(matView);
		}

		// ����ł���G�~�b�^�[���폜
		auto itr = std::stable_partition(emitters.begin(), emitters.end(),
			[](const ParticleEmitterPtr& e) {
				return !e->IsDead();
			});
		for (auto i = itr; i != emitters.end(); ++i)
		{
			(*i)->pManager = nullptr;
		}
		emitters.erase(itr, emitters.end());

		// �G�~�b�^�[���\�[�g
		std::stable_sort(emitters.begin(), emitters.end(),
			[](const ParticleEmitterPtr& a, const ParticleEmitterPtr& b) {
				return a->viewDepth < b->viewDepth;
			});
	}

	/**
	* SSBO�̓��e���X�V����
	*/
	void ParticleManager::UpdateSSBO(const Vector3& eye)
	{
		ssbo->WaitSync();

		// ���_���W�n�ŉ��ɂ���G�~�b�^�[����f�[�^��ݒ�
		auto* begin = reinterpret_cast<ParticleData*>(ssbo->GetMappedAddress());
		auto* pData = begin;
		for (auto& e : emitters)
		{
			// �G�~�b�^�[�̕`��p�f�[�^�ϐ����X�V
			e->dataOffset = (pData - begin) * sizeof(ParticleData);	// �f�[�^�̈ʒu
			e->dataCount = static_cast<GLsizei>(e->particles.size());	// �f�[�^�̐�

			// SSBO�Ƀf�[�^��ݒ�
			for (const auto particle : e->particles)
			{
				// �p�[�e�B�N�����W�ϊ��s����v�Z
				Matrix4x4 pTrs = Matrix4x4(1);

				const float t = particle->GetLifeTimeRatio();

				Vector3 pos;
				Matrix3x3 rot;
				Vector3 s;
				Matrix4x4::Decompose(e->ep.objTransform, pos, s, rot);

				// ���W
				pos = pos + particle->position;
				Matrix4x4 mTrs = Matrix4x4::Translate(pos);

				// �g��k��
				Vector3 scale = particle->pp->scale.Interporate(t);
				Matrix4x4 mScale = Matrix4x4::Scale(scale + s);

				// ��]
				pos.y = -pos.y;
				Vector3 eyePos = eye;
				eyePos.y = -eyePos.y;
				Matrix3x3 mRot = Matrix3x3(Matrix4x4::LookAt(pos, eyePos, Vector3::up));

				pTrs = mTrs * Matrix4x4(mRot) * mScale;

				// ���[���h���W�ϊ��s����v�Z
				pData->trasformMatrix = pTrs;

				auto tmpColor = particle->pp->color.Interporate(t);
				pData->color = Vector4(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
				pData->texcoord = particle->texcoord;
				++pData;
			}

			// ���̃I�t�Z�b�g��256�o�C�g����ɂȂ�悤�ɒ���
			pData += e->dataCount % 4;
		}
	}

	/**
	* �p�[�e�B�N����`�悷��
	*
	* @param matProj �`��Ɏg�p����v���W�F�N�V�����s��
	* @param matView �`��Ɏg�p����r���[�s��
	*/
	void ParticleManager::Draw()
	{
		if (!shader)
		{
			shader = ResouceSystem::ResouceManager::GetInstance()->GetShader(DefalutShader::Particle);
		}
		if (emitters.empty() || !shader)
		{
			return;
		}

		// �[�x�e�X�g�L���A�[�x�o�b�t�@�ւ̏������݂͍s��Ȃ��悢���ɐݒ�
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		glEnable(GL_BLEND);
		glDisable(GL_CULL_FACE);

		glBindVertexArray(*vao);
		glUseProgram(shader->GetProgId());

		// �p�[�e�B�N����`��
		for (auto& e : emitters)
		{

			if (e->dataCount <= 0 || e->texture == nullptr)
			{
				continue;
			}
			glBlendFunc(e->ep.srcFactor, e->ep.dstFactor);
			GLuint tex = *e->texture;
			glBindTextures(0, 1, &tex);
			ssbo->Bind(0, e->dataOffset, e->dataCount * sizeof(ParticleData));
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0, e->dataCount);
		}
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 0, 0, 0);
		ssbo->SwapBuffers();

		glBindTextures(0, 1, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);

		// �u�����h�ݒ�A�[�x�o�b�t�@�ւ̏������݂��f�t�H���g�ɖ߂�
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_TRUE);
	}

	/**
	* �G�~�b�^�[��ǉ�����
	*
	* @param ep �G�~�b�^�[�̏������p�����[�^
	* @param pp	�p�[�e�B�N���̏������p�����[�^
	*/
	ParticleEmitterPtr ParticleManager::AddEmitter(const ParticleEmitterParameter& ep, const ParticleParameter& pp)
	{
		ParticleEmitterPtr p = std::make_shared<ParticleEmitter>(ep, pp, this);
		emitters.push_back(p);
		return p;
	}

	/**
	* �w�肳�ꂽ���O�����G�~�b�^�[����������
	*
	* @param name �������閼�O
	*
	* @return name�ƈ�v���閼�O�����G�~�b�^�[�ւ̃|�C���^�[
	*/
	ParticleEmitterPtr ParticleManager::FindEmitter(const std::string& name) const
	{
		auto itr = std::find_if(emitters.begin(), emitters.end(),
			[name](const ParticleEmitterPtr& p) {
				return p->ep.name == name;
			});
		if (itr != emitters.end())
		{
			return *itr;
		}
		return nullptr;
	}

	/**
	* �w�肳�ꂽ�G�~�b�^�[���폜����
	*/
	void ParticleManager::RemoveEmitter(const ParticleEmitterPtr& p)
	{
		auto itr = std::find(emitters.begin(), emitters.end(), p);
		if (itr != emitters.end())
		{
			(*itr)->pManager = nullptr;	// �Ǘ��I�u�W�F�N�g�ւ̃|�C���^���폜
			std::swap(*itr, emitters.back());
			emitters.pop_back();
		}
	}

	/**
	* ���ׂẴG�~�b�^�[���폜����
	*/
	void ParticleManager::RemoveEmitterAll()
	{
		for (auto& e : emitters)
		{
			e->pManager = nullptr;	// �Ǘ��I�u�W�F�N�g�ւ̃|�C���^�[���폜
		}
		emitters.clear();
	}

	/**
	* �p�[�e�B�N�����������
	*
	* @retval nullptr		�p�[�e�B�N���̊m�ۂɎ��s
	* @retval nullptr�ȊO	�m�ۂ����p�[�e�B�N���̃A�h���X
	*/
	Particle* ParticleManager::AllocateParticle()
	{
		if (freeParticles.empty())
		{
			return nullptr;
		}
		auto p = freeParticles.back();
		freeParticles.pop_back();
		return p;
	}

	/**
	* �p�[�e�B�N�����J������
	*
	* @param p �������p�[�e�B�N���̃A�h���X
	*/
	void ParticleManager::DeallocateParticle(Particle* p)
	{
		if (p < &particles.front() || p > &particles.back())
		{
			LOG_ERROR("�Ǘ��͈͊O�̃A�h���X�ł�(p=%x, �͈�%x - %x", p, &particles.front(), &particles.back());
			return;
		}
		freeParticles.push_back(p);
	}
}