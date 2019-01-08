/*
Name: Omari Chatman
CIS-350 Prog#3 loonBalloon

Description:
This program was created to figure out if a message can be sent from the first to all other balloons. While 
each balloon can only visit its 2 closest balloons. If the message can reach all balloons then output yes, if
not then output no. My program uses a class loon to have the attributes(name, location, visited, dist) of each
balloon and class Atmosphere to have a vector of all balloons for each testcase and the methods used on all loon
instances. After collect input from the command line of each balloons location, it will transmit from the first 
loon useing only its closest 2 loons. After figuring out if there is a tie or not it will do a recursive call
to the outcome and keep calling transmit untill all have been visited. It then checks to see if the number of
visited ballons is equal to the number of ballons. If so cout "yes" , if not then cout "no".
*/

using namespace std;

#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <string>

class loon {
private:
	int name;
	//int previous;
	int xLoc, yLoc;
	bool visited = false;
	double dist;
	vector<loon> allDist;
	vector<loon> minDist;

public:
	loon(int x, int y, int who) {
		xLoc = x;
		yLoc = y;
		name = who;
	}
	int getX() {
		//pre none
		//post -20 <= xLoc <= 20
		//O(n) = 1

		return xLoc;
	}
	int getY() {
		//pre none
		//post -20 <= xLoc <= 20
		//O(n) = 1

		return yLoc;
	}
	int getName() {
		//pre none
		//post name >= 0
		//O(n) = 1

		return name;
	}
	double getDist() {
		//pre none
		//post dist > 0
		//O(n) = 1

		return dist;
	}
	bool getReached() {
		//pre none
		//post none
		//O(n) = 1

		return visited;
	}
	bool isTie() {
		//pre none
		//post none
		//O(n)

		if (minDist[0].getDist() == minDist[1].getDist()) {
			return true;
		}
		else {
			return false;
		}
	}
	/*void setPrev(int who) {
		previous = who;
	}*/
	/*int getPrev() {
		return previous;
	}*/
	void addDist(double distance) {
		//pre distance > 0
		//post dist > 0
		//O(n) = 1

		dist = distance;
	}
	void Visited() {
		//pre none
		//post visted = 1;
		//O(n) = 1

		visited = true;
	}
	void lookedAt(loon ball) {
		//pre none
		//post allDist.size() > 0
		//O(n) = 1

		allDist.push_back(ball);
	}
	void addMinTwo() {
		//pre none
		//post minDist.size() = 2
		//O(n) = n

		loon min1 = allDist[0];
		loon min2 = allDist[1];

		if (min2.getDist() < min1.getDist())
		{
			min2 = allDist[0]; 
			min1 = allDist[1];
		}
		for (int i = 2; i < allDist.size(); i++)
			if (allDist[i].getDist() < min1.getDist())
			{
				min2 = min1;
				min1 = allDist[i];
			}
			else if (allDist[i].getDist() < min2.getDist())
			{
				min2 = allDist[i];
			}
		minDist.push_back(min1);
		minDist.push_back(min2);
	}
	loon doPriority()
	{
		//pre none
		//post none
		//O(n) = n

		if (minDist[0].getX() < minDist[1].getX()) // ball 1 is more West, return that ballon
		{
			return minDist[0];
		}
		else if (minDist[0].getX() == minDist[1].getX()) // if equally West, which is more South ?
		{
			if (minDist[0].getY() < minDist[1].getY()) // if ball 1 is more South returh that ballon 1
			{
				return minDist[0];
			}
			return minDist[1]; // else return ballon 2
		}
		else {
			return minDist[1]; // if ball 2 is more West return that ballon 2
		}
	}
	loon notPriority() 
	{
		//pre none
		//post none
		//O(n) = 1

		if (minDist[0].getX() > minDist[1].getX()) // ball 1 is more West, return that ballon
		{
			return minDist[0];
		}
		else if (minDist[0].getX() == minDist[1].getX()) // if equally West, which is more South ?
		{
			if (minDist[0].getY() > minDist[1].getY()) // if ball 1 is more South returh that ballon 1
			{
				return minDist[0];
			}
			return minDist[1]; // else return ballon 2
		}
		else {
			return minDist[1]; // if ball 2 is more West return that ballon 2
		}
	}
	loon getMin() {
		//pre none
		//post none
		//O(n) = 1

		if (minDist[0].getReached() == false) {
			return minDist[0];
		}
		return minDist[1];
	}
};

