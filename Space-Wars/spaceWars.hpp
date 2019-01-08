#ifndef trekHeader
#define trekHeader

#include <iostream>
#include <string>
using namespace std;

enum Alignment { us, them, chaotic };

class Ship
{
public:

	Ship(string name, int x, int y, Alignment align, int maxHeal, int rng, int attackPwr)
	{
		this->name = name;
		xLoc = x;
		yLoc = y;
		this->align = align;
		maxHealth = maxHeal;
		range = rng;
		attackPower = attackPwr;
		currHealth = maxHeal;
	}
	virtual void attack(Ship* target)
	{ //Pre-Condition: target must be of class Ship*
      //Post-Condition: target->getHeatlth() - [0, maxHealth]
		double inRange = 0;
		inRange = sqrt((pow((this->getY() - target->getY()), 2)) + (pow((this->getX() - target->getX()), 2)));
		if (inRange < this->range  && this->getAlign() != chaotic && target->getAlign() != this->getAlign())
			if (this->getHealth() > 0 && target->getHealth() > 0)
				target->accessDamage(this->attackPower);
		else if ((inRange < this->range && this->getAlign() == chaotic))
			if (this->getHealth() > 0 && target->getHealth() > 0)
				target->accessDamage(this->attackPower);
	}
	int getX() { return xLoc; }; //Pre-Condition: xLoc and yLox must be intergal 
	int getY() { return yLoc; }; //Pre-Condition: xLoc and yLox must be intergal 
	int getHealth() { return currHealth; }; //Pre-Condition: currHealth must be intergal 
	Alignment getAlign() { return align; }; //Pre-Condition: align must be AlignMent
	virtual string status()  
	{ 
      //Post-Condition: stats nust be a string
		string stats;
		string nme = "name : <" + name + ">";  
		string tpe = "type : <" + getType() + ">";
		string hth = "health : <" + to_string(getHealth()) + ">"; 
		string locate = "location : (" + to_string(xLoc) + ", " + to_string(yLoc) + ") ";
		string align = "align : <" + to_string(getAlign()) + ">";
		stats = nme + " | " + tpe + " | " + hth + " | " + locate;

		return stats;
	}
	virtual void move() 
	{ 
      //Post-Condition: currHeakth <= maxHealth
		if (this->getHealth() > 0)
		{
			currHealth = currHealth + 1;
			if (currHealth > maxHealth)
				currHealth = maxHealth;
		}
	}
	void changeAlign(Alignment newAlign) { align = newAlign; } //Post-Condition: newAlign must be of Alignment
	void accessDamage(int amt) //Post-Condition:  amt > 0, currHealth = [0,maxHealth])
	{
		currHealth = currHealth - amt;
		if (currHealth < 0)
			currHealth = 0;
		else if (currHealth > maxHealth)
			currHealth = maxHealth;
	}
	int getMaxHealth() { return maxHealth; } //Pre-Condition: maxHealth must be integral

protected:

	int xLoc;
	int yLoc;

private:

	Alignment align;
	string name;
	int range;
	int attackPower;
	int maxHealth;
	int currHealth;
	virtual string getType() { return "Ship"; } 
};

class Battle : public Ship // maxHeal = 100 rng = 10 attackPwr = 10;
{
public:

	Battle(string name, int x, int y, Alignment align)
		: Ship(name, x, y, align, 100, 10, 10) { torpedos = 10; }
	void move() 
	{  //Post-Condition: currHeakth <= maxHealth
		Ship::move();
		if (this->getHealth() > 0)
		{
			xLoc = xLoc - 1;
			yLoc = yLoc - 1;
		}
	}
	void attack(Ship* target) 
	{ //Pre-Condition: target must be of class Ship*
      //Post-Condition: target->getHeatlth() - [0, maxHealth] fires torpedo >0 and does additional 10 damage, 1 less torpedo
		double inRange = 0;
		inRange = sqrt((pow((this->getY() - target->getY()), 2)) + (pow((this->getX() - target->getX()), 2)));
		
		if (inRange < this->rng  && this->getAlign() != chaotic && target->getAlign() != this->getAlign())
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (torpedos != 0)
				{
					target->accessDamage(this->attackPwr + 10);
					torpedos = torpedos - 1;
				}
				else
					target->accessDamage(this->attackPwr);
			}
		}
		if (inRange < this->rng && this->getAlign() == chaotic)
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (torpedos != 0)
				{
					target->accessDamage(this->attackPwr + 10);
					torpedos = torpedos - 1;
				}
				else
					target->accessDamage(this->attackPwr + 10);
			}
		}
	}
	string status() 
	{ //Post-Condition: stats nust be a string
		string stat = Ship::status();
		string torps = "| torpedos : <" + to_string(torpedos) + ">"; // returns the number of torpedos 
		return stat + torps;
	};

