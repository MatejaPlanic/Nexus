#pragma once

#include <memory>

#ifdef NX_PLATFORM_WINDOWS
	#ifdef NX_BUILD_DLL
		#define NEXUS_API __declspec(dllexport)
	#else
		#define NEXUS_API __declspec(dllimport)
	#endif
#endif

#define BIT(x) (1 << x)

#define NX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nexus
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}