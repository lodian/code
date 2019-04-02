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

//初始化
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

//压栈（在栈顶插入数据data）
void StackPush(Stack* ps, SDataType data)
{
	assert(ps);
	_CheckCapacity(ps);
	ps->_array[ps->_top++] = data;
}

//出栈（将栈顶的数据删除）
void StackPop(Stack* ps)
{
	assert(ps);
	if (StackEmpty(ps))
		return;
	ps->_top -= 1;
}

//获取栈顶数据
SDataType StackTop(Stack* ps)
{
	assert(!StackEmpty(ps));

	return ps->_array[ps->_top - 1];
}

//获取栈中有效元素的个数
int StackSize(Stack* ps)
{
	assert(ps);
	return ps->_top;
}

//判断栈是否为空
int StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->_top;
}

//销毁
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
