#pragma once

struct BinaryTreeNode;
typedef struct BinaryTreeNode* SDataType;

//��̬ջ
typedef struct Stack
{
	SDataType* _array;
	int _capacity;//��ЧԪ�ص�������
	int _top;//ջ��
}Stack;

//��ʼ��
void StackInit(Stack* ps);

//ѹջ����ջ����������data��
void StackPush(Stack* ps,SDataType data);

//��ջ����ջ��������ɾ����
void StackPop(Stack* ps);

//��ȡջ������
SDataType StackTop(Stack* ps);

//��ȡջ����ЧԪ�صĸ���
int StackSize(Stack* ps);

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(Stack* ps);

//����
void StackDestroy(Stack* ps);

void TestStack();