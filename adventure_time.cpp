#include <iostream>
#include <string>

using namespace std;

int main() {
	// Get the name
	string Name = "";
	cout << "What is your name stranger? \n";
	getline(cin, Name);

	string LastName = "";
	cout << "And your last name? \n";
	getline(cin, LastName);

	cout << "Hello there, " << LastName << " " << Name << ". ";

	// Get the age
	int Age = 0;
	cout << "What is your age Mr./Ms." << LastName << "? \n";
	while (!(cin >> Age)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter an integer for your age: \n";
	}

	if (Age < 30) {
		cout << "Still so young, only " << Age << ". \n";
	}
	else if (Age > 30 && Age < 60) {
		cout << "Right dab in the middle buddy, " << Age << ". \n";
	}
	else {
		cout << "At least you're alive!!!, " << Age << ". \n";
	}

	// Get the Feels
	char Happy = ' ';
	cout << "Are you happy so far?(Y or N) \n";
	while (!(cin >> Happy)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter Y or N: ";
	}

	if (Happy == 'Y' || Happy == 'y') {
		cout << "I knew you were " << Name << "! Keep it up. \n";
	}
	else if (Happy == 'N' || Happy == 'n') {
		cout << ":( I love you " << Name << " and I know it sucks! \n";
	}
	else {
		cout << "Come on now " << Name << ", " << Happy << " is not a answer to my question :( \n";
	}

	// Dog or Cat
	int Door = 0;
	cout << "Infront you have two doors with the number 1 or 2, what do you pick? \n";
	while (!(cin >> Door)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter 1 or 2: ";
	}

	if (Door == 1) {
		int i = 0;
		while (i < Age) {
			cout << "meow \n";
			i++;
		}
		cout << "You found a cute cat neat! \n";

		char Pet = ' ';
		cout << "Pet the cat?(Y or N) \n";
		while (!(cin >> Pet)) {
			cin.clear();
			cin.ignore();
			cout << "Please enter Y or N: ";
		}

		if (Pet == 'Y' || Pet == 'y') {
			int Times = 0;
			cout << "How many times do you pet \n";
			while (!(cin >> Times)) {
				cin.clear();
				cin.ignore();
				cout << "Please enter an integer: ";
			}
			for (i = 0; i < Times; i++) {
				cout << "PRR \n";
			}
		}
		else if (Pet == 'N' || Pet == 'n') {
			cout << "You lost your twin flame " << Name << " :( \n";
		}
		else {
			cout << "Come on now " << Name << ", " << Pet << " is not a answer to my question :( \n";
		}
	}
	else if (Door == 2) {
		int i = 100;
		while (i > Age)
		{
			cout << "Wof \n";
			i--;
		}
		cout << "A wild dog killed you :( Good Bye! \n";
	}
	else
	{
		cout << "Dont hit yourself in the wall ... " << Name << ", Good Bye! \n";
	}

	// Secrets of the universe
	char Ready;
	cout << "Last chance to know everything in life are you ready?(Y or N)(To stop say the magick word of CTRL + C!) \n";
	cin >> Ready;
	if (Ready == 'Y' || Ready == 'y')
	{
		long long i, n;
		long long t1 = 0, t2 = 1;
		long long nextTerm = t1 + t2;
		cout << "Till when do I STOP? \n";
		while (!(cin >> n)) {
			cin.clear();
			cin.ignore();
			cout << "Please enter an integer: ";
		}
		cout << t1 << ",\n" << t2 << ",\n";
		for (i = 3; i <= n; ++i)
		{
			cout << nextTerm << ", \n";
			t1 = t2;
			t2 = nextTerm;
			nextTerm = t1 + t2;
		}
	}
	else if (Ready == 'N' || Ready == 'n')
	{
		cout << "You wake up and wish you did not :( \n";
	}
	else
	{
		cout << "You wake up and never gonna drink that tea again! \n";
	}

	return 0;
}