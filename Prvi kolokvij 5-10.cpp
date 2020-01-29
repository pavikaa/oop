#include <iostream>
#include <fstream>
class PriceHistory
{
	friend bool operator<(PriceHistory& ref1, PriceHistory& ref2);
	friend std::ostream& operator<<(std::ostream& output, PriceHistory& ref);
	double* mPrices;
	int mCount;
public:
	PriceHistory(int count, float price)
	{
		mCount = count;
		mPrices = new double[count];
		for (int i = 0; i < count; i++)
			mPrices[i] = price;
	}
	PriceHistory(const PriceHistory& ref)
	{
			mCount = ref.mCount;
			mPrices = new double[mCount];
			for (int i = 0; i < mCount; i++)
			{
				mPrices[i] = ref.mPrices[i];
			}
	}
	~PriceHistory()
	{
		delete[] mPrices;
	}
	PriceHistory& operator=(const PriceHistory ref)
	{
		if (this != &ref)
		{
			delete []mPrices;
			mCount = ref.mCount;
			for (int i = 0; i < mCount; i++)
			{
				mPrices[i] = ref.mPrices[i];
			}

		}
		return *this;
	}
	int trend();
};
std::ostream& operator<<(std::ostream& output, PriceHistory& ref)
{
	output << "Broj cijena: " << ref.mCount << std::endl<<"Cijene: "<<std::endl;
	for (int i = 0; i < ref.mCount; i++)
	{
		output << ref.mPrices[i]<<std::endl;
	}
	return output;
}
bool operator<(PriceHistory& ref1, PriceHistory& ref2)
{
	double sum1=0.0, sum2=0.0;
	for (int i = 0; i < ref1.mCount; i++)
	{
		sum1 += ref1.mPrices[i];
	}
	for (int i = 0; i < ref2.mCount; i++)
	{
		sum2 += ref2.mPrices[i];
	}
	return ((sum1 / ref1.mCount) < (sum2 / ref2.mCount));
}
void run()
{
	PriceHistory ikeaSofa(10, 3420.0);
	PriceHistory* primaSofa = new PriceHistory(ikeaSofa);
	delete primaSofa;
}
int PriceHistory::trend()
{
	double check;
	int pad = 0, rast = 0, neutral = 0;
	for (int i = 1; i < mCount; i++)
	{
		check = mPrices[0];
		if (mPrices[i] > check)
			rast++;
		else if (mPrices[i] < check)
			pad++;
		else if (mPrices[i] = check)
			neutral++;
		if (rast > pad&& rast > neutral)
			return 1;
		else if (pad > rast&& pad > neutral)
			return -1;
		else 
			return 0;
	}
	
}
void toFile(std::string name,PriceHistory& ref)
{
	std::fstream izlazna(name,std::ios::app);
	if (!izlazna.is_open())
		return;
	//izlazna << ref.toString() << std::endl;
	izlazna.close();

}
int main()
{
	
	PriceHistory ikeaSofa(10, 3420.0);
	PriceHistory appleStock(6, 74545), googleStock(10, 41656);
	if (appleStock < googleStock) std::cout << appleStock << " - Invest in apple.";
	else std::cout << googleStock << " - Invest in google.";
	return 0;
	toFile("datoteka.txt", ikeaSofa);
}