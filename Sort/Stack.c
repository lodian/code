#include "Stack.h"
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _CheckCapacity(Stack* ps)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		ps->_array = (SDataType*)realloc(ps->_array, (ps->_capacity * 2)*sizeof(SDataType));
		ps->_capacity <<= 1;
	}
}

//��ʼ��
void StackInit(Stack* ps)
{
	assert(ps);
	ps->_array = (SDataType*)malloc(sizeof(SDataType)* 3);
	if (NULL == ps->_array)
	{
		exit(1);
	}
	ps->_capacity = 3;
	ps->_top = 0;
}

//ѹջ����ջ����������data��
void StackPush(Stack* ps, SDataType data)
{
	assert(ps);
	_CheckCapacity(ps);
	ps->_array[ps->_top++] = data;
}

//��ջ����ջ��������ɾ����
void StackPop(Stack* ps)
{
	assert(ps);
	if (StackEmpty(ps))
		return;
	ps->_top -= 1;
}

//��ȡջ������
SDataType StackTop(Stack* ps)
{
	assert(!StackEmpty(ps));

	return ps->_array[ps->_top - 1];
}

//��ȡջ����ЧԪ�صĸ���
int StackSize(Stack* ps)
{
	assert(ps);
	return ps->_top;
}

//�ж�ջ�Ƿ�Ϊ��
int StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->_top;
}

//����
void StackDestroy(Stack* ps)
{
	assert(ps);
	if (ps->_array)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_top = 0;
	}
}

void TestStack()
{
	Stack s;
	StackInit(&s);

	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	StackPush(&s, 4);
	StackPush(&s, 5);
	printf("%d\n", StackSize(&s));
	printf("%d\n", StackTop(&s));

	StackPop(&s);
	StackPop(&s);
	printf("%d\n", StackSize(&s));
	printf("%d\n", StackTop(&s));

	StackDestroy(&s);
}
