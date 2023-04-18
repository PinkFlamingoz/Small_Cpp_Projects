#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "basic_functions.h"

using namespace std;

// Globals
static int counter = 0;

// Classes
class Account
{
	private:
	// Member variables
	int account_number;
	char name[50];
	int deposit;
	char type;

	public:
	// Member functions

	// Constructor
	Account()
	{
		account_number = 0;
		strcpy(name, "");
		deposit = 0;
		type = 'D';
	}

	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int get_account_number() const;
	int get_deposit() const;
	char get_type() const;
};

// Create an account
void Account::create_account()
{
	cout << "\n================== Create account ==================\n";
	counter++;
	account_number = counter;
	cout << "\nEnter the name of the client: ";
	cin.getline(name, 50);
	do
	{
		type = get_valid_input<char>("Enter the type of the account (P for private, C for company): ");
		type = toupper(type);
	} while (type != 'P' && type != 'C');
	deposit = get_valid_input<int>("Enter deposit: ");
	cout << "\n====================================================\n";
}

// Display current account
void Account::show_account() const
{
	cout << "\n================== Balance detail ==================\n";
	cout << "\nAccount number:            " << account_number << endl;
	cout << "Name of the account owner: " << name << endl;
	cout << "Type of account:           " << type << endl;
	cout << "Current sum:               " << deposit << endl;
	cout << "\n====================================================\n";
}

// Modify an account
void Account::modify()
{
	cout << "\n================== Modify account ==================\n";
	cout << "\nAccount number: " << account_number << endl;
	cout << "Enter the name of the client: ";
	cin.getline(name, 50);
	do
	{
		type = get_valid_input<char>("Change type: ");
		type = toupper(type);
	} while (type != 'P' && type != 'C');
	deposit = get_valid_input<int>("Change deposit: ");
	cout << "\n====================================================\n";
}

// Deposit in account
void Account::dep(int x)
{
	deposit += x;
}

// Draw from account
void Account::draw(int x)
{
	deposit -= x;
}

// Print all the accounts
void Account::report() const
{
	cout << left << setfill(' ') << setw(10) << account_number << " "
		<< setw(50) << left << name << " "
		<< setw(5) << type << " "
		<< "$" << deposit << endl;
}

// Get the account number
int Account::get_account_number() const
{
	return account_number;
}

// Get the deposit
int Account::get_deposit() const
{
	return deposit;
}

// Get the type
char Account::get_type() const
{
	return type;
}

// Functions
void print_menu();
int get_choice();
void write_account();
void display_data(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
static int count_accounts();

int main()
{
	int choice = 0;
	do
	{
		print_menu();
		choice = get_choice();
		switch (choice)
		{
			case 1:
				counter = count_accounts();
				write_account();
				break;
			case 2:
				deposit_withdraw(get_valid_input<int>("\t\t   Enter account number: "), 1);
				break;
			case 3:
				deposit_withdraw(get_valid_input<int>("\t\t   Enter account number: "), 2);
				break;
			case 4:
				display_data(get_valid_input<int>("\t\t   Enter account number: "));
				break;
			case 5:
				display_all();
				break;
			case 6:
				delete_account(get_valid_input<int>("\t\t   Enter account number: "));
				break;
			case 7:
				modify_account(get_valid_input<int>("\t\t   Enter account number: "));
				break;
			case 8:
				cout << "\n\tThank you for using this bank system";
				break;
			default:
				cout << "\a";
				break;
		}
		cin.get(); // For a pause every new operation
	} while (choice != 8);

	return 0;
}

// Print the menu
void print_menu()
{
	cout << "\n==================== Main  menu ====================\n";
	cout << "\n\t\t   1. New account";
	cout << "\n\n\t\t   2. Deposit Sum";
	cout << "\n\n\t\t   3. Withdraw sum";
	cout << "\n\n\t\t   4. Current balance";
	cout << "\n\n\t\t   5. Print users";
	cout << "\n\n\t\t   6. Close account";
	cout << "\n\n\t\t   7. Change account";
	cout << "\n\n\t\t   8. Close\n";
	cout << "\n====================================================\n";
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("\n\t\t   Enter choice: ");
	} while (choice < 1 || choice > 8);
	return choice;
}

