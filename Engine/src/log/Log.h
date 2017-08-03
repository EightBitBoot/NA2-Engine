#pragma once

#include <iostream>
#include <ctime>
#include <cstring>

#include <stdarg.h>

#include "../filesystem/FileSystem.h"

namespace SWI {
	class Logger {
	public:
		
		enum LogLevel {
			LogLevelINFO = 0, LogLevelWARNING, LogLevelERROR
		};

		static Logger* getInstance();

		static void close() {
			delete m_instance;
		}

		void log(LogLevel logLevel, const char* format, ...);
		void newLine();

	private:
		Logger();
		~Logger();
		
		void writeLog(LogLevel logLevel, const char* message);
		
		static Logger* m_instance;
		
		FILE* m_logFile;
	};
}
