#include <iostream>
#include <string>
#include <ctime>
double getRandomDouble(double lowerBound, double upperBound) {
	if (lowerBound > upperBound) {
		std::swap(lowerBound, upperBound);
	}
	double factor = (double)rand() / RAND_MAX;
	return lowerBound + factor * (upperBound - lowerBound);
}
int getRandomInt(int lowerBound, int upperBound) {
	if (lowerBound > upperBound) {
		std::swap(lowerBound, upperBound);
	}
	return lowerBound + rand() % (upperBound - lowerBound);
}
class Enemy {
	std::string mName;
	int mHealth;
	int mAttackDamage;
public:
	Enemy(std::string name, int health, int attackDamage) :mName(name), mHealth(health), mAttackDamage(attackDamage) {}
	int getAttackDamage() const { return mAttackDamage; }
	int getHealth() const { return mHealth; }
	std::string getName() const { return mName; }
	virtual void heal(int amount);
	virtual void takeDamage(int amount) = 0;
};
void Enemy::heal(int amount)
{
	if (this->mHealth > 0)
		this->mHealth += amount;
}
class ShieldedEnemy : public Enemy
{
	double mhitProbability;
	int mshieldHealth;
public:
	ShieldedEnemy(std::string name, int attackDamage, double hitProbability, int shieldHealth) :Enemy(name, 100, attackDamage), mhitProbability(hitProbability), mshieldHealth(shieldHealth) {}
	ShieldedEnemy() :Enemy("Default", 100, 50), mhitProbability(0.5), mshieldHealth(100) {}
	int getShieldHealth() const { return mshieldHealth; }
	double getHitProbability() const { return mhitProbability; }
	void takeDamage(int);
};
void ShieldedEnemy::takeDamage(int amount)
{
	double r = getRandomDouble(0, 1);
	if (r < mhitProbability)
		return;
	else
	{
		if (mshieldHealth - amount >= 0)
			mshieldHealth -= amount;
		else if (mshieldHealth - amount < 0)
		{
			int healthDamage = amount - mshieldHealth;
			mshieldHealth = 0;
			heal(-healthDamage);
		}
	}
}
class IllegalEnemyException :public std::runtime_error
{
	Enemy* enemy;
public:
	IllegalEnemyException(std::string message, Enemy* enemy) :std::runtime_error(message), enemy(enemy) {}
	std::string getEnemyName() const { return enemy->getName(); }
	int getEnemyHealth() const { return enemy->getHealth(); }
	int getEnemyAttackDamage() const { return enemy->getAttackDamage(); }
};
Enemy** createEnemies(const int n)
{
	Enemy** data = new Enemy * [n];
	for (int i = 0; i < n; i++)
	{
		int attackDamage = getRandomInt(0, 100);
		int shieldHealth = getRandomInt(0, 100);
		double hitProbability = getRandomDouble(0, 1);
		try
		{
			data[i] = new ShieldedEnemy("Enemy" + std::to_string(i + 1), attackDamage, hitProbability, shieldHealth);
			if (data[i]->getAttackDamage() < 50)
			{
				throw(IllegalEnemyException("Attack damage too low", data[i]));
			}
		}
		catch (const IllegalEnemyException & e)
		{
			i--;
			std::cout << e.what() << ", " << e.getEnemyName() << ", " << e.getEnemyHealth() << ", " << e.getEnemyAttackDamage() << std::endl;
		}
	}
	return data;
}
int runBattle(Enemy** enemies1, Enemy** enemies2)
{
	int n = 5;
	for (int i = 0; i < n; i++)
	{
		enemies2[getRandomInt(0, n)]->takeDamage(enemies1[i]->getAttackDamage());
	}
	for (int i = 0; i < n; i++)
	{
		enemies1[getRandomInt(0, n)]->takeDamage(enemies2[i]->getAttackDamage());
	}
	int counter1 = 0, counter2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (enemies1[i]->getHealth() > 0)
			counter1++;
		if (enemies2[i]->getHealth() > 0)
			counter2++;
	}
	
	if (counter1 > counter2)
		return 1;
	if (counter1 < counter2)
		return 2;
	else
		return 0;
}
int main()
{
	srand(time(NULL));
	Enemy** enemies1 = createEnemies(5);
	Enemy** enemies2 = createEnemies(5);
	std::cout << runBattle(enemies1, enemies2);
	for (int i = 0; i < 5; i++)
	{
		delete enemies1[i];
		delete enemies2[i];
	}
	delete enemies1;
	delete enemies2;
}
