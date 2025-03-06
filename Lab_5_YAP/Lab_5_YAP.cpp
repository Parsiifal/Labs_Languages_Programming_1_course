#include <iostream>
#include <fstream>
using namespace std;

class Fraction
{
private:

	int numerator; // числитель
	int denominator; // знаменатель

	int NOD(int num, int den) // нахождение наибольшего общего делителя двух чисел
	{
		int mod = 1;

		if (num == 0 || den == 0)
			return 0;

		// находим модуль в случае отрицательного числа
		num = abs(num);
		den = abs(den);

		// частные случаи:
		if (num == den)
			return num;
		if (den > num)
		{
			mod = num; num = den; den = mod;
		}
		if (den == 0)
			return num;

		while (mod)
		{
			mod = num % den;
			if (mod)
			{
				num = den;
				den = mod;
			}
		}
		return den;
	}

public:

	Fraction() // конструктор по умолчанию
	{
		numerator = 0;
		denominator = 1; 
	}

	Fraction(const Fraction& fraction) // конструктор копирования
	{
		numerator = fraction.numerator;
		denominator = fraction.denominator;
	}

	Fraction(int a, int b) // конструктор инициализации
	{
		numerator = a;
		denominator = b;
	}

	~Fraction() {}; // деструктор

	// Перегрузка операции присваивания:
	Fraction operator=(const Fraction& fraction);

	// Перегрузка арифметических операций:
	Fraction operator+(const Fraction& fraction);
	Fraction operator-(const Fraction& fraction);
	Fraction operator*(const Fraction& fraction);
	Fraction operator/(const Fraction& fraction);

	// Перегрузка сравнения:
	bool operator>(const Fraction& fraction);
	bool operator<(const Fraction& fraction);
	bool operator<=(const Fraction& fraction);
	bool operator>=(const Fraction& fraction);
	bool operator==(const Fraction& fraction);

	// Перегрузка потоков:
	friend istream& operator>>(istream& is, Fraction& fraction);
	friend ostream& operator<<(ostream& os, const Fraction& fraction);


	double decimalFraction() // представление в виде десятичной дроби
	{ 
		return (double)numerator / (double)denominator; 
	} 

	Fraction operator-() // перегрузка оператора - для сокращения дроби
	{
		int nod = NOD(numerator, denominator);
		if (nod > 0)
		{
			numerator /= nod;
			denominator /= nod;
		}
		return *this;
	}
	
};

istream& operator>>(istream& is, Fraction& fraction) // перегрузка ввода
{
	is >> fraction.numerator >> fraction.denominator;
	return is;
}

ostream& operator<<(ostream& os, const Fraction& fraction) // перегрузка вывода
{
	os << fraction.numerator << "/" << fraction.denominator;
	return os;
}

Fraction Fraction::operator=(const Fraction& fraction) // перегрузка операции присваивания
{
	numerator = fraction.numerator;
	denominator = fraction.denominator;
	return *this;
}

// АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ:

Fraction Fraction::operator+(const Fraction& fraction) // сложение дробей
{
	int num_sum = numerator * fraction.denominator + fraction.numerator * denominator; // числитель суммы
	int denom_sum = denominator * fraction.denominator; // знаменатель суммы
	Fraction sum(num_sum, denom_sum); // сумма дробей
	return sum;
}

Fraction Fraction::operator-(const Fraction& fraction) // вычитание дробей
{
	int num_diff = numerator * fraction.denominator - fraction.numerator * denominator; // числитель разности
	int denom_diff = denominator * fraction.denominator; // знаменатель разности
	Fraction diff(num_diff, denom_diff); // разность дробей
	return diff;
}

Fraction Fraction::operator*(const Fraction& fraction) // умножение дробей
{
	return Fraction(numerator * fraction.numerator, denominator * fraction.denominator);
}

Fraction Fraction::operator/(const Fraction& fraction) // деление дробей
{
	return Fraction(numerator * fraction.denominator, denominator * fraction.numerator);
}

// ОПЕРАЦИИ СРАВНЕНИЯ:

bool Fraction::operator>(const Fraction& fraction)
{
	return (numerator * fraction.denominator > fraction.numerator * denominator);
}

bool Fraction::operator<(const Fraction& fraction)
{
	return (numerator * fraction.denominator < fraction.numerator * denominator);
}

bool Fraction::operator<=(const Fraction& fraction)
{
	return (numerator * fraction.denominator <= fraction.numerator * denominator);
}

bool Fraction::operator>=(const Fraction& fraction)
{
	return (numerator * fraction.denominator >= fraction.numerator * denominator);
}

bool Fraction::operator==(const Fraction& fraction)
{
	return (numerator == fraction.numerator && denominator == fraction.denominator);
}


int main() 
{
	int key = 0; //ключ

	ifstream ifs("input.txt");
	ofstream ofs("output.txt");

	ifs >> key;

	switch (key)
	{
	case 1: // конструктор по умолчанию
	{
		Fraction F;
		ofs << F;
		break;
	}
	case 2: // конструктор копирования
	{
		Fraction F;
		ifs >> F;
		Fraction G(F);
		ofs << G;
		break;
	}
	case 3: // конструктор инициализации
	{
		int a, b;
		ifs >> a >> b;
		Fraction F(a, b);
		ofs << F;
		break;
	}
	case 4: // присваивание
	{
		Fraction F;
		ifs >> F;
		Fraction G;
		G = F;
		ofs << G;
		break;
	}
	case 5: // рациональное представление
	{
		Fraction F;
		ifs >> F;
		ofs << F;
		break;
	}
	case 6: // десятичное представление
	{
		Fraction F;
		ifs >> F;
		ofs << F.decimalFraction();
		break;
	}
	case 7: // арифметические операции
	{
		Fraction F, G;
		ifs >> F >> G;
		ofs << F + G << "\n";
		ofs << F - G << "\n";
		ofs << F * G << "\n";
		ofs << F / G << "\n";
		break;
	}
	case 8: // сокращение дроби
	{
		Fraction F;
		ifs >> F;
		ofs << -F;
		break;
	}
	case 9: // сравнение дробей
	{
		Fraction F, G;
		ifs >> F >> G;
		if (F > G)
			ofs << F << " > " << G;
		else if (F < G)
			ofs << F << " < " << G;
		else if (F <= G)
			ofs << F << " <= " << G;
		else if (F >= G)
			ofs << F << " >= " << G;
		else if (F == G)
			ofs << F << " == " << G;
		break;
	}
	}

	ifs.close();
	ofs.close();
}