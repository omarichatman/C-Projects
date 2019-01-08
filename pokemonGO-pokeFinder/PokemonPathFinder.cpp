/*
Name: Omari Chatman

Description:
The objective of the program is to find the shortest route to capture all pokemon
given from the keyboard and calculate the minimum distance to be able to get to 
all pokemon with unqiue names and come back to the origin. My program has a class 
pokemon() to hold al of the pokemons location, name, order, distance, and visited.
I find the distance from (0,0) to all pokemon and run my branch and bound function
on each pokemon as the first pokemon. It will then generate the shortest route and 
have my class pokeTrainer() move to those spots and visited them. Finally, return the 
total distance travled, pushes it into a min priority queue and returns the lowest 
route distance. 
*/

using namespace std;

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<functional>

class pokemon {
public:
	int xLoc;
	int yLoc;
	int order;
	int pathDist;
	string name;
	bool visited;

	pokemon() {}
	pokemon(string nme, int x, int y, int ord) {
		name = nme;
		xLoc = x;
		yLoc = y;
		order = ord;
		pathDist = 0;
		visited = false;
	}
	bool operator<(const pokemon& rhs) const 
	{
		 (this->pathDist < rhs.pathDist);
	}
	bool operator>(const pokemon &rhs) const
	{
		 return (this->pathDist > rhs.pathDist);
	}
};

class pokeTrainer {

public: 
	int xLoc;
	int yLoc;
	int totalPathDistance;
	vector<pokemon> nearby;
	vector<string> uniqPoke;
	priority_queue<pokemon, vector<pokemon>, greater<pokemon>> minDistHeap;
	
	pokeTrainer() {
		xLoc = 0;
		yLoc = 0;
		int totalPathDistance = 0;
	}
	void addPokemon(pokemon poke)
	{
		//pre: poke has a location, distance, order and visited
		//post: nearby.size() = nearby.size() + 1

		nearby.push_back(poke);
	}
	pokemon getFromOrder(int ord) {
		//pre: 0 >= ord >= nearby.size() - 1
		//post: none

		return nearby[ord];
	}
	bool done() {
		//pre: none
		//post: none

		int count = 0;

		for (int i = 0; i < nearby.size(); i++) {
			if (nearby[i].visited == true) {
				count++;
			}
		}
		if (count == nearby.size()) {
			return true;
		}
		return false;
	}
	void visitName(pokemon poke) {
		//pre: poke has a location, distance, order and visited
		//post: none

		for (int i = 0; i < nearby.size(); i++) {
			if (nearby[i].name == poke.name) {
				nearby[i].visited = true;
			}
		}
	}
	void addUniquePokemon()
	{
		//pre: none
		//post: uniqPoke.size() = uniqPoke.size() + 1

		for (int i = 0; i < nearby.size(); i++) {
			if (find(uniqPoke.begin(), uniqPoke.end(), nearby[i].name) == uniqPoke.end()) {
				uniqPoke.push_back(nearby[i].name);
			}
		}
	}
	int branchBound(pokemon poke) {
		//pre: poke has a location, distance, order and visited
		//post: totalPathDistance > 0

		visitName(poke);

		if (!done()) {
			branchBound(getSets(poke));
		}
		
		return totalPathDistance;
	}
	pokemon getSets(pokemon poke) { 
		//pre: poke has a location, distance, order and visited
		//post: pokemon with lowest distance from pokeTrainer location

		priority_queue<pokemon, vector<pokemon>, greater<pokemon>> tempHeap;

		for (int i = 0; i < nearby.size(); i++) { 

			if (nearby[i].visited != true) 
			{
				getDist(nearby[i], i);
				tempHeap.push(nearby[i]); 
			}
		}
		minDistHeap.push(tempHeap.top()); 
		xLoc = tempHeap.top().xLoc; 
		yLoc = tempHeap.top().yLoc; 
		totalPathDistance += tempHeap.top().pathDist;

		return tempHeap.top();
	}
	void getDist(pokemon poke, int index) {
		//pre: poke has a location, distance, order and visited, index 0 >= index > nearby.size() - 1
		//post: none

		nearby[index].pathDist = abs(poke.xLoc - xLoc) + abs(poke.yLoc - yLoc);
	}
	void headOut(pokemon poke) {
		//pre: poke has a location, distance, order and visited
		//post: none

		xLoc = poke.xLoc;
		yLoc = poke.yLoc;
		totalPathDistance += abs(poke.xLoc) + abs(poke.yLoc);
	}
	void comeBack() {
		//pre: none
		//post: none

		totalPathDistance += abs(xLoc) + abs(yLoc);
		xLoc = 0;
		yLoc = 0;
	}
	void reset() {
		//pre: none
		//post: minDistHeap.empty() == true

		totalPathDistance = 0;
		for (int i = 0; i < nearby.size(); i++) {
			nearby[i].visited = false;
			nearby[i].pathDist = 0;
		}
		while(!minDistHeap.empty()){
			minDistHeap.pop();
		}
	}
};

int main() {

	int numStops, x, y;
	string pokeName;
	pokeTrainer Ash;
	priority_queue<int, vector<int>, greater<int>> differentPaths;

	cin >> numStops;

	for (int i = 0; i < numStops; i++) {
		cin >> x >> y >> pokeName;
		pokemon iChoseYou(pokeName, x, y, i);
		Ash.addPokemon(iChoseYou);
	}

	Ash.addUniquePokemon();

	for (int i = 0; i < numStops; i++) {
		Ash.headOut(Ash.getFromOrder(i));
		Ash.branchBound(Ash.getFromOrder(i));
		Ash.comeBack();
		differentPaths.push(Ash.totalPathDistance);
		Ash.reset();
	}

	cout << differentPaths.top();

	return 0;
}