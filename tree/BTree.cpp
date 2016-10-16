/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  datastruct (binary tree)
**************************************************************/
#include <iostream>
#include <string>
using namespace std;


template <typename T>
struct node {
	T data;
	struct node<T> *left, *right;
	node(T d) {
		data = d;
		left = NULL;
		right = NULL;
	}
};

template<typename T>
class Bintree {
private:
	node<T> *root;

	node<T> *Min(node<T> *parent) {
		node<T> *t = parent;
		while (!t) {
			if (!t->left)
				return t;
			else
				t = t->left;
		}
		return NULL;
	}

	node<T> *Max(node<T> *parent) {
		node<T> *t = parent;
		while (!t) {
			if (!t->right)
				return t;
			else
				t = t->right;
		}
		return NULL;
	}

	void Insert(node<T> *n, node<T> *t) {
		if (n->data > t->data) {
			if (!n->left) {
				n->left = t;
			}
			else {
				Insert(n->left, t);
			}
		}
		else {
			if (!n->right) {
				n->right = t;
			}
			else {
				Insert(n->right, t);
			}
		}
	}

	void Remove(node<T> *parent, string direction, T data) {
		node<T> *cur;
		int dir;
		if (!direction.compare("left")) {
			cur = parent->left;
			dir = -1;
		}
		else if (!direction.compare("right")) {
			cur = parent->right;
			dir = 1;
		}
		else {
			cerr << "ERROR:: wrong direction." << endl;
			return;
		}
		if (cur->data == data) {
			if (!cur->left) {
				if (dir == -1)
					parent->left = cur->right;
				else
					parent->right = cur->right;
				delete cur;
			}
			else if (!cur->right) {
				if (dir == -1)
					parent->left = cur->left;
				else
					parent->right = cur->left;
				delete cur;
			}
			else {
				node<T> *t = Min(cur->left);
				cur->data = t->data;
				Remove(cur, "left", t->data);
			}
		}
		else if (cur->data > data) {
			Remove(cur, "left", data);
		}
		else {
			Remove(cur, "right", data);
		}

	}

	void Preorder(node<T> *parent)
	{
		if (parent != NULL)
		{
			cout << parent->data << " ";
			Preorder(parent->left);
			Preorder(parent->right);
		}
	}

	void preorder(node<T> *parent)
	{
		stack<node<T>*> s;
		while(!s.empty() || parent)
		{
			while(parent)
			{
				cout << parent->data << " ";
				s.push(parent);
				parent = parent->left;
			}
			if(!s.empty())
			{
				parent = s.top();
				s.pop();
				parent = parent->right;
			}
		}
	}

	void Inorder(node<T> *parent)
	{
		if (parent != NULL)
		{
			Inorder(parent->left);
			cout << parent->data << " ";
			Inorder(parent->right);
		}
	}

	void inorder(node<T> *parent)
	{
		stack<node<T>*> s;
		while(parent || !s.empty())
		{
			while(parent)
			{
				s.push(parent);
				parent = parent->left;
			}
			if(!s.empty())
			{
				parent = s.top();
				s.pop();
				cout << parent->data << " ";
				parent = parent->right;
			}
		}
	}

	void Postorder(node<T> *parent)
	{
		if (parent != NULL)
		{
			Postorder(parent->left);
			Postorder(parent->right);
			cout << parent->data << " ";
		}
	}

	void postorder(node<T> *parent)
	{
		stack<node<T>*> s;
		node<T>*cur;
		node<T>*pre = nullptr;
		s.push(parent);
		while(!s.empty())
		{
			cur = s.top();
			if((!cur->left&&!cur->right)||(pre&&(cur->left==pre || cur->right==pre)))
			{
				cout << cur->data << " ";
				s.pop();
				pre = cur;
			}else
			{
				if (cur->right)
					s.push(cur->right);
				if (cur->left)
					s.push(cur->left);
			}
		}
	}
	
public:
	Bintree() {
		root = NULL;
	}
	~Bintree(){}
	void Insert(T data) {
		node<T> *t = new node<T>(data);
		//t->data = data;
		if (!root) {
			root = t;
		}
		else {
			Insert(root, t);
		}
	}

	void Remove(T data) {
		if (!root) return;
		node<T> *cur = root;
		if (cur->data == data) {
			if (!cur->left) {
				root = cur->right;
				delete cur;
			}
			else if (!cur->right) {
				root = cur->left;
				delete cur;
			}
			else {
				node<T> *t = Min(cur->left);
				cur->data = t->data;
				Remove(cur, "left", t->data);
			}
		}
		else if (cur->data > data) {
			Remove(cur, "left", data);
		}
		else {
			Remove(cur, "right", data);
		}
	}

	int Count(node<T> *parent)
	{
		if (parent == NULL)
			return 0;
		else
			return Count(parent->left) + Count(parent->right) + 1;
	}

	void Traversal() {
		cout << "先序遍历： ";
		Preorder(root);
		cout << endl << "中序遍历： ";
		Inorder(root);
		cout << endl << "后序遍历： ";
		Postorder(root);
		cout << endl << "二叉树大小：" << Count(root) << endl;
	}


};

int main1() {
	Bintree<int> *bt = new Bintree<int>();
	int arr[] = { 5, 2, 3, 6, 4, 1, 8, 7, 9, 0 };
	for (int i = 0; arr[i]; i++) {
		bt->Insert(arr[i]);
	}
	bt->Traversal();
	bt->Remove(6);
	bt->Traversal();
	return 0;
}