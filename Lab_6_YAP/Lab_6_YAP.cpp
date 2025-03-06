#include <iostream>
#include <fstream>
using namespace std;

class Fraction
{
private:

	int numerator; // числитель
	int denominator; // знаменатель

public:

	Fraction() // конструктор по умолчанию
	{
		numerator = 0;
		denominator = 1;
	}

	~Fraction() {}; // деструктор

	// Перегрузка операции присваивания:
	Fraction operator=(const Fraction& fraction);

	// Перегрузка сравнения: 
	bool operator<(const Fraction& fraction);
	bool operator>(const Fraction& fraction);
	bool operator!=(const Fraction& fraction);

	void Set_numerator(int bar) 
	{
		numerator = bar;
	}
	void Set_denominator(int bar) 
	{
		denominator = bar;
	}

};

// ПЕРЕГРУЗКИ:
Fraction Fraction::operator=(const Fraction& fraction) // перегрузка операции присваивания
{
	numerator = fraction.numerator;
	denominator = fraction.denominator;
	return *this;
}

bool Fraction::operator<(const Fraction& fraction)
{
	return (numerator * fraction.denominator < fraction.numerator* denominator);
}

bool Fraction::operator>(const Fraction& fraction)
{
	return (numerator * fraction.denominator > fraction.numerator * denominator);
}

bool Fraction::operator!=(const Fraction& fraction)
{
	return (numerator != fraction.numerator && denominator != fraction.denominator);
}


struct List
{
	Fraction fract;
	List* prev, * next;

	List(Fraction fract)
	{
		this->fract = fract;
		this->prev = this->next = NULL;
	}

};

struct LinkedList
{
	List* head, * tail;

	LinkedList()
	{
		head = tail = NULL;
	}

	~LinkedList()
	{
		while (head != NULL)
			pop_front();
	}

	// методы, которые будут отвечать за операции с двусвязным списком:

	List* push_back(Fraction fract) // добавить элемент в конец
	{
		List* ptr = new List(fract);
		ptr->prev = tail;

		if (tail != NULL) // если в списке уже есть объекты
			tail->next = ptr;

		if (head == NULL) // если добавляем первый объект в список
		{
			head = ptr;
		}

		tail = ptr; // конец указывает на добавленный объект
		return ptr;
	}

	void pop_front() // удаление элемента с начала списка
	{
		head->fract.~Fraction(); // вызов деструктора объекта

		if (head == NULL)
			return;
		List* ptr = head->next;
		if (ptr != NULL)
			ptr->prev = NULL;
		else
			tail = NULL;

		delete head;
		head = ptr;
	}

	size_t size() // вычисление размера списка
	{
		size_t size = 0;
		for (List* ptr = head; ptr; ptr = ptr->next)
		{
			size++;
		}
		return size;
	}

	void exchangeOfPointers(List* left, List* right) // функция обмена указателей
	{
		if (left->next == right) // ЕСЛИ ЭЛЕМЕНТЫ СТОЯТ РЯДОМ
		{
			if (right == tail) // если правый элемент последний то последним станет левый элемент
				tail = left;

			if (!left->prev) // если левый элемент первый в списке
			{
				head = right;
				right->prev = 0;
				left->prev = right;
				left->next = right->next;
				if (right->next) // если правый элемент не последний, указать следующему, что у него новый элемент слева
					right->next->prev = left;
				right->next = left;
			}
			else // если же левый елемент не первый в списке
			{
				right->prev = left->prev;
				left->prev->next = right;
				if (right->next) // если правый элемент не последний, указать следующему, что у него новый элемент слева
					right->next->prev = left;
				left->next = right->next;
				right->next = left;
				left->prev = right;
			}

		}
		else // ЕСЛИ ЭЛЕМЕНТЫ СТОЯТ НЕ РЯДОМ
		{
			List* buf_right = new List(*right); // создадим копию указателя right

			if (!left->prev) // если левый элемент первый в списке
			{
				head = right;
				right->prev = NULL;
				right->next = left->next;
				left->next->prev = right;
				left->prev = buf_right->prev;
				buf_right->prev->next = left;
				if (buf_right->next) // если правый элемент не последний 
				{
					left->next = buf_right->next; // next левого элемента присвоить next правого
					buf_right->next->prev = left; // указать следующему правого, что у него новый элемент слева
				}
				else
				{
					left->next = NULL;
					tail = left;
				}
			}
			else // если же левый елемент не первый в списке
			{
				right->prev = left->prev;
				left->prev->next = right;
				right->next = left->next;
				if (left->next) // если левый элемент не последний
					left->next->prev = right; // указать следующему левого, что у него новый элемент слева
				left->prev = buf_right->prev;
				buf_right->prev->next = left;
				if (buf_right->next) // если правый элемент не последний 
				{
					left->next = buf_right->next; // next левого элемента присвоить next правого
					buf_right->next->prev = left; // указать следующему правого, что у него новый элемент слева
				}
				else
				{
					left->next = NULL;
					tail = left;
				}
			}

			delete buf_right;

		}
	}

};


// СОРТИРОВКА:
void selectionSort(LinkedList& lst) // сортировка выбором
{
	List* current_element; // создадим указатель текущей ячейки
	List* buf; // создадим указатель для копирования
	List* min; // создадим указатель, в который будем записывать указатель на ячейку с минимальным значением

	for (List* ptr = lst.head; ptr; ptr = ptr->next)
	{
		current_element = new List(*ptr); // запомним указатель текущей ячейки		 
		buf = new List(*current_element); // создадим копию указателя текущей ячейки
		min = buf;

		while (buf) // найдем указатель ячейки с минимальным элементом и запишем в min
		{
			if (buf->fract < min->fract)
			{
				min = buf;
			}
			buf = buf->next;
		}

		if (current_element->fract != min->fract) // cделаем перестановку указателей такущей ячейки и ячейки с минимальным элементом
		{
			lst.exchangeOfPointers(current_element, min); // функция обмена указателей
		}

		delete buf;
	}

}


Fraction createRandomObject() // создание объекта со случайными параметрами
{
	Fraction fract;
	fract.Set_numerator(rand());
	fract.Set_denominator(rand());
	return fract;
}

bool check_Sort(List* head) // проверка факта упорядоченности структуры
{
	bool correct = true; // флаг корректности упорядочивания

	for (List* ptr = head; ptr; ptr = ptr->next) 
	{
		if (ptr != head && (ptr->prev->fract > ptr->fract))
		{
			correct = false;
		}
	}

	return correct;
}


int main()
{
	srand(time(NULL));

	ifstream ifs("input.txt");

	int size; // считывание числа объектов
	ifs >> size;

	ifs.close();

	LinkedList lst;

	for (int i = 0; i < size; i++) // заполняем список объектами со случайными параметрами
	{
		lst.push_back(createRandomObject()); // создание объекта со случайными параметрами и добавление в конец списка
	}
	
	selectionSort(lst); // сортировка списка выбором

	if (check_Sort(lst.head)) // проверка факта упорядоченности структуры и вывод в консоль
	{
		cout << "Correctly sorted!" << endl;
	}
	else
	{
		cout << "NOT correctly sorted!" << endl;
	}

	ofstream ofs("output.txt");

	ofs << lst.size(); // вывод в файл числа элементов отсортированного списка

	ofs.close();

	lst.~LinkedList(); // вызов деструктора для удаления списка
}