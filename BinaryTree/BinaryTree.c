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

		//创建根节点的左子树
		(*index)++;
		_CreateBinaryTree(array, size, &(*pRoot)->_pLeft,index,invalid);

		//创建根节点的右子树
		(*index)++;
		_CreateBinaryTree(array, size, &(*pRoot)->_pRight, index, invalid);
	}
}

//创建二叉树
//前序遍历规则
BTNode* CreateBinaryTree(BTDataType* array, int size, BTDataType invalid)
{
	BTNode* pRoot = NULL;
	int index = 0;
	_CreateBinaryTree(array, size, &pRoot, &index, invalid);
	return pRoot;
}

//销毁二叉树
//后序遍历规则
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

//拷贝二叉树
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

//返回值为data的第一个节点
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

//获取二叉树中总节点的个数
int BinaryTreeSize(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	return BinaryTreeSize(pRoot->_pLeft) + BinaryTreeSize(pRoot->_pRight) + 1;
}

//获取二叉树中叶子节点的个数
int BinaryTreeLeafSize(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight);
		return 1;

	return BinaryTreeLeafSize(pRoot->_pLeft) + BinaryTreeLeafSize(pRoot->_pRight);
}

//获取二叉树中第K层中节点的个数
int BinaryTreeLevelKSize(BTNode* pRoot, int k)
{
	if (NULL == pRoot || k<0 || k>BinaryTreeHeight(pRoot))
		return 0;

	if (1 == k)
		return 1;

	return BinaryTreeLevelKSize(pRoot->_pLeft, k - 1) + BinaryTreeLevelKSize(pRoot->_pRight, k - 1);
}

//获取二叉树的最大深度/高度
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
	int flag = 0;//临界点标记
	if (NULL == pRoot)
		return 1;

	//按照层序遍历的方式找临界点
	QueueInit(&q);
	QueuePush(&q, pRoot);

	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		if (flag)
		{
			//从临界点之后所有的节点不能有孩子
			if (pCur->_pLeft || pCur->_pRight)
			{
				QueueDestroy(&q);
				return 0;
			}
		}
		else
		{
			//找临界点
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
				//当前节点只有右孩子没有左孩子，一定不是完全二叉树
				QueueDestroy(&q);
				return 0;
			}
			else
			{
				//当前节点一个孩子都没有
				flag = 1;
			}
		}
		QueuePop(&q);
	}
	QueueDestroy(&q);
	return 1;
}

//获取二叉树的镜相对称二叉树，递归实现
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

//获取二叉树的镜相对称二叉树，非递归实现
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

//递归前序遍历
void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->_pLeft);
		PreOrder(pRoot->_pRight);
	}
}

//递归中序遍历
void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->_pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->_pRight);
	}
}

//递归后序遍历
void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->_pLeft);
		PostOrder(pRoot->_pRight);
		printf("%c ", pRoot->_data);
	}
}

//层序遍历
void LevelOrder(BTNode* pRoot)
{
	Queue q;//q的空间在栈上，队列中的节点的空间在堆上
	if (NULL == pRoot)
		return;//此处还没有放节点，所以不用摧毁队列，栈上的q在函数退出会自动释放空间
	
	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		printf("%c ", pCur->_data);
		QueuePop(&q);

		//如果pCur的左子树存在，保存pCur左子树的根
		if (pCur->_pLeft)
			QueuePush(&q, pCur->_pLeft);

		//如果pCur的右子树存在，保存pCur右子树的根
		if (pCur->_pRight)
			QueuePush(&q, pCur->_pRight);

	}
	printf("\n");
	QueueDestroy(&q);
}

//非递归前序遍历
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

//非递归中序遍历
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
		while (pCur)//找以pCur为根节点的二叉树最左侧的节点，并保存所经路径上的节点
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

//非递归后序遍历
void PostOrderNor(BTNode* pRoot)
{
	Stack s;
	BTNode* pCur = pRoot;
	BTNode* pPrev = NULL;//标记遍历过的节点
	if (NULL == pRoot)
		return;
	StackInit(&s);
	while (pCur || !StackEmpty(&s))
	{
		while (pCur)//找以pCur为根节点的二叉树最左侧的节点，并保存所经路径上的节点
		{
			StackPush(&s, pCur);
			pCur = pCur->_pLeft;
		}
		BTNode* pTop = StackTop(&s);
		//如果pTop的右子树为空或者pTop的右子树已经遍历
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
	
	printf("二叉树中节点的个数：%d\n", BinaryTreeSize(pRoot));
	printf("二叉树中叶子节点的个数：%d\n", BinaryTreeLeafSize(pRoot));
	printf("二叉树中第%d层节点的个数：%d\n",3,BinaryTreeLevelKSize(pRoot,3));
	printf("二叉树中的高度是：%d\n", BinaryTreeHeight(pRoot));

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
		printf("是完全二叉树！\n");
	else
		printf("不是完全二叉树！\n");

	BTNode* pNewRoot = NULL;
	pNewRoot=CopyBinaryTree(pRoot);
	printf("CopyPreOrder:");
	PreOrder(pNewRoot);
	printf("\n");
	DestroyBinaryTree(&pNewRoot);

	DestroyBinaryTree(&pRoot);
}