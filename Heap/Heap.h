#pragma once

typedef int HDataType;

typedef int (*PF)(HDataType left, HDataType right);

typedef struct Heap
{
	HDataType* _array;
	int _capacity;
	int _size;
	PF pCom;
}Heap;

int Greater(HDataType left, HDataType right);
int Less(HDataType left, HDataType right);

void HeapInit(Heap* hp, int* array, int size,PF pCom);
void HeapInsert(Heap* hp, HDataType data);
void HeapErase(Heap* hp);
HDataType HeapTop(Heap* hp);
int Heapsize(Heap* hp);
int HeapEmpty(Heap* hp);
void Heapdestroy(Heap* hp);

void TestHeap();