// Create a account
void write_account()
{
	Account account;

	ofstream output_file("account.dat", ios::binary | ios::app); //------------ Open account.dat file for writing in binary append mode
	if (!output_file)
	{
		cerr << "Cant open file! with name account.dat" << endl;
	}

	account.create_account(); //----------------------------------------------- Create new account and get user input

	output_file.write(reinterpret_cast<char *> (&account), sizeof(Account)); // Write account object to the file
	output_file.close();

	cout << "\n\t\t   Account created!" << endl;
}

// Display data for a current user
void display_data(int n)
{
	Account account;
	bool found = false;

	ifstream input_file("account.dat", ios::binary); //----------------------------- Open the input file in binary mode
	if (!input_file.is_open())
	{
		cerr << "Cant open file! with name account.dat" << endl;
		return;
	}

	while (input_file.read(reinterpret_cast<char *> (&account), sizeof(Account))) // Loop through all the accounts in the file
	{
		if (account.get_account_number() == n) //----------------------------------- If the account number matches n, display the account details
		{
			account.show_account();
			found = true;
		}
	}

	input_file.close();

	if (found == false)
	{
		cout << endl << "Account does not exist!" << endl;
	}
}

// Modify an account
void modify_account(int n)
{
	Account account;
	bool found = false;

	fstream file("account.dat", ios::binary | ios::in | ios::out); //----------- Create a binary file stream to read and write from the account.dat file
	if (!file.is_open())
	{
		cerr << "Cant open file! with name account.dat" << endl;
		return;
	}

	while (!file.eof() && found == false) //------------------------------------ Loop through all accounts in the file until the account with the given account number is found
	{
		file.read(reinterpret_cast<char *> (&account), sizeof(Account)); //----- Read the current account from the file

		if (account.get_account_number() == n) //------------------------------- Check if the current account has the given account number
		{
			account.show_account(); //------------------------------------------ Display the current account details
			account.modify(); //------------------------------------------------ Modify the current account

			int pos = (-1) * static_cast<int>(sizeof(Account)); //-------------- Move the file pointer back to the beginning of the current account record
			file.seekp(pos, ios::cur); //--------------------------------------- Move it
			file.write(reinterpret_cast<char *> (&account), sizeof(Account)); // Overwrite the current account record with the modified account

			cout << "\n\t\t   Information updated!" << endl;

			found = true;
		}
	}

	file.close();

	if (found == false)
	{
		cout << endl << "Account does not exist!" << endl;
	}
}

// Delete an account
void delete_account(int n)
{
	Account account;
	bool found = false;

	ifstream input_file("account.dat", ios::binary); //----------------------------- Open the input file for reading in binary mode
	if (!input_file.is_open())
	{
		cerr << "Cant open file! with name account.dat" << endl;
		return;
	}

	ofstream output_file("temp.dat", ios::binary); //------------------------------- Open a temporary file for writing in binary mode
	if (!output_file.is_open())
	{
		cerr << "Error: deleting account!" << endl;
		input_file.close();
		return;
	}

	input_file.seekg(0, ios::beg);  //---------------------------------------------- Move the file pointer to the beginning of the file

	while (input_file.read(reinterpret_cast<char *> (&account), sizeof(Account))) // Loop through the file, reading each account's information and writing it to the temporary file
	{
		if (account.get_account_number() != n)
		{
			output_file.write(reinterpret_cast<char *> (&account), sizeof(Account));
		}
		else
		{
			found = true;
		}
	}

	input_file.close();
	output_file.close();

	if (found == false) //---------------------------------------------------------- If the account is not found just remove the temp, otherwise rename it and remove the old file
	{
		remove("temp.dat");
		cout << endl << "Account does not exist!" << endl;
		return;
	}
	else
	{
		remove("account.dat");
		rename("temp.dat", "account.dat");
		cout << "\n\t\t   Account is deleted!" << endl;
	}
}

