#include "TimeUtils.h"
#include <iostream>

int64_t TimeUtils::getCurrentTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);    // sys/time.h
	return tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
}

// system local time
int64_t TimeUtils::getSysTimeMicros() {
#ifdef _WIN32
#define EPOCHFILETIME (116444736000000000UL)
	FILETIME ft;
	LARGE_INTEGER li;
	int64_t tt = 0;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	tt = (li.QuadPart - EPOCHFILETIME) /10;
	return tt;
#else
	timeval tv;
	gettimeofday(&tv, 0);
	return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
	return 0;
}
