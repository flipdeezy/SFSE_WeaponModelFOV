#include "Errors.h"
#include "Log.h"
#include "Types.h"
#include <cstdlib>
#include <intrin.h>

<<<<<<< HEAD
[[noreturn]] static void IErrors_Halt(void)
{
	__ud2();
}

/**
 *	Report a failed assertion and exit the program
 *	
=======
[[noreturn]] static void IErrors_Halt(void) { __ud2(); }

/**
 *	Report a failed assertion and exit the program
 *
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 */
<<<<<<< HEAD
[[noreturn]] void _AssertionFailed(const char * file, unsigned long line, const char * desc)
{
	_FATALERROR("Assertion failed in %s (%d): %s", file, line, desc);

	IErrors_Halt();
=======
[[noreturn]] void _AssertionFailed(const char *file, unsigned long line,
                                   const char *desc) {
  _FATALERROR("Assertion failed in %s (%d): %s", file, line, desc);

  IErrors_Halt();
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
}

/**
 *	Report a failed assertion and exit the program
<<<<<<< HEAD
 *	
=======
 *
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 *	@param code the error code
 */
<<<<<<< HEAD
[[noreturn]] void _AssertionFailed_ErrCode(const char * file, unsigned long line, const char * desc, unsigned long long code)
{
	if(code & 0xFFFFFFFF00000000)
		_FATALERROR("Assertion failed in %s (%d): %s (code = %16I64X (%I64d))", file, line, desc, code, code);
	else
	{
		u32	code32 = code;
		_FATALERROR("Assertion failed in %s (%d): %s (code = %08X (%d))", file, line, desc, code32, code32);
	}
	
	IErrors_Halt();
=======
[[noreturn]] void _AssertionFailed_ErrCode(const char *file, unsigned long line,
                                           const char *desc,
                                           unsigned long long code) {
  if (code & 0xFFFFFFFF00000000)
    _FATALERROR("Assertion failed in %s (%d): %s (code = %16I64X (%I64d))",
                file, line, desc, code, code);
  else {
    u32 code32 = code;
    _FATALERROR("Assertion failed in %s (%d): %s (code = %08X (%d))", file,
                line, desc, code32, code32);
  }

  IErrors_Halt();
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
}

/**
 *	Report a failed assertion and exit the program
<<<<<<< HEAD
 *	
=======
 *
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
 *	@param file the file where the error occured
 *	@param line the line number where the error occured
 *	@param desc an error message
 *	@param code the error code
 */
<<<<<<< HEAD
[[noreturn]]void _AssertionFailed_ErrCode(const char * file, unsigned long line, const char * desc, const char * code)
{
	_FATALERROR("Assertion failed in %s (%d): %s (code = %s)", file, line, desc, code);

	IErrors_Halt();
=======
[[noreturn]] void _AssertionFailed_ErrCode(const char *file, unsigned long line,
                                           const char *desc, const char *code) {
  _FATALERROR("Assertion failed in %s (%d): %s (code = %s)", file, line, desc,
              code);

  IErrors_Halt();
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
}
