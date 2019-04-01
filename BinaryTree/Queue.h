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
	QueueNode* _front; // 队头
	QueueNode* _rear; // 队尾
}Queue;

//初始化
void QueueInit(Queue* q);

//入队列
void QueuePush(Queue* q, QUDataType x);

//出队列
void QueuePop(Queue* q);

//获取队列队头元素
QUDataType QueueFront(Queue* q);

//获取队列队尾元素
QUDataType QueueBack(Queue* q);

//判断队列是否为空
int QueueEmpty(Queue* q);

//获取队列有效元素个数
int QueueSize(Queue* q);

//销毁队列
void QueueDestroy(Queue* q);

