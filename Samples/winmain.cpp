
#ifdef NUTMEG_PLATFORM_WINDOWS

#include <windows.h>

namespace Nutmeg {
	int engineMain(int argc, const char **argv);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	return Nutmeg::engineMain(0, nullptr);
}

#endif
