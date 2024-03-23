/**
* @file EngineSystemFrd.h
*/
#ifndef ENGINESYSTEMFRD_H_INCLUDED
#define ENGINESYSTEMFRD_H_INCLUDED
#include <memory>

namespace FGEngine
{
	class Engine;
	
	namespace ObjectSystem
	{
		class ObjectManager;
	}
	namespace SceneSystem
	{
		class SceneManager;
		using SceneManagerPtr = std::shared_ptr<SceneManager>;
	}
}

#endif // !ENGINESYSTEMFRD_H_INCLUDED
