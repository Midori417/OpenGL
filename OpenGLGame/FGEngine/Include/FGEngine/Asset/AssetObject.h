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
	* �A�Z�b�g�I�u�W�F�N�g�̊��N���X
	*/
	class AssetObject
	{
	protected:

		/**
		* �R���X�g���N�^
		*/
		AssetObject() = default;

		/**
		* �R���X�g���N�^
		* 
		* @param name �I�u�W�F�N�g�̖��O
		*/
		AssetObject(const std::string& name)
			:name(name)
		{

		}

		/**
		* �f�X�g���N�^
		*/
		virtual ~AssetObject() = default;

	public:

		/**
		* �V�F�[�_�̖��O���擾
		*/
		std::string ToString() const
		{
			return name;
		}

	protected:

		// �I�u�W�F�N�g�̖��O
		std::string name = "Object";
	};
}

#endif // !FGENGINE_ASSETOBJECT_H_INCLUDED
