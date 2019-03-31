#pragma once

typedef int SLDataType;

//不带头结点的链表
typedef struct SListNode
{
	struct SListNode* _pNext;
	SLDataType _data;
}SListNode;

//初始化
void SListInit(SListNode** pList);

//尾插
void SListPushBack(SListNode** pList, SLDataType data);

//尾删
void SListPopBack(SListNode** pList);

//头插
void SListPushFront(SListNode** pList, SLDataType data);

//头删
void SListPopFront(SListNode** pList);

//查找值为data的元素
SListNode* SListFind(SListNode* pHead, SLDataType data);

//在指定pos的后面插入元素data
void SListInsert(SListNode* pos, SLDataType data);

//在指定位置pos删除元素
void SListErase(SListNode** pHead,SListNode* pos);

//销毁
void SListDestory(SListNode** pHead);

//获取有效节点个数
int SListSize(SListNode* pHead);

//判空
int SListEmpty(SListNode* pHead);

//获取首个节点
SLDataType Front(SListNode* pHead);

//获取最后一个节点
SLDataType Back(SListNode* pHead);

//删除指定元素的节点
void SListRemove(SListNode** pHead, SLDataType data);

//删除值为data的所有节点
void SListRemoveAll(SListNode** pHead, SLDataType data);

//冒泡排序链表
void SListBubbleSort(SListNode** pHead);

//打印链表
void SListPrint(SListNode* pList);

void TestList();