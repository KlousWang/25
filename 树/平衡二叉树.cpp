#include <iostream>
using namespace std;

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height; // 节点高度

    TreeNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    TreeNode<T>* root;

    int height(TreeNode<T>* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode<T>* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(TreeNode<T>* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    TreeNode<T>* rightRotate(TreeNode<T>* y) {
        TreeNode<T>* x = y->left;
        TreeNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode<T>* leftRotate(TreeNode<T>* x) {
        TreeNode<T>* y = x->right;
        TreeNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        if (!node) return new TreeNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        updateHeight(node);

        int balance = balanceFactor(node);

        // 左左情况
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);
        // 右右情况
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);
        // 左右情况
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // 右左情况
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(TreeNode<T>* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T value) {
        root = insert(root, value);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "中序遍历: ";
    tree.inorderTraversal();

    return 0;
}
