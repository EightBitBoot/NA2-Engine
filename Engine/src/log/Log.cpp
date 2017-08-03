#include "Log.h"

namespace SWI {

	Logger* Logger::m_instance = nullptr;

	Logger::Logger() {
		m_logFile = FileSystem::open("LOG.txt", "w+");

		if (!m_logFile) {
			log(LogLevelERROR, "Failed to open log file!\n");
		}

	}

	Logger::~Logger() {
		fclose(m_logFile);
	}
	
	//Create and or return the instance of this class
	Logger* Logger::getInstance() {
		if (!m_instance) {
			m_instance = new Logger;
		}
		return m_instance;
	}

	void Logger::log(LogLevel logLevel, const char* message, ...) {
		static char buffer[256];

		va_list args;

		va_start(args, message);
		vsprintf_s(buffer, message, args);
		va_end(args);

		writeLog(logLevel, buffer);
	}

	void Logger::writeLog(LogLevel logLevel, const char* message) {
		char output[1000];

		switch (logLevel) {
		case LogLevelINFO:
			sprintf_s(output, "[INFO] %s\n", message);
			break;

		case LogLevelWARNING:
			sprintf_s(output, "[WARNING] %s\n", message);
			break;

		case LogLevelERROR:
			sprintf_s(output, "[ERROR] %s\n", message);
			break;

		default:
			strcpy_s(output, message);
			break;
		}

		if (m_logFile) {
			fputs(output, m_logFile);
		}
		printf(output);
	}

	void Logger::newLine() {
		if (m_logFile) {
			fputs("\n\n", m_logFile);
		}
		printf("\n\n");
	}
}