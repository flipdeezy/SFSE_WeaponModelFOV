#pragma once

#include "sfse_common/Types.h"
#include <string>

<<<<<<< HEAD
enum
{
	kProcType_Steam,
	kProcType_Normal,
	kProcType_WinStore,
	kProcType_GOG,
	kProcType_Epic,

	kProcType_Packed,

	kProcType_Unknown
};

struct ProcHookInfo
{
	u64	version;
	u32	procType;
};

bool IdentifyEXE(const char * procName, bool isEditor, std::string * dllSuffix, ProcHookInfo * hookInfo);
=======
enum {
  kProcType_Steam,
  kProcType_Normal,
  kProcType_WinStore,
  kProcType_GOG,
  kProcType_Epic,

  kProcType_Packed,

  kProcType_Unknown
};

struct ProcHookInfo {
  u64 version;
  u32 procType;
};

bool IdentifyEXE(const char *procName, bool isEditor, std::string *dllSuffix,
                 ProcHookInfo *hookInfo);
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
