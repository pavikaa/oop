#include <iostream>
#include <ctime>
template<typename T>
double funkcija(T* polje, int n,T donjaGranica,T gornjaGranica)
{
	if (donjaGranica > gornjaGranica)
		std::swap(donjaGranica, gornjaGranica);
	double elementi = 0;
	for (int i = 0; i < n; i++)
	{
		if (polje[i]<=donjaGranica || polje[i]>=gornjaGranica)
			elementi++;
	}
	double rezultat =(double) 100 * elementi / n;
	return rezultat;
}
class Money {
	friend bool operator<= (const Money&, const Money&);
	friend bool operator> (const Money&, const Money&);
	friend bool operator>= (const Money&, const Money&);
	int mAmount;
	public:
	Money(int amount) : mAmount(amount) {}
	Money() : mAmount(0) {}
};
bool operator <=(const Money& ref1,const Money& ref2)
{
	return (ref1.mAmount <=ref2.mAmount);
}
bool operator >=(const Money& ref1, const Money& ref2)
{
	return (ref1.mAmount >= ref2.mAmount);
}
bool operator >(const Money& ref1, const Money& ref2)
{
	return (ref1.mAmount > ref2.mAmount);
}
int main()
{
	srand(time(NULL));
	int n = 10;
	Money *polje=new Money[n];
	for (int i = 0; i < n; i++)
	{
		polje[i] = Money(rand());
	}
	std::cout << funkcija(polje, n, Money(5000), Money(10000));
}
