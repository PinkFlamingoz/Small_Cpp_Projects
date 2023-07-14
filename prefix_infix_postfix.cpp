#include <iostream>
#include <stack>
#include <algorithm>
#include "headers/basic_functions.h"

using namespace std;

// INFIX TO POSTFIX:
// 1.  Scan Expression from LEFT to RIGHT.
//
// 2.  Print OPERANDs as the arrive.
//
// 3.  If OPERATOR arrives & Stack is empty, PUSH this OPERATOR onto the stack.
//
// 4.  If incoming OPERATOR has HIGHER precedence than the TOP of the Stack, PUSH it on stack.
//
// 5.  If incoming OPERATOR has LOWER precedence than the TOP of the Stack, then POP and print the TOP. Then test the incoming OPERATOR against the new TOP of stack.
//
// 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
//
// 6.1 For ASSOCIATIVITY of LEFT to RIGHT –
//     POP and print the TOP of stack, then PUSH the incoming OPERATOR.
//
// 6.2 For ASSOCIATIVITY of RIGHT to LEFT – for operators '^'.
//     PUSH incoming OPERATOR on stack.
//
// 7.  At the end of Expression, POP & print all OPERATORS from the stack.
//
// 8.  If incoming SYMBOL is '(' PUSH it onto Stack.
//
// 9.  If incoming SYMBOL is ')' POP the stack and print OPERATORs till '(' is found. POP that '('.
//
// 10. If TOP of stack is '(' PUSH OPERATOR on Stack.

// INFIX TO PREFIX ( Same as INFIX TO POSTFIX BUT RULE 6 IS SWAPED ):
// 0.  Reverse infix expression & swap '(' to ')' & ')' to '('.
//
// 1.  Scan Expression from LEFT to RIGHT.
//
// 2.  Print OPERANDs as the arrive.
//
// 3.  If OPERATOR arrives & Stack is empty, PUSH this OPERATOR onto the stack.
//
// 4.  If incoming OPERATOR has HIGHER precedence than the TOP of the Stack, PUSH it on stack.
//
// 5.  If incoming OPERATOR has LOWER precedence than the TOP of the Stack, then POP and PRINT the TOP. Then test the incoming OPERATOR against the NEW TOP of stack.
//
// 6.1 For ASSOCIATIVITY of LEFT to RIGHT – for operators '^'.
//     POP and print the TOP of stack, then PUSH the incoming OPERATOR.
//
// 6.2 For ASSOCIATIVITY of RIGHT to LEFT –
//     PUSH incoming OPERATOR on stack.
//
// 7.  At the end of Expression, POP & PRINT all OPERATORS from the stack
//
// 8.  If incoming SYMBOL is '(' PUSH it onto Stack.
//
// 9.  If incoming SYMBOL is ')' POP the stack and print OPERATORs till '(' is found. POP that '('.
//
// 10. If TOP of stack is '(' PUSH OPERATOR on Stack.
//
// 0.  At the end Reverse output string again.

// POSTFIX TO INFIX:
// 1. Scan POSTFIX expression from LEFT to RIGHT.
//
// 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
//
// 3. If the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in between the 2 OPERANDs, ADD '(' & ')' to the whole expression & PUSH this whole new expression string back into the Stack.
//
// 4. At the end POP and PRINT the full INFIX expression from the Stack.

// PREFIX TO INFIX:
// 1. Scan PREFIX expression from RIGHT to LEFT or REVERSE the PREFIX expression and scan it from LEFT to RIGHT.
//
// 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
//
// 3. If the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in between the 2 OPERANDs, ADD '(' & ')' to the whole expression & PUSH this whole new expression string back into the Stack.
//
// 4. At the end POP and PRINT the full INFIX expression from the Stack.

// POSTFIX TO PREFIX:
// 1. Scan POSTFIX expression from LEFT to RIGHT
// 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
// 3. If the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in before the 2 OPERANDs & PUSH this whole new expression string back into the Stack.
// 4. At the end POP and PRINT the full PREFIX expression from the Stack.

// PREFIX TO POSTFIX:
// 1. Scan PREFIX expression from RIGHT to LEFT
// 2. IF the incoming symbol is an OPERAND, PUSH it onto the Stack.
// 3. IF the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in before the 2 OPERANDs & PUSH this whole new expression string back into the Stack.
// 4. At the end POP and PRINT the full POSTFIX expression from the Stack.

