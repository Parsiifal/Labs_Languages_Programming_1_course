#include <iostream>
#include <string>
#include <fstream>
using namespace std;

char check_S_E()
{
	string inp;
	bool state = true;

	while (state)
	{
		getline(cin, inp);

		if (inp.size() == 1 && (inp[0] == 'S' || inp[0] == 'E'))
		{
			state = false;
		}
		else
			cout << "\nMistake! Repeat the input: ";

	}
	return inp[0];
}

int main()
{
	cout << "\nEnter S to execute the program, or E to terminate the program: ";
	char work = check_S_E();

	if (work == 'S')
	{
		ifstream file;
		file.open("Bonus task 01.cpp");

		if (file.is_open())
		{
			cout << "\nThe result of the program: \n" << endl;
			string line;
			while (getline(file, line))
			{
				cout << line << endl;
			}

			file.close();
		}
		else
		{
			cout << "\nThe file is not open! Something went wrong!\n";
		}

	}

}