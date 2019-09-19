#include "StdAfx.h"
#include ".\memoryblock.h"

CMemoryBlock::CMemoryBlock(long size/*= MIN_MEMORYBLOCK_SIZE*/)
{
	//size�������ڴ�������ȵĹ�����������ϵ���漰���ڴ��������
	if(size<MIN_MEMORYBLOCK_SIZE)
		size = MIN_MEMORYBLOCK_SIZE;

	m_iBufferSize = size;
	m_pMemoryBlock = new char[size];
}

CMemoryBlock::~CMemoryBlock(void)
{
  delete []m_pMemoryBlock;
  m_pMemoryBlock = NULL;
}
