/**
* @file AnimationClip.h
*/
#ifndef FGENGINE_ANIMATIONCLIP_H_INCLUDED
#define FGENGINE_ANIMATIONCLIP_H_INCLUDED
#include "Object.h"
#include "Debug.h"
#include "Mathf.h"

namespace FGEngine
{
	/*
	* �A�j���[�V�����̕ۊǕ��@
	*/
	enum class Interpolation
	{
		// ��ԂȂ�
		Step,

		// ���`���
		Linear,

		// 3���X�v���C�����
		CubicSpline,
	};

	/**
	* �A�j���[�V�����̃L�[�t���[��
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
	* �L�[�t���[���̏W����
	*/
	template<typename T>
	struct AnimationCurve
	{

		/**
		* �L�[�t���[����ǉ�����
		* 
		* @param time ����
		* @parma value �A�j���[�V�����̏��
		* 
		* @retval true �ǉ�����
		* @retval false �ǉ����s(���������̃L�[������)
		*/
		bool AddKey(float time, T& value)
		{
			// �ǉ�����ʒu������
			auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
				[](const KeyFrame& key, float time) {
					return key.time < time;
				});

			// �����̓������L�[�t���[�������݂���ꍇ�͒ǉ��ł��Ȃ�
			if (itr != keyFrames.end() && itr->time == time)
			{
				LOG_WARNINGS("���Ԃ̏d������KeyFrame�͒ǉ��ł��܂���(time=%0.3f)", time);
				return false;
			}

			// �L�[�t���[����ǉ�
			keyFrames.insert(itr, KeyFrame{ time, value });
			return true;	// �ǉ�����
		}

		/**
		* �L�[�t���[����ǉ�����
		* 
		* @param begin	�z��̐�[
		* @param end	�z��̏I�[
		* 
		* @return �ǉ������L�[�̐�
		*/
		int AddKey(const KeyFrame<T>* begin, const KeyFrame<T>* end)
		{
			// �v�f����\��
			keyFrames.reserve(end - begin);

			int count = 0;	// �ǉ������v�f��
			for (auto itr = begin; itr != end; ++itr)
			{
				count += AddKey(itr->time, itr->value);
			}
			return count;
		}

		/**
		* ����̎����̃A�j���[�V������Ԃ��擾
		* 
		* @pamm time ����
		* 
		* @return time�ɑΉ�����A�j���[�V�������
		*/
		T Evaluate(float time) const
		{
			if (keyFrames.empty())
			{
				return T{};
			}
			else if (keyFrames.size() == 1)
			{
				return keyFrames.begin()->value;	// �L�[�t���[�����ЂƂ̏ꍇ
			}

			// �����ɑΉ�����L�[�t���[�������Y��
			auto itr = std::lower_bound(keyFrames.begin(), keyFrames.end(), time,
				[](const KeyFrame& key, float time) {
					return key.time, time;
				});

			// �擪�����������ꍇ�͐擪���[�ӂ�ނ̒l��Ԃ�
			if (itr == keyFrames.begin())
			{
				return itr->value;
			}

			// ������Ȃ������ꍇ�͖����̃L�[�t���[���̒l��Ԃ�
			if (itr == keyFrames.end())
			{
				return keyFrames.back().value;
			}

			// �������L�[�t���[���ƂЂƂO�̃L�[�t���[�����`�ۊǂ���
			auto prev = itr - 1;	// �ЂƂO�̃L�[�t���[��
			const float ratio = (time - prev->time) / (itr->time - prev->time);
			return prev->value * (1 - ratio) + itr->value * ratio;
		}

		/**
		* �A�j���[�V�����̒������擾����
		* 
		* @return �A�j���[�V�����̒���(�b)
		*/
		float Length() const
		{
			if (keyFrames.empty())
			{
				return 0;
			}
			return keyFrames.time;
		}

	public:

		// �l��K�p����ID
		int targetNodeId = 0;

		// �l�̕�ԕ��@
		Interpolation interpolation = Interpolation::Step;

