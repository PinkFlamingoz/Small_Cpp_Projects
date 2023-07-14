#include <iostream>
#include "headers/basic_functions.h"
#include <string>

using namespace std;

// Globals
const int MAX_SIZE = 100;

int main()
{
	string word = "";
	string cut = "";

	int i = 0, j = 0, length = 0, k = 0;

	word = get_valid_input<string>("Enter word: ");
	length = word.length();
	k = get_valid_input<int>("Portion sizes: ");

	if (k > length) //---------------------------- Check if the cut is bigger than the string
	{
		cerr << "Out of bounds!" << endl;
	}
	else
	{
		for (i = 0; i < length - k + 1; i++) //--- Loop for total cuts, example "Word" k=2, Wo, or, rd;
		{
			cut.clear(); //----------------------- Clear the cut string before each iteration
			for (j = 0; j < k; j++) //------------ Loop for each new cut
			{
				cut += word[i + j]; //------------ Append characters to the cut string
			}
			cut[k] = '\0'; //--------------------- Move this statement outside the inner loop
			cout << cut << endl;
			//------------------------------------ NOTE: Alternatively, we can use cout.write(cut.c_str(), k) to output only the first k characters of cut
		}
	}

	return 0; //---------------------------------- Success
}