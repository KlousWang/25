#include<iostream>
using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(T val):data(val),left(nullptr),right(nullptr){}
};

template<typename T>
class BinaryTree {
private:
	TreeNode<T>* root;

	//����ڵ�ĸ�������
	TreeNode<T>* insert(TreeNode<T>* node, T value) {
		if (node == nullptr) {
			return new TreeNode<T>(value);
		}
		if (value < node->data) {
			node->left = insert(node->left, value);
		}
		else
		{
			node->right = insert(node->right, value);
		}
		return node;
	}

	void inorder(TreeNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		inorder(node->left);
		cout << node->data << " ";
		inorder(node->right);
	}

	void preorder(TreeNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->data << " ";
		preorder(node->left);
		preorder(node->right);
	}

	void postorder(TreeNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		postorder(node->left);
		postorder(node->right);
		cout << node->data << " ";
	}
public:
	BinaryTree() :root(nullptr) {}

	void insert(T value) {
		root = insert(root, value);
	}

	void inorderTraversal() {
		inorder(root);
		cout << endl;
	}
	void preorderTravel() {
		preorder(root);
		cout << endl;
	}
	void PostorderTravelsal() {
		postorder(root);
		cout << endl;
	}
};

int main() {
	BinaryTree<int>tree;

	tree.insert(20);
	tree.insert(90);
	tree.insert(30);
	tree.insert(40);
	tree.insert(50);
	tree.insert(60);
	tree.insert(10);

	cout << "�������";
	tree.inorderTraversal();

	// ǰ�������Preorder������� 50 30 20 40 70 60 80
	std::cout << "ǰ�����: ";
	tree.preorderTravel();

	// ���������Postorder������� 20 40 30 60 80 70 50
	std::cout << "�������: ";
	tree.PostorderTravelsal();

	return 0;
}
