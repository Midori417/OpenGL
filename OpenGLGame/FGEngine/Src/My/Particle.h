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

// 先行宣言
class Particles;
class ParticleEmitter;
using ParticleEmitterPtr = std::shared_ptr<ParticleEmitter>;
class ParticleManager;
using ParticleManagerPtr = std::shared_ptr<ParticleManager>;

namespace FGEngine
{
	/**
	* 値の保管方法
	*/
	enum class InterporationType
	{
		// 線形補間
		Linear,

		// 徐々に加速
		EaseIn,

		// 徐々に減速
		EaseOut,

		// 徐々に加速し、抒情に減速する
		EaseInOut,

		// 補完しない
		None,
	};

	/**
	* 値を補完する機能を持つクラス
	*/
	template <typename T>
	class Interporator
	{
	public:

		// コンストラクタ・デストラクタ
		Interporator() = default;
		~Interporator() = default;
		explicit Interporator(const T& start) :start(start), end(start){}

	public:

		// 補間開始時の値
		T start;

		// 補間終了時の値
		T end;

		// 補間方法
		InterporationType type = InterporationType::Linear;
	};
	using Interporator1f = Interporator<float>;
	using Interporator2f = Interporator<Vector2>;
	using Interporator3f = Interporator<Vector3>;
	using Interporator4f = Interporator<Vector4>;

	/**
	* パーティクルの動作を定義するパラメータ
	*/
	struct ParticleParameter
	{
		// 生存時間
		float lifeTime = 1;

		// テクスチャ座標
		Texcoord tc = { 0, 0, Vector2::one };

		// 半径方向の速度
		Interporator1f radial = Interporator1f(10);

		// 速度
		Interporator3f velocity = Interporator3f(Vector3::zero);

		// 大きさ
		Interporator2f scale = Interporator2f(Vector2::one);

		// 回転
		Interporator1f rotation = Interporator1f(0);

		// 色と不透明度
		Interporator<Color> color = Interporator<Color>(Color::white);
	};

	/**
	* エミッターの形状
	*/
	enum class ParticleEmitterShape
	{
		// 球
		Sphere,

		// 直方体
		Box,
	};

	/**
	* パーティクル。エミッターのパラメータ
	*/
	struct ParticleEmitterParameter
	{
		// エミッター名
		std::string name;

		// 重力
		float gravity = -9.8f;

		// テクスチャ
		TexturePtr texture;

		// テクスチャの縦と横の分割数
		Vector2 tiles = Vector2::one;

		// ブレンド係数
		GLenum srcFactor = GL_SRC0_ALPHA;

		// ブレンド係数
		GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA;

		// パーティクルを放出する秒数
		float diuration = 1.0f;

		// duration経過後の動作(true=ループ、false=停止)
		bool isLoop = false;

		// 1秒あたりのパーティクル放出数
		float emissionsPerSecond = 10.0f;

		// 座標
		Vector3 position = Vector3::zero;

		// 回転
		Vector3 rotation = Vector3::zero;

		// 形状
		ParticleEmitterShape shape = ParticleEmitterShape::Sphere;

		// 放出方向の乱数性(0=無し、1=完全ランダム)
		float radomizeDirection = 0;

		union
		{
			struct Sphere
			{
				// 球の半径
				float radius = 1;

				// 球殻の厚み(0=最薄、1=中心までぎっしり)
				float thickness = 1;
			};
			Sphere sphere;

			struct Box
			{
				// 長方形のサイズ
				Vector3 size = Vector3::one;
			};

			Box box;
		};

		// コンストラクタ・デストラクタ
		ParticleEmitterParameter() : sphere({1,1}){}
		~ParticleEmitterParameter() = default;

		/**
		* 放出範囲に球を指定する
		* 
		* @param radius		球の半径
		* @param thickness	球殻の厚み
		*/
		void SetSphereShape(float radius, float thickness)
		{
			shape = ParticleEmitterShape::Sphere;
			sphere.radius = radius;
			sphere.thickness = thickness;
		}

		/**
		* 放出範囲に直方系を指定する
		* 
		* @param size 長方形のサイズ
		*/
		void SetBoxShape(const Vector3& size)
		{
			shape = ParticleEmitterShape::Box;
			box.size = size;
		}
	};

	/**
	* パーティクル
	*/
	class Particle
	{
	public:

		friend ParticleManager;
		friend ParticleEmitter;

		// コンストラクタ・デストラクタ
		Particle() = default;
		~Particle() = default;

		/**
		* 生存時間の比率
		*/
		float GetLifeTimeRatio() const
		{
			const float t = 1 - lifeTime / pp->lifeTime;
			return Mathf::Clamp(t, 0.0f, 1.0f);
		}

		/**
		* 死亡しているかを取得
		* 
		* @retval true  死亡
		* @retval false 生存
		*/
		bool IsDead() const
		{
			return  lifeTime <= 0;
		}

	private:

		// === 変化しないパラメータ === //

		// 基本パラメータ
		const ParticleParameter* pp;

		// 中心からの向き
		Vector3 radialDirection = Vector3(1, 0, 0);

		// 速度
		Interporator3f velocity = Interporator3f(Vector3::zero);

		// テクスチャ座標
		Texcoord texcoord = { 0, 0,Vector2::one };

		// === 変化するパラメータ === //

		// 生存期間
		float lifeTime = 0;

		// 座標
		Vector3 position = Vector3::zero;

		// 重力による加速度の合計
		float gravityAccel = 0;

		// 重量による速度の合計
		float gravitySpeed = 0;

		// 視点からの深度値
		float viewDepth = 0;
	};

	/**
	* パーティクル発生クラス
	*/
	class ParticleEmitter
	{
	public:

		friend ParticleManager;
		
		// コンストラクタ・デストラクタ
		ParticleEmitter(const ParticleEmitterParameter& ep,
			const ParticleParameter& pp, ParticleManager* pManager);
		~ParticleEmitter() = default;

		// コピーと代入を禁止
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

		// パラメータの取得・設定
		ParticleEmitterParameter & GetEmitterParameter() { return ep; }
		const ParticleEmitterParameter & GetEmitterParameter() const { return ep; }
		ParticleParameter & GetParticleParameter() { return pp; }
		const ParticleParameter & GetParticleParameter() const { return pp; }

	private:

		void AddParticle();

	private:

		// エミッターのパラメータ
		ParticleEmitterParameter ep;

		// パーティクルのパラメータ
		ParticleParameter pp;

		// 管理クラスのアドレス
		ParticleManager* pManager = nullptr;

		// パーティクル用テクスチャ
		TexturePtr texture;

		// パーティクルの発生間隔(秒)
		float interval = 0;

		// 総経過時間(秒)
		float timer = 0;

		// パーティクル発生タイマー(秒)
		float emissionTimer = 0;

		// 視点からの深度値
		float viewDepth = 0;
		
		// パーティクルリスト
		std::vector<Particle*> particles;

		// 描画するパーティクル数
		GLsizei dataCount = 0;

		// 描画の基準となる頂点のオフセット
		size_t dataOffset = 0;
	};
}

#endif // !FGENGINE_PARTICLE_H_INCLUDED
