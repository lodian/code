#pragma once

typedef char BTDataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* _pLeft;
	struct BinaryTreeNode* _pRight;
	BTDataType _data;
}BTNode;

//创建二叉树
BTNode* CreateBinaryTree(BTDataType* array, int size, BTDataType invalid);
//销毁二叉树
void DestroyBinaryTree(BTNode** pRoot);
//拷贝二叉树
BTNode* CopyBinaryTree(BTNode* pRoot);
//返回值为data的第一个节点
BTNode* Find(BTNode* pRoot, BTDataType data);

//判断是否为完全二叉树
int IsCompleteBinaryTree(BTNode* pRoot);

//获取二叉树中总节点的个数
int BinaryTreeSize(BTNode* pRoot);
//获取二叉树中叶子节点的个数
int BinaryTreeLeafSize(BTNode* pRoot);
//获取二叉树中第K层中节点的个数
int BinaryTreeLevelKSize(BTNode* pRoot, int k);
//获取二叉树的最大深度/高度
int BinaryTreeHeight(BTNode* pRoot);

//获取二叉树的镜相对称二叉树，递归实现
void MirrorBinaryTree(BTNode* pRoot);
//获取二叉树的镜相对称二叉树，非递归实现
void MirrorBinaryTreeNor(BTNode* pRoot);

//递归遍历二叉树
void PreOrder(BTNode* pRoot);
void InOrder(BTNode* pRoot);
void PostOrder(BTNode* pRoot);
//层序遍历
void LevelOrder(BTNode* pRoot);

//非递归前序遍历
void PreOrderNor(BTNode* pRoot);
//非递归中序遍历
void InOrderNor(BTNode* pRoot);
void InOrderNor2(BTNode* pRoot);
//非递归后序遍历
void PostOrderNor(BTNode* pRoot);

void TestBinaryTree();