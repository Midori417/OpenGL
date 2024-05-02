/**
* @file AnimationClip.h
*/
#ifndef FGENGINE_ANIMATIONCLIP_H_INCLUDED
#define FGENGINE_ANIMATIONCLIP_H_INCLUDED
#include <string>
#include <vector>
#include <memory>
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Quaternion.h"

namespace FGEngine
{
	/**
* �A�j���[�V�����̒l�̕ۊǕ��@
*/
	enum class GltfIterpolation
	{
		// ��ԂȂ�
		None,

		// ���`���
		Linear,

		// 3���X�v���C�����
		CubicSphline,
	};

	/**
	* �A�j���[�V�����L�[�t���[��
	*/
	template<typename T>
	struct KeyFrame
	{
		// ����
		float time = 0;

		// �K������l
		T value;
	};

	/**
	* �A�j���[�V�����J�[�u
	*/
	template<typename T>
	struct AnimationCurve
	{
		// �l��K�p����m�[�hId
		int targetNodeid = -1;

		// ��ԕ��@
		GltfIterpolation interpolation = GltfIterpolation::None;

		// �L�[�t���[���z��
		std::vector<KeyFrame<T>> keyFrames;
	};

	/**
	* �A�j���[�V�����N���b�v
	*/
	struct AnimationClip
	{
		// �A�j���[�V�����N���b�v��
		std::string name;

		// �p�B�ړ��`���l���z��
		std::vector<AnimationCurve<Vector3>> translations;

		// ��]�`���l���z��
		std::vector<AnimationCurve<Quaternion>> rotations;

		// �g�嗦�`���l���̔z��
		std::vector<AnimationCurve<Vector3>> scales;

		// �A�j���[�V�������Ȃ��m�[�hID�̔z��
		std::vector<int> staticNodes;

		// �A�j���[�V��������
		float totalTime = 0;
	};
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;

}
#endif // !FGENGINE_ANIMATIONCLIP_H_INCLUDED
