#include <iostream>
#include "./Module/user.h"
#include "./Manage/user_manage.h"

// boost
// #include "boost/lexical_cast.hpp"

int main()
{
	using namespace std;
	int choice;
	// Simple menu
	while (true)
	{
		cout << "Please select an operation:" << endl;
		cout << "1. Manage students" << endl;
		cout << "2. File operations" << endl;
		cout << "3. Database operations" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			// manageStudents(userManage);
			break;
		case 2:
			// fileOperations();
			break;
		case 3:
			// databaseOperations();
			break;
		case 4:
			cout << "Exiting the program" << endl;
			return 0;
		default:
			cout << "Invalid option, please try again" << endl;
		}
	}

	return 0;
}