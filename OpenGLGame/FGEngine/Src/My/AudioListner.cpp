/**
* @file AudioListner.cpp
*/
#include "AudioListner.h"
#include "EasyAudio/EasyAudio.h"
#include "Transform.h"

namespace FGEngine
{
	/**
	* ���X�i�[�̈ʒu���X�V
	*/
	void AudioListner::PosUpdate()
	{
		auto trs = GetTransform();
		if (trs)
		{
			EasyAudio::SetListenr(trs->position, trs->Right());
		}
	}
}
