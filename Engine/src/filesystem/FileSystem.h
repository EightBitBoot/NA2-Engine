#pragma once

#include<iostream>

#include "..\log\Log.h"

namespace SWI {
	namespace FileSystem {
		extern FILE* open(const char* path, const char* mode);
	}
}