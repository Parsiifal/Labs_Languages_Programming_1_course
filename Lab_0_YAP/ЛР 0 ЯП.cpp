#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream file;
	file.open("input.txt");
	int a, b;
	file >> a >> b;
	file.close();
	int sum = a + b;
	ofstream file2;
	file2.open("output.txt");
	file2 << sum;
	file2.close();
}