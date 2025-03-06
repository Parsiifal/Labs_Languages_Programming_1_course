#include <iostream>
#include <fstream>
using namespace std;

void multiplierOfElem(int** mtrx, size_t lines, size_t cols)
{
	int multiplier = 1;
	ofstream ofs_file("output.txt");

	for (long unsigned int i = 0; i < lines; i++) // находим произведение элементов матрицы по строкам
	{
		for (long unsigned int j = 0; j < cols; j++)
		{
			multiplier *= mtrx[i][j];
		}
		ofs_file << multiplier << " "; // выводим в файл
		multiplier = 1;
	}

	ofs_file.close();
}

int main()
{
	ifstream ifs_file("input.txt");
	size_t lines, cols;

	ifs_file >> lines >> cols; // читаем из файла количество строк и столбцов матрицы

	int** mtrx = new int*[lines]; // создаем двумерный динамический массив
	for (long unsigned int i = 0; i < lines; i++)
		mtrx[i] = new int[cols];

	for (long unsigned int i = 0; i < lines; i++) // читаем из файла элементы по строкам
		for (long unsigned int j = 0; j < cols; j++)
		{
			ifs_file >> mtrx[i][j];
		}
	
	ifs_file.close();

	multiplierOfElem(mtrx, lines, cols); // функция обработки в соответствии с заданием
	
	for (long unsigned int i = 0; i < lines; i++) // удаляем двумерный динамический массив
		delete[] mtrx[i];
	delete[] mtrx;
}