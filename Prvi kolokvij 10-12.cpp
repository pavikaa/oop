#include <iostream>
#include<cstdlib>
#include<ctime>
class Sensor
{
	std::string mName;
	bool mIsActive;
public:
	double mPreviousRead;

	Sensor(std::string mName) :mName(mName) {}
	double getCurrentRead()
	{
		float random = (float)rand() / RAND_MAX * (10);
		mPreviousRead = random;
		return random;

	}
	void onOffSwitch()
	{
		mIsActive != mIsActive;
	}
};
int main()
{
	srand(time(NULL));
	Sensor accelerationSensor("Acceleration");
	std::cout << accelerationSensor.getCurrentRead()<< std::endl;
	std::cout << accelerationSensor.getCurrentRead() <<" "<< accelerationSensor.mPreviousRead << std::endl;

}