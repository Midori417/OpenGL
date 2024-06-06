/**
* @file AudioListner.h
*/
#ifndef FGENGINE_AUDIOLISTNER_H_INCLUDED
#define FGENGINE_AUDIOLISTNER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �I�[�f�B�I���X�i�[
	*/
	class AudioListner : public Component
	{
	public:

		AudioListner() = default;
		virtual ~AudioListner() = default;

		/**
		* �X�V����
		*/
		void PosUpdate();
	};
	using AudioListnerPtr = std::shared_ptr<AudioListner>;
}

#endif // !FGENGINE_AUDIOLISTNER_H_INCLUDED
