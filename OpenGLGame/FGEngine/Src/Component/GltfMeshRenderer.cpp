/**
* @file GltfMeshRenderer.cpp
*/
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Asset/GltfFile.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Asset/StaticMesh.h"
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"

namespace FGEngine
{
	/**
	* 描画の前処理
	*/
	void GltfMeshRenderer::PreDraw()
	{
		if (!glTFfile)
		{
			return;
		}
		auto animator = GetComponent<Animator>();
		if (!animator)
		{
			return;
		}

		// シーンに含まれるメッシュのアニメーション行列を更新
		// シーンに含まれるメッシュのアニメーション行列を更新
		const auto scene = &glTFfile->scenes[0];
		const Matrix4x4 matModel = GetTransform()->GetLocalTransformMatrix();
		ssboRanges.clear();
		for (const auto e : scene->meshNodes)
		{
			// アニメーション行列を計算
			auto matBones = CalcAnimationMatrices(glTFfile, e, animator->GetAnimationClip().get(), animator->time);
			for (auto& m : matBones)
			{
				m = matModel * m; // アニメーション行列にモデル行列を合成
			}
			// アニメーション行列をバッファに追加し、追加先のオフセットとサイズを記録
			ssboRanges.push_back(glTFfile->gltfFileBuffer->AddAnimationMatrices(matBones));
		}
	}

	/**
	* メッシュを描画
	*/
	void GltfMeshRenderer::Draw(DrawType drawType) const
	{
		if (!glTFfile)
		{
			return;
		}

		// 関節の有無
		if (ssboRanges.empty())
		{
			// インデックスにメッシュは存在しない
			if (meshIndex >= static_cast<int>(glTFfile->meshes.size()))
			{
				return;
			}

			// 座標変換行列を計算
			const Matrix4x4 matModel = GetTransform()->GetWorldTransformMatrix() * glTFfile->matRoot;

			// マテリアルが設定されたいない場合、今日はを使って描画する
			const auto* pMaterials = &materials;
			if (materials.empty())
			{
				pMaterials = &glTFfile->materials;
			}

			auto transform = GetTransform();
			switch (drawType)
			{
			case FGEngine::DrawType::normal:

				// シェーダが未設定
				if (!shader)
				{
					return;
				}

				// 変換座標変換行列をGPUにコピー
				shader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());
				shader->SetMatrix3x3("normalMatrix", transform->GetNormalMatrix());

				// インデックスが負の場合は全メッシュを描画,0以上は指定されたメッシュだけ描画
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						FGEngine::Draw(shader, *x, *pMaterials);
					}
				}
				else
				{
					FGEngine::Draw(shader, *glTFfile->meshes[meshIndex], *pMaterials);
				}

				break;
			case FGEngine::DrawType::shadow:

				// シェーダが未設定
				if (!shadowShader)
				{
					return;
				}

				// 変換座標変換行列をGPUにコピー
				shadowShader->SetMatrix4x4("transformMatrix", transform->GetWorldTransformMatrix());

				// インデックスが負の場合は全メッシュを描画,0以上は指定されたメッシュだけ描画
				if (meshIndex < 0)
				{
					for (const auto& x : glTFfile->meshes)
					{
						FGEngine::Draw(shadowShader, *x, *pMaterials);
					}
				}
				else
				{
					FGEngine::Draw(shadowShader, *glTFfile->meshes[meshIndex], *pMaterials);
				}

				break;
			}
		}
		else
		{
			// シーンに含まれるメッシュを描画
			const auto scene = &glTFfile->scenes[0];
			for (size_t i = 0; i < scene->meshNodes.size(); ++i)
			{
				const int meshNo = scene->meshNodes[i]->mesh;
				const StaticMeshPtr mesh = glTFfile->meshes[meshNo];

				// SSBOをバインディングポイント0番に割り当てる
				glTFfile->gltfFileBuffer->BindAnimationBuffer(0, ssboRanges[i]);


				// マテリアルが指定されていない場合、共有マテリアルを使って描画する
				const auto* pMaterials = &materials;
				if (materials.empty())
				{
					pMaterials = &glTFfile->materials;
				}

				switch (drawType)
				{
				case FGEngine::DrawType::normal:

					if (shader)
					{
						// メッシュに含まれるすべてのプリミティブを描画
						FGEngine::Draw(shader, *mesh, *pMaterials);
					}

					break;
				case FGEngine::DrawType::shadow:

					if (shadowShader)
					{
						// メッシュに含まれるすべてのプリミティブを描画
						FGEngine::Draw(shadowShader, *mesh, *pMaterials);
					}

					break;
				}
			}
		}
	}

	/**
	* Gltfメッシュ
	*/
	ComponentPtr GltfMeshRenderer::Clone() const
	{
		GltfMeshRendererPtr p = std::make_shared<GltfMeshRenderer>();

		// 基底クラスの変数をコピー
		p->enabled = this->enabled;
		p->renderQueue = this->renderQueue;
		p->shader = this->shader;
		p->shadowShader = this->shadowShader;

		p->glTFfile = this->glTFfile;
		p->materials = this->materials;
		p->meshIndex = this->meshIndex;
		p->glTFfile = this->glTFfile;

		return p;
	}
}