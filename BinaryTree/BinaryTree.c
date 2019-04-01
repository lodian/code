#include "BinaryTree.h"
#include "Queue.h"
#include "Stack.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

BTNode* BuyBinaryTreeNode(BTDataType data)
{
	BTNode* pNode = (BTNode*)malloc(sizeof(BTNode));
	if (NULL == pNode)
		exit(1);

	pNode->_data = data;
	pNode->_pLeft = NULL;
	pNode->_pRight = NULL;

	return pNode;
}

void _CreateBinaryTree(BTDataType* array, int size, BTNode** pRoot, int* index, BTDataType invalid)
{
	assert(pRoot);
	if ((*index) < size && array[*index] != invalid)
	{
		*pRoot = BuyBinaryTreeNode(array[*index]);

		//�������ڵ��������
		(*index)++;
		_CreateBinaryTree(array, size, &(*pRoot)->_pLeft,index,invalid);

		//�������ڵ��������
		(*index)++;
		_CreateBinaryTree(array, size, &(*pRoot)->_pRight, index, invalid);
	}
}

//����������
//ǰ���������
BTNode* CreateBinaryTree(BTDataType* array, int size, BTDataType invalid)
{
	BTNode* pRoot = NULL;
	int index = 0;
	_CreateBinaryTree(array, size, &pRoot, &index, invalid);
	return pRoot;
}

//���ٶ�����
//�����������
void DestroyBinaryTree(BTNode** pRoot)
{
	assert(pRoot);
	if (*pRoot)
	{
		DestroyBinaryTree(&(*pRoot)->_pLeft);
		DestroyBinaryTree(&(*pRoot)->_pRight);
		free(*pRoot);
		*pRoot = NULL;
	}
}

//����������
BTNode* CopyBinaryTree(BTNode* pRoot)
{
	BTNode* pNewRoot = NULL;
	if (pRoot)
	{
		pNewRoot = BuyBinaryTreeNode(pRoot->_data);
		if (pRoot->_pLeft)
			pNewRoot->_pLeft = CopyBinaryTree(pRoot->_pLeft);
		
		if (pRoot->_pRight)
			pNewRoot->_pRight = CopyBinaryTree(pRoot->_pRight);
	}
	return pNewRoot;
}

//����ֵΪdata�ĵ�һ���ڵ�
BTNode* Find(BTNode* pRoot, BTDataType data)
{
	BTNode* pRet = NULL;
	if (NULL == pRoot)
		return NULL;
	if (data == pRoot->_data)
		return pRoot;
	if (pRet = Find(pRoot->_pLeft,data))
		return pRet;

	return Find(pRoot->_pRight, data);
}

//��ȡ���������ܽڵ�ĸ���
int BinaryTreeSize(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	return BinaryTreeSize(pRoot->_pLeft) + BinaryTreeSize(pRoot->_pRight) + 1;
}

//��ȡ��������Ҷ�ӽڵ�ĸ���
int BinaryTreeLeafSize(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight);
		return 1;

	return BinaryTreeLeafSize(pRoot->_pLeft) + BinaryTreeLeafSize(pRoot->_pRight);
}

//��ȡ�������е�K���нڵ�ĸ���
int BinaryTreeLevelKSize(BTNode* pRoot, int k)
{
	if (NULL == pRoot || k<0 || k>BinaryTreeHeight(pRoot))
		return 0;

	if (1 == k)
		return 1;

	return BinaryTreeLevelKSize(pRoot->_pLeft, k - 1) + BinaryTreeLevelKSize(pRoot->_pRight, k - 1);
}

//��ȡ��������������/�߶�
int BinaryTreeHeight(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	int LeftHeight = BinaryTreeHeight(pRoot->_pLeft);
	int RightHeight = BinaryTreeHeight(pRoot->_pRight);

	return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
}

