#pragma once

//打印数组
void PrintArray(int *array, int size);

//插入排序
void InsertSort(int *array, int size);

//希尔排序
void ShellSort(int *array, int size);

//直接选择排序
void SelectSort(int *array, int size);

//堆排序
void HeapSort(int *array, int size);

//冒泡排序
void BubbleSort(int* array, int size);

//快速排序
void QuickSort(int* array, int left,int right);
//非递归快排
void QuickSortNor(int* array, int size);

//归并排序
void MergeSort(int* array, int size);
//非递归归并排序
void MergeSortNor(int* array, int size);

//非选择排序：计数排序
void CountSort(int* array, int size);

void TestSort();