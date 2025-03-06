#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void numberOfElements(int& n, string elements) // счёт числа элементов в файле
{
	while (!elements.empty())
	{
		string elem;
		size_t b = elements.find(' ');
		elem = (b != string::npos) ? elements.substr(0, b) : elements;
		elements.erase(0, elem.size() + 1);
		n++;
	}
}

void arrayFilling(double* array, string& elements, int n, bool& element_with_a_minus) // заполнение массива и проверка существования хотя бы одного отрицательного элемента
{
	for (int i = 0; i < n; ++i)
	{
		string elem;
		size_t b = elements.find(' ');
		elem = (b != string::npos) ? elements.substr(0, b) : elements;
		elements.erase(0, elem.size() + 1);

		array[i] = stod(elem);
		array[i] < 0 ? element_with_a_minus = true : 0;
	}
}

void arrayProcessing(double* array, double& multiplier, int n) // обработка массива
{
	for (int i = 0; i < n; ++i)
	{
		if (array[i] < 0)
		{
			multiplier *= array[i] * array[i];
		}
	}

}


int main()
{
	ifstream file_in;
	file_in.open("input.txt");

	string elements;
	getline(file_in, elements);  // получаем все элементы из файла

	file_in.close();
	int n = 0;

	numberOfElements(n, elements);	// счёт числа элементов в файле

	double* array = new double[n]; // объявление массива
	bool element_with_a_minus = false; // переключатель для проверки существования отрицательного элемента

	arrayFilling(array, elements, n, element_with_a_minus); // заполнение массива

	double multiplier = 0;

	if (element_with_a_minus == true) // если есть хотя бы один отрицательный элемент делаем обработку
	{
		multiplier = 1;
		arrayProcessing(array, multiplier, n);  // обработка массива
	}

	delete[] array; // удаление массива

	ofstream file_out;
	file_out.open("output.txt");

	file_out << multiplier;

	file_out.close();
}