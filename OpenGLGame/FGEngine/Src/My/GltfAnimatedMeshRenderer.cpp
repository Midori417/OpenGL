/**
* @file GltfAnimatedMeshRenderer.cpp
*/
#include "GltfAnimatednMeshRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"
#include "Mathf.h"
#include <algorithm>

/**
* アニメーション状態を更新する
*/
void GltfAnimatedMeshRenderer::Update()
{
	if (file->animations.empty() || !animation)
	{
		return;
	}

	// アニメーション状態を更新
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		// 再生時刻を更新
		time += animationSpeed * Time::deltaTime();
		if (isLoop)
		{
 			time -= animation->totalTime * std::floor(time / animation->totalTime);
		}
		else
		{
			time = Mathf::Clamp(time, 0.0f, animation->totalTime);
			if (time >= animation->totalTime)
			{
				state = State::stop;
			}
		}
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		break;
	}
}

/**
* 描画の前処理を実行
*
* @param gameObject 描画対象のゲームオブジェクト
*/
void GltfAnimatedMeshRenderer::PreDraw()
{
	if (!fileBuffer || !file)
	{
		return;
	}

	// シーンに含まれるメッシュのアニメーション行列を更新
	const auto scene = &file->scenes[0];
	const Matrix4x4 matModel = transform->GetModelMatrix();
	ssboRanges.clear();
	for (const auto e : scene->meshNodes)
	{
		// アニメーション行列を計算
		auto matBones = CalcAnimationMatrices(file, e, animation.get(), time);
		for (auto& m : matBones)
		{
			m = matModel * m; // アニメーション行列にモデル行列を合成
		}
		// アニメーション行列をバッファに追加し、追加先のオフセットとサイズを記録
		ssboRanges.push_back(fileBuffer->AddAnimationMatrices(matBones));
	}
}

/**
* メッシュを描画する
*
* @param progaram 描画に使うプログラムパイプラインオブジェクト
* @param matGameObject ゲームオブジェクトのモデル行列
*/
void GltfAnimatedMeshRenderer::Draw(const ProgramObject& program, Type type) const
{
	if (!fileBuffer || !file || ssboRanges.empty())
	{
		return;
	}

	// シーンに含まれるメッシュを描画
	const auto scene = &file->scenes[0];
	for (size_t i = 0; i < scene->meshNodes.size(); ++i)
	{
		const int meshNo = scene->meshNodes[i]->mesh;
		const GltfMesh& mesh = file->meshes[meshNo];

		// SSBOをバインディングポイント0番に割り当てる
		fileBuffer->BindAnimationBuffer(0, ssboRanges[i]);

		// マテリアルが指定されていない場合、共有マテリアルを使って描画する
		const auto* pMaterials = &materials;
		if (materials.empty())
		{
			pMaterials = &file->materials;
		}

		// メッシュに含まれるすべてのプリミティブを描画
		::Draw(mesh, *pMaterials, program);
	}
}

/**
* アニメーションの再生を開始・再開する
*/
void GltfAnimatedMeshRenderer::Play()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		time = 0;	// 先頭から再生
		state = State::play;
		break;
	case GltfAnimatedMeshRenderer::State::play:
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		state = State::play;
		break;
	}
}

/**
* アニメーションの再生を停止する
*/
void GltfAnimatedMeshRenderer::Stop()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		state = State::stop;
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		state = State::stop;
		break;
	}
}

/**
* アニメーションの再生を一時停止する
*/
void GltfAnimatedMeshRenderer::Pause()
{
	switch (state)
	{
	case GltfAnimatedMeshRenderer::State::stop:
		break;
	case GltfAnimatedMeshRenderer::State::play:
		state = State::pause;
		break;
	case GltfAnimatedMeshRenderer::State::pause:
		break;
	}
}

/**
* アニメーションを設定する
* 
* @param animation	再生するアニメーション
* @param isLoop		ループ再生の指定(true=ループする、false=ループしない)
* 
* @retval true	設定成功
* @retval false	設定失敗
*/
bool GltfAnimatedMeshRenderer::SetAnimation(const GltfAnimationPtr& animation, bool isLoop)
{
	// 同じアニメーションが指定された場合は何もしない
	if (this->animation == animation)
	{
		return true;	// 設定成功として扱う
	}
	this->animation = animation;	// アニメーションを設定

	// 状態を「停止中」に設定
	time = 0;
	state = State::stop;
	this->isLoop = isLoop;

	return true;
}

/**
* アニメーションを設定する
*
* @param name		再生するアニメーションの名前
* @param isLoop		ループ再生の指定(true=ループする、false=ループしない)
*
* @retval true	設定成功
* @retval false	設定失敗
*/
bool GltfAnimatedMeshRenderer::SetAnimation(const std::string& name, bool isLoop)
{
	if (!file)
	{
		return false;
	}
	for (const auto& e : file->animations)
	{
		if (e->name == name)
		{
			return SetAnimation(e, isLoop);
		}
	}

	return false;
}

/**
* アニメーションを設定する
*
* @param index		再生するアニメーション番号
* @param isLoop		ループ再生の指定(true=ループする、false=ループしない)
*
* @retval true	設定成功
* @retval false	設定失敗
*/
bool GltfAnimatedMeshRenderer::SetAnimation(size_t index, bool isLoop)
{
	if (!file || index >= file->animations.size())
	{
		return false;
	}
	return SetAnimation(file->animations[index], isLoop);
}
