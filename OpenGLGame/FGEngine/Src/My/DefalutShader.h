/**
* @file DefalutShader.h
*/
#ifndef FGENGINE_DEFALUTSHADER_H_INCLUDED
#define FGENGINE_DEFALUTSHADER_H_INCLUDED

namespace FGEngine
{
	/**
	* ��b�V�F�[�_���X�g
	*/
	enum class DefalutShader
	{
		// �ʏ�V�F�[�_
		Standard3D,

		// �X�P���^�����b�V���V�F�[�_
		Skeletal3D,

		// �ʏ�V���h�E�V�F�[�_
		Shadow3D,

		// �X�P���^���V���h�E�V�F�[�_
		ShadowSkeletal3D,

		// �����Ȃ��V�F�[�_
		Unlit,
	};
}

#endif // !FGENGINE_DEFALUTSHADERLIST_H_INCLUDED
