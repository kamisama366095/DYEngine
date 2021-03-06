#pragma once

#include "DYEngine/Core.h"

#include "DYEngine/System.h"

#include <vector>
#include <list>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <algorithm>

namespace DYE
{
	class ISystem;

	//====================================================================================
	//	RendererSystem: keep track of every Renderers, 
	//====================================================================================
	class DYE_API RendererSystem : public ISystem
	{

	public:
		//==========================================
		//	procedure
		//==========================================
		void RegisterRenderer();							// Register renderer to graphics engine

	public:
		//==========================================
		//	constructor/destructor
		//==========================================
		RendererSystem() {}
		~RendererSystem() {}
	};
}