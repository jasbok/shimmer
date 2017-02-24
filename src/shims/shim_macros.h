#ifndef SHIM_MACROS_H
#define SHIM_MACROS_H

#include <dlfcn.h>

#define DLSYM(FUNC) namespace sym {                                         \
                static auto FUNC = [](){                                    \
                    auto dlsym_ptr = dlsym(RTLD_NEXT, #FUNC);                   \
                    if(!dlsym_ptr){                                             \
                        printf("Unable to find function: %s\n", #FUNC);     \
                        abort();                                            \
                    }                                                       \
                    return (FUNC##_Handle)(dlsym_ptr);                          \
                }();                                                        \
            }

#define HANDLE_TYPEDEF(RET, FUNC, ARGS...) typedef RET (*FUNC##_Handle)(ARGS)
#define SHIM(RET, FUNC, ARGS...) HANDLE_TYPEDEF(RET, FUNC, ARGS); DLSYM(FUNC); RET FUNC (ARGS)
#define HANDLE (*__handle)

#ifdef DEBUG
#define SHIM_LOG() static unsigned int _SHIM_LOG_COUNT = 0; if (_SHIM_LOG_COUNT++ < 1) printf("=> Handle: %s\n", __FUNCTION__)
#define SHIM_LOG_ALL() printf("=> Handle: %s\n", __FUNCTION__)
#define DLOG_(LOG...) printf("DLOG => "); printf(LOG); printf("\n")
#define DLOG(LOG...)
#else
#define SHIM_LOG(MAX)
#define DLOG(LOG)
#endif


#endif