int IsCompleteBinaryTree(BTNode* pRoot)
{
	Queue q;
	int flag = 0;//�ٽ����
	if (NULL == pRoot)
		return 1;

	//���ղ�������ķ�ʽ���ٽ��
	QueueInit(&q);
	QueuePush(&q, pRoot);

	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		if (flag)
		{
			//���ٽ��֮�����еĽڵ㲻���к���
			if (pCur->_pLeft || pCur->_pRight)
			{
				QueueDestroy(&q);
				return 0;
			}
		}
		else
		{
			//���ٽ��
			if (pCur->_pLeft && pCur->_pRight)
			{
				QueuePush(&q, pCur->_pLeft);
				QueuePush(&q, pCur->_pRight);
			}
			else if (pCur->_pLeft)
			{
				QueuePush(&q, pCur->_pLeft);
				flag = 1;
			}
			else if (pCur->_pRight)
			{
				//��ǰ�ڵ�ֻ���Һ���û�����ӣ�һ��������ȫ������
				QueueDestroy(&q);
				return 0;
			}
			else
			{
				//��ǰ�ڵ�һ�����Ӷ�û��
				flag = 1;
			}
		}
		QueuePop(&q);
	}
	QueueDestroy(&q);
	return 1;
}

//��ȡ�������ľ���Գƶ��������ݹ�ʵ��
void MirrorBinaryTree(BTNode* pRoot)
{
	if (pRoot)
	{
		BTNode* pTemp = pRoot->_pLeft;
		pRoot->_pLeft = pRoot->_pRight;
		pRoot->_pRight = pTemp;

		MirrorBinaryTree(pRoot->_pLeft);
		MirrorBinaryTree(pRoot->_pRight);
	}
}

//��ȡ�������ľ���Գƶ��������ǵݹ�ʵ��
void MirrorBinaryTreeNor(BTNode* pRoot)
{
	Queue q;
	if (NULL == pRoot)
		return;

	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		BTNode* pTemp = pCur->_pLeft;
		pCur->_pLeft = pCur->_pRight;
		pCur->_pRight = pTemp;

		if (pCur->_pLeft)
			QueuePush(&q,pCur->_pLeft);

		if (pCur->_pRight)
			QueuePush(&q,pCur->_pRight);
		QueuePop(&q);
	}
	QueueDestroy(&q);
}

//�ݹ�ǰ�����
void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->_pLeft);
		PreOrder(pRoot->_pRight);
	}
}

//�ݹ��������
void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->_pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->_pRight);
	}
}

//�ݹ�������
void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->_pLeft);
		PostOrder(pRoot->_pRight);
		printf("%c ", pRoot->_data);
	}
}

//�������
void LevelOrder(BTNode* pRoot)
{
	Queue q;//q�Ŀռ���ջ�ϣ������еĽڵ�Ŀռ��ڶ���
	if (NULL == pRoot)
		return;//�˴���û�зŽڵ㣬���Բ��ôݻٶ��У�ջ�ϵ�q�ں����˳����Զ��ͷſռ�
	
	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		printf("%c ", pCur->_data);
		QueuePop(&q);

		//���pCur�����������ڣ�����pCur�������ĸ�
		if (pCur->_pLeft)
			QueuePush(&q, pCur->_pLeft);

		//���pCur�����������ڣ�����pCur�������ĸ�
		if (pCur->_pRight)
			QueuePush(&q, pCur->_pRight);

	}
	printf("\n");
	QueueDestroy(&q);
}

//�ǵݹ�ǰ�����
void PreOrderNor(BTNode* pRoot)
{
	Stack s;
	if (NULL == pRoot)
		return;

	StackInit(&s);
	StackPush(&s, pRoot);
	while (!StackEmpty(&s))
	{
		BTNode* pCur = StackTop(&s);
		printf("%c ", pCur->_data);
		StackPop(&s);

		if (pCur->_pRight)
			StackPush(&s,pCur->_pRight);

		if (pCur->_pLeft)
			StackPush(&s, pCur->_pLeft);
	}
	printf("\n");
	StackDestroy(&s);
}