private:

	int torpedos = 10;
	int maxHeal = 100;
	int rng = 10;
	int attackPwr = 10;
	int currHealth = maxHeal;
	string getType() { return "Battleship"; }
};

class Cruiser : public Ship // range is 50, maxHealth is 50, attackPwr = 5
{
public:
	Cruiser(string name, int x, int y, Alignment align)
		: Ship(name, x, y, align, 50, 50, 5) {}

	Cruiser(string name, int x, int y, Alignment align, int maxHeal, int rng, int attackPwr)
		: Ship(name, x, y, align, 20, 25, 0) {}
	void move() 
	{  //Post-Condition: currHeakth <= maxHealth
		Ship::move();
		if (this->getHealth() > 0)
		{
			xLoc = xLoc + 1;
			yLoc = yLoc + 2;
		}
	}
	void attack(Ship* target) 
	{ //Pre-Condition: target must be of class Ship*
      //Post-Condition: target->getHeatlth() - [0, maxHealth]
		Ship::attack(target);
	}
	string status() // see format below 
	{ //Post-Condition: stats nust be a string
		string stat = Ship::status();
		return stat;
	}
private:

	int maxHeal = 50;
	int attackPwr = 50;
	int rng = 5;
	int currHealth = maxHeal;
	string getType() { return "Cruiser"; }
};

class Corvette : public Ship  // range is 25, maxHealth is 20   
{
public:
	Corvette::Corvette(string name, int x, int y, Alignment align)
		: Ship(name, x, y, align, 20, 25, 0) {}

	void move()  
	{  //Post-Condition: currHeakth <= maxHealth
		Ship::move();
		if (this->getHealth() > 0)
		{
			xLoc = xLoc + 5;
			yLoc = yLoc + 5;
		}
	}
	void attack(Ship* target)
	{ //Pre-Condition: target must be of class Ship*
      //Post-Condition: target->getHeatlth() - [0, maxHealth]
		double inRange = 0;
		inRange = sqrt((pow((this->getY() - target->getY()), 2)) + (pow((this->getX() - target->getX()), 2)));
		if (inRange < this->rng  && this->getAlign() != chaotic && target->getAlign() != this->getAlign())
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (target->getAlign() == us)
					target->changeAlign(them);
				else if (target->getAlign() == them)
					target->changeAlign(us);
				else
					target->changeAlign(chaotic);
			}
		}
		else if (inRange < this->rng  && this->getAlign() == chaotic)
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (target->getAlign() == us)
					target->changeAlign(them);
				else if (target->getAlign() == them)
					target->changeAlign(us);
				else
					target->changeAlign(chaotic);
			}
		}
	}
	string status() // see format below 
	{ //Post-Condition: stats nust be a string
		string stat = Ship::status();
		return stat;
	}
private:

	int maxHeal = 20;
	int rng = 25;
	int currHealth = maxHeal;
	string getType() { return "Corvette"; }
};

class Repair : public Cruiser // range is 25, maxHealth = 20
{
public:
	Repair(string name, int x, int y, Alignment align)
		: Cruiser(name, x, y, align, 20, 25, 0) {}
	void attack(Ship* target) 
	{ //Pre-Condition: target must be of class Ship*
      //Post-Condition: target->getHeatlth() - [0, maxHealth] 
		double inRange = 0;
		inRange = sqrt((pow((this->getY() - target->getY()), 2)) + (pow((this->getX() - target->getX()), 2)));
		if (inRange < this->rng  && this->getAlign() != chaotic && target->getAlign() != this->getAlign())
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (target->getAlign() == this->getAlign())
					while (target->getHealth() != this->getMaxHealth())
						target->accessDamage(-1);
			}
		}
		if (inRange < this->rng  && this->getAlign() == chaotic)
		{
			if (this->getHealth() > 0 && target->getHealth() > 0)
			{
				if (target->getAlign() == this->getAlign())
					while (target->getHealth() != this->getMaxHealth())
						target->accessDamage(-1);
			}
		}

	}
	string status() 
	{ //Post-Condition: stats nust be a string
		string stat = Ship::status();
		return stat;
	}
private:

	int maxHeal = 20;
	int rng = 25;
	int currHealth = maxHeal;
	string getType() { return "Repair"; }
};
