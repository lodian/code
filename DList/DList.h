#pragma once

//����ͷ���ĵ�����
//��ͷ���ĵ�����


//��ͷ�ڵ��ѭ��˫������
typedef int DLDataType;

//�����еĽڵ�
typedef struct DListNode
{
	struct DListNode* _pNext;
	struct DListNode* _pPre;
	DLDataType _data;
}DListNode;

//��װ����Ľṹ�����⴫����ָ��
typedef struct DList
{
	struct DListNode* _pHead;
}DList;

//��ʼ��
void DListInit(DList* plist);

//���������е���Ч�ڵ�
void DListDestory(DList* plist);

//β��
void DListPushBack(DList* plist, DLDataType x);

//βɾ
void DListPopBack(DList* plist);

//ͷ��
void DListPushFront(DList* plist, DLDataType x);

//ͷɾ
void DListPopFront(DList* plist);

//���������е���Ч�ڵ�
void DListDestory(DList* plist);

//����ֵΪx�Ľڵ�
DListNode* DListFind(DList* plist, DLDataType x);

//��pos��ǰ����в���
void DListInsert(DListNode* pos, DLDataType x);

//ɾ��posλ�õĽڵ�
void DListErase(DListNode* pos);

//ɾ��ֵΪx�Ľڵ�
void DListRemove1(DList* plist, DLDataType x);
int DListRemove2(DList* plist, DLDataType x);

//ɾ������ֵΪx�Ľڵ�
void DListRemoveAll(DList* plist, DLDataType x);

//�����������Ч�ڵ�ĸ���������ͷ�ڵ㣩
int DListSize(DList* plist);

//�ж������Ƿ�Ϊ�գ�������ͷ�ڵ㣩
int DListEmpty(DList* plist);

//��ȡ�����г�ͷ�ڵ���ĵ�һ����Ч�ڵ����ֵ
DLDataType DListFront(DList* plist);

//��ȡ���������һ����Ч�ڵ����ֵ
DLDataType DListBack(DList* plist);

void DListPrint(DList* plist);

void TestDList();