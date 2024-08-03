/**
* @file GltfFile.h
*/
#ifndef FGENGINE_GLTFFILE_H_INCLUDED
#define FGENGINE_GLTFFILE_H_INCLUDED
#include "Package/Glad.h"
#include <string>
#include <memory>
#include <vector>
#include "MatrixPoint.h"

namespace FGEngine
{
	/**
	* glTFスキン
	*/
	struct GltfSkin
	{
		// スキン名
		std::string name;

		/**
		* ジョイント(ボーン)データ
		*/
		struct Joint
		{
			// ジョイント対応するノード番号
			int nodeId = -1;

			// 逆バインドポーズ配列
			Matrix4x4 matInverseBindPose = Matrix4x4(1);
		};
		
		// ジョイント配列
		std::vector<Joint> joints;
	};

	/**
	* glTFノード
	*/
	struct GltfNode
	{
		// ノード名
		std::string name;

		// メッシュ番号
		int mesh = -1;

		// スキン番号
		int skin = -1;

		// 親ノード
		GltfNode* parent = nullptr;

		// 子ノード配列
		std::vector<GltfNode*> children;

		// ローカル行列
		Matrix4x4 matLocal = Matrix4x4(1);

		// グローバル行列
		Matrix4x4 matGlobal = Matrix4x4(1);
	};

	/**
	* glTfシーン
	*/
	struct GltfScene
	{
		// ノード配列
		std::vector<const GltfNode*> nodes;

		// メッシュを持つノードのみの配列
		std::vector<const GltfNode*> meshNodes;
	};

	struct StaticMesh;
	using StaticMeshPtr = std::shared_ptr<StaticMesh>;
	struct AnimationClip;
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace RenderingSystem
	{
		class GltfFileBuffer;
	}
	/**
	* glTfファイル
	*/
	struct GltfFile
	{
		// ファイル名
		std::string name;

		// シーン配列
		std::vector<GltfScene> scenes;

		// ノード配列
		std::vector<GltfNode> nodes;

		// スキン配列
		std::vector<GltfSkin> skins;

		// メッシュ配列
		std::vector<StaticMeshPtr> meshes;

		// マテリアル配列
		std::vector<MaterialPtr> materials;

		// アニメーションクリップ配列
		std::vector<AnimationClipPtr> animationClips;

		// 基本姿勢行列
		Matrix4x4 matRoot = Matrix4x4(1);

		// GltfFileBuffer
		RenderingSystem::GltfFileBuffer* gltfFileBuffer;
	};
	using GltfFilePtr = std::shared_ptr<GltfFile>;

	/**
	* 姿勢行列の配列
	*/
	struct AnimMatrixRange
	{
		GLintptr offset;

		size_t size;
	};


}

#endif // !FGENGINE_GLTFFILE_H_INCLUDED
