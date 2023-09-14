#include "LoaderError.h"
<<<<<<< HEAD
#include <cstdarg>
#include <cstdio>
#include <Windows.h>

void PrintLoaderError(const char * fmt, ...)
{
	char	buf[4096];

	va_list	args;

	va_start(args, fmt);
//	gLog.Log(IDebugLog::kLevel_FatalError, fmt, args);
	va_end(args);

	va_start(args, fmt);
	vsprintf_s(buf, sizeof(buf), fmt, args);
	va_end(args);

	MessageBox(NULL, buf, "SFSE Loader", MB_OK | MB_ICONEXCLAMATION);
=======
#include <Windows.h>
#include <cstdarg>
#include <cstdio>

void PrintLoaderError(const char *fmt, ...) {
  char buf[4096];

  va_list args;

  va_start(args, fmt);
  //	gLog.Log(IDebugLog::kLevel_FatalError, fmt, args);
  va_end(args);

  va_start(args, fmt);
  vsprintf_s(buf, sizeof(buf), fmt, args);
  va_end(args);

  MessageBox(NULL, buf, "SFSE Loader", MB_OK | MB_ICONEXCLAMATION);
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
}
