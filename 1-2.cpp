#include <iostream>
#include <ctime>
template<typename T>
double funkcija(T* polje, int n,int donjaGranica,int gornjaGranica)
{
	if (donjaGranica > gornjaGranica)
		std::swap(donjaGranica, gornjaGranica);
	int elementi = 0;
	for (int i = 0; i < n; i++)
	{
		if (polje[i]<donjaGranica || !(polje[i]<gornjaGranica))
			elementi++;
	}
	double rezultat = 100 * elementi / n;
	return rezultat;
}
class Money {
	friend bool operator< (const Money&, const int);
	int mAmount;
	public:
	Money(int amount) : mAmount(amount) {}
	Money() : mAmount(0) {}
};
bool operator <(const Money& ref, int value)
{
	return ref.mAmount < value;
}
int main()
{
	srand(time(NULL));
	int n = 1000;
	Money *polje=new Money[n];
	for (int i = 0; i < n; i++)
	{
		polje[i] = Money(rand());
	}
	std::cout << funkcija(polje, n, 5000, 10000);
}