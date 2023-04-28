#include <iostream>
#include "basic_functions.h"

using namespace std;

// INFIX TO POSTFIX:
// 1.  Scan Expression from Left to Right.
//
// 2.  Print OPERANDs as the arrive.
//
// 3.  If OPERATOR arrives & Stack is empty, push this OPERATOR onto the stack.
//
// 4.  If incoming OPERATOR has HIGHER precedence than the TOP of the Stack, push it on stack.
//
// 5.  If incoming OPERATOR has LOWER precedence than the TOP of the Stack, then POP and print the TOP. Then test the incoming OPERATOR against the new TOP of stack.
//
// 6.  If incoming OPERATOR has EQUAL precedence with TOP of Stack, use ASSOCIATIVITY Rules.
//
// 6.1 For ASSOCIATIVITY of LEFT to RIGHT –
//     POP and print the TOP of stack, then push the incoming OPERATOR.
//
// 6.2 For ASSOCIATIVITY of RIGHT to LEFT –
//     PUSH incoming OPERATOR on stack.
//
// 7.  At the end of Expression, POP & print all  OPERATORS from the stack.
//
// 8.  If incoming SYMBOL is '(' PUSH it onto Stack.
//
// 9.  If incoming SYMBOL is ')' POP the stack and print OPERATORs till '(' is found. POP that '('.
//
// 10. If TOP of stack is '(' PUSH OPERATOR on Stack.

int main()
{}