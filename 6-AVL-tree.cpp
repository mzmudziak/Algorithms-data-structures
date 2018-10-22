#include <iostream>
using namespace std;

class node
{
public:
	 int key;
	 node *parent = 0;
	 node *left = 0;
	 node *right = 0;
	 int children = 0;
	 int height = 0;
};

class tree
{
private:
	 node  *root;
public:
	 tree()
	 {
		  root = 0;
	 }
	 ~tree() {}
	 node* insert(const int &arg)
	 {
		  if (root == 0)
		  {
			   root = new node;
			   root->key = arg;
			   return root;
		  }
		  else
		  {
			   node  *current = root;
			   node *newNode = new node;
			   while (true)
			   {
					current->children++;
					if (arg == current->key)   // jesli wartosc szukana juz jest, to koncz dzialanie
					{
						// decreaseChildren(current);
						 root->children--;
						 return NULL;
					}
					else if (arg < current->key)   // jesli poszukiwana wartosc jest mniejsz
					{
						 if (current->left == 0)
						 {
							  current->left = newNode;
							  current->left->key = arg;
							  current->left->parent = current;
							  return current->left;
						 }
						 else
						 {
							  current = current->left;
						 }

					}
					else if (arg > current->key)
					{
						 if (current->right == 0)
						 {
							  current->right = newNode;
							  current->right->key = arg;
							  current->right->parent = current;
							  return current->right;
						 }
						 else
						 {
							  current = current->right;
						 }
					}
			   }
		  }
	 }
	 void decreaseChildren(node* arg) {
		  while (arg->parent)
		  {
			   arg->children--;
			   arg = arg->parent;
		  }
	 }
	 int getChildren(node *arg) {
		  if (arg) {
			   return arg->children + 1;
		  }
		  else return 0;
	 }
	 void findNode(int arg)
	 {
		  int smaller = 0;
		  if (root == 0)
		  {
			   cout << "N,0 ";
		  }
		  else
		  {
			   node  *current = root;
			   while (current != 0)
			   {
					if (current->key == arg)
					{
						 smaller = smaller + getChildren(current->left) + 1;
						 cout << "T," << smaller << " ";
						 return;
					}
					else
					{
						 if (arg > current->key)
						 {
							  smaller = smaller + getChildren(current->left) + 1;
							  current = current->right;
						 }
						 else
						 {
							  current = current->left;
						 }
					}
			   }
			   cout << "N," << smaller << " ";
		  }
	 }
	 int setHeight(node *arg) {
		  int leftHeight = getHeight(arg->left);
		  int rightHeight = getHeight(arg->right);
		  arg->height =  (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	 }
	 int getHeight(node *arg) {
		  if (arg) {
			   return arg->height;
		  }
		  else return 0;
	 }
	 void rebalance(node *node) {
		  while (node) {
			   setHeight(node);
			   if (getHeight(node->left) >= 2 + getHeight(node->right)) {
					if (getHeight(node->left->left) >= getHeight(node->left->right)) {
						 rightRotate(node);
					}
					else {
						 leftRotate(node->left);
						 rightRotate(node);
					}
			   }
			   else if (getHeight(node->right) >= 2 + getHeight(node->left)) {
					if (getHeight(node->right->right) >= getHeight(node->right->left)) {
						 leftRotate(node);
					}
					else {
						 rightRotate(node->right);
						 leftRotate(node);

					}
			   }
			   node = node->parent;
		  }
	 }
	 int checkBalance(node *arg) {
		  if (arg == NULL) {
			   return 0;
		  }
		  else {
			   return getHeight(arg->left) - getHeight(arg->right);
		  }
	 }
	 void updateChildren(node* arg) {
		  if (arg) {
			   arg->children = 0;
			   if (arg->right) {
					arg->children +=  1 + arg->right->children;
			   }
			   if (arg->left) {
					arg->children += 1 + arg->left->children;
			   }
		  }
	 }
	 void leftRotate(node *arg) { 
		  if (arg) {
			   node *rightNode = arg->right;
			   rightNode->parent = arg->parent;
			   if (!rightNode->parent) {
					root = rightNode;
			   }
			   else {
					if (rightNode->parent->left == arg) {
						 rightNode->parent->left = rightNode;
					}
					else if (rightNode->parent->right == arg) {
						 rightNode->parent->right = rightNode;
					}
			   }
			   arg->right = rightNode->left;
			   if (arg->right) {
					arg->right->parent = arg;
			   }
			   rightNode->left = arg;
			   arg->parent = rightNode;
			   updateChildren(arg);
			   updateChildren(rightNode);
			   setHeight(arg);
			   setHeight(rightNode);
		  }
	 }
	 void rightRotate(node *arg) {
		  if (arg) {
			   node *leftNode = arg->left;
			   leftNode->parent = arg->parent;
			   if (!leftNode->parent) {
					root = leftNode;
			   }
			   else {
					if (leftNode->parent->left == arg) {
						 leftNode->parent->left = leftNode;
					}
					else if (leftNode->parent->right == arg) {
						 leftNode->parent->right = leftNode;
					}
			   }
			   arg->left = leftNode->right;
			   if (arg->left) {
					arg->left->parent = arg;
			   }
			   leftNode->right = arg;
			   arg->parent = leftNode;
			   updateChildren(arg);
			   updateChildren(leftNode);
			   setHeight(arg);
			   setHeight(leftNode);
		  }
	 }
};


int main()
{
	 int z, m, k, element, search;
	 tree t;
	 cin >> z;
	 for (int i = 0; i < z; i++) {
		  cin >> m;
		  for (int j = 0; j < m;j++) {
			   cin >> element;
			   t.rebalance(t.insert(element));
		  }
		  cin >> k;
		  for (int l = 0; l < k; l++) {
			   cin >> search;
			    t.findNode(search);
		  }
		  cout << endl;
	 }
    return 0;
}
