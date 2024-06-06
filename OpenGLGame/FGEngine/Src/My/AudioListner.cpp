/**
* @file AudioListner.cpp
*/
#include "AudioListner.h"
#include "EasyAudio/EasyAudio.h"
#include "Transform.h"

namespace FGEngine
{
	/**
	* リスナーの位置を更新
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
