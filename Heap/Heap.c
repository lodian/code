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
	int child = parent * 2 + 1;//让child标记左右孩子中较小的孩子，默认左孩子较小
	while (child<size)
	{
		//找左右孩子中最小的孩子
		if (child + 1<size&&Less(array[child + 1],array[child]))
		{
			child += 1;
		}
		//将双亲与最小的孩子比较
		if (Greater(array[parent],array[child]))
		{
			HDataType temp = array[parent];
			array[parent] = array[child];
			array[child] = temp;
			//可能会导致以child为根的树不满足堆的性质，所以再次改变parent和child的位置进行比较
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

void HeapInit(Heap* hp, int* array, int size,PF pCom)//时间复杂度为O(NlogN)，排序建堆时间复杂度为0(N^2)
{
	assert(hp);
	hp->_array = (HDataType*)malloc(sizeof(HDataType)* size);
	if (NULL == hp->_array)
	{
		exit(1);
	}
	//将数组中的元素拷贝堆的空间中
	for (int i = 0; i < size; ++i)
	{
		hp->_array[i] = array[i];
	}
	hp->_capacity = size;
	hp->_size = size;
	

	//调整让其满足堆的性质
	//找倒数第一个非叶节点
	int root = ((size - 2) >> 1);//size-1是最后一个节点，它的双亲节点为(size-1-1)/2
	for (; root >= 0; --root)
	{
		AdjustDown(root, hp->_array, size);
	}
}

void HeapInsert(Heap* hp, HDataType data)
{
	//1.先将元素放入堆中
	//2.可能会破坏堆的性质，向上调整
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
	//默认双亲的左孩子较大
	int child = parent * 2 + 1;
	while (child < size)
	{
		//找左右孩子中较大的孩子
		if (child + 1<size&&array[child + 1] > array[child])
		{
			child += 1;
		}
		//将双亲与最小的孩子比较
		if (array[parent]<array[child])
		{
			HDataType temp = array[parent];
			array[parent] = array[child];
			array[child] = temp;
			//可能会导致以child为根的树不满足堆的性质，所以再次改变parent和child的位置进行比较
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

void HeapSort(int* array, int size)
{
	//1.建堆
	int root = ((size - 2) >> 1);
	for (; root >= 0; root--)
	{
		HeapAdjust(root, array, size);
	}
	//2.堆排序(实际上用的删除操作)
	int end = size - 1;
	while (end)
	{
		//交换堆顶元素和堆中最后一个元素
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