#include <iostream>
#include <string>

using namespace std;

template <class T> class node
{
public:
	 T key;
	 node *parent = 0;
	 node *left = 0;
	 node *right = 0;
};

template <class T, class TYPE_NAME>
class tree
{
private:
	 TYPE_NAME *root;
public:
	 tree()
	 {
		  root = 0;
	 }
	 ~tree() {}
	 TYPE_NAME* insert(const T &arg)
	 {
		  if (root == 0)
		  {
			   root = new TYPE_NAME;
			   root->key = arg;
			   return root;
		  }
		  else
		  {
			   TYPE_NAME *curr = root;
			   while (true)
			   {
					if (arg == curr->key)   // jesli wartosc szukana juz jest, to koncz dzialanie
					{
						 return curr;
					}
					else if (arg < curr->key)   // jesli poszukiwana wartosc jest mniejsz
					{
						 if (curr->left == 0)
						 {
							  curr->left = new TYPE_NAME;
							  curr->left->key = arg;
							  curr->left->parent = curr;
							  return curr->left;
						 }
						 else
						 {
							  curr = curr->left;
						 }
					}
					else if (arg > curr->key)
					{
						 if (curr->right == 0)
						 {
							  curr->right = new TYPE_NAME;
							  curr->right->key = arg;
							  curr->right->parent = curr;
							  return curr->right;
						 }
						 else
						 {
							  curr = curr->right;
						 }
					}
			   }
		  }
	 }
	 void rmv(TYPE_NAME *tbd)
	 {
		  if (tbd)
		  {
			   TYPE_NAME *ptrx;
			   TYPE_NAME *ptry;
			   if (tbd->left == NULL || tbd->right == NULL)
			   {
					ptry = tbd;
			   }
			   else
			   {
					ptry = findNext(tbd);
			   }
			   if (ptry->left != NULL)
			   {
					ptrx = ptry->left;
			   }
			   else
			   {
					ptrx = ptry->right;
			   }
			   if (ptrx != NULL)
			   {
					ptrx->parent = ptry->parent;
			   }
			   if (ptry->parent == NULL)
			   {
					root = ptrx;
			   }
			   else
			   {
					if (ptry == ptry->parent->left)
					{
						 ptry->parent->left = ptrx;
					}
					else
					{
						 ptry->parent->right = ptrx;
					}
			   }
			   if (ptry != tbd)
			   {
					tbd->key = ptry->key;
			   }
		  }
	 }
	 void rmvName(TYPE_NAME *tbd)
	 {
		  if (tbd)
		  {
			   TYPE_NAME *ptrx;
			   TYPE_NAME *ptry;
			   if (tbd->left == NULL || tbd->right == NULL)
			   {
					ptry = tbd;
			   }
			   else
			   {
					ptry = findNext(tbd);
			   }
			   if (ptry->left != NULL)
			   {
					ptrx = ptry->left;
			   }
			   else
			   {
					ptrx = ptry->right;
			   }
			   if (ptrx != NULL)
			   {
					ptrx->parent = ptry->parent;
			   }
			   if (ptry->parent == NULL)
			   {
					root = ptrx;
			   }
			   else
			   {
					if (ptry == ptry->parent->left)
					{
						 ptry->parent->left = ptrx;
					}
					else
					{
						 ptry->parent->right = ptrx;
					}
			   }
			   if (ptry != tbd)
			   {
					tbd->key = ptry->key;
					tbd->pages = ptry->pages;

			   }
		  }
	 }
	 void print()
	 {
		  printInOrder1(root);
	 }
	 void printInOrder1(TYPE_NAME *p)
	 {
		  if (p == 0)
		  {
			   return;
		  }
		  else
		  {
			   printInOrder1(p->left);
			   cout << p->key << " ";
			   p->pages.printO();
			   printInOrder1(p->right);
		  }
	 }
	 void printO()
	 {
		  printInOrder(root);
		  cout << endl;
	 }
	 void printInOrder(TYPE_NAME *p)
	 {
		  if (p == 0)
		  {
			   return;
		  }
		  else
		  {
			   printInOrder(p->left);
			   cout << p->key << " ";
			   printInOrder(p->right);
		  }
	 }
	 TYPE_NAME* findNode(T arg)
	 {
		  if (root == 0)
		  {
			   return NULL;
		  }
		  else
		  {
			   TYPE_NAME *curr = root;
			   while (curr != 0)
			   {
					if (curr->key == arg)
					{
						 return curr;
					}
					else
					{
						 if (arg > curr->key)
						 {
							  curr = curr->right;
						 }
						 else
						 {
							  curr = curr->left;
						 }
					}
			   }
			   return NULL;
		  }
	 }
	 TYPE_NAME* findMin(TYPE_NAME *arg)
	 {
		  while (arg->left != NULL)
		  {
			   arg = arg->left;
		  }
		  return arg;
	 }
	 TYPE_NAME* findMax(TYPE_NAME *arg)
	 {
		  while (arg->right != NULL)
		  {
			   arg = arg->right;
		  }
		  return arg;
	 }
	 TYPE_NAME* findPrevious(TYPE_NAME *arg)
	 {
		  if (arg->left != NULL)
		  {
			   return findMax(arg->left);
		  }
		  TYPE_NAME *temp = arg->parent;
		  while (temp != NULL && temp->right != arg)
		  {
			   arg = temp;
			   temp = temp->parent;
		  }
		  return temp;
	 }
	 TYPE_NAME* findNext(TYPE_NAME *arg)
	 {
		  if (arg->right != NULL)
		  {
			   return findMin(arg->right);
		  }
		  TYPE_NAME *temp = arg->parent;
		  while (temp != NULL && temp->left != arg)
		  {
			   arg = temp;
			   temp = temp->parent;
		  }
		  return temp;
	 }
	 void find(const string &arg)
	 {
		  int x;
		  cin >> x;
		  if (root == 0)
		  {
			   cout << 0 << endl;
			   return;
		  }
		  else
		  {
			   TYPE_NAME *curr = root;
			   while (curr != 0)
			   {
					if (curr->key == arg)
					{
					
					
						 node<int> *found = curr->pages.findNode(x);
						 if (found == NULL)
						 {
							  cout << 0 << endl;
							  return;
						 }
						 else
						 {
							  cout << 1 << endl;
							  return;
						 }
					}
					else
					{
						 if (arg > curr->key)
						 {
							  curr = curr->right;
						 }
						 else
						 {
							  curr = curr->left;
						 }
					}
			   }
			   cout << 0 << endl;
			   return;
		  }
	 }
	 void findAll(const string &arg)
	 {
		  if (root == 0)
		  {
			   cout << -1 << endl;
			   return;
		  }
		  else
		  {
			   TYPE_NAME *curr = root;
			   while (curr != 0)
			   {
					if (curr->key == arg)
					{
						 cout << curr->key << " ";
						 curr->pages.printO();
						 return;
					}
					else
					{
						 if (arg > curr->key)
						 {
							  curr = curr->right;
						 }
						 else
						 {
							  curr = curr->left;
						 }
					}
			   }
			   cout << -1 << endl;
			   return;
		  }
	 }
	 bool checkIfEmpty()
	 {
		  return root == 0;
	 }
};

