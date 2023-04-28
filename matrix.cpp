#include <iostream>
#include <math.h>
#include <vector>
#include <unordered_map>
#include "basic_functions.h"

using namespace std;

class Matrix
{
	private:
	// Member variables
	int rows;
	int cols;
	vector<vector<double>> data;
	static int counter;

	// Member functions

	// Helper function to compute submatrix
	Matrix submatrix(int row, int col) const
	{
		Matrix sub(rows - 1, cols - 1);
		int r = 0;
		for (int i = 0; i < rows; ++i)
		{
			if (i == row)
			{
				continue;
			}
			int c = 0;
			for (int j = 0; j < cols; ++j)
			{
				if (j == col)
				{
					continue;
				}
				sub.data[r][c] = data[i][j];
				++c;
			}
			++r;
		}
		return sub;
	}

	// Helper function to compute adjugate matrix
	Matrix adjugate() const
	{
		Matrix adj(cols, rows);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				adj.data[j][i] = pow(-1, i + j) * submatrix(i, j).determinant();
			}
		}
		return adj;
	}

	public:
	// Member functions

	Matrix()
	{
		rows = 0;
		cols = 0;
	}

	// Parameter constructor
	Matrix(int rows, int cols)
	{
		this->rows = rows;
		this->cols = cols;
		data.resize(rows, vector<double>(cols));
	}

	// Get the rows
	int get_rows() const
	{
		return rows;
	}

	// Get the cols
	int get_cols() const
	{
		return cols;
	}

	// Static function get counter
	static int get_count()
	{
		return counter;
	}

	// Static function increment counter
	static int increment_counter()
	{
		return counter++;
	}

	// Set the data of the matrix
	void set_data()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "Enter element [" << i << "][" << j << "]: ";
				data[i][j] = get_valid_input<double>("");
			}
		}
	}

	// Print the data of the matrix
	void print_data() const
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "[" << data[i][j] << "]" << "\t";
			}
			cout << endl;
		}
	}

	// Addition
	Matrix operator+(const Matrix &other) const
	{
		try
		{
			if (cols != other.cols || rows != other.rows)
			{
				throw invalid_argument("Matrices must be of same size.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //-------------------------------------- Return a static dummy Matrix object as a reference
			return dummy;
		}

		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}

	// Subtraction
	Matrix operator-(const Matrix &other) const
	{
		try
		{
			if (cols != other.cols || rows != other.rows)
			{
				throw invalid_argument("Matrices must be of same size.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //-------------------------------------- Return a static dummy Matrix object as a reference
			return dummy;
		}

		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return result;
	}

	// Multiplication
	Matrix operator*(const Matrix &other) const
	{
		try
		{
			if (cols != other.rows)
			{
				throw invalid_argument("Number of columns of the first matrix must match the number of rows of the second matrix.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //------------------------------------------------------------------------------------------------- Return a static dummy Matrix object as a reference
			return dummy;
		}

		Matrix result(rows, other.cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < other.cols; ++j)
			{
				for (int k = 0; k < cols; ++k)
				{
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}

	// Multiply by a scalar value (element-wise multiplication)
	Matrix operator*(double scalar) const
	{
		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				result.data[i][j] = data[i][j] * scalar;
			}
		}
		return result;
	}

	// Divide by a scalar value (element-wise division)
	Matrix operator/(double scalar) const
	{
		try
		{
			if (scalar == 0)
			{
				throw invalid_argument("Division by zero.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //------------------------- Return a static dummy Matrix object as a reference
			return dummy;
		}

		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				result.data[i][j] = data[i][j] / scalar;
			}
		}
		return result;
	}

	// Assignment
	Matrix &operator=(const Matrix &other)
	{
		if (this != &other)
		{
			// Clear existing data
			data.clear();

			// Copy new data
			rows = other.rows;
			cols = other.cols;
			data.resize(rows, vector<double>(cols));
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	// Override << operator to print matrix
	friend ostream &operator<<(ostream &os, const Matrix &matrix)
	{
		for (int i = 0; i < matrix.rows; i++)
		{
			for (int j = 0; j < matrix.cols; j++)
			{
				os << "[" << matrix.data[i][j] << "]" << "\t";
			}
			os << endl;
		}
		return os;
	}

	// Transpose matrix
	Matrix transpose() const
	{
		Matrix result(cols, rows);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				result.data[j][i] = data[i][j];
			}
		}
		return result;
	}

	// Calculate matrix determinant
	double determinant() const
	{
		try
		{
			if (rows != cols)
			{
				throw invalid_argument("Matrix must be square to compute determinant.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static double dummy = 0; //------------------------------------------------- Return a static dummy double as a reference
			return dummy;
		}

		if (rows == 1)
		{
			return data[0][0];
		}

		double det = 0;
		for (int i = 0; i < rows; ++i)
		{
			det += pow(-1, i) * data[0][i] * submatrix(0, i).determinant();
		}
		return det;
	}

	// Calculate matrix inverse
	Matrix inverse() const
	{
		double det = 0;
		try
		{
			if (rows != cols)
			{
				throw invalid_argument("Matrix must be square to compute inverse.");
			}

			det = determinant();
			if (det == 0)
			{
				throw runtime_error("Matrix is singular, cannot compute inverse.");
			}
		}
		catch (const invalid_argument &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //------------------------------------------------ Return a static dummy Matrix object as a reference
			return dummy;
		}
		catch (const runtime_error &e)
		{
			cerr << e.what() << endl;
			static Matrix dummy; //------------------------------------------------ Return a static dummy Matrix object as a reference
			return dummy;
		}

		Matrix adj = adjugate();
		return adj / det;
	}

	// Add function
	static Matrix add(const Matrix &a, const Matrix &b)
	{
		return a + b;
	}

	// Sub function
	static Matrix sub(const Matrix &a, const Matrix &b)
	{
		return a - b;
	}

	// Multiply function
	static Matrix multiply(const Matrix &a, const Matrix &b)
	{
		return a * b;
	}

	// Multiply by scalar function
	static Matrix multiply_by_scalar(const Matrix &a, double scalar)
	{
		return a * scalar;
	}

	// Division by scalar function
	static Matrix divide_by_scalar(const Matrix &a, double scalar)
	{
		return a / scalar;
	}

	// Transpose matrix function
	static Matrix tran(const Matrix &a)
	{
		return a.transpose();
	}

	// Determinant of a matrix function
	static double dete(const Matrix &a)
	{
		double det = 0;
		return det = a.determinant();
	}

	// Inverse of a matrix function
	static Matrix inve(const Matrix &a)
	{
		return a.inverse();
	}
};

// Globals
unordered_map<string, Matrix> matrices;
Matrix temp(0, 0);

// Initialize static member variables
int  Matrix::counter = 0;

// Functions
void create_matrix();
void delete_matrix();
Matrix &select_from_hash_table();
void print_menu();
int get_choice();
void print_created_matrices();
int get_choice_for_temp();
void add_or_clear_temp(Matrix n);
void clear_temp();
void print_result(Matrix n);
bool check_if_empty_hash_table();

int main()
{
	bool done = false;
	while (!done)
	{
		print_menu();
		int choice = get_choice();
		switch (choice)
		{
			case 1:
				create_matrix();
				break;
			case 2:
				if (check_if_empty_hash_table())
				{
					break;
				}
				delete_matrix();
				break;
			case 3:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::add(select_from_hash_table(), select_from_hash_table()));
				break;
			case 4:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::sub(select_from_hash_table(), select_from_hash_table()));
				break;
			case 5:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::multiply(select_from_hash_table(), select_from_hash_table()));
				break;
			case 6:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::multiply_by_scalar(select_from_hash_table(), get_valid_input<double>("Enter scalar: ")));
				break;
			case 7:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::divide_by_scalar(select_from_hash_table(), get_valid_input<double>("Enter scalar: ")));
				break;
			case 8:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::tran(select_from_hash_table()));
				break;
			case 9:
				if (check_if_empty_hash_table())
				{
					break;
				}
				cout << Matrix::dete(select_from_hash_table()) << endl;
				break;
			case 10:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_result(Matrix::inve(select_from_hash_table()));
				break;
			case 11:
				if (temp.get_rows() == 0 && temp.get_cols() == 0)
				{
					cerr << "Temp is empty!" << endl;
					break;
				}
				clear_temp();
				break;
			case 12:
				if (check_if_empty_hash_table())
				{
					break;
				}
				print_created_matrices();
				break;
			case 13:
				system("cls");
				break;
			case 14:
				done = true;
				break;
			default:
				cout << "Try again!" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	}
	return 0;
}

// Create a matrix with increasing name, we will store them in a hash table, with the key being their name, and the value will be the actual matrix
void create_matrix()
{
	string name = "c" + to_string(Matrix::get_count()); //---------------------------------- Get the name of the matrix

	Matrix c(get_valid_input<int>("Enter rows: "), get_valid_input<int>("Enter cols: ")); // Crate the matrix

	c.set_data(); //------------------------------------------------------------------------ Set the data for the matrix

	matrices[name] = c; //------------------------------------------------------------------ Add the matrix with the key name and the created matrix

	cout << "Matrix " << name << " has been created!" << endl;

	Matrix::increment_counter(); //--------------------------------------------------------- Increment the object counter so we increase the value of the next matrix name

	c.print_data();
}

// Delete a matrix in the hash table
void delete_matrix()
{
	string name = get_valid_input<string>("Enter the name of the matrix you want to delete: "); // Get the name we want to delete

	auto it = matrices.find(name); //------------------------------------------------------------- Get the name we want to find
	if (it != matrices.end())
	{
		matrices.erase(it); //-------------------------------------------------------------------- Delete it
		cout << "Matrix " << name << " deleted." << endl;
		print_created_matrices();
	}
	else
	{
		cerr << "Invalid matrix name: " + name << endl;
		return;
	}
}

// Select a matrix from the hash table
Matrix &select_from_hash_table()
{
	string name = get_valid_input<string>("Select a matrix: ");

	auto it = matrices.find(name); //-------------------------- Get the key aka name
	if (it != matrices.end())
	{
		return it->second; //---------------------------------- Return a reference to the value in the map
	}
	else
	{
		cerr << "Invalid matrix name: " + name << endl;
		static Matrix dummy; //-------------------------------- Return a static dummy Matrix object as a reference
		return dummy;
	}
}

// Print the menu options
void print_menu()
{
	cout << "Chose operations: " << endl;

	cout << "1. Create a matrix " << endl;
	cout << "2. Remove a matrix " << endl;

	cout << "3. Add                    ,operator: (+) " << endl;
	cout << "4. Subtract               ,operator: (-) " << endl;
	cout << "5. Multiply               ,operator: (*) " << endl;
	cout << "6. Multiply by scalar     ,operator: (*) " << endl;
	cout << "7. Divide by scalar       ,operator: (/) " << endl;

	cout << "8. Transpose " << endl;
	cout << "9. Determinant " << endl;
	cout << "10. Inverse " << endl;

	cout << "11. Clear temp " << endl;
	cout << "12. Print Matrices " << endl;
	cout << "13. Clear screen " << endl;
	cout << "14. DONE " << endl;
}

// Get choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 1 || choice > 14);
	return choice;
}

// Pint the matrix we have created
void print_created_matrices()
{
	for (auto &matrix : matrices)
	{
		cout << matrix.first << ": " << endl << matrix.second << endl;
	}

	if (temp.get_rows() == 0 && temp.get_cols() == 0)
	{
		return;
	}

	cout << "Temp: " << endl << temp << endl;
}

// Get choice for the temp matrix
int get_choice_for_temp()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 1 || choice > 3);
	return choice;
}

