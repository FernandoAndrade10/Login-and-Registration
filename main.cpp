//Login and Registration
//Visual Studio 2019

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


void registration(fstream& file, string name) {
	string username;
	string password;
	string line;

	cout  << endl << "Register for a new account" << endl;
	cout << "Enter a username: ";
	getline(cin, username);

	file.open(name);
	while (getline(file, line))
	{
		string checkUsername;

		istringstream ss(line);
		getline(ss, checkUsername, ' ');

		//Check that inputted username is unique
		if (username == checkUsername)
		{
			cout << endl << "Username already taken." << endl << "Try a differnt username or press 1 to return to menu: ";
			getline(cin, username);
			if (username == "1")
			{
				cout << endl;
				return;
			}
		}
	}
	file.close();

	//Password needs to be minimum 6 characters
	while (password.length() < 6)
	{
		cout << "Enter a password: ";
		getline(cin, password);

		if (password.length() < 6)
		{
			cout << "Password too short. Must be between of 6 characters." << endl;
		}
		else
		{
			cout << endl << "Successfully Registered Account!" << endl << endl;
		}
	}

	ofstream append(name, ios::app);
	append << username << " " << password << endl;
	append.close();
}

bool login(fstream& file, string name) {
	string username;
	string password;
	string accountPassword = " ";
	string line;
	bool validUsername = false;
	bool validPassword = false;

	cout << endl << "Login" << endl;
	cout << "Username: ";

	getline(cin, username);

	file.open(name);

	while (validUsername == false)
	{
		//Check that inputted username matches a registered username
		while (getline(file, line))
		{
			string checkUsername;

			istringstream ss(line);
			getline(ss, checkUsername, ' ');

			if (username == checkUsername)
			{
				validUsername = true;
			}
		}
	
		if (validUsername == false)
		{
			cout << endl << "Invalid username" << endl;
			cout << "Enter Username or press 1 for menu: ";
			getline(cin, username);

			if (username == "1")
			{
				return false;
			}

			file.clear();
			file.seekg(0);
		}

		cout << endl;
	}

	file.clear();
	file.seekg(0);

	//Get matching password to check against the password the user will input
	while (getline(file, line))
	{
		string findUsername;

		istringstream ss(line);
		getline(ss, findUsername, ' ');

		if (findUsername == username)
		{
			size_t pos = line.find(' ');
			string temp = line.substr(pos);
			accountPassword = temp.substr(1);
			cout << endl << accountPassword << endl;
		}

	}

	//Check user inputted password to stored password
	while (validPassword == false)
	{
		cout << "Password: ";
		getline(cin, password);

		if (password == accountPassword)
		{
			cout << endl << "Successfully logged in!" << endl << endl;
			return true;
		}
		else
		{
			cout << endl << "Incorrect Password" << endl << endl;
		}
	}
}

bool logout() {
	cout << endl << "Successfully Logged Out!" << endl << endl;
	return false;
}

int main() {
	string filename = "users.txt";
	fstream file;
	bool loginAuth = false;

	file.open(filename);

	if (!file)
	{
		cout << "Cannot open file, file does not exist." << endl << "Creating new file..." << endl << endl;
		file.open(filename, fstream::in | fstream::out | fstream::trunc);
		file << "USERNAME PASSWORD \n";
		file.close();
	}
	else
	{
		cout << filename << " found." << endl;
		cout << "Working with existing file" << endl << endl;
		file.close();
	}

	int input = 0;
	while (input != 3)
	{
		cout << "Please select an option:" << endl;
		cout << "1 - Register" << endl;

		//Check Login status and otput accordingly
		if (loginAuth == false)
		{
			cout << "2 - Login" << endl;
		}
		else
		{
			cout << "2 - Logout" << endl;
		}
		cout << "3 - Quit" << endl << endl;

		//Check for legal inputs
		if (!(cin >> input))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input." << endl << endl;
			input = 0;
		}
		else
		{
			if (input < 1 || input > 3)
			{
				cout << "Invalid input." << endl << endl;
			}
		}
		
		//Menu
		if (input == 1 )
		{
			cin.clear();
			cin.ignore();

			registration(file, filename);
		}
		else if (input == 2 && loginAuth == false)
		{
			cin.clear();
			cin.ignore();

			loginAuth = login(file, filename);
		}
		else if (input == 2 && loginAuth == true)
		{
			cin.clear();
			cin.ignore();

			loginAuth = logout();
		}
	}

	file.close();

	
}