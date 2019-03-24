#include "Heap.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int Greater(HDataType left, HDataType right)
{
	return left > right;
}

int Less(HDataType left, HDataType right)
{
	return left < right;
}

void AdjustDown(int root, HDataType* array, int size)
{
	int parent = root;
	int child = parent * 2 + 1;//��child������Һ����н�С�ĺ��ӣ�Ĭ�����ӽ�С
	while (child<size)
	{
		//�����Һ�������С�ĺ���
		if (child + 1<size&&Less(array[child + 1],array[child]))
		{
			child += 1;
		}
		//��˫������С�ĺ��ӱȽ�
		if (Greater(array[parent],array[child]))
		{
			HDataType temp = array[parent];
			array[parent] = array[child];
			array[child] = temp;
			//���ܻᵼ����childΪ������������ѵ����ʣ������ٴθı�parent��child��λ�ý��бȽ�
			parent = child;
			child = parent * 2 + 1; 
		}
		else
			return;
	}
}

void AdjustUp(int child, HDataType* array, int size)
{
	int parent = (child - 1) >> 1;

	while (child)
	{
		if (array[child] < array[parent])
		{
			HDataType temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;

			child = parent;
			parent = (child - 1) >> 1;
		}
		else
			return;
	}
}

void _CheckCapacity(Heap* hp)
{
	assert(hp);
	if (hp->_size == hp->_capacity)
	{
		hp->_array = realloc(hp->_array, hp->_capacity * 2 * sizeof(HDataType));
		assert(hp->_array);
		hp->_capacity *= 2;
	}
}

void HeapInit(Heap* hp, int* array, int size,PF pCom)//ʱ�临�Ӷ�ΪO(NlogN)�����򽨶�ʱ�临�Ӷ�Ϊ0(N^2)
{
	assert(hp);
	hp->_array = (HDataType*)malloc(sizeof(HDataType)* size);
	if (NULL == hp->_array)
	{
		exit(1);
	}
	//�������е�Ԫ�ؿ����ѵĿռ���
	for (int i = 0; i < size; ++i)
	{
		hp->_array[i] = array[i];
	}
	hp->_capacity = size;
	hp->_size = size;
	

	//������������ѵ�����
	//�ҵ�����һ����Ҷ�ڵ�
	int root = ((size - 2) >> 1);//size-1�����һ���ڵ㣬����˫�׽ڵ�Ϊ(size-1-1)/2
	for (; root >= 0; --root)
	{
		AdjustDown(root, hp->_array, size);
	}
}

void HeapInsert(Heap* hp, HDataType data)
{
	//1.�Ƚ�Ԫ�ط������
	//2.���ܻ��ƻ��ѵ����ʣ����ϵ���
	_CheckCapacity(hp);
	hp->_array[hp->_size++] = data;
	AdjustUp(hp->_size - 1, hp->_array, hp->_size);
}

void HeapErase(Heap* hp)
{
	HDataType temp;
	if (HeapEmpty(hp))
		return;
	temp = hp->_array[0];
	hp->_array[0] = hp->_array[hp->_size - 1];
	hp->_array[hp->_size - 1] = temp;
	hp->_size -= 1;

	AdjustDown(0, hp->_array, hp->_size);
}


HDataType HeapTop(Heap* hp)
{
	assert(hp);
	return hp->_array[0];
}

int Heapsize(Heap* hp)
{
	assert(hp);
	return hp->_size;
}

int HeapEmpty(Heap* hp)
{
	assert(hp);
	return 0 == hp->_size;
}

void HeapAdjust(int parent, int* array, int size)
{
	//Ĭ��˫�׵����ӽϴ�
	int child = parent * 2 + 1;
	while (child < size)
	{
		//�����Һ����нϴ�ĺ���
		if (child + 1<size&&array[child + 1] > array[child])
		{
			child += 1;
		}
		//��˫������С�ĺ��ӱȽ�
		if (array[parent]<array[child])
		{
			HDataType temp = array[parent];
			array[parent] = array[child];
			array[child] = temp;
			//���ܻᵼ����childΪ������������ѵ����ʣ������ٴθı�parent��child��λ�ý��бȽ�
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

void HeapSort(int* array, int size)
{
	//1.����
	int root = ((size - 2) >> 1);
	for (; root >= 0; root--)
	{
		HeapAdjust(root, array, size);
	}
	//2.������(ʵ�����õ�ɾ������)
	int end = size - 1;
	while (end)
	{
		//�����Ѷ�Ԫ�غͶ������һ��Ԫ��
		int tmp = array[0];
		array[0] = array[end];
		array[end] = tmp;
		HeapAdjust(0, array, end--);

	}
}

void Heapdestroy(Heap* hp)
{
	assert(hp);
	free(hp->_array);
	hp->_array = NULL;
	hp->_capacity = 0;
	hp->_size = 0;
}

void TestHeap()
{
	int array[] = { 9, 7, 8, 5, 6, 3, 4, 1, 2, 0 };
	Heap hp;
	HeapInit(&hp, array, sizeof(array) / sizeof(array[0]),);
	HeapInsert(&hp, -1);
	HeapErase(&hp);
	HeapSort(array, sizeof(array) / sizeof(array[0]));
	Heapdestroy(&hp);
}