template <class T>
struct nodeString
{
	 T key;
	 nodeString *parent = 0;
	 nodeString *left = 0;
	 nodeString *right = 0;
	 tree<int, node<int> > pages;
};

int main()
{

	 int commandsAmount;
	 char command;
	 tree<string, nodeString<string> > l;

	 //Pobieranie komend
	 std::cin >> commandsAmount;
	 string name;
	 int amountofPages;
	 int page;
	 for (int i = 0; i < commandsAmount; i++)
	 {

		  std::cin >> command;
		//  cout << "                 CMD: " << i << "  " << command << endl;
		  switch (command)
		  {
		  case 'I':
		  {
			   cin >> name;
			   nodeString<string> *tmp = l.insert(name);
			   cin >> amountofPages;
			   for (int i = 0; i < amountofPages; i++)
			   {
					cin >> page;
					tmp->pages.insert(page);
			   }
			   break;
		  }
		  case 'P':
		  {
			   l.print();
			   break;
		  }
		  case 'F':
		  {
			   cin >> name;
			   l.find(name);
			   break;
		  }
		  case 'A':
		  {
			   cin >> name;
			   l.findAll(name);
			   break;
		  }
		  case 'D':
		  {
			   string s;
			   int toBeDeleted;
			   int amountofdeleteditems;
			   int uselessInt;
			   cin >> s;
			   nodeString<string> * elementToBeDeleted = l.findNode(s);
			   cin >> amountofdeleteditems;
			   if (elementToBeDeleted == NULL)   // element nie znaleziony. wczytaj tylko dane..
			   {
					for (int i = 0; i < amountofdeleteditems; i++)
					{
						 cin >> uselessInt;
					}
			   }
			   else   // element znaleziony
			   {
					for (int i = 0; i<amountofdeleteditems; i++)
					{

						 cin >> toBeDeleted; // wczytaj inta do usuniecia
						 node<int> * pageToBeDeleted = elementToBeDeleted->pages.findNode(toBeDeleted); // sprawdz czy ten int jest na stronach hasła
						 if (pageToBeDeleted != NULL)
						 {
							  elementToBeDeleted->pages.rmv(pageToBeDeleted); // usuń go
						 }
					}
					if (elementToBeDeleted->pages.checkIfEmpty()) // jeśli hasło pozostałe puste to usuń go
					{

						 l.rmvName(elementToBeDeleted);
					}
			   }
			   break;
		  }
		  default:
		  {
			   break;
		  }
		  }
	 }
	 return 0;
}
