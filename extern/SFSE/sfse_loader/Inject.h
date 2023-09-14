#pragma once

#include "IdentifyEXE.h"

<<<<<<< HEAD
bool InjectDLL(PROCESS_INFORMATION * info, const char * dllPath, ProcHookInfo * hookInfo);
bool InjectDLLThread(PROCESS_INFORMATION * info, const char * dllPath, bool sync, bool noTimeout);
=======
bool InjectDLL(PROCESS_INFORMATION *info, const char *dllPath,
               ProcHookInfo *hookInfo);
bool InjectDLLThread(PROCESS_INFORMATION *info, const char *dllPath, bool sync,
                     bool noTimeout);
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
