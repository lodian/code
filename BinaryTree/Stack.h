#pragma once

struct BinaryTreeNode;
typedef struct BinaryTreeNode* SDataType;

//动态栈
typedef struct Stack
{
	SDataType* _array;
	int _capacity;//有效元素的最大个数
	int _top;//栈顶
}Stack;

//初始化
void StackInit(Stack* ps);

//压栈（在栈顶插入数据data）
void StackPush(Stack* ps,SDataType data);

//出栈（将栈顶的数据删除）
void StackPop(Stack* ps);

//获取栈顶数据
SDataType StackTop(Stack* ps);

//获取栈中有效元素的个数
int StackSize(Stack* ps);

//判断栈是否为空
int StackEmpty(Stack* ps);

//销毁
void StackDestroy(Stack* ps);

void TestStack();