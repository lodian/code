#pragma once

typedef int SLDataType;

//����ͷ��������
typedef struct SListNode
{
	struct SListNode* _pNext;
	SLDataType _data;
}SListNode;

//��ʼ��
void SListInit(SListNode** pList);

//β��
void SListPushBack(SListNode** pList, SLDataType data);

//βɾ
void SListPopBack(SListNode** pList);

//ͷ��
void SListPushFront(SListNode** pList, SLDataType data);

//ͷɾ
void SListPopFront(SListNode** pList);

//����ֵΪdata��Ԫ��
SListNode* SListFind(SListNode* pHead, SLDataType data);

//��ָ��pos�ĺ������Ԫ��data
void SListInsert(SListNode* pos, SLDataType data);

//��ָ��λ��posɾ��Ԫ��
void SListErase(SListNode** pHead,SListNode* pos);

//����
void SListDestory(SListNode** pHead);

//��ȡ��Ч�ڵ����
int SListSize(SListNode* pHead);

//�п�
int SListEmpty(SListNode* pHead);

//��ȡ�׸��ڵ�
SLDataType Front(SListNode* pHead);

//��ȡ���һ���ڵ�
SLDataType Back(SListNode* pHead);

//ɾ��ָ��Ԫ�صĽڵ�
void SListRemove(SListNode** pHead, SLDataType data);

//ɾ��ֵΪdata�����нڵ�
void SListRemoveAll(SListNode** pHead, SLDataType data);

//ð����������
void SListBubbleSort(SListNode** pHead);

//��ӡ����
void SListPrint(SListNode* pList);

void TestList();