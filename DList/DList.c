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
		printf("空间申请失败!\n");
		exit(1);
	}
	pNewNode->_pNext = NULL;
	pNewNode->_pPre = NULL;
	pNewNode->_data = x;
	return pNewNode;
}

//初始化
void DListInit(DList* plist)
{
	assert(plist);
	plist->_pHead = BuyDListNode(0);
	plist->_pHead->_pNext = plist->_pHead;
	plist->_pHead->_pPre = plist->_pHead;
}

//尾插
void DListPushBack(DList* plist, DLDataType x)
{
	DListNode* pNewNode = BuyDListNode(x);
	pNewNode->_pPre = plist->_pHead->_pPre;
	pNewNode->_pNext = plist->_pHead;
	plist->_pHead->_pPre = pNewNode;
	pNewNode->_pPre->_pNext = pNewNode;
}

//尾删
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

//头插
void DListPushFront(DList* plist, DLDataType x)
{
	DListNode* pNewNode = BuyDListNode(x);
	pNewNode->_pNext = plist->_pHead->_pNext;
	pNewNode->_pPre = plist->_pHead;
	plist->_pHead->_pNext = pNewNode;
	pNewNode->_pNext->_pPre = pNewNode;
}

//头删
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

//销毁链表中的有效节点
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

//查找值为x的节点
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
	printf("链表中无此数据！\n");
	return NULL;
}

//在pos的前面进行插入
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

//删除pos位置的节点
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

//删除第一个值为x的节点
void DListRemove1(DList* plist, DLDataType x)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		printf("链表中无此数据！\n");
		return;
	}
	DListNode* pDel = DListFind(plist, x);
	if (NULL == pDel)//因为DListFind可能返回NULL，若不做此判断会发生段错误！
	{
		return;
	}
	pDel->_pPre->_pNext = pDel->_pNext;
	pDel->_pNext->_pPre = pDel->_pPre;
	free(pDel);
}

//删除第一个值为x的节点
//int DListRemove2(DList* plist, DLDataType x)
//{
//	assert(plist);
//	if (plist->_pHead == plist->_pHead->_pNext)
//	{
//		printf("链表中无此数据！\n");
//		return -1;
//	}
//	DListNode* pDel = DListFind(plist, x);
//	if (NULL == pDel)//因为DListFind可能返回NULL，若不做此判断会发生段错误！
//	{
//		return -1;
//	}
//	pDel->_pPre->_pNext = pDel->_pNext;
//	pDel->_pNext->_pPre = pDel->_pPre;
//	free(pDel);	
//	return 0;
//}

//   1   2   3   3   3   4   3   5   6
//删除所有值为x的节点
//void DListRemoveAll(DList* plist, DLDataType x)
//{
//	assert(plist);
//	if (plist->_pHead == plist->_pHead->_pNext)
//	{
//		printf("链表中无此数据！\n");
//		return;
//	}
//	while (DListRemove2(plist, x) == 0)
//	{
//		DListRemove2(plist, x);
//	}
//}

//删除所有值为x的节点
void DListRemoveAll(DList* plist, DLDataType x)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		printf("链表中无此数据！\n");
		return;
	}
	DListNode* pCur = plist->_pHead->_pNext;
	while (pCur != plist->_pHead)
	{
		if (pCur->_data == x) 
		{
			DListNode* pDel = pCur;
			pCur = pCur->_pNext;//先把下一个节点保存起来，避免free（pDel）之后找不到pCur
			pDel->_pPre->_pNext = pDel->_pNext;
			pDel->_pNext->_pPre = pDel->_pPre;
			free(pDel);
			continue;
		}
		pCur = pCur->_pNext;
	}
}

//输出链表中有效节点的个数（包括头节点）
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

//判断链表是否为空（不包括头节点）
int DListEmpty(DList* plist)
{
	assert(plist);
	if (plist->_pHead == plist->_pHead->_pNext)
	{
		return 0;
	}
	return 1;
}

//获取链表中除头节点外的第一个有效节点的数值
DLDataType DListFront(DList* plist)
{
	assert(plist);
	return plist->_pHead->_pNext->_data;
}

//获取链表中最后一个有效节点的数值
DLDataType DListBack(DList* plist)
{
	assert(plist);
	return plist->_pHead->_pPre->_data;
}

//正向遍历链表
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

//反向遍历链表
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
