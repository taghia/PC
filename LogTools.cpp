//---------------------------------------------------------------------------
#ifdef FILE_LOG
#include "text.h"
#endif
#include "LogTools.h"
#include <ctime>
#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include "stdio.h"
#elif _Windows
#include <windows.h>
#endif
#ifdef __BORLANDC__
#define nullptr NULL
#endif
// ------------------------------------------------------------------------------
void getLocalTime(char *buffer, int size)
{
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, size, "%H:%M:%S", timeinfo);
}
//---------------------------------------------------------------------------
#ifdef _Windows
//#define vswprintf vswprintf_s
#include <cstdio>
int vasprintf(char **retv, const char *format, va_list args)
{
	int len = vsnprintf(0, 0, format, args);
	if (len == -1)
		return -1;
	char *str = (char*) malloc((size_t) len + 1);
	if (!str)
		return -1;
	len = vsnprintf(str, len + 1, format, args); /* "secure" version of vsprintf */
	if (len == -1)
	{
		free(str);
		return -1;
	}
	*retv = str;
	return len;
}
#endif
//---------------------------------------------------------------------------
void base_print(const char *func, const char *format, va_list args, bool time = true)
{
	char *buffer = nullptr;
	int len = strlen(func) + strlen(format) + 10;
	if(time)
		len += 10;
	char *format_ex = (char*) malloc(len);
	format_ex[0] = 0;
	if(time)
	{
		char time_str[10];
		getLocalTime(time_str, sizeof(time_str));
		strncat(format_ex, time_str, len);
		strncat(format_ex, " ", len);
	}
	strncat(format_ex, func, len);
	if(func && func[0])
		strncat(format_ex, " -> ", len);
	strncat(format_ex, format, len);
	strncat(format_ex, "\n", len);
	len = vasprintf(&buffer, format_ex, args);
	free(format_ex);
	if(len == -1)
		return;
#ifdef __APPLE__
	printf("%s", buffer);
	fflush(stdout);
#else
	(void)(len);
	OutputDebugStringA(buffer);
#endif
	free(buffer);
}
// ------------------------------------------------------------------------------
void println(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	base_print("", format, args);
	va_end(args);
}
// ------------------------------------------------------------------------------
void print_debug(const char *func, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	base_print(func, format, args);
#ifdef FILE_LOG
	text getUserDesktopDirectory();
	text fileName = getUserDesktopDirectory() + "qalambartar.log";
	FILE *file = fopen(fileName.toUtf8(), "a");
	if (file)
	{
		char time_str[10];
		getLocalTime(time_str, sizeof(time_str));
		va_list args;
		va_start(args, format);
		fprintf(file, "%s %s -> ", time_str, func);
		vfprintf(file, format, args);
		fprintf(file, "\n");
		va_end(args);
		fclose(file);
	}
#endif
	va_end(args);
}
// ------------------------------------------------------------------------------
char FlogDir[255];
// ------------------------------------------------------------------------------
void setFlogDir(char *flogDir)
{
	strncpy(FlogDir, flogDir, 254);
}
// ------------------------------------------------------------------------------
void fprint_debug(const char *func, const char *format, ...)
{
	(void)format;
	(void)func;
#if defined(RELEASE_LOG) || defined(FILE_LOG)
	va_list args;
	va_start(args, format);
	base_print(func, format, args);

	char fileName[256];
	strncpy(fileName, FlogDir, 255);
	strncat(fileName, "qalambartar.log", 255);
	FILE *file = fopen(fileName, "a");
	if(file)
	{
		char time_str[10];
		getLocalTime(time_str, sizeof(time_str));
		va_list args;
		va_start(args, format);
		fprintf(file, "%s %s -> ", time_str, func);
		vfprintf(file, format, args);
		fprintf(file, "\n");
		va_end(args);
		fclose(file);
	}

	va_end(args);
#endif
}
// ------------------------------------------------------------------------------
DWORD prev_tick = 0;
void logTick()
{
    DWORD ms = GetTickCount();

    if (prev_tick == 0)
        prev_tick = ms;

    println("tick=%u (elapsed=%u)", ms, ms - prev_tick);

    prev_tick = ms;
}
