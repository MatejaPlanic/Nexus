#pragma once

#ifdef NX_PLATFORM_WINDOWS
	#ifdef NX_BUILD_DLL
		#define NEXUS_API __declspec(dllexport)
	#else
		#define NEXUS_API __declspec(dllimport)
	#endif
#endif