// Functions
void print_menu();
int get_choice();
bool is_operator(char c);
int precedence(char c);
string infix_to_postfix(stack<char> container, string infix);
void swap_parentheses(int length, string &infix);
string infix_to_prefix(stack<char> container, string infix);
bool is_operand(char c);
string postfix_to_infix(string postfix);
string prefix_to_infix(string prefix);
string postfix_to_prefix(string postfix);
string prefix_to_postfix(string prefix);

int main()
{
	int choice = 0;

	do
	{
		print_menu();
		choice = get_choice();
		stack<char> container;
		string infix = get_valid_input<string>("Enter infix: ");
		string postfix = "";
		string prefix = "";

		switch (choice)
		{
			case 0:
				break;
			case 1: //--------------------------------------- INFIX TO POSTFIX
				postfix = infix_to_postfix(container, infix);
				cout << "Infix   = " << infix << endl;
				cout << "Postfix = " << postfix << endl;
				break;
			case 2: //--------------------------------------- INFIX TO PREFIX
				prefix = infix_to_prefix(container, infix);
				cout << "Infix   = " << infix << endl;
				cout << "Prefix = " << prefix << endl;
				break;
			case 3: //--------------------------------------- POSTFIX TO INFIX
				postfix = infix_to_postfix(container, infix);
				infix = postfix_to_infix(postfix);
				cout << "Postfix = " << postfix << endl;
				cout << "Infix   = " << infix << endl;
				break;
			case 4: //--------------------------------------- PREFIX TO INFI
				prefix = infix_to_prefix(container, infix);
				infix = prefix_to_infix(prefix);
				cout << "Prefix = " << prefix << endl;
				cout << "Infix   = " << infix << endl;
				break;
			case 5: //--------------------------------------- POSTFIX TO PREFIX
				postfix = infix_to_postfix(container, infix);
				prefix = postfix_to_prefix(postfix);
				cout << "Postfix = " << postfix << endl;
				cout << "Prefix  = " << prefix << endl;
				break;
			case 6: //--------------------------------------- PREFIX TO POSTFIX
				prefix = infix_to_prefix(container, infix);
				postfix = prefix_to_postfix(prefix);
				cout << "Prefix  = " << prefix << endl;
				cout << "Postfix = " << postfix << endl;
				break;
			case 7:
				system("cls");
				break;
			default:
				cout << "Try again!" << endl;
				break;
		}
		cout << "\n\t\t"; system("pause"); // or cin.get(); // For a pause every new operation
	} while (choice != 0);

	return 0;
}

// Print the menu
void print_menu()
{
	cout << "\nWhat operation do you want to perform? Select Option number. Enter 0 to exit." << endl;
	cout << "Use - for a minus, and ~ for a negative number." << endl;
	cout << "1. Infix to Postfix" << endl;
	cout << "2. Infix to Prefix" << endl;
	cout << "3. Postfix to Infix" << endl;
	cout << "4. Prefix to Infix" << endl;
	cout << "5. Postfix to Prefix" << endl;
	cout << "6. Prefix to Postfix" << endl;
	cout << "7. Clear Screen" << endl << endl;
}

// Get the choice for the menu
int get_choice()
{
	int choice = 0;
	do
	{
		choice = get_valid_input<int>("Enter choice: ");
	} while (choice < 0 || choice > 7);
	return choice;
}

// Is it an operator
bool is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		return true;
	}

	return false;
}

// Calculate precedence so we know what operation to do first
int precedence(char c)
{
	if (c == '^')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}

	return -1; //----------------- 10. If TOP of stack is '(' PUSH OPERATOR on Stack.
}

