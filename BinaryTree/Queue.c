#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

//初始化
void QueueInit(Queue* q)
{
	q->_front = q->_rear = NULL;
}

//入队列
void QueuePush(Queue* q, QUDataType data)
{
	assert(q);
	QueueNode* pCur = (QueueNode*)malloc(sizeof(QueueNode));
	pCur->_data = data;
	pCur->_next = NULL;
	if (NULL == q->_front)
		q->_front = q->_rear = pCur;
	else
	{
		q->_rear->_next = pCur;
		q->_rear = pCur;
	}
}

//出队列
void QueuePop(Queue* q)
{
	assert(q);
	if (!QueueEmpty(q))
	{
		if (q->_front == q->_rear)
		{
			free(q->_front);
			q->_front = q->_rear = NULL;
		}
		else
		{
			QueueNode* pDel = q->_front;
			q->_front = pDel->_next;
			free(pDel);
		}
	}
}

//获取队列队头元素
QUDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}

//获取队列队尾元素
QUDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_rear->_data;
}

//判断队列是否为空
int QueueEmpty(Queue* q)
{
	assert(q);
	return NULL == q->_front;
}

//获取队列有效元素个数
int QueueSize(Queue* q)
{
	int count = 0;
	QueueNode* pCur = q->_front;
	while (pCur)
	{
		count++;
		pCur = pCur->_next;
	}
	return count;
}

//销毁队列
void QueueDestroy(Queue* q)
{
	QueueNode* pCur = q->_front;
	while (pCur)
	{
		q->_front = pCur->_next;
		free(pCur);
		pCur = q->_front;
	}
	q->_front = q->_rear = NULL;
}