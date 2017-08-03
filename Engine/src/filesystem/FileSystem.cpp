#include "FileSystem.h"

namespace SWI {
	FILE* FileSystem::open(const char* path, const char* mode) {
		FILE* file;
		fopen_s(&file, path, mode);
		return file;
	}
}