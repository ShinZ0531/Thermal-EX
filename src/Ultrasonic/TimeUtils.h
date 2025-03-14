#pragma once
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif  // _WIND32
// 64
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else 
typedef long long int64t;
#endif  // _WIN32


class TimeUtils {
public:
	// ms
	static int64_t getCurrentTime();
	// us
	static int64_t getSysTimeMicros();
};