// Display all the accounts
void display_all()
{
	Account account;

	ifstream input_file("account.dat", ios::binary);  //-------------------------------------------- Open the input file for reading in binary mode
	if (!input_file.is_open())
	{
		cerr << "Cant open file! with name account.dat" << endl;
		return;
	}

	cout << "\nAc no.     Name                                              Type   Deposit";
	cout << "\n=================================================================================\n";

	while (input_file.read(reinterpret_cast<char *> (&account), sizeof(Account))) //---------------- Loop through the file, reading each account's information and printing it to the console
	{
		account.report(); //------------------------------------------------------------------------ Display the data
	}

	input_file.close();
}

// Deposit and withdraw function
void deposit_withdraw(int n, int option)
{
	Account account;
	int amount = 0;
	bool found = false;

	fstream file("account.dat", ios::binary | ios::in | ios::out); //-------------------------------------------------------------- Create a binary file stream to read and write from the account.dat file
	if (!file.is_open())
	{
		cerr << "Cant open file! with name account.dat amount" << endl;
		return;
	}

	while (!file.eof() && found == false) //--------------------------------------------------------------------------------------- Read from the file until the end of file or the account with the specified number is found
	{
		file.read(reinterpret_cast<char *> (&account), sizeof(Account));  //------------------------------------------------------- Read the next Account object from the file

		if (account.get_account_number() == n) //---------------------------------------------------------------------------------- Check if the account number matches the specified number
		{
			account.show_account(); //--------------------------------------------------------------------------------------------- Display the account details

			if (option == 1) //---------------------------------------------------------------------------------------------------- Deposit
			{
				amount = get_valid_input<int>("Enter amount to deposit: "); //----------------------------------------------------- Get the user to enter the amount to deposit and update the account balance
				account.dep(amount);

				cout << "\n\t\t   Balance changed!" << endl;
			}

			if (option == 2) //---------------------------------------------------------------------------------------------------- Withdraw
			{
				amount = get_valid_input<int>("Enter amount to withdraw: "); //---------------------------------------------------- Get the user to enter the amount to withdraw
				int total = account.get_deposit() - amount;

				if ((total < 500 && account.get_type() == 'P') || (total < 1000 && account.get_type() == 'C')) //------------------ Calculate the new balance after the withdrawal and check if it meets the minimum balance requirements
				{
					cout << "Cant take out when you don't have at least 500$ for private and 1000 for company in deposit!" << endl;

					file.close();
					return; //----------------------------------------------------------------------------------------------------- If condition is not met return and don't change anything
				}
				else
				{
					account.draw(amount);

					cout << "\n\t\t   Balance changed!" << endl;
				}
			}

			int pos = (-1) * static_cast<int>(sizeof(account)); //----------------------------------------------------------------- Move the file pointer back to the position of the current account object and overwrite it with the updated object, because we read the data and the pointer is at the end now we need to set it back to the beginning of the object
			file.seekp(pos, ios::cur); //------------------------------------------------------------------------------------------ Move it
			file.write(reinterpret_cast<char *> (&account), sizeof(Account)); //--------------------------------------------------- Overwrite the current account record with the modified account

			found = true;
		}
	}

	file.close();

	if (found == false)
	{
		cout << endl << "Account does not exist!" << endl;
	}
}

// Get the last index of the user in the file
static int count_accounts()
{
	Account account;
	int counter = 0;

	ifstream input_file("account.dat", ios::binary);  //-------------------------------------------- Open the input file for reading in binary mode
	if (!input_file.is_open())
	{
		cerr << "Cant open file! with name account.dat" << endl;
		return counter;
	}

	while (input_file.read(reinterpret_cast<char *> (&account), sizeof(Account))) //---------------- Loop through the file, adding the account index to the counter
	{
		counter = account.get_account_number();
	}

	input_file.close();

	return counter;
}