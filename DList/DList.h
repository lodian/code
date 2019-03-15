#pragma once

//不带头结点的单链表
//带头结点的单链表


//带头节点的循环双向链表
typedef int DLDataType;

//链表中的节点
typedef struct DListNode
{
	struct DListNode* _pNext;
	struct DListNode* _pPre;
	DLDataType _data;
}DListNode;

//封装链表的结构，避免传二级指针
typedef struct DList
{
	struct DListNode* _pHead;
}DList;

//初始化
void DListInit(DList* plist);

//销毁链表中的有效节点
void DListDestory(DList* plist);

//尾插
void DListPushBack(DList* plist, DLDataType x);

//尾删
void DListPopBack(DList* plist);

//头插
void DListPushFront(DList* plist, DLDataType x);

//头删
void DListPopFront(DList* plist);

//销毁链表中的有效节点
void DListDestory(DList* plist);

//查找值为x的节点
DListNode* DListFind(DList* plist, DLDataType x);

//在pos的前面进行插入
void DListInsert(DListNode* pos, DLDataType x);

//删除pos位置的节点
void DListErase(DListNode* pos);

//删除值为x的节点
void DListRemove1(DList* plist, DLDataType x);
int DListRemove2(DList* plist, DLDataType x);

//删除所有值为x的节点
void DListRemoveAll(DList* plist, DLDataType x);

//输出链表中有效节点的个数（包括头节点）
int DListSize(DList* plist);

//判断链表是否为空（不包括头节点）
int DListEmpty(DList* plist);

//获取链表中除头节点外的第一个有效节点的数值
DLDataType DListFront(DList* plist);

//获取链表中最后一个有效节点的数值
DLDataType DListBack(DList* plist);

void DListPrint(DList* plist);

void TestDList();