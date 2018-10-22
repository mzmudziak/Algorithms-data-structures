#include <iostream>
#include <string>
using namespace std;

struct page {
	int value;
	page *next = NULL;
};

class pagesList {
private:
	page *head;
public:
	pagesList(): head(0) {}
	void insert(int);
	void insert(const pagesList &);
	void print();
	void remove(int);
	bool checkIfEmpty();
	void checkForPage(int);
	page* findE(int);
	void del(page*);
};

page* pagesList::findE(int s) {

	if (head == NULL)
	{
		return NULL;
	}
	if (head->value == s)
	{
		return head;
	}
	page* current = head->next;
	page* last = head;
	while (last->next != NULL)
	{
		if (current->value == s)
		{
			return current;
		}
		current = current->next;
		last = last->next;
	}
	return NULL;
}

void pagesList::del(page* p) {
	if (p == head)
	{
		head = head->next;
		delete p;
		return;
	}
	page* current = head->next;
	page* last = head; 
	while (current->next != NULL)
	{
		if (current == p)
		{
			last->next = current->next;
			delete p;
			return;
		}
		current = current->next;
		last = last->next;
	}
	last->next = NULL;
	delete p;
}

void pagesList::insert(int e) {
	page *newElement = new page;
	page *current;
	newElement->value = e;
	if (head == NULL) {
			newElement->next = head;
			head = newElement;
		} else
		if (head->value >= e) {
			if (head->value == e)
			{
				delete newElement;
				return;
			}
			else
				newElement->next = head;
				head = newElement;
		}
		else {
		current = head;
		while (current->next != NULL && current->next->value <= newElement->value) {
			
			current = current->next;
		}
		if (current->value == e) {
			delete newElement;

		} else
		{
			newElement->next = current->next;
			current->next = newElement;
		}
	}
}

void pagesList::insert(const pagesList &externalPagesList) {
	page *p;
	p = externalPagesList.head;
	while (p != NULL) {
		insert(p->value);
		p = p->next;
	}
}

void pagesList::print() {
	page *p;
	p = head;
	while (p != NULL) {
			std::cout << p->value<< " ";
			p = p->next;
	}
	std::cout << endl;
}

bool pagesList::checkIfEmpty() {
	return head == NULL;
}

void pagesList::checkForPage(int t) {
	page *p = head;
	while (p != NULL) {
		if (p->value == t)
		{
			cout << "1" << endl;
			return;
		}
		p = p->next;
	}
	cout << "0" << endl;
	return;
}

struct element{
	string name;
	pagesList pages;
	element *next = NULL;
};

class entriesList {
private:
	element *head;
public:
	entriesList() :head(NULL) {}
	~entriesList();
	void insert();
	void print();
	void find();
	void findAll();
	void remove();
	element* findE(string);
	void del(element*);
};

entriesList::~entriesList() {
	element* current = head;
	while (current != 0) {
		element* next = current->next;
		delete current;
		current = next;
	}
	head = 0;
}

void entriesList::insert() {
	//	DEKLARACJE POTRZEBNYCH ZMIENNYCH:
	element *newElement = new element;
	element *current;
	string tmp;
	int amountOfPages;
	int pageNum;

	// POBIERANIE HASŁA ORAZ STRON
	std::cin >> tmp;
	newElement->name = tmp;
	std::cin >> amountOfPages;
	for (int i = 0; i < amountOfPages;i++) {
		std::cin >> pageNum;
		newElement->pages.insert(pageNum);
	}

	// jesli pierwsza strona jest pusta, to ją utwórz!
	if (head == NULL)
	{
		newElement->next = head;
		head = newElement;
	}
	else if (head->name >= newElement->name)
	{
		if (head->name == newElement->name)
		{
			/*dodawanie do istniejącego hasła!!*/
			head->pages.insert(newElement->pages);
		}
		else
		{
			newElement->next = head;
			head = newElement;
		}
	}
	else
	{
		current = head;
		while (current->next != NULL && current->next->name <= newElement->name) {

			current = current->next;
		}
		if (current->name == newElement->name) {
			/*dodawanie do istniejącego hasła*/
			current->pages.insert(newElement->pages);
		}
		else
		{
			newElement->next = current->next;
			current->next = newElement;
		}
	}
}

