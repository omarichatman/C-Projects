#include <iostream>
#include <fstream>
#include <string>
using namespace std;

# define account "account.dat"
# define updaccount "updated_account.dat"

struct balance
{
	float initial_saving;
	float initial_checking;
};

struct birth_date
{
	int day;
	int month;
	int year;
};

struct Name
{
	string firstname;
	string middlename;
	string lastname;
};

struct Customer
{
	birth_date date;
	Name name;
	balance balance;

	Customer(Name username)
	{
		name.firstname = username.firstname + " "; 
		name.middlename = username.middlename + " ";
		name.lastname = username.lastname + " ";
		date.day = 0;
		date.month = 0;
		date.year = 0;
		balance.initial_saving = 0.00;
		balance.initial_checking = 0.00;
	}
};

class Bank
{

private: 
	float Balance_saving;
	float Balance_checking;

	birth_date date;
	Name name;
	balance balance;

public: 
	void withdraw(float amount, int  account_type);
	void deposit(float amount, int  account_type);
	void check_balance();  // print out the balance on screen
	
	
	int customer(birth_date date, Name name, float initial_saving, float initial_checking);
	
	void setValuebirth(int x, int y, int z) { date.day = x; date.month = y; date.year = z; }
	void setValuename(string a, string b, string c) { name.firstname = a; name.middlename = b; name.lastname = c; }
	void setValuebalance(float w, float r) { balance.initial_saving = w; balance.initial_checking = r; }

	
};

int value3;


void getBalance(Customer user) {
	cout << "Your savings account balance is " << user.balance.initial_saving << endl;
	cout << "Your checking account balance is " << user.balance.initial_checking << endl;
}

Customer makeDeposit(Customer user) {
	cout << "Which account would you like to deposit the money into?" << endl;
	cout << "Enter 1 for savings or 2 for checking." << endl;
	int whichAccount;
	cin >> whichAccount;

	if (whichAccount == 1)
	{
		cout << "How much would you like to Deposit?" << endl;
		int amount;
		cin >> amount;
		float new_savings;
		new_savings = user.balance.initial_saving + amount;
		cout << "$" << amount << " has been deposited into your savings account" << endl;
		cout << "Your new balance is " << new_savings << endl;
		return user;
	}
	
	else if (whichAccount == 2)
	{
		cout << "How much would you like to Deposit?" << endl;
		int amount;
		cin >> amount;
		float new_checking;
		new_checking = user.balance.initial_checking + amount;
		cout << "$" << amount << " has been deposited into your checking account" << endl;
		cout << "Your new balance is " << new_checking << endl;
		return user;
	}
	else
	{
		cout << "Your did not input the correct value. Please enter a 1 for savings account or a 2 for checkings account." << endl;
		return(makeDeposit(user));
	}
}

Customer makeWithdrawal(Customer user) {
	cout << "Which account would you like to withdrawl the money from?." << endl;
	cout << "Enter 1 for savings or 2 for checking." << endl;
	int whichAccount;
	cin >> whichAccount;

	if (whichAccount == 1)
	{
		cout << "How much would you like to Withdrawal?" << endl;
		int amount;
		cin >> amount;
		float new_savings;
		new_savings = user.balance.initial_saving - amount;

		if (new_savings < 0)
		{
			cout << "You do not have enough money in your account for this transaction." << endl;
			return(makeWithdrawal(user));
		}
		else
		{
			cout << "$" << amount << " has been withdrawn from you savings account" << endl;
			cout << "Your new balance is " << new_savings << endl;
		}
	}
	else if (whichAccount == 2)
	{
		cout << "How much would you like to Withdrawal?" << endl;
		int amount;
		cin >> amount;
		float new_checking;
		new_checking = user.balance.initial_checking - amount;
		if (new_checking < 0)
		{
			cout << "You do not have enough money in your account for this transaction." << endl;
			return(makeWithdrawal(user));
		}
		else
		{
		cout << "$" << amount << " has been withdrawn from you checking account" << endl;
		cout << "Your new balance is " << new_checking << endl;
		return user;
		}
	}
	else
	{
		cout << "Your did not input the correct value. Please enter a 1 for savings account or a 2 for checkings account." << endl;
		return(makeWithdrawal(user));
	}
}

