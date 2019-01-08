#include <iostream>
#include <string>
#include <math.h>
#include <assert.h>
using namespace std;


float stu_perc_grade(int numCorrect);
float minScore = 9999;
float maxScore = 0;
float total = 0;
void max_min(float percent);
int ans_compare(string stu_ans, string answer_key);
int number_stu;
char stu_let_grade(float numCorrect);
string length_check(string stu_id);
string digit_check(string stu_id);
string answer_size_check(string stu_ans);
string answer_key;

int main()
{

	cout << "Please enter answer key." << endl;  
	cin >> answer_key;

	
	cout << "How many students do you want to grade? " << endl;
	cin >> number_stu;

	int i;
	int student_count = 0;
	float max, min, average;
	string stu_ans;
	string stu_id;
	string ans_check;

	for (i = 0; i < number_stu; i++)
	{
		cout << "Please enter the students 7-digit ID number" << endl;
		cin >> stu_id;

		stu_id = length_check(stu_id);

		stu_id = digit_check(stu_id);

		cout << "Please input the students answer for student " << i + 1 << endl;
		cin >> stu_ans;

		ans_check = answer_size_check(stu_ans);

		int numCorrect = ans_compare(stu_ans, answer_key);

		cout << "The number of correct answers is " << numCorrect << endl;

		float percent = stu_perc_grade(numCorrect);

		cout << "Your percent grade is " << percent << endl;

		char score = stu_let_grade(percent);

		cout << "Your letter grade score is " << score << endl;

		total += percent;

		max_min(percent);

	}

	cout << "The minimium and maximum test score values are " << minScore << "%" << " and " << maxScore << "%"<< endl; 
	
	average = total / number_stu;

	cout << "The average of the test scores is " << average << endl;

	system("pause");
	return 0;
}

string length_check(string stu_id)   // Checks the length of the students id input.
{
	if (stu_id.length() != 7)
	{
		string new_id;
		cout << "Error. Please enter a 7-digit number" << endl;
		cin >> new_id;
		return length_check(new_id);
	}
	return stu_id;
}

string digit_check(string stu_id)    // Checks to see if the id's components are all digits between 0-9.
{
	int i;
	for (i = 0; i < stu_id.length(); i++)
	{
		if (!(isdigit(stu_id[i])))
		{
			string new_id;
			cout << "Your value is not in the correct format. Please enter digits from 0-9." << endl;
			cin >> new_id;
			new_id = length_check(new_id);
			return digit_check(new_id);
		}
	}
	return stu_id;
}


int ans_compare(string stu_ans, string answer_key)     // Compares the students answers with the answer key and holds the values.
{
	int i, numCorrect;
	numCorrect = 0;

	int len = answer_key.length();
	if (stu_ans.length() < len)
	{
		len = stu_ans.length();
	}

	for (i = 0; i < len; i++)
	{
		if (answer_key[i] == stu_ans[i])
		{
			numCorrect++;
		}
	}
	return numCorrect;
}

float stu_perc_grade(int numCorrect)    // Calculates the percentage grade for each student. 
{
	float percent = (100) * numCorrect / answer_key.length();

	return percent;
}

char stu_let_grade(float percent)     // Calculates the letter grade for each student. 
{
	char score;

	if (percent >= 90)
		score = 'A';
	else if (percent < 90 && percent >= 80)
		score = 'B';
	else if (percent < 80 && percent >= 70)
		score = 'C';
	else if (percent < 70 && percent >= 60)
		score = 'D';
	else
		score = 'F';

	return score;
}

string answer_size_check(string stu_ans)    // Makes sure the size of the students answer is equal to the answer key size.
{

	if (stu_ans.length() > answer_key.length())
	{
		stu_ans.resize(answer_key.length());
	}

	if (stu_ans.length() < answer_key.length())
	{
		int diff = answer_key.length() - stu_ans.length();
		int i;

		for (i = 0; i < diff; i++)
		{
			stu_ans.append("g");
		}
	}

	return stu_ans;
}

void max_min(float percent)    // Calcualtes the max and min test score. 
{
	if (percent > maxScore)
	{
		maxScore = percent;
	}

	if(percent < minScore)
	{
		minScore = percent;
	}
}