void entriesList::print() {
	element *p;
	p = head;
	while (p !=  0) {
		std::cout << p->name << " ";
		p->pages.print();
		p = p->next;
		}
}

element* entriesList::findE(string s) {
	
		if (head == NULL)
		{
			return NULL;
		}
		if (head->name == s)
		{
			return head;
		}
		element* current = head->next;
		element* last = head;
		while (last->next != NULL)
		{
			if (current->name == s)
			{
				return current;
			}
			current = current->next;
			last = last->next;
		}
		return NULL;
}

void entriesList::del(element* p) {
	if (p == head)
	{
		head = head->next;
		delete p;
		return;
	}
	element* current = head->next;
	element* last = head;
	while (current->next != NULL)
	{
		if (current == p)
		{
			last->next = current->next;
			delete p;
			return;
		}
		current = current->next;
		last = last->next;
	}
	last->next = NULL;
	delete p;
}

void entriesList::find() {
	element *p;
	p = head;
	string s;
	cin >> s;
	int pageNum;
	cin >> pageNum;
	while (p != 0) {
		if (p->name == s) {
			p->pages.checkForPage(pageNum);
			return;
		}
		else
			p = p->next;
	}
	cout <<"0" << endl;
}

void entriesList::findAll() {
	element *p;
	string s;
	cin >> s;
	p = head;
	while (p != 0) {
		if (p->name == s) {
			cout << p->name << " ";
			p->pages.print();
			return;
		}
		else
			p = p->next;
	}
	cout << "-1" << endl;
	return;
}


int main()
{
	//Deklaracje zmiennych dla pobierania komend
	int commandsAmount;
	char command;
	entriesList l;

	//Pobieranie komend
	std::cin >> commandsAmount;
	for (int i = 0;i < commandsAmount;i++) {

		std::cin >> command;
		switch (command)
		{
			case 'I':
				{
					l.insert();
					break;
				}
			case 'P':
				{
					l.print();
					break;
				}
			case 'F':
				{
					l.find();
					break;
				}
			case 'A':
				{
					l.findAll();
					break;
				}
			case 'D':
			{
				string s;
				int toBeDeleted;
				int amountofdeleteditems;
				int uselessInt;
				cin >> s;
				element* elementToBeDeleted = l.findE(s);
				cin >> amountofdeleteditems;
				if (elementToBeDeleted == NULL) { // element nie znaleziony. wczytaj tylko dane.. 
					for (int i = 0;i < amountofdeleteditems;i++) {
						cin >> uselessInt;
					}
				} 
				else { // element znaleziony
					for (int i = 0; i<amountofdeleteditems; i++)
					{

						cin >> toBeDeleted; // wczytaj inta do usuniecia
						page* pageToBeDeleted = elementToBeDeleted->pages.findE(toBeDeleted); // sprawdz czy ten int jest na stronach hasła
						if (pageToBeDeleted != NULL)
						{
							elementToBeDeleted->pages.del(pageToBeDeleted); // usuń go
						}
					}
					if (elementToBeDeleted->pages.checkIfEmpty()) // jeśli hasło pozostałe puste to usuń go
					{
						l.del(elementToBeDeleted);
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

/*
I ANNA 10 1 2 3 4 5 6 7 8 9 10
I ANNB 10 1 2 3 4 5 6 7 8 9 10
I ANNC 10 1 2 3 4 5 6 7 8 9 10
P

D ANNA 3 1 5 10
P

D ANNB 3 1 5 10
P

D ANNC 3 1 5 10
P

D ANNA 6 2 3 4 6 7 8 
P

D ANNB 6 2 3 4 6 7 8 
P

D ANNC 6 2 3 4 6 7 8 
P

D ANNA 1 9
P

D ANNB 1 9
P

D ANNC 1 9
P

*/
