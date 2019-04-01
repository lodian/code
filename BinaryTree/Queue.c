#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

//��ʼ��
void QueueInit(Queue* q)
{
	q->_front = q->_rear = NULL;
}

//�����
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

//������
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

//��ȡ���ж�ͷԪ��
QUDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}

//��ȡ���ж�βԪ��
QUDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_rear->_data;
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(Queue* q)
{
	assert(q);
	return NULL == q->_front;
}

//��ȡ������ЧԪ�ظ���
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

//���ٶ���
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