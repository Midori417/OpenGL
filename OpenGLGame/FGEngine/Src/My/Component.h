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
	* コンポーネントの基底クラス
	*/
	class Component : public Object
	{
	public:

		Component() = default;
		virtual ~Component() = default;

	};
}
#endif // !COMPONENT_H_INCLUDED
