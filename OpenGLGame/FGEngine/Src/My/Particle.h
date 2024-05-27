/**
* @file Particle.h
*/
#ifndef FGENGINE_PARTICLE_H_INCLUDED
#define FGENGINE_PARTICLE_H_INCLUDED
#include "Package/Glad.h"
#include "Texture.h"
#include "Sprite.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "Shader.h"
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Random.h"
#include "Color.h"
#include "Mathf.h"
#include <vector>
#include <memory>

// ��s�錾
class Particles;
class ParticleEmitter;
using ParticleEmitterPtr = std::shared_ptr<ParticleEmitter>;
class ParticleManager;
using ParticleManagerPtr = std::shared_ptr<ParticleManager>;

namespace FGEngine
{
	/**
	* �l�̕ۊǕ��@
	*/
	enum class InterporationType
	{
		// ���`���
		Linear,

		// ���X�ɉ���
		EaseIn,

		// ���X�Ɍ���
		EaseOut,

		// ���X�ɉ������A�R��Ɍ�������
		EaseInOut,

		// �⊮���Ȃ�
		None,
	};

	/**
	* �l��⊮����@�\�����N���X
	*/
	template <typename T>
	class Interporator
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Interporator() = default;
		~Interporator() = default;
		explicit Interporator(const T& start) :start(start), end(start){}

	public:

		// ��ԊJ�n���̒l
		T start;

		// ��ԏI�����̒l
		T end;

