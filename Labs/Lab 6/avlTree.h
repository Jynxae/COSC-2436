#include <iostream>
#include <fstream>
using namespace std;

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

struct node
{
	int data;
	node *left;
	node *right;
	int height;
	node(int d)
	{
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree
{
private:
	node *root;
	int size;

public:
	avlTree() { 
		root = nullptr; 
		size = 0;
		}

	node *add(int data)
	{
		root = insert(root, data);
		return root;
	}

	node *getRoot() { return root; }

	node *insert(node *t, int x)
	{
		if (t == nullptr)
			t = new node(x);
		else if (x < t->data)
		{
			t->left = insert(t->left, x);
			if (bFactor(t) == 2)
			{
				if (x < t->left->data)
					t = singleRight(t);
				else
					t = leftRight(t);
			}
		}
		else if (x > t->data)
		{
			t->right = insert(t->right, x);
			if (bFactor(t) == -2)
			{
				if (x > t->right->data)
					t = singleLeft(t);
				else
					t = rightLeft(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node *singleRight(node *t)
	{
		node *u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node *singleLeft(node *t)
	{
		// needs implementation
		node *u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node *leftRight(node *t)
	{
		t->left = singleLeft(t->left);
		return singleRight(t);
	}

	node *rightLeft(node *t)
	{
		// need implementation
		t->right = singleRight(t->right);
		return singleLeft(t);
	}

	int height(node *cu)
	{
		if (cu == nullptr)
			return -1;
		else
			return cu->height;
	}

	int bFactor(node *cu)
	{
		return (height(cu->left) - height(cu->right));
	}

	void printCurrentLevel(node *root, int level, ofstream &fout, int s)
	{
		if (root == NULL)
		{
			return;
		}
		if (level == 1)
			if (size+1 == s)
			{
				fout << root->data;
			}
			else
			{
				size++;
				fout << root->data << " ";
			}
		else if (level > 1)
		{
			printCurrentLevel(root->left, level - 1, fout, s);
			printCurrentLevel(root->right, level - 1, fout, s);
		}
	}

	void printLevelOrder(node *root, ofstream& fout, int s)
	{
		int h = height(root)+2;
		int i;
		bool flag = false;
		for (i = 1; i <= h; i++)
			printCurrentLevel(root, i, fout, s);
	}
};