// Options for the temp matrix
void add_or_clear_temp(Matrix n)
{
	cout << "Add in temp? " << endl;
	cout << "1: ADD, 2: CLEAR, 3: SKIP" << endl;
	Matrix new_temp(n.get_rows(), n.get_cols());
	int choice = get_choice_for_temp();
	switch (choice)
	{
		case 1:
			temp = new_temp + n;
			break;
		case 2:
			temp = new_temp;
			break;
		case 3:
			cout << "SKIP" << endl;
			break;
	}

	if (temp.get_rows() == 0 && temp.get_cols() == 0)
	{
		return;
	}

	cout << "Temp: " << endl << temp << endl;
}

// Options for the temp matrix
void clear_temp()
{
	Matrix new_temp(0, 0);
	temp = new_temp;
	cout << "Temp is cleared!" << endl;
}

// Print the result and decide if we add that result to the temp matrix in doing this we create a a step by step calculator for bigger equations
void print_result(Matrix n)
{
	if (n.get_rows() == 0 && n.get_cols() == 0)
	{
		return;
	}

	cout << "Result: " << endl << n << endl;
	add_or_clear_temp(n);
}

// Check if the hash table is empty
bool check_if_empty_hash_table()
{
	if (matrices.empty())
	{
		cerr << "Create a matrix first! " << endl;
		return true;
	}
	return false;
}