//---------------------------------------------------------------------------

#ifndef LogToolsH
#define LogToolsH
//---------------------------------------------------------------------------
#define __HINT__ debug("line %i", __LINE__);
#if defined(_FINAL) && !defined(RELEASE_LOG)
#define debug(...) (void)0
#else
#define debug(...) print_debug(__FUNCTION__, __VA_ARGS__)
#endif
#ifdef LOG_LEVEL2
#define l2(...) print_debug(__FUNCTION__, __VA_ARGS__)
#else
#define l2(...)
#endif
#define output(...) print_debug(__FUNCTION__, __VA_ARGS__)
#define hint(...) print_debug(__FUNCTION__, __VA_ARGS__)
//---------------------------------------------------------------------------
void print(const char* format, ...);
void println(const char* format, ...);
void print_debug(const char* func, const char* format, ...);
void fprint_debug(const char* func, const char* format, ...);
#define flog(...) fprint_debug(__FUNCTION__, __VA_ARGS__);
extern char FlogDir[255];
void setFlogDir(char* flogDir);
void logTick();
//---------------------------------------------------------------------------
#endif
