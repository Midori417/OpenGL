/**
* @file AudioListner.cpp
*/
#include "FGEngine/Component/AudioListner.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Audio//EasyAudio.h"

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