//�ǵݹ��������
void InOrderNor(BTNode* pRoot)
{
	Stack s;
	BTNode* pCur = NULL;
	if (NULL == pRoot)
		return;
	StackInit(&s);
	StackPush(&s, pRoot);
	while (!StackEmpty(&s))
	{
		while ((pCur = StackTop(&s)) && pCur)
		{
			StackPush(&s, pCur->_pLeft);
		}
		StackPop(&s);
		if (!StackEmpty(&s))
		{
			pCur = StackTop(&s);
			printf("%c ", pCur->_data);
			StackPop(&s);
			StackPush(&s, pCur->_pRight);
		}
	}
	printf("\n");
	StackDestroy(&s);
}

void InOrderNor2(BTNode* pRoot)
{
	Stack s;
	BTNode* pCur = pRoot;
	if (NULL == pRoot)
		return;
	StackInit(&s);
	while(pCur || !StackEmpty(&s))
	{
		while (pCur)//����pCurΪ���ڵ�Ķ����������Ľڵ㣬����������·���ϵĽڵ�
		{
			StackPush(&s, pCur);
			pCur = pCur->_pLeft;
		}
		pCur = StackTop(&s);
		StackPop(&s);
		printf("%c ", pCur->_data);
		pCur = pCur->_pRight;
	}
	printf("\n");
	StackDestroy(&s);
}

//�ǵݹ�������
void PostOrderNor(BTNode* pRoot)
{
	Stack s;
	BTNode* pCur = pRoot;
	BTNode* pPrev = NULL;//��Ǳ������Ľڵ�
	if (NULL == pRoot)
		return;
	StackInit(&s);
	while (pCur || !StackEmpty(&s))
	{
		while (pCur)//����pCurΪ���ڵ�Ķ����������Ľڵ㣬����������·���ϵĽڵ�
		{
			StackPush(&s, pCur);
			pCur = pCur->_pLeft;
		}
		BTNode* pTop = StackTop(&s);
		//���pTop��������Ϊ�ջ���pTop���������Ѿ�����
		if (NULL == pTop->_pRight || pTop->_pRight==pPrev)
		{
			printf("%c ", pTop->_data);
			pPrev = pTop;
			StackPop(&s);
		}
		else
		{
			pCur = pTop->_pRight;
		}
	}
	printf("\n");
	StackDestroy(&s);
}

void TestBinaryTree()
{
	BTNode* pRoot = NULL;
	BTDataType* pStr = "ABD###CE##F";
	pRoot=CreateBinaryTree(pStr, strlen(pStr), '#');
	
	printf("�������нڵ�ĸ�����%d\n", BinaryTreeSize(pRoot));
	printf("��������Ҷ�ӽڵ�ĸ�����%d\n", BinaryTreeLeafSize(pRoot));
	printf("�������е�%d��ڵ�ĸ�����%d\n",3,BinaryTreeLevelKSize(pRoot,3));
	printf("�������еĸ߶��ǣ�%d\n", BinaryTreeHeight(pRoot));

	printf("%c \n", Find(pRoot, 'B')->_data);

	printf("PreOrder:");
	PreOrder(pRoot);
	printf("\n");

	printf("PreOrderNor:");
	PreOrderNor(pRoot);

	printf("InOrder:");
	InOrder(pRoot);
	printf("\n");

	printf("InOrderNor:");
	InOrderNor(pRoot);

	printf("InOrderNor2:");
	InOrderNor2(pRoot);

	printf("PostOrder:");
	PostOrder(pRoot);
	printf("\n");

	printf("PostOrderNor:");
	PostOrderNor(pRoot);

	printf("LevelOrder:");
	LevelOrder(pRoot);

	MirrorBinaryTree(pRoot);
	MirrorBinaryTreeNor(pRoot);
	printf("MirrorPreOrder:");
	PreOrder(pRoot);
	printf("\n");

	if (IsCompleteBinaryTree(pRoot))
		printf("����ȫ��������\n");
	else
		printf("������ȫ��������\n");

	BTNode* pNewRoot = NULL;
	pNewRoot=CopyBinaryTree(pRoot);
	printf("CopyPreOrder:");
	PreOrder(pNewRoot);
	printf("\n");
	DestroyBinaryTree(&pNewRoot);

	DestroyBinaryTree(&pRoot);
}