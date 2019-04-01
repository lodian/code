#pragma once

struct BinaryTreeNode;
typedef struct BinaryTreeNode* QUDataType;

typedef struct QueueNode
{
	struct QueueNode* _next;
	QUDataType _data;
}QueueNode;

typedef struct Queue
{
	QueueNode* _front; // ��ͷ
	QueueNode* _rear; // ��β
}Queue;

//��ʼ��
void QueueInit(Queue* q);

//�����
void QueuePush(Queue* q, QUDataType x);

//������
void QueuePop(Queue* q);

//��ȡ���ж�ͷԪ��
QUDataType QueueFront(Queue* q);

//��ȡ���ж�βԪ��
QUDataType QueueBack(Queue* q);

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(Queue* q);

//��ȡ������ЧԪ�ظ���
int QueueSize(Queue* q);

//���ٶ���
void QueueDestroy(Queue* q);

