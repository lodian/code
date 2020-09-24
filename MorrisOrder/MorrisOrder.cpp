#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(NULL), right(NULL) {}
};

// 中序遍历:
//  1. 如果当前节点的左子节点为空时，输出当前节点，并将当前节点置为该节点的右子节点；
//  2. 如果当前节点的左子节点不为空，找到当前节点左子树的最右节点（该节点为当前节点中序遍历的前驱节点）；
//   2.1. 如果最右节点的右指针为空(right=null)，将最右节点的右指针指向当前节点，当前节点置为其左子节点；
//   2.2. 如果最右节点的右指针不为空，将最右节点右指针重新置为空(恢复树的原状)，输出当前节点，并将当前节点置为其右节点；
//  3. 重复1~2，直到当前节点为空。
vector<int> MorrisInOrder(TreeNode* root) {
  vector<int> res;
  if (root == NULL) return res;
  TreeNode* cur = root;
  while(cur != NULL) {
    if (cur->left == NULL) {
      res.push_back(cur->val);
      cur = cur->right;
    } else {
      TreeNode* mostRight = cur->left;
      while (mostRight->right != NULL && mostRight->right != cur)
        mostRight = mostRight->right;

      if (mostRight->right == NULL) {
        mostRight->right = cur;
        cur = cur->left;
      } else {
        res.push_back(cur->val);
        mostRight->right = NULL;
        cur = cur->right;
      }
    }
  }
  return res;
}

// 前序遍历:
//  1. 如果当前节点的左子节点为空时，输出当前节点，并将当前节点置为该节点的右子节点；
//  2. 如果当前节点的左子节点不为空，找到当前节点左子树的最右节点（该节点为当前节点中序遍历的前驱节点）；
//   2.1. 如果最右节点的右指针为空(right=null)，将最右节点的右指针指向当前节点，并输出当前节点（在此处输出），当前节点置为其左子节点；
//   2.2. 如果最右节点的右指针不为空，将最右节点右指针重新置为空(恢复树的原状)，并将当前节点置为其右节点；
//  3. 重复1~2，直到当前节点为空。
vector<int> MorrisPreOrder(TreeNode* root) {
  vector<int> res;
  if (root == NULL) return res;
  TreeNode* cur = root;
  while (cur != NULL) {
    if (cur->left == NULL) {
      res.push_back(cur->val);
      cur = cur->right;
    } else {
      TreeNode* mostRight = cur->left;
      while (mostRight->right != NULL && mostRight->right != cur)
        mostRight = mostRight->right;

      if (mostRight->right == NULL) {
        res.push_back(cur->val);
        mostRight->right = cur;
        cur = cur->left;
      } else {
        mostRight->right = NULL;
        cur = cur->right;
      }
    }
  }
  return res;
}

// 后序遍历:
//  要建立一个临时节点，并令该节点的左子节点为root，初始化当前节点为临时节点, 并且需要一个子过程，倒序输出某两个节点之间路径上的各个节点。
// 1. 如果当前节点的左子节点为空时，则将其右子节点作为当前节点；
// 2. 如果当前节点的左子节点不为空，找到当前节点左子树的最右节点（该节点为当前节点中序遍历的前驱节点）；
//   2.1. 如果最右节点的右指针为空(right=null)，将最右节点的右指针指向当前节点，当前节点置为其左子节点；
//   2.2. 如果最右节点的右指针不为空，将最右节点右指针重新置为空(恢复树的原状)，倒序输出从当前节点的左子节点到该最右节点路径上的所有节点，并将当前节点置为其右节点；
// 3. 重复1~2，直到当前节点为空。
vector<int> MorrisPostOrder(TreeNode* root) {
  vector<int> res;
  if (root == NULL) return res;
  TreeNode* tmpNode = new TreeNode;
  tmpNode->left = root;
  TreeNode* cur = tmpNode;
  while (cur != NULL) {
    if (cur->left == NULL) {
      cur = cur->right;
    } else {
      TreeNode* mostRight = cur->left;
      while (mostRight->right !=NULL && mostRight->right != cur)
        mostRight = mostRight->right;
    
      if (mostRight->right == NULL) {
        mostRight->right = cur;
        cur = cur->left;
      } else {
        mostRight->right = NULL;
        TreeNode* t = cur->left;
        vector<int> tmp;
        while (t != NULL) {
          tmp.insert(tmp.begin(), t->val);
          t = t->right;
        }
        res.insert(res.end(), tmp.begin(), tmp.end());
        cur = cur->right;
      }
    }
  }
  return res;
}