class Atmosphere {
private:
	vector<loon> stations; // all ballons in each testcase
public:
	Atmosphere() {}
	double findDist(loon ball1, loon ball2) {
		//pre none
		//post result > 0
		//O(n) = 1

		int x1 = (ball2.getX() - ball1.getX());
		int y1 = (ball2.getY() - ball1.getY());
		int pow1 = pow(x1, 2);
		int pow2 = pow(y1, 2);
		double result = sqrt(pow1 + pow2);

		return result;
	}

	void transmit(loon ball)
	{
		//pre none
		//post none
		//O(n) = n

		justVisted(ball.getName());

		for (int i = 0; i < stations.size(); i++) {
			if (findDist(ball, stations[i]) != 0) { // dont look at self
				addDistLoon(findDist(ball, stations[i]), stations[i]); 
				addLoon2Vec(stations[i], ball);
			}
		}

		addMinDistLoon(ball.getName()); // calculate the 2 minimum of the ball

		if (findTie(ball)) {
			if (getPriority(ball).getReached() == false) {
				transmit(getPriority(ball));
			}
			else if (nonPriority(ball).getReached() == false) {
					transmit(nonPriority(ball));
				}
		}
		else {
			if (getMinLoon(ball).getReached() == false) {
				transmit(getMinLoon(ball));
			}
		}
	}
	loon getPriority(loon ball) {
		//pre none
		//post none
		//O(n) = 1

		return stations[ball.getName()].doPriority();
	}
	loon nonPriority(loon ball) {
		//pre none
		//post none
		//O(n) = 1

		return stations[ball.getName()].notPriority();
	}
	bool findTie(loon ball) {
		//pre none
		//post none
		//O(n) = 1

		return stations[ball.getName()].isTie();
	}
	loon getMinLoon(loon ball) {
		//pre none
		//post none
		//O(n) = 1

		return stations[ball.getName()].getMin();
	}
	/*loon findPrevious(int name)
	{
		for (int i = 0; i < stations.size(); i++)
		{
			if (stations[i].getName() == name)
			{
				return stations[i];
			}
		}
	}*/
	void addDistLoon(double distance, loon ball) {
		//pre none
		//post none
		//O(n) = 1

		stations[ball.getName()].addDist(distance);
	}
	void addLoon2Vec(loon toAdd, loon ball) {
		//pre none
		//post none
		//O(n) = 1

		stations[ball.getName()].lookedAt(toAdd);
	}
	void addMinDistLoon(int name) {
		//pre none
		//post none
		//O(n) = 1

		stations[name].addMinTwo();
	}
	void justVisted(int name) {
		//pre none
		//post none
		//O(n) = 1

		stations[name].Visited();
	}
	string allTrue() {
		//pre none
		//post yes or no
		//O(n) = n

		int count = 0;

		for (int i = 0; i < stations.size(); i++)
		{
			if (stations[i].getReached()) {
				count++;
			}
		}
		if (count == stations.size()) {
			return "yes";
		}
		else {
			return "no";
		}
	}
	
	void addBallon(loon ballon) {
		//pre none
		//post none
		//O(n) = 1

		stations.push_back(ballon);
	}
	loon getBallon(int index) {
		//pre none
		//post none
		//O(n) = 1

		return stations[index];
	}
	void clear() {
		//pre none
		//post none
		//O(n) = 1

		stations.clear();
	}
};

int main() {

	int X, Y;
	int numPairs;
	vector<int> pairs;
	vector<string> output;
	vector<Atmosphere> stratos; // has a collection of sky
	Atmosphere sky; 

	cin >> numPairs;

	while (numPairs != 0) {
		for (int i = 0; i < numPairs; i++) {
			cin >> X >> Y;
			loon ballon(X, Y, i);
			sky.addBallon(ballon);
		}
		stratos.push_back(sky);
		sky.transmit(sky.getBallon(0));
		output.push_back(sky.allTrue());
		sky.clear();
		cin >> numPairs;
	}

	for (int i = 0; i < output.size(); i++) // each test case
	{
		cout << output[i] << endl;
	}

	return 0;
}