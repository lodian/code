#include "DList.h"
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

DListNode* BuyDListNode(DLDataType x)
{
	DListNode* pNewNode = (DListNode*)malloc(sizeof(DListNode));
	if (NULL == pNewNode)
	{
		printf("�ռ�����ʧ��!\n");
		exit(1);
	}
	pNewNode->_pNext = NULL;
	pNewNode->_pPre = NULL;
	pNewNode->_data = x;
	return pNewNode;
}

//��ʼ��
void DListInit(DList* plist)
{
	assert(plist);
	plist->_pHead = BuyDListNode(0);
	plist->_pHead->_pNext = plist->_pHead;
	plist->_pHead->_pPre = plist->_pHead;
}

//β��
void DListPushBack(DList* plist, DLDataType x)
{
	DListNode* pNewNode = BuyDListNode(x);
	pNewNode->_pPre = plist->_pHead->_pPre;
	pNewNode->_pNext = plist->_pHead;
	plist->_pHead->_pPre = pNewNode;
	pNewNode->_pPre->_pNext = pNewNode;
}

//βɾ
void DListPopBack(DList* plist)
{
	DListNode* pDel = plist->_pHead->_pPre;
	if (pDel != plist->_pHead)
	{
		pDel->_pPre->_pNext = plist->_pHead;
		plist->_pHead->_pPre = pDel->_pPre;
		free(pDel);
	}
}

//ͷ��
void DListPushFront(DList* plist, DLDataType x)
{
	DListNode* pNewNode = BuyDListNode(x);
	pNewNode->_pNext = plist->_pHead->_pNext;
	pNewNode->_pPre = plist->_pHead;
	plist->_pHead->_pNext = pNewNode;
	pNewNode->_pNext->_pPre = pNewNode;
}

//ͷɾ
void DListPopFront(DList* plist)
{
	assert(plist);
	DListNode* pDel = plist->_pHead->_pNext;
	if (pDel != plist->_pHead)
	{
		plist->_pHead->_pNext = pDel->_pNext;
		pDel->_pNext->_pPre = plist->_pHead;
		free(pDel);
	}
}

//���������е���Ч�ڵ�
void DListDestory(DList* plist)
{
	DListNode* pDel = plist->_pHead->_pNext;
	while (pDel != plist->_pHead)
	{
		plist->_pHead->_pNext = pDel->_pNext;
		free(pDel);
		pDel = plist->_pHead->_pNext;
	}
	free(plist->_pHead);
	plist->_pHead = NULL;
}

//����ֵΪx�Ľڵ�
DListNode* DListFind(DList* plist, DLDataType x)
{
	assert(plist);
	DListNode* pCur = plist->_pHead->_pNext;
	while (pCur != plist->_pHead)
	{
		if (pCur->_data == x)
		{
			return pCur;
		}
		pCur = pCur->_pNext;
	}
	printf("�������޴����ݣ�\n");
	return NULL;
}

//��pos��ǰ����в���
void DListInsert(DListNode* pos, DLDataType x)
{
	if (NULL == pos)
	{
		return;
	}
	DListNode* pNewNode = BuyDListNode(x);
	DListNode* pFront = pos->_pPre;
	pFront->_pNext = pNewNode;
	pNewNode->_pPre = pFront;
	pNewNode->_pNext = pos;
	pos->_pPre = pNewNode;
}

//ɾ��posλ�õĽڵ�
void DListErase(DListNode* pos)
{
	if (NULL == pos)
	{
		return;
	}
	DListNode* pFront = pos->_pPre;
	DListNode* pBack = pos->_pNext;
	pFront->_pNext = pBack;
	pBack->_pPre = pFront;
	free(pos);
}

//ɾ����һ��ֵΪx�Ľڵ�
void DListRemove1(DList* plist, DLDataType x)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		printf("�������޴����ݣ�\n");
		return;
	}
	DListNode* pDel = DListFind(plist, x);
	if (NULL == pDel)//��ΪDListFind���ܷ���NULL�����������жϻᷢ���δ���
	{
		return;
	}
	pDel->_pPre->_pNext = pDel->_pNext;
	pDel->_pNext->_pPre = pDel->_pPre;
	free(pDel);
}

