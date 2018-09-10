#include "stdafx.h"
#include "UniformBuffer.h"


UniformBuffer::UniformBuffer(void * buf, int size)
{

	UBuf = new MemBuffer(size, buf, false);
	UBuf->MakeUniformBuffer();


	/*

	*/


	


}


UniformBuffer::~UniformBuffer()
{
}
