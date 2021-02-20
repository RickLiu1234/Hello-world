#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {};
};
//There are three types of traversal
//Recursive functions+
void preorder(TreeNode* cur, vector<int>& vec) {
	//cur is initialized to the root 
	if (cur == nullptr)
		return;
	else {
		vec.push_back(cur->val);
		preorder(cur->left, vec);
		preorder(cur->right, vec);
	}

}

void inorder(TreeNode* cur, vector<int>& vec) {
	if (cur == nullptr)
		return;
	else {
		inorder(cur->left, vec);
		vec.push_back(cur->val);
		inorder(cur->right, vec);
	}
}

void postorder(TreeNode* cur, vector<int>& vec) {
	if (cur == nullptr)
		return;
	else {
		postorder(cur->left, vec);
		postorder(cur->right, vec);
		vec.push_back(cur->val);
	}
}
//Regular Functions+
vector <int> preorder(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int>result;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		st.pop();
		if (node != nullptr)
			result.push_back(node->val);
		else
			continue;
		st.push(node->right);
		st.push(node->left);
	}
	return result;
}


vector<int>inorder (TreeNode* root){
	stack<TreeNode*>st;
	vector<int>result;
	st.push(root);
	TreeNode* cur = root;
	while (cur != nullptr || !st.empty()) {
		if (cur != nullptr) {
			st.push(cur);
			cur = cur->left;
		}
		else {
			cur = st.top();
			st.pop();
			result.push_back(cur->val);
			cur = cur->right;
		}
	}
}
vector<int>preorder_general(TreeNode* root) {
	stack<TreeNode*>st;
	vector<int>result;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		if (node != nullptr) {
			st.pop();
			if (node->right)
				st.push(node->right);
			if (node->left)
				st.push(node->left);
			st.push(node);
			st.push(nullptr);
		}
		else {
			st.pop();
			node = st.top();
			st.pop();
			result.push_back(node->val);
		}
	}
}
vector<int>inorder_general(TreeNode* root) {
	vector<int>result;
	stack<TreeNode* >st;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		if (node != NULL) {
			st.pop();
			if (node->right)
				st.push(node->right);
			st.push(node);
			st.push(nullptr);
			if (node->left)
				st.push(node->left);
		}
		else {
			st.pop();
			node = st.top();
			st.pop();
			result.push_back(node->val);
		}
	}
}
vector<int>postorder(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int>result;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		st.pop();
		if (node != nullptr)
			result.push_back(node->val);
		else
			continue;
		st.push(node->left);
		st.push(node->right);
	}
	reverse(result.begin(), result.end());
	return result;
}
vector<int>postorder_general(TreeNode* root) {
	vector<int>result;
	stack<TreeNode* >st;
	st.push(root);
	while (!st.empty()) {
		TreeNode* node = st.top();
		if (node != NULL) {
			st.pop();
			st.push(node);
			st.push(nullptr);
			if (node->right)
				st.push(node->right);
			if (node->left)
				st.push(node->left);
		}
		else {
			st.pop();
			node = st.top();
			st.pop();
			result.push_back(node->val);
		}
	}
}
//层序遍历
vector<vector<int>>levelOrder(TreeNode* root) {
	queue<TreeNode*> que;
	que.push(root);
	vector<vector<int>>result;
	while (!que.empty()) {
		int size = que.size();
		vector<int>vec;
		//这里一定要使用固定大小size，不要使用que.size(),因为que.size是不断变化的
		for (int i = 0; i < size; i++) {
			TreeNode* node = que.front();
			que.pop();
			vec.push_back(node->val);
			if (node->left)
				que.push(node->left);
			if (node->right)
				que.push(node->right);
		}
		result.push_back(vec);
	}
	return result;
}
//翻转二叉树
//方法：互换每一个节点的左右孩子
TreeNode* invertTree(TreeNode* root) {
	if (root == NULL)
		return root;
	else {
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
}

//检测一个二叉树是否对称
//方法1；使用递归
bool compare(TreeNode* left, TreeNode* right) {
	if (left == nullptr || right == nullptr)
		return false;
	else if (left == nullptr && right == nullptr)
		return true;
	else if (left->val != right->val)
		return false;
	else { // in this case, the two values must be equal to each other
		bool outside = compare(left->left, right->right);
		bool inside = compare(left->right, right->left);
		bool isSame = outside && inside;
		return isSame;
	}
}
bool isSymmetric(TreeNode* root) {
	if (root == NULL)
		return true;
	return compare(root->left, root->right);
}
//方法2：using queue
bool compare_using_queue(TreeNode* root) {
	queue<TreeNode*>que;
	que.push(root->left);
	que.push(root->right);
	while (!que.empty()) {
		TreeNode* leftNode = que.front();
		que.pop();
		TreeNode* rightNode = que.front();
		que.pop();
		if (leftNode == NULL && rightNode == NULL) {
			continue;
		}
		else if (leftNode == NULL || rightNode == NULL || leftNode->val != rightNode->val) {
			return false;
		}
		else { //in this condition, the values in leftNode and rightNode are equal
			//Outer pair 
			que.push(leftNode->left);
			que.push(rightNode->right);
			//Inner pair
			que.push(leftNode->right);
			que.push(rightNode->left);
		}
	}
	return true;
}
//返回二叉树的最大深度
//方法1：递归
int getDepth(TreeNode* node) {
	if (node == NULL)
		return 0;
	else {
		int leftDepth = getDepth(node->left);
		int rightDepth = getDepth(node->right);
		int depth = 1 + max(leftDepth, rightDepth);
		return depth;
	}
}
//方法2：层序遍历模块
int maxDepth(TreeNode* root) {
	if (root == NULL)
		return 0;
	int depth = 0;
	queue<TreeNode*>que;
	que.push(root);
	while (!que.empty()) {
		int size = que.size();
		depth++;
		for (int i = 0; i < size; i++) {
			TreeNode* node = que.front();
			que.pop();
			if (node->left)
				que.push(node->left);
			que.push(node->right);
		}
	}
	return depth;
}
