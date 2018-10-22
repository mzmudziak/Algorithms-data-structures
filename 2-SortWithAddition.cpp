#include <iostream>
using namespace std;

class singleElement
{
private:
    unsigned int value;
    unsigned int count;
public:
    unsigned int getValue();
    unsigned int getCount();
    void setData();
    singleElement& operator=(const singleElement&);
    singleElement& operator+=( singleElement&);
    bool operator==(const singleElement&);
};

unsigned int singleElement::getValue()
{
    return this->value;
}

unsigned int singleElement::getCount()
{
    return this->count;
}

void singleElement::setData()
{
    cin >> this->value;
    cin >> this->count;
}

singleElement& singleElement::operator=(const singleElement &temp)
{
    value = temp.value;
    count = temp.count;
    return *this;
}

singleElement& singleElement::operator+=( singleElement &temp)
{
    count += temp.count;
    return *this;
}

bool singleElement::operator==(const singleElement &temp)
{
    if (this->value == temp.value)
    {
        return true;
    }
    else return false;
}

class container
{
private:
    singleElement *myArray;
    int arraySize;
public:
    container();
    container(int);
    ~container();
    void setSize();
    void setSize(int);
    int getSize();
    void fillArray();
    void listElements();
    void swapElements(int,int);
    bool checkSort();
    static container mergeArrays(container [], int, int);
    void searchValues(int, int, int);
    void sortArrays(int,int);
    container& operator=(const container&);
    container addDuplicates();
};




container& container::operator=(const container &other)
{
    arraySize = other.arraySize;
    for (int i=0; i<other.arraySize; i++)
    {
        myArray[i] = other.myArray[i];
    }
    return *this;
}
container::container()
{
}
container::container(int temp)
{
    this->arraySize = temp;
    myArray = new singleElement[temp];
}
container::~container()
{
    delete []myArray;
}

void container::setSize()
{
    cin >> arraySize;
    myArray = new singleElement[this->arraySize];
}
void container::setSize(int tmp)
{
    myArray = new singleElement[tmp];
}

int container::getSize()
{
    return this->arraySize;
}

void container::fillArray()
{
    for (int i=0; i<arraySize; i++)
    {
        myArray[i].setData();
    }
}

void container::listElements()
{
    cout << arraySize << " ";
    for (int i=0; i<arraySize; i++)
    {
        cout << myArray[i].getValue() << " " << myArray[i].getCount() << " ";
    }
}

bool container::checkSort()
{
    for(int i=0; i<arraySize; i++)
    {
        if (myArray[i].getValue() >  myArray[i+1].getValue())
        {
         return false;
        }
    }
    return true;
}

void container::swapElements(int l, int r)
{
    singleElement temp;
    temp = myArray[l];
    myArray[l] = myArray[r];
    myArray[r] = temp;
}

void container::sortArrays(int l, int r) {
      int i = l, j = r;
      int tmp;
      int x = (l + r)/2;
      int pivot = myArray[x].getValue();
      while (i <= j) {
            while (myArray[i].getValue() < pivot)
                  i++;
            while (myArray[j].getValue() > pivot)
                  j--;
            if (i <= j) {
                    swapElements(i,j);
                  i++;
                  j--;
            }
      };
      if (l < j)
            sortArrays(l, j);
      if (i < r)
            sortArrays(i, r);
}

container container::addDuplicates()
{
    int j=0;
    container tempArray(arraySize);
    for (int i=0; i<arraySize; i++)
    {
        if (myArray[i].getValue() == myArray[i-1].getValue())
        {
            if (tempArray.myArray[j-1].getValue() == myArray[i].getValue())
            {
                tempArray.myArray[j-1] += myArray[i];
            }
            else
                tempArray.myArray[j] += myArray[i];
        }
        else
        {
            tempArray.myArray[j] = myArray[i];
            j++;
        }
    }
    tempArray.arraySize = j;
    return tempArray;
}

