#include <iostream>
#include "basic_functions.h"

using namespace std;

// Globals
int GENERATIONS = get_valid_input<int>("Enter number of generations:");
int INDENT_LENGTH = GENERATIONS + 1;

// Struct
struct Person
{
	Person *parents[2];
	char alleles[2];
};

// Functions
Person *create_family(int generations);
void print_family(Person *p, int generation);
void free_family(Person *p);
char random_allele();

int main()
{
	srand(time(0)); //------------------------ Seed random number generator

	Person *p = create_family(GENERATIONS); // Create a new family with three generations

	print_family(p, 0); //-------------------- Print family tree of blood types

	free_family(p); //------------------------ Free memory
}

// Create a new individual with `generations`
Person *create_family(int generations)
{
	// Allocate memory for new person
	Person *new_person = new Person;

	// Generations left to create
	if (generations > 1)
	{
		// Recursively create two new parents
		Person *parent0 = create_family(generations - 1);
		Person *parent1 = create_family(generations - 1);

		// Set parent pointers
		new_person->parents[0] = parent0;
		new_person->parents[1] = parent1;

		// Assign current person's alleles based on the alleles of their parents
		new_person->alleles[0] = parent0->alleles[rand() % 2];
		new_person->alleles[1] = parent1->alleles[rand() % 2];
	}
	// No generations left to create
	else
	{
		// Set parent pointers to NULL
		new_person->parents[0] = nullptr;
		new_person->parents[1] = nullptr;

		// Randomly assign alleles
		new_person->alleles[0] = random_allele();
		new_person->alleles[1] = random_allele();
	}

	return new_person;
}

// Free `p` and all ancestors of `p`.
void free_family(Person *p)
{
	if (p == nullptr)
	{
		return;
	}

	// Free parents recursively
	free_family(p->parents[0]);
	free_family(p->parents[1]);

	// Free child
	delete p;
}

// Print each family member and their alleles.
void print_family(Person *p, int generation)
{
	if (p == nullptr)
	{
		return;
	}

	// Print indentation
	for (int i = 0; i < generation * INDENT_LENGTH; i++)
	{
		cout << " ";
	}

	// Print person
	if (generation == 0)
	{
		cout << "Child (Generation " << generation << "): blood type " << p->alleles[0] << p->alleles[1] << "\n";
	}
	else if (generation == 1)
	{
		cout << "Parent (Generation " << generation << "): blood type " << p->alleles[0] << p->alleles[1] << "\n";
	}
	else
	{
		for (int i = 0; i < generation - 2; i++)
		{
			cout << "Great-";
		}
		cout << "Grandparent (Generation " << generation << "): blood type " << p->alleles[0] << p->alleles[1] << "\n";
	}

	// Print parents
	print_family(p->parents[0], generation + 1);
	print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
	int r = rand() % 3;
	if (r == 0)
	{
		return 'A';
	}
	else if (r == 1)
	{
		return 'B';
	}
	else
	{
		return 'O';
	}
}