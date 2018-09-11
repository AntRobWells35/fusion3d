#include "stdafx.h"
#include "UniformBuffer.h"


UniformBuffer::UniformBuffer(void * buf, int size)
{

	UBuf = new MemBuffer(size, buf, false);
	UBuf->MakeUniformBuffer();


	/*

	*/


	


}

void UniformBuffer::Set(void *buf, int size) {
	UBuf->Set(buf);
}

UniformBuffer::~UniformBuffer()
{
}
