#include "SList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

SListNode* BuySListNode(SLDataType data)
{
	SListNode* pNewNode = (SListNode*)malloc(sizeof(SListNode));
	if (NULL == pNewNode)
	{
		printf("����ռ�ʧ�ܣ�\n");
		exit(1);
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;
	return pNewNode;
}

void SListInit(SListNode** pHead)
{
	*pHead = NULL;
}

//pHead pList����ʱ����
//�����Ƿ���ڣ�������NULL��û�д�pList
//�����������Ѿ����ڣ�������û�нڵ�
void SListPushBack(SListNode** pHead, SLDataType data)
{
	assert(pHead);//ȷ������һ������
	SListNode* pNewNode = BuySListNode(data);
	if (NULL == *pHead)//pHead���汣���������ĵ�ַ,һ������Ϊ��
	{
		*pHead = pNewNode;
	}
	else
	{    
		SListNode* pCur =*pHead;
		while (pCur->_pNext)//�����������һ�����
		{
			pCur = pCur->_pNext;
		}
		pCur->_pNext = pNewNode;
	}
}

void SListPopBack(SListNode** pHead)
{
	assert(pHead);
	//1.������
	if (NULL == *pHead)
	{
		return;
	}
	//2.������ֻ��һ���ڵ�
	else if (NULL == (*pHead)->_pNext)
	{
		free(*pHead);
		*pHead = NULL;
	}
	//3.�����������������ڵ�
	else
	{
		SListNode* pCur = *pHead;
		while (pCur->_pNext->_pNext)//�ҵ����ڶ����ڵ�
		{
			pCur = pCur->_pNext;
		}
		free(pCur->_pNext);
		pCur->_pNext = NULL;
	}
}

void SListPushFront(SListNode** pHead, SLDataType data)
{
	assert(pHead);

	SListNode* pNewNode = (SListNode*)BuySListNode(data);
	pNewNode->_pNext = *pHead;
	*pHead = pNewNode;
}

void SListPopFront(SListNode** pHead)
{
	assert(pHead);
	SListNode* pDel = *pHead;
	//1.������----->ֱ�ӷ���
	if (NULL == *pHead)
	{
		return;
	}
	//2.ֻ��һ���ڵ�-->ֱ��ɾ����*pHead=NULL
	//3.����ڵ�
	*pHead = pDel->_pNext;
	free(pDel);

}

SListNode* SListFind(SListNode* pHead, SLDataType data)
{
	SListNode* pCur = pHead;
	while (pCur)
	{
		if (data == pCur->_data)
		{
			return pCur;
		}
		pCur = pCur->_pNext;
	}
	return NULL;
}

void SListInsert(SListNode* pos, SLDataType data)
{
	if (NULL == pos)
	{
		return;
	}
	SListNode* pNewNode=(SListNode*)BuySListNode(data);
	pNewNode->_pNext = pos->_pNext;
	pos->_pNext = pNewNode;
}

void SListErase(SListNode** pHead,SListNode* pos)
{
	assert(pHead);
	if (NULL == pos || NULL == *pHead)
		return;

	if (pos == *pHead)
	{
		*pHead = pos->_pNext;
	}
	else
	{
		//��pos��ǰһ�����
		SListNode* posPre = *pHead;
		while (posPre->_pNext != pos)
		{
			posPre = posPre->_pNext;
		}
		posPre->_pNext = pos->_pNext;
	}
	free(pos);
}

void SListDestory(SListNode** pHead)
{
	SListNode* pDel = *pHead;
	while (*pHead)
	{
		pDel = *pHead;
		*pHead = pDel->_pNext;
		free(pDel);
	}
}

int SListSize(SListNode* pHead)
{
	int count = 0;
	SListNode* pCur = pHead;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}

int SListEmpty(SListNode* pHead)
{
	return NULL == pHead;
}

SLDataType Front(SListNode* pHead)
{
	assert(pHead);
	return pHead->_data;
}

SLDataType Back(SListNode* pHead)
{
	assert(pHead);
	SListNode* pCur = pHead;
	while (pCur->_pNext)//�����NULL==pCur�����жϣ�����ѭ��ʱ����ֵ����
	{
		pCur = pCur->_pNext;
	}
	return pCur->_data;
}

void SListRemove(SListNode** pHead, SLDataType data)
{
	assert(pHead);
	SListNode* pCur = *pHead;
	SListNode* pPre = NULL;
	while (pCur)
	{
		//���pCur�ڵ��е�ֵ���Ƿ�Ϊdata
		if (data == pCur->_data)
		{
			//��ɾ���ڵ�Ϊ��һ���ڵ�
			if (pCur == *pHead)
			{
				*pHead = pCur->_pNext;
			}
			else
			{
				pPre->_pNext = pCur->_pNext;
			}
			free(pCur);
			return;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}
}

void SListRemoveAll(SListNode** pHead, SLDataType data)
{
	assert(pHead);
	SListNode* pCur = *pHead;
	SListNode* pPre = NULL;
	while (pCur)
	{
		//���pCur�ڵ��е�ֵ���Ƿ�Ϊdata
		if (data == pCur->_data)
		{
			//��ɾ���ڵ�Ϊ��һ���ڵ�
			if (pCur == *pHead)
			{
				*pHead = pCur->_pNext;
				free(pCur);
				pCur = *pHead;
			}
			else
			{
				pPre->_pNext = pCur->_pNext;
				free(pCur);
				pCur = pPre->_pNext;
			}
		}
		else
		{
			pPre = pCur;
			pCur = pCur->_pNext;
		}
	}
}

void SListBubbleSort(SListNode** pHead)
{

}


void PrintSList(SListNode* pHead)
{
	SListNode* pCur = pHead;
	while (pCur)
	{
		printf("%d->", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("NULL\n");
}

void TestList1()
{
	SListNode* pList=NULL;
	SListInit(&pList);

	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);
	SListPushBack(&pList, 5);
	SListPushBack(&pList, 6);
	PrintSList(pList);

	SListPopBack(&pList);
	PrintSList(pList);

	SListPopBack(&pList);
	SListPopBack(&pList);
	SListPopBack(&pList);
	SListPopBack(&pList);
	PrintSList(pList);

	SListPopBack(&pList);
	PrintSList(pList);

	SListPopBack(&pList);
	PrintSList(pList);

}

void TestList2()
{
	SListNode* pList = NULL;
	SListInit(&pList);

	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);
	SListPushBack(&pList, 5);
	SListPushBack(&pList, 6);
	PrintSList(pList);

	SListPushFront(&pList, 0);
	PrintSList(pList);

	SListPopFront(&pList);
	PrintSList(pList);

	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	SListPopFront(&pList);
	PrintSList(pList);

	SListPopFront(&pList);
	PrintSList(pList);

	SListPopFront(&pList);
	PrintSList(pList);
}

void TestList3()
{
	SListNode* pList = NULL;
	SListInit(&pList);

	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);
	SListPushBack(&pList, 5);
	SListPushBack(&pList, 6);
	PrintSList(pList);

	printf("%d\n",SListSize(pList));

	printf("%d\n",Front(pList));
	printf("%d\n",Back(pList));

	/*SListInsert(SListFind(pList, 3), 7);
	PrintSList(pList);

	SListErase(&pList,SListFind(pList, 7));
	PrintSList(pList);

	SListErase(&pList, SListFind(pList, 1));
	PrintSList(pList);*/

}

void TestList4()
{
	SListNode* pList = NULL;
	SListInit(&pList);

	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);
	SListPushBack(&pList, 5);
	SListPushBack(&pList, 6);
	PrintSList(pList);

	SListRemove(&pList, 1);
	PrintSList(pList);

	SListRemove(&pList, 4);
	PrintSList(pList);
}

void TestList5()
{
	SListNode* pList = NULL;
	SListInit(&pList);

	SListPushBack(&pList, 2);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 4);
	SListPushBack(&pList, 5);
	SListPushBack(&pList, 6);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 7);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 2);
	PrintSList(pList);

	SListRemoveAll(&pList, 2);
	PrintSList(pList);
}

void TestList()
{
	//TestList1();
	//TestList2();
	//TestList3();
	//TestList4();
	TestList5();
}