//ɾ����һ��ֵΪx�Ľڵ�
//int DListRemove2(DList* plist, DLDataType x)
//{
//	assert(plist);
//	if (plist->_pHead == plist->_pHead->_pNext)
//	{
//		printf("�������޴����ݣ�\n");
//		return -1;
//	}
//	DListNode* pDel = DListFind(plist, x);
//	if (NULL == pDel)//��ΪDListFind���ܷ���NULL�����������жϻᷢ���δ���
//	{
//		return -1;
//	}
//	pDel->_pPre->_pNext = pDel->_pNext;
//	pDel->_pNext->_pPre = pDel->_pPre;
//	free(pDel);	
//	return 0;
//}

//   1   2   3   3   3   4   3   5   6
//ɾ������ֵΪx�Ľڵ�
//void DListRemoveAll(DList* plist, DLDataType x)
//{
//	assert(plist);
//	if (plist->_pHead == plist->_pHead->_pNext)
//	{
//		printf("�������޴����ݣ�\n");
//		return;
//	}
//	while (DListRemove2(plist, x) == 0)
//	{
//		DListRemove2(plist, x);
//	}
//}

//ɾ������ֵΪx�Ľڵ�
void DListRemoveAll(DList* plist, DLDataType x)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		printf("�������޴����ݣ�\n");
		return;
	}
	DListNode* pCur = plist->_pHead->_pNext;
	while (pCur != plist->_pHead)
	{
		if (pCur->_data == x) 
		{
			DListNode* pDel = pCur;
			pCur = pCur->_pNext;//�Ȱ���һ���ڵ㱣������������free��pDel��֮���Ҳ���pCur
			pDel->_pPre->_pNext = pDel->_pNext;
			pDel->_pNext->_pPre = pDel->_pPre;
			free(pDel);
			continue;
		}
		pCur = pCur->_pNext;
	}
}

//�����������Ч�ڵ�ĸ���������ͷ�ڵ㣩
int DListSize(DList* plist)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		return 1;
	}
	DListNode* pCur = plist->_pHead->_pNext;
	int count = 1;
	while (pCur != plist->_pHead)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}

//�ж������Ƿ�Ϊ�գ�������ͷ�ڵ㣩
int DListEmpty(DList* plist)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		return 0;
	}
	return 1;
}

//��ȡ�����г�ͷ�ڵ���ĵ�һ����Ч�ڵ����ֵ
DLDataType DListFront(DList* plist)
{
	assert(plist);
	return plist->_pHead->_pNext->_data;
}

//��ȡ���������һ����Ч�ڵ����ֵ
DLDataType DListBack(DList* plist)
{
	assert(plist);
	return plist->_pHead->_pPre->_data;
}

//�����������
void DListPrint(DList* plist)
{
	DListNode* pCur = plist->_pHead->_pNext;
	while (pCur != plist->_pHead)
	{
		printf("%d ", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("\n");
}

//�����������
void DListReversePrintf(DList* plist)
{
	DListNode* pCur = plist->_pHead->_pPre;
	while (pCur != plist->_pHead)
	{
		printf("%d ", pCur->_data);
		pCur = pCur->_pPre;
	}
	printf("\n");
}

void TestDList1()
{
	DList dl;
	DListInit(&dl);
	DListPushBack(&dl, 1);
	DListPushBack(&dl, 2);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 4);
	DListPushBack(&dl, 5);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	DListPushFront(&dl, 0);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	DListPopFront(&dl);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	DListDestory(&dl);
}

void TestDList2()
{
	DList dl;
	DListInit(&dl);
	DListPushBack(&dl, 1);
	DListPushBack(&dl, 2);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 4);
	DListPushBack(&dl, 5);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	DListFind(&dl, 3);
	DListFind(&dl, 6);

	DListInsert(DListFind(&dl, 3), 6);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	DListErase(DListFind(&dl, 6));
	DListPrint(&dl);
	DListReversePrintf(&dl);
}

void TestDList3()
{
	DList dl;
	DListInit(&dl);
	DListPushBack(&dl, 1);
	DListPushBack(&dl, 2);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 4);
	DListPushBack(&dl, 3);
	DListPushBack(&dl, 5);
	DListPushBack(&dl, 3);
	DListPrint(&dl);
	DListReversePrintf(&dl);

	/*printf("%d\n",DListFront(&dl));
	printf("%d\n", DListBack(&dl));

	printf("%d\n", DListSize(&dl));
	printf("%d\n", DListEmpty(&dl));*/

	//DListRemove2(&dl, 3);
	//DListRemove(&dl, 8);
	DListRemoveAll(&dl, 3);
	DListPrint(&dl);
	DListReversePrintf(&dl);
}

void TestDList()
{
	//TestDList1();
	//TestDList2();
	TestDList3();
}