		// �L�[�t���[���z��
		std::vector<KeyFrame<T>> keyFrames;
	};
	template<typename T>
	using AnimationCurvePtr = std::shared_ptr<AnimationCurve<T>>;

	/**
	* �A�j���[�V�����̑ΏۂƂȂ�f�[�^
	*/
	enum class AnimationTarget
	{
		// �ʒu
		position,

		// ��]
		rotation,

		// �g�嗦
		scale,
	};

	/**
	* �A�j���[�V�����N���b�v
	*/
	class AnimationClip : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		AnimationClip() = default;
		virtual ~AnimationClip() = default;

		/**
		* �A�j���[�V�����J�[�u��ǉ�
		* 
		* @parma targetNodeId	�A�j���[�V������K�p����m�[�h�ԍ�
		* @param target			�A�j���[�V�����̑ΏۂƂȂ�f�[�^
		* @parma curve			�ǉ�����A�j���[�V�����J�[�u
		* 
		* @retval true	�ǉ��ɐ���
		* @retval false	�ǉ��Ɏ��s
		*/
		template<typename T>
		bool AddCurve(int targetNodeId, AnimationTarget target, const AnimationCurvePtr<T>& curve)
		{
			switch (target)
			{
			case FGEngine::AnimationTarget::position:		

				if constexpr (std::is_base_of_v<Vector3, T>)
				{
					LOG_ERROR("�^�������Ă��Ȃ�");
					return false;
				}

				return AddCurveHelpe(positions, targetNodeId, target, curve);
				break;
			case FGEngine::AnimationTarget::rotation:

				if constexpr (std::is_base_of_v<Quaternion, T>)
				{
					LOG_ERROR("�^�������Ă��Ȃ�");
					return false;
				}

				return AddCurveHelpe(rotations, targetNodeId, target, curve);

				break;
			case FGEngine::AnimationTarget::scale:

				if constexpr (std::is_base_of_v<Vector3, T>)
				{
					LOG_ERROR("�^�������Ă��Ȃ�");
					return false;
				}

				return AddCurveHelpe(scales, targetNodeId, target, curve);

				break;
			default:
				break;
			}
		}

		/**
		* �A�j���[�V�����𔽉f����
		* 
		* @param gameObject ���f��̃Q�[���I�u�W�F�N�g
		* @parma time		�A�j���[�V������]�����鎞��
		*/
		void Evaluate(GameObject& gameObject, float time);

		/**
		* �A�j���[�V�����̍Đ����Ԃ��擾
		*/
		float Length() const;

	private:

		/**
		* �A�j���[�V�����J�[�u�̐ݒ���
		*/
		template<typename T>
		struct CurveInfo
		{
			// �A�j���[�V�����̑ΏۂƂȂ�f�[�^
			AnimationTarget target;

			// �A�j���[�V�����J�[�u
			AnimationCurvePtr<T> curve;
		};

		/**
		* �A�j���[�V�����J�[�u�ǉ��̕⏕�֐�
		* 
		* @param curveList		�A�j���[�V�����J�[�u�z��
		* @param targetNodeId	�A�j���[�V������K�p����m�[�h�ԍ�
		* @param target			�A�j���[�V�����̑ΏۂƂȂ�f�[�^
		* @param curve			�ǉ�����A�j���[�V�����J�[�u
		*
		* @retval true	�ǉ��ɐ���
		* @retval false	�ǉ��Ɏ��s
		*/
		template<typename T>
		bool AddCurveHelpe(std::vector<CurveInfo<T>>& curveList, int targetNodeId,
			AnimationTarget target, const AnimationCurvePtr<T>& curve)
		{
			// �^�[�Q�b�g�m�[�hID�ƃ^�[�Q�b�g����v����f�[�^������
			auto itr = std::find_if(curveList.begin(), curveList.end(),
				[targetNodeId, target](const CurveInfo<T>& info) {
					info.curve->targetNodeId == targetNodeId && info.target == target;
				});

			// �{�[���ԍ��ƃ^�[�Q�b�g�̗������������J�[�u�����݂���ꍇ�͐ݒ�ł��Ȃ�
			if (itr != curveList.end())
			{
				LOG_WARNINGS("�^�[�Q�b�g���d������J�[�u��ݒ�ł��܂���");
				return false;	// �ǉ����s
			}

			// �V�����J�[�u��ǉ�
			curveList.push_back(CurveInfo<Vector3>{targetNodeId, target, curve});
			length = Mathf::Max(length, curve->Length());
			return true;
		}

	public:

		// ���[�v�Đ��̗L��
		bool isLoop = false;

	private:

		// �ʒu�̃A�j���[�V�����J�[�u
		std::vector<CurveInfo<Vector3>> positions;

		// ��]�̃A�j���[�V�����J�[�u
		std::vector<CurveInfo<Quaternion>> rotations;

		// �g�嗦�̃A�j���[�V�����J�[�u
		std::vector<CurveInfo<Vector3>> scales;

		// �A�j���[�V�������Ȃ��m�[�hID
		std::vector<int> staticNodes;

		// �A�j���[�V�����̍Đ�����
		float totalTime = 0;

		// �A�j���[�V�����̒���
		float length = 0;
	};
	using AnimationClipPtr = std::shared_ptr<AnimationClip>;
}

#endif // !FGENGINE_ANIMATION_H_INCLUDED
