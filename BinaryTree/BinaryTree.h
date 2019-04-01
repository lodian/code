#pragma once

typedef char BTDataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* _pLeft;
	struct BinaryTreeNode* _pRight;
	BTDataType _data;
}BTNode;

//����������
BTNode* CreateBinaryTree(BTDataType* array, int size, BTDataType invalid);
//���ٶ�����
void DestroyBinaryTree(BTNode** pRoot);
//����������
BTNode* CopyBinaryTree(BTNode* pRoot);
//����ֵΪdata�ĵ�һ���ڵ�
BTNode* Find(BTNode* pRoot, BTDataType data);

//�ж��Ƿ�Ϊ��ȫ������
int IsCompleteBinaryTree(BTNode* pRoot);

//��ȡ���������ܽڵ�ĸ���
int BinaryTreeSize(BTNode* pRoot);
//��ȡ��������Ҷ�ӽڵ�ĸ���
int BinaryTreeLeafSize(BTNode* pRoot);
//��ȡ�������е�K���нڵ�ĸ���
int BinaryTreeLevelKSize(BTNode* pRoot, int k);
//��ȡ��������������/�߶�
int BinaryTreeHeight(BTNode* pRoot);

//��ȡ�������ľ���Գƶ��������ݹ�ʵ��
void MirrorBinaryTree(BTNode* pRoot);
//��ȡ�������ľ���Գƶ��������ǵݹ�ʵ��
void MirrorBinaryTreeNor(BTNode* pRoot);

//�ݹ����������
void PreOrder(BTNode* pRoot);
void InOrder(BTNode* pRoot);
void PostOrder(BTNode* pRoot);
//�������
void LevelOrder(BTNode* pRoot);

//�ǵݹ�ǰ�����
void PreOrderNor(BTNode* pRoot);
//�ǵݹ��������
void InOrderNor(BTNode* pRoot);
void InOrderNor2(BTNode* pRoot);
//�ǵݹ�������
void PostOrderNor(BTNode* pRoot);

void TestBinaryTree();