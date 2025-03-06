#include <iostream>
#include <fstream>
using namespace std;

struct List
{
	int numbers;
	List* prev, * next;

	List(int numbers)
	{
		this->numbers = numbers;
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

	List* push_back(int numbers) // добавить элемент в конец
	{
		List* ptr = new List(numbers);
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

	void fileInput(ifstream& ifs) // ввод списка из файла
	{
		while (!ifs.eof())
		{
			int d;
			ifs >> d;
			push_back(d);		
		}
	}

	int size() // вычисление размера списка
	{
		int size = 0;
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
				if(left->next) // если левый элемент не последний
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
			if (buf->numbers < min->numbers)
			{
				min = buf;
			}
			buf = buf->next;
		}
	
		if (current_element != min) // cделаем перестановку указателей такущей ячейки и ячейки с минимальным элементом
		{
			lst.exchangeOfPointers(current_element, min); // функция обмена указателей
		}

		delete buf;
	}
	
}


int main()
{
	ifstream ifs("input.txt");

	int key; // считывание ключа
	ifs >> key;

	LinkedList lst;

	lst.fileInput(ifs); // чтение элементов из файла в список

	int list_size = lst.size(); // размер списка

	ifs.close();

	key == 1 ? selectionSort(lst) : (void)0; // выбор метода сортировки
   
	ofstream ofs("output.txt");

	ofs << list_size << " "; // вывод размера списка в файл

	for (List* ptr = lst.head; ptr; ptr = ptr->next) // вывод списка в файл
	{
		ofs << ptr->numbers << " ";
	}
	
	ofs.close();

	lst.~LinkedList(); // вызов деструктора для удаления списка
}