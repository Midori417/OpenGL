/**
* @file Component.h
*/
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include "Object.h"
#include <memory>

namespace FGEngine
{
	/**
	* �R���|�[�l���g�̊��N���X
	*/
	class Component : public Object
	{
	public:

		Component() = default;
		virtual ~Component() = default;

	};
}
#endif // !COMPONENT_H_INCLUDED
