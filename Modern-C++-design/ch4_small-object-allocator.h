#ifndef h_ch4_small
#define h_ch4_small

#include "prelude.h"

using namespace std;

// block_size ͳһ���ϲ���� ��ʵ��һ��chunk��˵ ��һ���̶�ֵ�� Ϊ�˽�ʡchunk�ռ䣬�����block_size

//  |---b1---|---b2---|---b3---|---b4---|---b5---|---b6---|---...
//  { size   }  ��char(1 byte)��
struct Chunk
{
	// chunk��鱾��
	void init(size_t block_size, unsigned char blocks_amount)      
	{                                                              // chunk��block������������ char= 255������
		pData = new unsigned char[block_size * blocks_amount];
		firstAvailableBlock = 0;  // ����
		blocksAvailable = blocks_amount;

		// ��ÿ����δʹ������ĵ�һ�� ��� ��һ����δʹ�����������index
		unsigned char i = 1, *p = pData;
		for (; i != blocks_amount; p += block_size) {
			*p = ++i;
		}
	}
	void release();

	// ʹ��һ������
	void* allocate(size_t block_size)     
	{
		if (!blocksAvailable) return nullptr;
		unsigned char* pResult = pData + (firstAvailableBlock * block_size);  // ��λ����һ�����õ�block
		// ����chunk״̬
		firstAvailableBlock = *pResult;
		--blocksAvailable;
		//
		return pResult;
	}
	void de_allocate(void* p, size_t block_size)
	{
		assert(p >= pData);
		unsigned char* to_release = static_cast<unsigned char*>(p);   // to_releaseָ�򼴽����ͷŵ��Ǹ�block
		*to_release = firstAvailableBlock;
		assert((to_release - pData) % block_size == 0);
		*to_release = firstAvailableBlock;
		firstAvailableBlock = static_cast<unsigned char>((to_release - pData) / block_size);
		assert(firstAvailableBlock == (to_release - pData) / block_size);
		++blocksAvailable;
	}

	unsigned char* pData;                   // ָ�򱻹�����ڴ汾��
	unsigned char firstAvailableBlock;      // ��һ������block������
	unsigned char blocksAvailable;
};

class FixedAllocator
{
	
private:
	using Chunks = vector<Chunk>;

	size_t        block_size;
	unsigned char num_blocks;
	Chunks        chunks;

	Chunks* alloc_chunk;
	Chunks* de_alloc_chunk;
};

class SmallObjAllocator
{
	
};

class SmallObj
{
public:
	static void* operator new(size_t size);
	static void operator delete(void* p ,size_t size);
	virtual ~SmallObj() = default;

};

#endif

