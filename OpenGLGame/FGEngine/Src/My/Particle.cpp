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
	* 頂点データ構造体
	*/
	struct ParticleVertex
	{
		// 座標
		float x, y;

		// テクスチャ座標
		float u, v;
	};

	/**
	* 画像表示用データを格納する構造体(float*16個=64バイト)
	*/
	struct ParticleData
	{
		Matrix4x4 trasformMatrix;

		// 色と不透明度
		Vector4 color;

		// テクスチャ座標
		Texcoord texcoord;
	};

	/**
	* コンストラクタ
	*/
	ParticleEmitter::ParticleEmitter(const ParticleEmitterParameter& ep,
		const ParticleParameter& pp, ParticleManager* pManager)
		:ep(ep), pp(pp), pManager(pManager), interval(1.0f / ep.emissionsPerSecond)
	{
		texture = ep.texture;
	}

	/**
	* エミッターの管理下にあるパーティクルの状態を更新する
	*
	* @param matView	描画に使用するビュー行列
	*/
	void ParticleEmitter::Update(const Matrix4x4& matView)
	{
		// 管理オブジェクトが未設定なら何もしない
		if (!pManager)
		{
			return;
		}

		// 時間を経過させる
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
		// ソートに使う「視点からの深度値」を計算
		viewDepth = (matView * Vector4(ep.position, 1)).z;

		// パーティクルの放出
		for (; timer - emissionTimer >= interval; emissionTimer += interval)
		{
			AddParticle();
		}

		// パーティクルの更新
		for (auto e : particles)
		{
			if (e->lifeTime <= 0)
			{
				continue;
			}
			e->lifeTime -= Time::DeltaTime();

			// 速度を計算
			const float t = e->GetLifeTimeRatio();
			Vector3 velocity = e->velocity.Interporate(t);

			// 半径方向の速度を計算
			velocity += e->radialDirection * e->pp->radial.Interporate(t);

			// 重力による加速度と速度を更新
			// 加速度
			e->gravityAccel += ep.gravity * Time::DeltaTime();
			// 速度
			e->gravitySpeed += e->gravityAccel * Time::DeltaTime();
			velocity.y += e->gravitySpeed;

			// 座標を更新
			e->position += velocity * Time::DeltaTime();

			// ソートに使う「視点からの深度値」を計算
			e->viewDepth = (matView * Vector4(e->position, 1)).z;
		}

		// 死んでいるパーティクルを削除
		auto itr = std::partition(particles.begin(), particles.end(),
			[](const Particle* p) {
				return !p->IsDead();
			});
		for (auto i = itr; i != particles.end(); ++i)
		{
			pManager->DeallocateParticle(*i);	// パーティクルを返却
		}
		particles.erase(itr, particles.end());

		// パーティクルをソート
		std::sort(particles.begin(), particles.end(),
			[](const Particle* a, const Particle* b) {
				return a->viewDepth < b->viewDepth;
			});
	}

	/**
	* パーティクルを追加する
	*/
	void ParticleEmitter::AddParticle()
	{
		// パーティクルを確保できなければ何もしない
		Particle* particle = pManager->AllocateParticle();
		if (!particle)
		{
			return;
		}

		// ローカル放出座標を計算
		Vector4 position = Vector4(0, 0, 0, 1);
		switch (ep.shape)
		{
		case ParticleEmitterShape::Sphere:
		{
			const float cosTheta = pManager->RandomFloat(-1, 1);
			const float sinTheta = Mathf::Sqrt(1 - cosTheta * cosTheta);
			const float phi = pManager->RandomFloat(0, 2 * Mathf::PI);
			// 弾の体積の公式4/3π^から、半径ごとの放出頻度は半駅の３乗根で求められる
			// thicknessを3乗することで、3乗根をとった時最小値がthicknessと一致する
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

		// パーティクルのメンバー変数を初期化
		particle->pp = &pp;
		particle->lifeTime = pp.lifeTime;
		particle->position = ep.position + rot * Vector3(position);
		particle->radialDirection = Vector3(particle->position - ep.position).Normalized();
		particle->gravityAccel = 0;
		particle->gravitySpeed = 0;
		particle->viewDepth = 0;

		// 方向ランダム係数が0でなければ、移動方向にランダムを加える
		if (ep.radomizeDirection)
		{
			// 移動方向をランダム化する行列を計算
			const float randomRanage = Mathf::PI * ep.radomizeDirection;
			const Quaternion rotRandom = Quaternion::EulerToQuaternion(Vector3(
				pManager->RandomFloat(-randomRanage, randomRanage),
				pManager->RandomFloat(-randomRanage, randomRanage),
				pManager->RandomFloat(-randomRanage, randomRanage)));
			rot = rot * rotRandom;	// 回転とランダムを合成

			// 半径方向をランダム化
			particle->radialDirection = Vector3(rotRandom * particle->radialDirection);
		}
		// 速度ベクトルを回転
		particle->velocity.start = Vector3(rot * pp.velocity.start);
		particle->velocity.end = Vector3(rot * pp.velocity.end);

		// タイル数が1より多い場合、ランダムにタイルを選択する
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

		// エミッターの管理リストにパーティクルを追加
		particles.push_back(particle);
	}

	/**
	* パーティクル管理オブジェクトを作成する
	*
	* @param maxParticleCount 表示可能なパーティクルの最大数
	*/
	ParticleManagerPtr ParticleManager::Create(size_t maxParticleCount)
	{
		return std::make_shared<ParticleManager>(maxParticleCount);
	}

	/**
	* コンストラクタ
	*
	* @param maxParticleCount 表示可能なパーティクルの最大数
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

		// 必要なメモリ領域を確保
		emitters.reserve(100);
		particles.resize(maxParticleCount);

		// 未使用パーティクルリストを作成
		freeParticles.resize(maxParticleCount);
		auto itr = particles.end();
		for (auto& e : freeParticles)
		{
			--itr;
			e = &*itr;
		}

		// 乱数を初期化
		std::random_device rd;
		randomEngine.seed(rd());

		shader = ResouceSystem::ResouceManager::GetInstance()->GetShader(DefalutShader::Particle);
	}

	/**
	* デストラクタ
	*/
	ParticleManager::~ParticleManager()
	{
		// 全てのエミッターからマネージャーのアドレスを消去する
		for (auto& e : emitters)
		{
			e->pManager = nullptr;
		}
	}

	/**
	* パーティクルの状態を更新する
	*
	* @param matView 描画に使用するビュー行列
	*/
	void ParticleManager::Update(const Matrix4x4& matView)
	{
		if (emitters.empty())
		{
			return;
		}

		// エミッターの更新
		for (auto& e : emitters)
		{
			e->Update(matView);
		}

		// 死んでいるエミッターを削除
		auto itr = std::stable_partition(emitters.begin(), emitters.end(),
			[](const ParticleEmitterPtr& e) {
				return !e->IsDead();
			});
		for (auto i = itr; i != emitters.end(); ++i)
		{
			(*i)->pManager = nullptr;
		}
		emitters.erase(itr, emitters.end());

		// エミッターをソート
		std::stable_sort(emitters.begin(), emitters.end(),
			[](const ParticleEmitterPtr& a, const ParticleEmitterPtr& b) {
				return a->viewDepth < b->viewDepth;
			});
	}

	/**
	* SSBOの内容を更新する
	*/
	void ParticleManager::UpdateSSBO(const Vector3& eye)
	{
		ssbo->WaitSync();

		// 視点座標系で奥にあるエミッターからデータを設定
		auto* begin = reinterpret_cast<ParticleData*>(ssbo->GetMappedAddress());
		auto* pData = begin;
		for (auto& e : emitters)
		{
			// エミッターの描画用データ変数を更新
			e->dataOffset = (pData - begin) * sizeof(ParticleData);	// データの位置
			e->dataCount = static_cast<GLsizei>(e->particles.size());	// データの数

			// SSBOにデータを設定
			for (const auto particle : e->particles)
			{
				// パーティクル座標変換行列を計算
				Matrix4x4 pTrs = Matrix4x4(1);

				const float t = particle->GetLifeTimeRatio();

				Vector3 pos;
				Matrix3x3 rot;
				Vector3 s;
				Matrix4x4::Decompose(e->ep.objTransform, pos, s, rot);

				// 座標
				pos = pos + particle->position;
				Matrix4x4 mTrs = Matrix4x4::Translate(pos);

				// 拡大縮小
				Vector3 scale = particle->pp->scale.Interporate(t);
				Matrix4x4 mScale = Matrix4x4::Scale(scale + s);

				// 回転
				pos.y = -pos.y;
				Vector3 eyePos = eye;
				eyePos.y = -eyePos.y;
				Matrix3x3 mRot = Matrix3x3(Matrix4x4::LookAt(pos, eyePos, Vector3::up));

				pTrs = mTrs * Matrix4x4(mRot) * mScale;

				// ワールド座標変換行列を計算
				pData->trasformMatrix = pTrs;

				auto tmpColor = particle->pp->color.Interporate(t);
				pData->color = Vector4(tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.a);
				pData->texcoord = particle->texcoord;
				++pData;
			}

			// 次のオフセットが256バイト協会になるように調整
			pData += e->dataCount % 4;
		}
	}

	/**
	* パーティクルを描画する
	*
	* @param matProj 描画に使用するプロジェクション行列
	* @param matView 描画に使用するビュー行列
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

		// 深度テスト有効、深度バッファへの書き込みは行わないよいうに設定
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		glEnable(GL_BLEND);
		glDisable(GL_CULL_FACE);

		glBindVertexArray(*vao);
		glUseProgram(shader->GetProgId());

		// パーティクルを描画
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

		// ブレンド設定、深度バッファへの書き込みをデフォルトに戻す
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_TRUE);
	}

	/**
	* エミッターを追加する
	*
	* @param ep エミッターの初期化パラメータ
	* @param pp	パーティクルの初期化パラメータ
	*/
	ParticleEmitterPtr ParticleManager::AddEmitter(const ParticleEmitterParameter& ep, const ParticleParameter& pp)
	{
		ParticleEmitterPtr p = std::make_shared<ParticleEmitter>(ep, pp, this);
		emitters.push_back(p);
		return p;
	}

	/**
	* 指定された名前を持つエミッターを検索する
	*
	* @param name 検索する名前
	*
	* @return nameと一致する名前を持つエミッターへのポインター
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
	* 指定されたエミッターを削除する
	*/
	void ParticleManager::RemoveEmitter(const ParticleEmitterPtr& p)
	{
		auto itr = std::find(emitters.begin(), emitters.end(), p);
		if (itr != emitters.end())
		{
			(*itr)->pManager = nullptr;	// 管理オブジェクトへのポインタを削除
			std::swap(*itr, emitters.back());
			emitters.pop_back();
		}
	}

	/**
	* すべてのエミッターを削除する
	*/
	void ParticleManager::RemoveEmitterAll()
	{
		for (auto& e : emitters)
		{
			e->pManager = nullptr;	// 管理オブジェクトへのポインターを削除
		}
		emitters.clear();
	}

	/**
	* パーティクルを解放する
	*
	* @retval nullptr		パーティクルの確保に失敗
	* @retval nullptr以外	確保したパーティクルのアドレス
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
	* パーティクルを開放する
	*
	* @param p 解放するパーティクルのアドレス
	*/
	void ParticleManager::DeallocateParticle(Particle* p)
	{
		if (p < &particles.front() || p > &particles.back())
		{
			LOG_ERROR("管理範囲外のアドレスです(p=%x, 範囲%x - %x", p, &particles.front(), &particles.back());
			return;
		}
		freeParticles.push_back(p);
	}
}