void log_out(Customer user)
{
	ofstream myOutputFile;
		
	//ins >> user.date.month >> user.date.day >> user.date.year;
	//ins >> user.name.firstname >> user.name.middlename >> user.name.lastname;
	//ins >> user.balance.initial_saving;
//	ins >> user.balance.initial_checking;


	myOutputFile.open("updated_account.dat", ios::app);

		myOutputFile << user.date.month << " " << user.date.day << " " << user.date.year << endl;
		myOutputFile << user.name.firstname << " " << user.name.middlename << " " <<  user.name.lastname << endl;
		myOutputFile << user.balance.initial_saving << endl;
		myOutputFile << user.balance.initial_checking << endl;
		
}

void userHome(Customer user) {
	cout << "Would you like to check your balance, make a deposit or make a withdrawal." << endl;
	cout << "Please enter a 1 for balance, a 2 for deposit or a 3 for withdrawal, or 4 to exit" << endl;

	cin >> value3;
	Customer currUser = Customer(user.name);

	if (value3 == 1) {
		getBalance(user);
		userHome(user);
	}
	else if (value3 == 2) {
		currUser = makeDeposit(user);
		userHome(currUser);
	}
	else if (value3 == 3) {
		currUser = makeWithdrawal(user);
		userHome(currUser);
	}
	else if (value3 == 4)
	{
		log_out(user);
		cout << "Thank you. Please come again." << endl;
	}
	else
	{
		cout << "You did not enter a 1, 2, 3, 4. Please retry." << endl;
		userHome(user);
	}

}

int value1, value2, value4, firstname, middlename, lastname, deposit;
string month, day, year;

Customer getUser(string birthday)
{
	ifstream ins;
	ins.open(account);
	//cout << "Looking for " << birthday << endl;
	string input;

	while (!ins.eof())
	{
		getline(ins, input);
		//cout << input << endl;

		if (input == birthday)
		{
			//cout << "found" << endl;
			
			Name username;
			getline(ins, input, ' ');
			username.firstname = input;

			getline(ins, input, ' ');
			username.middlename = input;

			getline(ins, input);
			username.lastname = input;

			Customer User = Customer(username);
			getline(ins, input);

			User.balance.initial_saving = stof(input);

			getline(ins, input);
			User.balance.initial_checking = stof(input);
			return User;
		}

	}
	cout << "User not found, please enter another birthdate." << endl;
	string response;
	cin >> month >> day >> year;
	response = month + " " + day + " " + year;

	return(getUser(response));
}



int main()
{
	ifstream ins;
	ins.open(account);

	while (!(ins.eof()))
	{
		cout << "Hello. Welcome to Michigan Regional Bank. Are you a new user or a current user?" << endl;
		cout << "Please enter a 1 for new user and a 2 for current user." << endl;
		cin >> value1;

		if (value1 == 1)
		{ 
				Name username;
				birth_date date;

				cout << "Please enter your first name." << endl;
				cin >> username.firstname; 
			
				cout << "Please enter you middle name." << endl;
				cin >> username.middlename;
				
				cout << "Please enter your last name." << endl;
				cin >> username.lastname;
				
				cout << "Please enter your birthdates month. (MM)" << endl;
				cin >> date.month;
				//cout << date.month << endl;

				cout << "Please enter your birthdates day. (DD)" << endl;
				cin >> date.day;
				//cout << date.day << endl;

				cout << "Please enter your birthdates year. (YYYY)" << endl;
				cin >> date.year;
				//cout << date.year << endl;

				Customer newCustomer = Customer(username);
				newCustomer.date.month = date.month;
				newCustomer.date.day = date.day;
				newCustomer.date.year = date.year;

				cout << "You have now created a new account " << newCustomer.name.firstname << newCustomer.name.middlename << newCustomer.name.lastname << endl;
				cout << "Your current savings account balance is " << newCustomer.balance.initial_saving << endl;
				cout << "Your current checking account balance is " << newCustomer.balance.initial_checking << endl;

				userHome(newCustomer); 
				return 0;
				// Not if they want to exit. 
				//Create function for writing new user's to the file.
		}
		else if (value1 == 2)
		{
			cout << "Please enter your birthday" << endl;
			string response;
			cin >> month >> day >> year;
			response = month + " " + day + " " + year;

			Customer User = getUser(response);

			cout << "Welcome Back " << User.name.firstname << User.name.middlename << User.name.lastname << endl;
			cout << "Your current savings account balance is " << User.balance.initial_saving << endl;
			cout << "Your current checking account balance is " << User.balance.initial_checking << endl;

			userHome(User);
			return 0;
		}
	}
	

	system("pause");
	return 0;
}