		// ��ԕ��@
		InterporationType type = InterporationType::Linear;
	};
	using Interporator1f = Interporator<float>;
	using Interporator2f = Interporator<Vector2>;
	using Interporator3f = Interporator<Vector3>;
	using Interporator4f = Interporator<Vector4>;

	/**
	* �p�[�e�B�N���̓�����`����p�����[�^
	*/
	struct ParticleParameter
	{
		// ��������
		float lifeTime = 1;

		// �e�N�X�`�����W
		Texcoord tc = { 0, 0, Vector2::one };

		// ���a�����̑��x
		Interporator1f radial = Interporator1f(10);

		// ���x
		Interporator3f velocity = Interporator3f(Vector3::zero);

		// �傫��
		Interporator2f scale = Interporator2f(Vector2::one);

		// ��]
		Interporator1f rotation = Interporator1f(0);

		// �F�ƕs�����x
		Interporator<Color> color = Interporator<Color>(Color::white);
	};

	/**
	* �G�~�b�^�[�̌`��
	*/
	enum class ParticleEmitterShape
	{
		// ��
		Sphere,

		// ������
		Box,
	};

	/**
	* �p�[�e�B�N���B�G�~�b�^�[�̃p�����[�^
	*/
	struct ParticleEmitterParameter
	{
		// �G�~�b�^�[��
		std::string name;

		// �d��
		float gravity = -9.8f;

		// �e�N�X�`��
		TexturePtr texture;

		// �e�N�X�`���̏c�Ɖ��̕�����
		Vector2 tiles = Vector2::one;

		// �u�����h�W��
		GLenum srcFactor = GL_SRC0_ALPHA;

		// �u�����h�W��
		GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA;

		// �p�[�e�B�N������o����b��
		float diuration = 1.0f;

		// duration�o�ߌ�̓���(true=���[�v�Afalse=��~)
		bool isLoop = false;

		// 1�b������̃p�[�e�B�N�����o��
		float emissionsPerSecond = 10.0f;

		// ���W
		Vector3 position = Vector3::zero;

		// ��]
		Vector3 rotation = Vector3::zero;

		// �`��
		ParticleEmitterShape shape = ParticleEmitterShape::Sphere;

		// ���o�����̗�����(0=�����A1=���S�����_��)
		float radomizeDirection = 0;

		union
		{
			struct Sphere
			{
				// ���̔��a
				float radius = 1;

				// ���k�̌���(0=�Ŕ��A1=���S�܂ł�������)
				float thickness = 1;
			};
			Sphere sphere;

			struct Box
			{
				// �����`�̃T�C�Y
				Vector3 size = Vector3::one;
			};

			Box box;
		};

		// �R���X�g���N�^�E�f�X�g���N�^
		ParticleEmitterParameter() : sphere({1,1}){}
		~ParticleEmitterParameter() = default;

		/**
		* ���o�͈͂ɋ����w�肷��
		* 
		* @param radius		���̔��a
		* @param thickness	���k�̌���
		*/
		void SetSphereShape(float radius, float thickness)
		{
			shape = ParticleEmitterShape::Sphere;
			sphere.radius = radius;
			sphere.thickness = thickness;
		}

		/**
		* ���o�͈͂ɒ����n���w�肷��
		* 
		* @param size �����`�̃T�C�Y
		*/
		void SetBoxShape(const Vector3& size)
		{
			shape = ParticleEmitterShape::Box;
			box.size = size;
		}
	};

	/**
	* �p�[�e�B�N��
	*/
	class Particle
	{
	public:

		friend ParticleManager;
		friend ParticleEmitter;

		// �R���X�g���N�^�E�f�X�g���N�^
		Particle() = default;
		~Particle() = default;

		/**
		* �������Ԃ̔䗦
		*/
		float GetLifeTimeRatio() const
		{
			const float t = 1 - lifeTime / pp->lifeTime;
			return Mathf::Clamp(t, 0.0f, 1.0f);
		}

		/**
		* ���S���Ă��邩���擾
		* 
		* @retval true  ���S
		* @retval false ����
		*/
		bool IsDead() const
		{
			return  lifeTime <= 0;
		}

	private:

		// === �ω����Ȃ��p�����[�^ === //

		// ��{�p�����[�^
		const ParticleParameter* pp;

		// ���S����̌���
		Vector3 radialDirection = Vector3(1, 0, 0);

		// ���x
		Interporator3f velocity = Interporator3f(Vector3::zero);

		// �e�N�X�`�����W
		Texcoord texcoord = { 0, 0,Vector2::one };

		// === �ω�����p�����[�^ === //

		// ��������
		float lifeTime = 0;

		// ���W
		Vector3 position = Vector3::zero;

		// �d�͂ɂ������x�̍��v
		float gravityAccel = 0;

		// �d�ʂɂ�鑬�x�̍��v
		float gravitySpeed = 0;

		// ���_����̐[�x�l
		float viewDepth = 0;
	};

	/**
	* �p�[�e�B�N�������N���X
	*/
	class ParticleEmitter
	{
	public:

		friend ParticleManager;
		
		// �R���X�g���N�^�E�f�X�g���N�^
		ParticleEmitter(const ParticleEmitterParameter& ep,
			const ParticleParameter& pp, ParticleManager* pManager);
		~ParticleEmitter() = default;

		// �R�s�[�Ƒ�����֎~
		ParticleEmitter(const ParticleEmitter&) = delete;
		ParticleEmitter& operator=(const ParticleEmitter&) = delete;

		void Update(const Matrix4x4& matView);
		void Die()
		{
			ep.isLoop = false;
			ep.diuration = 0;
		}
		bool IsDead() const
		{
			return !ep.isLoop && timer >= ep.diuration && particles.empty();
		}

		// �p�����[�^�̎擾�E�ݒ�
		ParticleEmitterParameter & GetEmitterParameter() { return ep; }
		const ParticleEmitterParameter & GetEmitterParameter() const { return ep; }
		ParticleParameter & GetParticleParameter() { return pp; }
		const ParticleParameter & GetParticleParameter() const { return pp; }

	private:

		void AddParticle();

	private:

		// �G�~�b�^�[�̃p�����[�^
		ParticleEmitterParameter ep;

		// �p�[�e�B�N���̃p�����[�^
		ParticleParameter pp;

		// �Ǘ��N���X�̃A�h���X
		ParticleManager* pManager = nullptr;

		// �p�[�e�B�N���p�e�N�X�`��
		TexturePtr texture;

		// �p�[�e�B�N���̔����Ԋu(�b)
		float interval = 0;

		// ���o�ߎ���(�b)
		float timer = 0;

		// �p�[�e�B�N�������^�C�}�[(�b)
		float emissionTimer = 0;

		// ���_����̐[�x�l
		float viewDepth = 0;
		
		// �p�[�e�B�N�����X�g
		std::vector<Particle*> particles;

		// �`�悷��p�[�e�B�N����
		GLsizei dataCount = 0;

		// �`��̊�ƂȂ钸�_�̃I�t�Z�b�g
		size_t dataOffset = 0;
	};
}

#endif // !FGENGINE_PARTICLE_H_INCLUDED
