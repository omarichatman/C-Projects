#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
using namespace std;

#define record "record.dat"

struct Date
{
	int day; 
	int month;
	int year;
};

struct Author
{
	string firstname;
	string middlename;
	string lastname;
};

struct Book
{
	Date date;
	Author author;
	string title;
	float cost;
	int type;
};

ofstream myOutputFile;
ifstream ins;

int main()
{
	
	ins.open(record);

	Book x[100];
	int count = 0;

	while (!(ins.eof()))
	{
		ins >> x[count].date.day >> x[count].date.month >> x[count].date.year;

		ins >> x[count].author.firstname >> x[count].author.middlename >> x[count].author.lastname;

		getline(ins, x[count].title);

		if (x[count].title.length() == 0)
		{
			getline(ins, x[count].title);
		}
	
		string costTemp, typeTemp;

		getline(ins, costTemp);

		x[count].cost = stof(costTemp);

		getline(ins, typeTemp);

		x[count].type = stoi(typeTemp);
		
		count++;
	}

	myOutputFile.open("grouped_record.dat");
	
	for (int i = 0; i < count; i++)
	{
		if (x[i].type == 1)
		{
			myOutputFile << "Here is a list of all the Science books" << endl;
			myOutputFile << x[i].date.day << " " << x[i].date.month << " " <<  x[i].date.year << endl;
			myOutputFile << x[i].author.firstname << " " <<  x[i].author.middlename << " " << x[i].author.lastname << endl;
			myOutputFile << x[i].title << endl;
			myOutputFile << x[i].cost << endl;
			myOutputFile << x[i].type << endl;
		}
	}

	for (int i = 0; i < count; i++)
	{
		if (x[i].type == 2)
		{
			myOutputFile << "Here is a list of all the Art books" << endl; 
			myOutputFile << x[i].date.day << " " << x[i].date.month << " " << x[i].date.year << endl;
			myOutputFile << x[i].author.firstname << " " << x[i].author.middlename << " " << x[i].author.lastname << endl;
			myOutputFile << x[i].title << endl;
			myOutputFile << x[i].cost << endl;
			myOutputFile << x[i].type << endl;
		}
	}

	for (int i = 0; i < count; i++)
	{
		if (x[i].type == 3)
		{
			myOutputFile << "Here is a list of all the Langauge books" << endl; 
			myOutputFile << x[i].date.day << " " << x[i].date.month << " " << x[i].date.year << endl;
			myOutputFile << x[i].author.firstname << " " << x[i].author.middlename << " " << x[i].author.lastname << endl;
			myOutputFile << x[i].title << endl;
			myOutputFile << x[i].cost << endl;
			myOutputFile << x[i].type << endl;
		}
	}

	for (int i = 0; i < count; i++)
	{
		if (x[i].type == 4)
		{
			myOutputFile << "Here is a list of all other books" << endl; 
			myOutputFile << x[i].date.day << " " << x[i].date.month << " " << x[i].date.year << endl;
			myOutputFile << x[i].author.firstname << " " << x[i].author.middlename << " " << x[i].author.lastname << endl;
			myOutputFile << x[i].title << endl;
			myOutputFile << x[i].cost << endl;
			myOutputFile << x[i].type << endl;
		}
	}
	
	ins.close();
	myOutputFile.close();

	system("pause");
	return 0;
}
