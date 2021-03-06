#pragma once

#include "DYEngine/Core.h"

#include "DYEngine/GameCore.h"
#include "DYEngine/Time.h"

#include <iostream>

struct GLFWwindow;

namespace DYE
{
	class Core;

	//====================================================================================
	//	IApp: user interface for game engine
	//====================================================================================
	class DYE_API IApplication
	{
	public:
		//==========================================
		//	memeber/variable
		//==========================================
	protected:
		GameCore* m_pCore;
		GLFWwindow* m_pWindow;
		std::string m_WindowName = "DYE";

		//==========================================
		//	flag
		//==========================================
	protected:
		bool m_IsRunning;
		//==========================================
		//	procedure
		//==========================================
	public:
		virtual void Run();								// init -> gameLoop(createScene -> Core->Init) -> release

	private:
		void init();
		void gameLoop();					// main game loop
		void release();

	protected:
		virtual void initGL();
		virtual void releaseGL();
		virtual bool checkIfWindowClosed();
		virtual void render();

		virtual void setupScenes() = 0;		// setup scene, need to implement
		
		//==========================================
		//	event
		//==========================================
	protected:
		virtual void onNextSceneLoaded();
		virtual void onRelease();

		//==========================================
		//	method
		//==========================================
	private:
#ifdef DYE_DEBUG
		void debugGLSetup();
		int shaderProgram;
		unsigned int VBO, VAO, EBO;
		float move_timer = 0.0f;
		float move_max = 1.0f;
#endif // DEBUG
		//==========================================
		//	getter
		//==========================================
	public:
		//==========================================
		//	setter
		//==========================================
		void SetWindowName(std::string _name);
		//==========================================
		//	constructor/destructor
		//==========================================
	public:
		IApplication();
		virtual ~IApplication();
	};
}