// INFIX TO POSTFIX
string infix_to_postfix(stack<char> container, string infix)
{
	string postfix = "";
	int length = infix.length();

	for (int i = 0; i < length; i++) //----------------------------------------------------------------- 1.  Scan Expression from LEFT to RIGHT.
	{
		if (isalnum(infix[i]) || infix[i] == '~') //---------------------------------------------------- 2.  Print OPERANDs as the arrive.
		{
			postfix += infix[i];
		}
		else if (infix[i] == '(') //-------------------------------------------------------------------- 8.  If incoming SYMBOL is '(' PUSH it onto Stack.
		{
			container.push(infix[i]);
		}
		else if (infix[i] == ')') //-------------------------------------------------------------------- 9.  If incoming SYMBOL is ')' POP the stack and print OPERATORs till '(' is found. POP that '('.
		{
			while (container.top() != '(' && !container.empty())
			{
				postfix += container.top();
				container.pop();
			}

			if (container.top() == '(') //-------------------------------------------------------------- 9.  POP that '('.
			{
				container.pop();
			}
		}
		else if (is_operator(infix[i]))
		{
			if (container.empty()) //------------------------------------------------------------------- 3.  If OPERATOR arrives & Stack is empty, PUSH this OPERATOR onto the stack.
			{
				container.push(infix[i]);
			}
			else
			{
				if (precedence(infix[i]) > precedence(container.top())) //------------------------------ 4.  If incoming OPERATOR has HIGHER precedence than the TOP of the Stack, PUSH it on stack.
				{
					container.push(infix[i]);
				}
				else if (precedence(infix[i]) == precedence(container.top()) && (infix[i] == '^')) //--- 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
				{                                                                                     // 6.2 For ASSOCIATIVITY of RIGHT to LEFT – for operators '^'.
					container.push(infix[i]);                                                         //     PUSH incoming OPERATOR on stack.
				}
				else
				{
					while (!container.empty() && precedence(infix[i]) <= precedence(container.top())) // 5.  If incoming OPERATOR has LOWER precedence than the TOP of the Stack, then POP and print the TOP. Then test the incoming OPERATOR against the new TOP of stack.
					{                                                                                 // 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
						postfix += container.top();                                                   // 6.1 For ASSOCIATIVITY of LEFT to RIGHT –
						container.pop();                                                              //     POP and print the TOP of stack, then PUSH the incoming OPERATOR.
					}
					container.push(infix[i]);
				}
			}
		}
	}

	while (!container.empty()) //----------------------------------------------------------------------- 7.  At the end of Expression, POP & print all OPERATORS from the stack.
	{
		postfix += container.top();
		container.pop();
	}

	return postfix;
}

// Swap parentheses
void swap_parentheses(int length, string &infix)
{
	for (int i = 0; i < length; i++)
	{
		if (infix[i] == '(')
		{
			infix[i] = ')';
		}
		else if (infix[i] == ')')
		{
			infix[i] = '(';
		}
	}
}

// INFIX TO PREFIX
string infix_to_prefix(stack<char> container, string infix)
{
	string prefix = "";
	int length = infix.length();

	reverse(infix.begin(), infix.end()); //------------------------------------------------------------- 0.  Reverse infix expression & swap '(' to ')' & ')' to '('.
	swap_parentheses(length, infix);

	for (int i = 0; i < length; i++) //----------------------------------------------------------------- 1.  Scan Expression from LEFT to RIGHT.
	{
		if (isalnum(infix[i]) || infix[i] == '~') //---------------------------------------------------- 2.  Print OPERANDs as the arrive.
		{
			prefix += infix[i];
		}
		else if (infix[i] == '(') //-------------------------------------------------------------------- 8.  If incoming SYMBOL is '(' PUSH it onto Stack.
		{
			container.push(infix[i]);
		}
		else if (infix[i] == ')') //-------------------------------------------------------------------- 9.  If incoming SYMBOL is ')' POP the stack and print OPERATORs till '(' is found. POP that '('.
		{
			while (container.top() != '(' && !container.empty())
			{
				prefix += container.top();
				container.pop();
			}

			if (container.top() == '(') //-------------------------------------------------------------- 9.  POP that '('.
			{
				container.pop();
			}
		}
		else if (is_operator(infix[i]))
		{
			if (container.empty()) //------------------------------------------------------------------- 3.  If OPERATOR arrives & Stack is empty, PUSH this OPERATOR onto the stack.
			{
				container.push(infix[i]);
			}
			else
			{
				if (precedence(infix[i]) > precedence(container.top())) //------------------------------ 4.  If incoming OPERATOR has HIGHER precedence than the TOP of the Stack, PUSH it on stack.
				{
					container.push(infix[i]);
				}
				else if (precedence(infix[i]) == precedence(container.top()) && (infix[i] == '^'))    // 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
				{																					  // 6.1 For ASSOCIATIVITY of LEFT to RIGHT – for operators '^'.
					while (precedence(infix[i]) == precedence(container.top()) && infix[i] == '^')    //     POP and print the TOP of stack, then PUSH the incoming OPERATOR.
					{
						prefix += container.top();
						container.pop();
					}
					container.push(infix[i]);
				}
				else if (precedence(infix[i]) == precedence(container.top())) //------------------------ 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
				{                                                                                     // 6.2 For ASSOCIATIVITY of RIGHT to LEFT –
					container.push(infix[i]);                                                         //     PUSH incoming OPERATOR on stack.
				}
				else
				{
					while (!container.empty() && precedence(infix[i]) < precedence(container.top()))  // 5.  If incoming OPERATOR has LOWER precedence than the TOP of the Stack, then POP and print the TOP. Then test the incoming OPERATOR against the new TOP of stack.
					{
						prefix += container.top();
						container.pop();
					}
					container.push(infix[i]);
				}
			}
		}
	}

	while (!container.empty()) //----------------------------------------------------------------------- 7.  At the end of Expression, POP & print all OPERATORS from the stack.
	{
		prefix += container.top();
		container.pop();
	}

	reverse(prefix.begin(), prefix.end()); //----------------------------------------------------------- 0.  At the end Reverse output string again.

	return prefix;
}

