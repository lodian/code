#include "Sort.h"
#include "Stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

//交换函数
void Swap(int* left, int* right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

//打印数组
void PrintArray(int *array, int size)
{
	for (int i = 0; i < size ; ++i)
		printf("%d  ", array[i]);
	printf("\n");
}

//插入排序
void InsertSort(int *array, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int key = array[i];
		int end = i - 1;
		while (end >= 0 && key < array[end])
		{
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}

//希尔排序
void ShellSort(int *array, int size)
{
	int gap = size;
	while (gap>1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; ++i)
		{
			int key = array[i];
			int end = i - gap;
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}

//直接选择排序
void SelectSort(int *array, int size)
{
	//选择的趟数
	for (int i = 0; i < size - 1; i++)
	{
		//选择的方式
		int maxPos = 0;
		for (int j = 1; j < size - i; j++)
		{
			if (array[j]>array[maxPos])
				maxPos = j;
		}
		if (maxPos!=size-i-1)
			Swap(&array[maxPos], &array[size - 1 - i]);
	}
}

//选择排序优化
void SelectSortOP(int *array, int size)
{
	int begin = 0;
	int end = size - 1;
	while (begin < end)
	{
		int minPos = begin;
		int maxPos = begin;
		int index = begin + 1;
		//找最大最小元素的位置
		while (index<=end)
		{
			if (array[index] < array[minPos])
				minPos = index;

			if (array[index]>array[maxPos])
				maxPos = index;

			index++;
		}
		if (maxPos != end)
			Swap(&array[maxPos], &array[end]);
			
		if (minPos == end)
			minPos = maxPos;

		if (minPos != begin)
			Swap(&array[minPos], &array[begin]);

		begin++;
		end--;
	}
}

//堆调整算法
void HeapAdjust(int* array, int size, int parent)
{
	int child = ((parent << 1) + 1);
	while (child < size)
	{
		//找左右孩子中较大的孩子
		if (child + 1 < size && array[child + 1] > array[child])
			child += 1;

		//检测双亲是否比较大的孩子大
		if (array[child]>array[parent])
		{
			Swap(&array[child], &array[parent]);
			parent = child;
			child = ((parent << 1) + 1);
		}
		else
			return;
	}
}

//堆排序
void HeapSort(int *array, int size)
{
	//1.建堆
	int root = ((size - 2) >> 1);
	for (; root >= 0; root--)
	{
		HeapAdjust(array, size, root);
	}
	//2.堆排序
	int end = size - 1;
	while (end)
	{
		Swap(&array[0], &array[end]);
		HeapAdjust(array, end, 0);
		end--;
	}
}

//冒泡排序
void BubbleSort(int* array, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = 0;
		for (int j = 1; j < size-i; ++j)
		{
			if (array[j - 1]>array[j])
			{
				flag = 1;
				Swap(&array[j - 1], &array[j]);
			}
		}
		if (!flag)
			return;
	}
}


int GetMiddleIndex(int* array, int left, int right)
{
	int mid = left + ((right - left) >> 1);
	if (array[left] < array[right - 1])
	{
		if (array[mid] < array[left])
			return left;

		else if (array[mid]>array[right - 1])
			return right - 1;

		else
			return mid;
	}
	else
	{
		if (array[mid] > array[left])
			return left;

		else if (array[mid] > array[right - 1])
			return right - 1;

		else
			return mid;
	}
}

//hoare法
int Pation1(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int mid = GetMiddleIndex(array, left, right);
	if (right - 1 != mid)
		Swap(&array[mid], &array[right - 1]);

	int key = array[right - 1];

	while (begin<end)
	{
		//从前往后找比key大的元素
		while (begin<end && array[begin] <= key)
			begin++;

		//从后往前找比key小的元素
		while (begin<end && array[end] >= key)
			end--;

		Swap(&array[begin], &array[end]);
	}
	if (begin<end)
		Swap(&array[begin], &array[end]);

	if (begin!=right-1)
		Swap(&array[begin], &array[right - 1]);

	return begin;
}

//挖坑法
int Pation2(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int mid = GetMiddleIndex(array, left, right);
	if (right - 1 != mid)
		Swap(&array[mid], &array[right - 1]);

	int key = array[right - 1];

	while (begin<end)
	{
		while (begin < end && array[begin] <= key)
			begin++;

		if (begin < end)
		{
			array[end] = array[begin];
			end--;
		}

		while (begin<end && array[end] >= key)
			end--;

		if (begin < end)
		{
			array[begin] = array[end];
			begin++;
		}
	}
	array[begin] = key;
	return begin;
}

//前后指针法
int Pation3(int* array, int left, int right)
{
	int prev = left - 1;
	int cur = left;
	int mid = GetMiddleIndex(array, left, right);
	if ((right - 1) != mid)
		Swap(&array[mid], &array[right - 1]);

	int key = array[right - 1];

	while (cur<right)
	{
		if (array[cur] < key && ++prev != cur)
			Swap(&array[cur], &array[prev]);
		
		++cur;
	}
	if (++prev != right - 1)
		Swap(&array[prev], &array[right - 1]);

	return prev;
}

//快速排序
void QuickSort(int* array, int left,int right)
{
	if (right - left <= 16)
	{
		InsertSort(array + left, right);
	}
	else
	{
		int div = Pation3(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}

//非递归快排
void QuickSortNor(int* array, int size)
{
	Stack s;
	StackInit(&s);
	StackPush(&s, size);
	StackPush(&s, 0);

	while (!StackEmpty(&s))
	{
		int left = StackTop(&s);
		StackPop(&s);

		int right = StackTop(&s);
		StackPop(&s);

		if (right - left > 1)
		{
			int div = Pation2(array, left, right);

			StackPush(&s, right);
			StackPush(&s, div + 1);

			StackPush(&s, div);
			StackPush(&s, left);
		}
	}
	StackDestroy(&s);
}

//归并算法
void MergeData(int* array, int left, int mid,int right ,int* temp)
{
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid ;
	int end2 = right;
	int index = left;
	while (begin1 < end1 && begin2<end2)
	{
		if (array[begin1] <= array[begin2])
		{
			temp[index++] = array[begin1++];
		}
		else
		{
			temp[index++] = array[begin2++];
		}
	}
	while (begin1 < end1)
	{
		temp[index++] = array[begin1++];
	}
	while (begin2<end2)
	{
		temp[index++] = array[begin2++];
	}
}

void _MergeSort(int* array,int left,int right,int* temp)
{
	if (right - left <= 16)
	{
		InsertSort(array + left, right - left);
	}
	else
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(array, left, mid,temp);
		_MergeSort(array, mid, right,temp);
		MergeData(array, left, mid, right, temp);
		memcpy(array + left, temp + left, (right - left)*sizeof(array[0]));
	}
}

//归并排序
void MergeSort(int* array, int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	assert(temp);

	_MergeSort(array, 0, size,temp);
	free(temp);

}

//非递归归并排序
void MergeSortNor( int* array,int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	assert(temp);

	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;

			if (mid>size)
				mid = size;

			if (right>size)
				right = size;

			MergeData(array, left, mid, right, temp);
		}
		memcpy(array, temp, size*sizeof(array[0]));
		gap *= 2;
	}
	free(temp);
}

//非选择排序：计数排序
void CountSort(int* array, int size)
{
	//1.确定元素的范围
	int minValue = array[0];
	int maxValue = array[0];
	for (int i = 0; i < size; ++i)
	{
		if (array[i] < minValue)
			minValue = array[i];

		if (array[i]>maxValue)
			maxValue = array[i];
	}
	int range = maxValue - minValue + 1;
	int* count = (int*)malloc(sizeof(array[0])*range);
	assert(count);
	memset(count, 0, range*sizeof(array[0]));

	//2.统计每个元素出现的次数
	for (int i = 0; i < size; ++i)
	{
		count[array[i] - minValue]++;
	}

	//3.回收
	size_t index = 0;
	for (int i = 0; i < range; ++i)
	{
		int j = 0;
		while (j < count[i])
		{
			array[index++] = i + minValue;
			j++;
		}
	}
	free(count);
}

//测试函数
void TestSort()
{
	int array[] = {2,5,4,9,3,6,8,7,1,0};
	int size = sizeof(array) / sizeof(array[0]);
	printf("array:");
	PrintArray(array, size);

	//printf("InsertSortResult:");
	//InsertSort(array, size);
	//PrintArray(array, size);

	//printf("ShellSortResult:");
	//ShellSort(array, size);
	//PrintArray(array, size);

	//printf("SelectSortResult:");
	//SelectSort(array, size);
	//PrintArray(array, size);

	//printf("SelectSortOPResult:");
	//SelectSortOP(array, size);
	//PrintArray(array, size);

	//printf("HeapSortResult:");
	//HeapSort(array, size);
	//PrintArray(array, size);

	//printf("BubbleSortResult:");
	//BubbleSort(array, size);
	//PrintArray(array, size);

	//printf("QuickSortResult:");
	//QuickSort(array, 0, size);
	//PrintArray(array, size);

	//printf("QuickSortNorResult:");
	//QuickSortNor(array, size);
	//PrintArray(array, size);

	//printf("MergeSortResult:");
	//MergeSort(array, size);
	//PrintArray(array, size);

	//printf("MergeSortNorResult:");
	//MergeSortNor(array, size);
	//PrintArray(array, size);

	printf("CountSortResult:");
	CountSort(array, size);
	PrintArray(array, size);
}