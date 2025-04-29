#include <iostream>

// boost
// #include "boost/lexical_cast.hpp"

/**
 * * @brief 文件操作菜单
 */
void fileOperations()
{
	using namespace std;
	int choice;
	while (true)
	{
		cout << "Please select a file operation:" << endl;
		cout << "1. Create a file" << endl;
		cout << "2. Read a file" << endl;
		cout << "3. Write to a file" << endl;
		cout << "4. Delete a file" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Creating a file..." << endl;
			break;
		case 2:
			cout << "Reading a file..." << endl;
			break;
		case 3:
			cout << "Writing to a file..." << endl;
			break;
		case 4:
			cout << "Deleting a file..." << endl;
			break;
		case 5:
			return; // Exit the loop
		default:
			cout << "Invalid option, please try again" << endl;
		}
	}
}

int main()
{
	using namespace std;
	int choice;
	// Simple menu
	while (true)
	{
		cout << "Please select an operation:" << endl;
		cout << "1. File operations" << endl;
		cout << "2. Database operations" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			fileOperations();
			break;
		case 2:
			// databaseOperations();
			break;
		case 3:
			cout << "Exiting the program" << endl;
			return 0;
		default:
			cout << "Invalid option, please try again" << endl;
		}
	}

	return 0;
}

