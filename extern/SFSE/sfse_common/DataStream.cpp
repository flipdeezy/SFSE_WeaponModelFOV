#include "DataStream.h"

<<<<<<< HEAD
void copy(DataStream * src, DataStream * dst, size_t len, void * buf, size_t bufLen)
{
	bool localBuf = false;

	if (!buf)
	{
		localBuf = true;
		bufLen = 1024 * 1024 * 1;	// 1MB
		buf = new u8[bufLen];
	}

	while (len > 0)
	{
		size_t copyLen = len;
		if (copyLen > bufLen)
			copyLen = bufLen;

		src->read(buf, copyLen);
		dst->write(buf, copyLen);

		len -= copyLen;
	}

	if (localBuf)
		delete [] buf;
=======
void copy(DataStream *src, DataStream *dst, size_t len, void *buf,
          size_t bufLen) {
  bool localBuf = false;

  if (!buf) {
    localBuf = true;
    bufLen = 1024 * 1024 * 1; // 1MB
    buf = new u8[bufLen];
  }

  while (len > 0) {
    size_t copyLen = len;
    if (copyLen > bufLen)
      copyLen = bufLen;

    src->read(buf, copyLen);
    dst->write(buf, copyLen);

    len -= copyLen;
  }

  if (localBuf)
    delete[] buf;
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
}
