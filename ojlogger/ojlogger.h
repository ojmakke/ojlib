#include <stdio.h>

#ifdef WARNLOG
#define LOGW(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOGW(...)
#endif

#ifdef ERRLOG
#define LOGE(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOGE(...)
#endif

#ifdef INFOLOG
#define LOGI(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOGI(...)
#endif

#ifdef DEBUGLOG
#define LOGD(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOGD(...)
#endif

#ifdef TESTLOG
#define LOGT(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOGT(...)
#endif

#ifdef LEVEL1LOG
#define LOG1(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOG1(...)
#endif

#ifdef LEVEL2LOG
#define LOG2(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOG2(...)
#endif

#ifdef LEVEL3LOG
#define LOG3(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOG3(...)
#endif
  
#ifdef LEVEL4LOG
#define LOG4(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOG4(...)
#endif
  
#ifdef LEVEL5LOG
#define LOG5(...) fprintf(stdout, __VA_ARGS__)
#else
#define LOG5(...)
#endif

