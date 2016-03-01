/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  datastruct (AVL tree)
**************************************************************/

#include <iostream>
using namespace std;

template<typename T>
struct TreeNode {
	TreeNode() :lson(NULL), rson(NULL), frequent(1), height(0) {}
	T data;
	int height;
	unsigned int frequent;
	TreeNode *lson;
	TreeNode *rson;
};

template <typename T>
class AVLTree
{
private:
	TreeNode<T> *root;

	void Insert(TreeNode<T>* &parent, T x);
	TreeNode<T>* Find(TreeNode<T>* parent, T x);
	void Inorder(TreeNode<T>* parent);
	void Remove(TreeNode<T>* &parent, T x);
	int Height(TreeNode<T>* parent);
	TreeNode<T>* LL(TreeNode<T>* &parent);
	TreeNode<T>* RR(TreeNode<T>* &parent);
	TreeNode<T>* LR(TreeNode<T>* &parent);
	TreeNode<T>* RL(TreeNode<T>* &parent);
	int Max(int a, int b);
public:
	AVLTree() :root(NULL) {}
	~AVLTree() {};
	void Insert(T x);
	TreeNode<T> *Find(T x);
	void Remove(T x);
	void Traversal();
};

template<typename T>
void AVLTree<T>::Insert(TreeNode<T>* &parent, T x)
{
	if (!parent) {
		parent = new TreeNode<T>();
		parent->data = x;
		return;
	}
	if (parent->data > x) {
		Insert(parent->lson, x);
		if (2 == Height(parent->lson) - Height(parent->rson)) {
			if (x < parent->lson->data) {
				parent = LL(parent);
			}
			else {
				parent = LR(parent);
			}
		}
	}
	else if (parent->data < x) {
		Insert(parent->rson, x);
		if (2 == Height(parent->rson) - Height(parent->lson)) {
			if (x > parent->rson->data) {
				parent = RR(parent);
			}
			else {
				parent = RL(parent);
			}
		}
	}
	else {
		++(parent->frequent);
	}
	parent->height = Max(Height(parent->lson), Height(parent->rson)) + 1;
}

template<typename T>
TreeNode<T>* AVLTree<T>::Find(TreeNode<T>* parent, T x)
{
	if (!parent) return NULL;
	if (parent->data > x) {
		return Find(parent->lson, x);
	}
	else if (parent->data < x) {
		return Find(parent->rson, x);
	}
	else {
		return parent;
	}
}

template<typename T>
void AVLTree<T>::Inorder(TreeNode<T>* parent)
{
	if (!parent) return;
	Inorder(parent->lson);
	cout << parent->data << "  ";
	Inorder(parent->rson);
}

template<typename T>
void AVLTree<T>::Remove(TreeNode<T>* &parent, T x)
{
	if (!parent) return;
	if (x < parent->data) {
		Remove(parent->lson, x);
		if (2 == Height(parent->rson) - Height(parent->lson)) {
			if (parent->rson->lson && (Height(parent->rson->lson) > Height(parent->rson->rson))) {
				RL(parent);
			}
			else {
				RR(parent);
			}
		}
	}
	else if (x > parent->data) {
		Remove(parent->rson, x);
		if (2 == Height(parent->lson) - Height(parent->rson)) {
			if (parent->lson->rson && (Height(parent->lson->rson) - Height(parent->lson->lson))) {
				LR(parent);
			}
			else {
				LL(parent);
			}
		}
	}
	else {
		if (parent->lson&&parent->rson) {
			TreeNode<T> *t = parent->rson;
			while (t->lson)
				t = t->lson;
			parent->data = t->data;
			parent->frequent = t->frequent;
			Remove(parent->rson, t->data);
			if (2 == Height(parent->lson) - Height(parent->rson)) {
				if (parent->lson->lson && (Height(parent->lson->rson) - Height(parent->lson->lson))) {
					LR(parent);
				}
				else {
					LL(parent);
				}
			}
		}
		else {
			TreeNode<T> *t = parent;
			if (!parent->lson)
				parent = parent->rson;
			else if (!parent->rson)
				parent = parent->lson;
			delete t;
			t = NULL;
		}
	}
	if (!parent) return;
	parent->height = Max(Height(parent->lson), Height(parent->rson)) + 1;
	return;
}

template<typename T>
int AVLTree<T>::Height(TreeNode<T>* parent)
{
	if (parent)
		return parent->height;
	return -1;
}

template<typename T>
TreeNode<T>* AVLTree<T>::LL(TreeNode<T>* &parent)
{
	TreeNode<T> *t;
	t = parent->lson;
	parent->lson = t->rson;
	t->rson = parent;
	parent->height = Max(Height(parent->lson), Height(parent->rson)) + 1;
	t->height = Max(Height(t->lson), parent->height) + 1;
	return t;
}

template<typename T>
TreeNode<T>* AVLTree<T>::RR(TreeNode<T>* &parent)
{
	TreeNode<T> *t;
	t = parent->rson;
	parent->rson = t->lson;
	t->lson = parent;
	parent->height = Max(Height(parent->lson), Height(parent->rson)) + 1;
	t->height = Max(Height(t->rson), parent->height) + 1;
	return t;
}

template<typename T>
TreeNode<T>* AVLTree<T>::LR(TreeNode<T>* &parent)
{
	parent->lson = RR(parent->lson);
	parent = LL(parent);
	return parent;
}

template<typename T>
TreeNode<T>* AVLTree<T>::RL(TreeNode<T>* &parent)
{
	parent->rson = LL(parent->rson);
	parent = RR(parent);
	return parent;
}

template<typename T>
int AVLTree<T>::Max(int a, int b)
{
	return a > b ? a : b;
}

template<typename T>
void AVLTree<T>::Insert(T x)
{
	Insert(root, x);
}

template<typename T>
TreeNode<T>* AVLTree<T>::Find(T x)
{
	return Find(root, x);
}

template<typename T>
void AVLTree<T>::Remove(T x)
{
	Remove(root, x);
}

template<typename T>
void AVLTree<T>::Traversal()
{
	Inorder(root);
	cout << endl;
}


int main() {
	AVLTree<int> *avl = new AVLTree<int>();
	int arr[] = { 5, 2, 3, 4, 6, 1, 8, 7, 9, 0 };
	for (int i = 0; arr[i]; i++) {
		avl->Insert(arr[i]);
		avl->Traversal();
	}
	avl->Traversal();
	avl->Remove(6);
	avl->Traversal();
	return 0;
}