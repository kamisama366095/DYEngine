#pragma once

#include "DYEngine/Core.h"

#include <fstream>
#include <iostream>
#include <string>

#define LOG Logger::GetInstance()
#define LOG_DIR "Log/"

namespace DYE
{
	class DYE_API Logger
	{
	public:
		enum LogType
		{
			Info,
			Debug,
			Error,
			Warning,

			NumOfType
		};

	private:
		//==========================================
		//	memeber/variable
		//==========================================
		static Logger* s_pInstance;

		std::ofstream m_FileStream;

		bool m_IsLoggedToFile = false;

		//==========================================
		//	method
		//==========================================
		void customPrint(const char* type, const char* file, int line, const char* msg, va_list args);

		//==========================================
		//	ctor, dtor
		//==========================================
		Logger();

	public:
		static Logger* GetInstance();

		void SetOutputFile(std::string filename);

		void Print(LogType type, const char* file, int line, const char* msg, ...);
		void CustomPrint(const char* type, const char* file, int line, const char* msg, ...);

		void ForceFlush();

		//==========================================
		//	flag
		//==========================================

		//==========================================
		//	procedure
		//==========================================

	};

#ifdef DYE_DEBUG

#define LogError( ... )																\
	do																				\
	{																				\
		LOG->Print(Logger::LogType::Error, __FILE__, __LINE__, __VA_ARGS__ );		\
	} while(false)							

#define LogDebug( ... )																\
	do																				\
	{																				\
		LOG->Print(Logger::LogType::Debug, __FILE__, __LINE__, __VA_ARGS__ );		\
	} while(false)							

#define LogInfo( ... )																\
	do																				\
	{																				\
		LOG->Print(Logger::LogType::Info, __FILE__, __LINE__, __VA_ARGS__ );		\
	} while(false)							

#define LogWarning( ... )															\
	do																				\
	{																				\
		LOG->Print(Logger::LogType::Warning, __FILE__, __LINE__, __VA_ARGS__ );		\
	} while(false)							

#define LogGL( ... )																\
	do																				\
	{																				\
		LOG->CustomPrint("OPENGL", __FILE__, __LINE__, __VA_ARGS__ );				\
	} while(false)

#else

#define LogError( ... )		__VA_ARGS__
#define LogDebug( ... )     __VA_ARGS__
#define LogInfo( ... )		__VA_ARGS__
#define LogWarning( ... )   __VA_ARGS__
#define Log( TYPE, ... )    __VA_ARGS__

#endif // DEBUG
}