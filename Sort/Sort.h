#pragma once

//��ӡ����
void PrintArray(int *array, int size);

//��������
void InsertSort(int *array, int size);

//ϣ������
void ShellSort(int *array, int size);

//ֱ��ѡ������
void SelectSort(int *array, int size);

//������
void HeapSort(int *array, int size);

//ð������
void BubbleSort(int* array, int size);

//��������
void QuickSort(int* array, int left,int right);
//�ǵݹ����
void QuickSortNor(int* array, int size);

//�鲢����
void MergeSort(int* array, int size);
//�ǵݹ�鲢����
void MergeSortNor(int* array, int size);

//��ѡ�����򣺼�������
void CountSort(int* array, int size);

void TestSort();