container container::mergeArrays(container arrays[], int count, int suma)
{
    int wsk[count];
    for (int i=0; i<count; i++)
    {
        wsk[i] = 0;
    }
    container temp(suma);
    unsigned int min;
    int min_i;
    int t=0;
    while(t<suma)
    {
        min = 4294967295;
        for (int i=0; i<count; i++)
        {
            if (wsk[i] < arrays[i].getSize())
            {
                if (arrays[i].myArray[wsk[i]].getValue() < min)
                {
                    min = arrays[i].myArray[wsk[i]].getValue();
                    min_i = i;
                }
            }
        }
        temp.myArray[t] = arrays[min_i].myArray[wsk[min_i]];
        wsk[min_i]++;
        t++;
    }
    return temp;
}

void container::searchValues(int p, int k, int n)
{
    //ITERACYJNY

    int s;        // SRODEK TABLICY
    while (p <=k)   // DOPOKI POCZATEK TABLICY JEST MNIEJSZY LUB ROWNY OD KONCA TABLICY
    {
        s =(p+k)/2;  // OBIERANIE SRODKA
        if (n== myArray[s].getValue())  // JESLI ELEMENT ZNALEZIONY TO WYPISZ GO
        {
            cout << myArray[s].getCount() << " ";
            break;
        }
        else if (n<myArray[s].getValue())  // JESLI NIE ZNALEZIONY I MNIEJSZY TO SZUKAJ PO LEWEJ STRONIE OD SRODKA (KONIEC = SRODEK-1)
            k  = s - 1;
        else
            p = s + 1; // JESLI NIE ZNALEZIONY I WIEKSZY TO SZUKAJ PO PRAWEJ STRONIE OD ŚRODKA
    }
    if (k<p)  // JESLI NIE ZNALEZIONO W CALEJ TABLICY TO WYPISZ 0
    {
        cout << "0 ";
    }
}

int main()
{
    // POBRANIE ILOSCI TABLIC
    int arrayCount=0;
    cin >> arrayCount;
    container arraysContainer[arrayCount];

    // WCZYTANIE WARTOSCI DO TABLIC
    for (int i=0; i<arrayCount; i++)
    {
        arraysContainer[i].setSize();
        arraysContainer[i].fillArray();
    }

    // POBRANIE ILOSCI WARTOSCI DO SZUKANIA
    int amountOfSearchedElements;
    cin >> amountOfSearchedElements;
    int searchN[amountOfSearchedElements];

    // POBIERANIE WARTOSCI DO SZUKANIA
    for (int i=0; i<amountOfSearchedElements; i++)
    {
        cin >> searchN[i];
    }

    // SORTOWANIE sortArrays JESLI NIE JEST POSORTOWANA
   for (int i=0; i<arrayCount; i++)
    {
       if (arraysContainer[i].checkSort() == false)
        {
            arraysContainer[i].sortArrays(0,arraysContainer[i].getSize()-1);
        }
    }

    // MERGE'OWANIE USUWANIE DUPLIKATÓW ORAZ POBIERANIE #SUMA <- WIELKOSC BEDACA ROZMIAREM NOWEJ TABLICY ZMERGE'OWANEJ
    int suma=0;
    container arraysWithNoDup[arrayCount];
    for (int i=0; i<arrayCount; i++)
    {
        arraysWithNoDup[i].setSize(arraysContainer[i].addDuplicates().getSize()); // NADANIE ROZMIARU
        arraysWithNoDup[i] = arraysContainer[i].addDuplicates();  // PRZYPISYWANIE TABLICY Z USUNIETYMI POWTORZENIAMI
        suma += arraysWithNoDup[i].getSize();  // ZLICZANIE SUMY ROZMIAROW
        arraysWithNoDup[i].listElements(); // WYPISYWANIE ELEMENTOW
        cout << endl;
    }

    // NOWY OBIEKT Z TABLICA O ROZMIARZE SUMA
    container merged(suma);
    merged = container::mergeArrays(arraysWithNoDup,arrayCount, suma);     // MERGOWANIE WSZYSTKICH TABLIC DO JEDNEJ
    merged = merged.addDuplicates();                            // USUWANIE DUPLIKATÓW
    merged.listElements();                       // WYPISYWANIE ELEMENTOW TABLICY ZMERGOWANEJ
    cout << endl;

    // WYSZUKIWANIE BINARNE DLA KAZDEJ LICZBY Z TABLICY searchN[]
    for (int i=0; i<amountOfSearchedElements; i++)
    {
        merged.searchValues(0, merged.getSize()-1 ,searchN[i]);
    }
    return 0;
}