// Is it an operand
bool is_operand(char c)
{
	if (isalnum(c))
	{
		return true;
	}

	return false;
}

// POSTFIX TO INFIX
string postfix_to_infix(string postfix)
{
	stack<string> container;
	int length = postfix.length();

	for (int i = 0; i < length; i++) //------------------------------------ 1. Scan POSTFIX expression from LEFT to RIGHT.
	{
		if (is_operand(postfix[i])) //------------------------------------- 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
		{
			string operand(1, postfix[i]); //------------------------------ We must use this constructor because if we simply string operand = postfix[i]; we get a error!
			container.push(operand);
		}
		else //------------------------------------------------------------ 3. If the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in between the 2 OPERANDs, ADD '(' & ')' to the whole expression & PUSH this whole new expression string back into the Stack.
		{
			string operand_1 = container.top();
			container.pop();
			string operand_2 = container.top();
			container.pop();
			container.push("(" + operand_2 + postfix[i] + operand_1 + ")");
		}
	}

	return container.top();
}

// PREFIX TO INFIX
string prefix_to_infix(string prefix)
{
	stack<string> container;
	int length = prefix.length();

	for (int i = length - 1; i >= 0; i--) //------------------------------ 1. Scan PREFIX expression from RIGHT to LEFT or REVERSE the PREFIX expression and scan it from LEFT to RIGHT.
	{
		if (is_operand(prefix[i])) //------------------------------------- 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
		{
			string operand(1, prefix[i]); //------------------------------ We must use this constructor because if we simply string operand = prefix[i]; we get a error!
			container.push(operand);
		}
		else //----------------------------------------------------------- 3. If the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in between the 2 OPERANDs, ADD '(' & ')' to the whole expression & PUSH this whole new expression string back into the Stack.
		{
			string operand_1 = container.top();
			container.pop();
			string operand_2 = container.top();
			container.pop();
			container.push("(" + operand_1 + prefix[i] + operand_2 + ")");
		}
	}

	return container.top();
}

// POSTFIX TO PREFIX
string postfix_to_prefix(string postfix)
{
	stack<string> container;
	int length = postfix.length();

	for (int i = 0; i < length; i++) //------------------------ 1. Scan POSTFIX expression from LEFT to RIGHT
	{
		if (is_operand(postfix[i])) //------------------------- 2. If the incoming symbol is an OPERAND, PUSH it onto the Stack.
		{
			string operand(1, postfix[i]);
			container.push(operand);
		}
		else //------------------------------------------------ 3. IF the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in before the 2 OPERANDs & PUSH this whole new expression string back into the Stack.
		{
			string operand_1 = container.top();
			container.pop();
			string operand_2 = container.top();
			container.pop();
			container.push(postfix[i] + operand_2 + operand_1);
		}
	}
	return container.top();
}

// PREFIX TO POSTFIX
string prefix_to_postfix(string prefix)
{
	stack<string> container;
	int length = prefix.length();

	for (int i = length - 1; i >= 0; i--) //------------------ 1. Scan PREFIX expression from RIGHT to LEFT
	{
		if (is_operand(prefix[i])) //------------------------- 2. IF the incoming symbol is an OPERAND, PUSH it onto the Stack.
		{
			string operand(1, prefix[i]);
			container.push(operand);
		}
		else //----------------------------------------------- 3. IF the incoming symbol is an OPERATOR, POP 2 OPERANDs from the Stack, ADD this incoming OPERATOR in before the 2 OPERANDs & PUSH this whole new expression string back into the Stack.
		{
			string operand_1 = container.top();
			container.pop();
			string operand_2 = container.top();
			container.pop();
			container.push(operand_1 + operand_2 + prefix[i]);
		}
	}

	return container.top();
}