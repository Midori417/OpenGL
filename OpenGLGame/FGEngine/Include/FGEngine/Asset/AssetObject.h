/**
* @file AssetObject,h
*/
#ifndef FGENGINE_ASSETOBJECT_H_INCLUDED
#define FGENGINE_ASSETOBJECT_H_INCLUDED
#include "FGEngine/UsingNames/UsingAsset.h"
#include <string>

namespace FGEngine
{
	/**
	* アセットオブジェクトの基底クラス
	*/
	class AssetObject
	{
	protected:

		/**
		* コンストラクタ
		*/
		AssetObject() = default;

		/**
		* コンストラクタ
		* 
		* @param name オブジェクトの名前
		*/
		AssetObject(const std::string& name)
			:name(name)
		{

		}

		/**
		* デストラクタ
		*/
		virtual ~AssetObject() = default;

	public:

		/**
		* シェーダの名前を取得
		*/
		std::string ToString() const
		{
			return name;
		}

	protected:

		// オブジェクトの名前
		std::string name = "Object";
	};
}

#endif // !FGENGINE_ASSETOBJECT_H_INCLUDED
