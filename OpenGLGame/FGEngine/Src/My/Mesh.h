/**
* @file Mesh.h
*/
#ifndef FGENGINE_MESH_H_INCLUDED
#define FGENGINE_MESH_H_INCLUDED
#include "Object.h"
#include "Material.h"

namespace FGEngine
{
	namespace Rendering
	{
		// 先行宣言
		struct DrawParams;
	}

	/**
	* スタティックメッシュ
	*/
	class StaticMesh : public Object
	{
	public:

		// コンストラクタ・デストラクタ
		StaticMesh() = default;
		virtual ~StaticMesh() = default;

	public:

		MaterialList materials;		// マテリアル配列
		std::vector<Rendering::DrawParams> drawParamsList;	// 描画パラメータ
	};
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;

	/**
	* スケルタルメッシュ
	*/
	class SkeletalMesh : public StaticMesh
	{
	public:

		// コンストラクタ・デストラクタ
		SkeletalMesh() = default;
		virtual ~SkeletalMesh() = default;

	public:
		
		/**
		* 関節データ
		*/
		struct Joint
		{
			// バインドポーズ行列
			Matrix4x4 bindPose = Matrix4x4(1);	

			// 逆バインドポーズ行列
			Matrix4x4 incerseBindPose = Matrix4x4(1);

			// 親関節の番号
			int32_t parent = -1;
		};
		std::vector<Joint> joints;
	};
	using SkeletalMeshPtr = std::shared_ptr<SkeletalMesh>;
}

#endif // !FGENGINE_MESH_H_INCLUDED
