#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

/**
 * EXPRESSION EVALUATION PROJECT
 * Converts infix mathematical expressions to postfix notation
 * Evaluates the postfix expression to get the result
 * Supports: +, -, *, /, ^ (power), and nested brackets: (), {}, []
 * Supports decimal numbers like 3.14, 2.5, etc.
 * Example: (2+3)*4 → 20
 */

/**
 * isValid - Validates if the input expression is mathematically correct
 * Uses rank system: rank increases for operand, decreases for operator
 * Final rank should be 1 for valid expression: operand operator operand
 * 
 * Validates:
 * - Matching brackets: (, {, [
 * - Valid operands (digits with optional decimal point)
 * - Proper operator placement
 * - No multiple decimal points in one number
 * 
 * Returns: true if valid, throws error with descriptive message if invalid
 */
bool isValid(std::string str){
    int rank=0;                        // Rank system: operand=+1, operator=-1
    stack<char> opening_bracket;       // Stack to track opening brackets
    opening_bracket.push('N');         // 'N' is sentinel for initial state
    bool pre_digit=false;              // Flag: was previous character a digit?
    bool decimal=false;                // Flag: was decimal point already found?
    int digit=0;                       // Count of characters in current number

    // Process each character in the expression
    for(char c: str){
        // CASE 1: Character is digit (ASCII 48-57) or decimal point
        if((c>=48 && c<=57)||c=='.'){
            if(c=='.'){
                // Check for multiple decimal points in one number
                if(decimal==true){
                    throw runtime_error("Too many decimal in one operand,like->1.2.3");
                }
                decimal=true;           // Mark decimal point found
            }
            digit++;                    // Increment digit count
            pre_digit=true;             // Mark that we found a digit
        }

        // CASE 2: Character is opening bracket
        else if(c=='('||c=='{'||c=='['){

            // Check if decimal point exists without any digits (e.g., '.' before bracket)
            if(decimal==true && digit==1){
              throw runtime_error("invalid operand,decimal without digit");
            }

            // Push opening bracket to stack
            opening_bracket.push(c);    
            
            // If previous token was operand, increment rank
            if(pre_digit==true){
                rank++;
                pre_digit=false;
                digit=0;
                decimal=false;
            }
            rank++;                     // Bracket itself increases rank
        }

        // CASE 3: Character is operator (+, -, /, *, ^)
        else if(c=='+'||c=='-'||c=='/'||c=='*'||c=='^'){

            // Check if decimal point exists without any digits
            if(decimal==true && digit==1){
                throw runtime_error("invalid operand,decimal without digit");
            }
            
            // If previous token was operand, increment rank
            if(pre_digit==true){
                rank++;
                pre_digit=false;
                decimal=false;
                digit=0;
            }
            rank--;                     // Operator decreases rank
        }

        // CASE 4: Character is closing bracket
        else if(c==')'||c=='}'||c==']'){

            if(opening_bracket.size()==1){
                throw runtime_error("bracket matching issue");
            }
            char opening=opening_bracket.pop();
            char closing;

            if(opening=='('){                
                closing=')';
            }
            else if(opening=='{'){                
                closing='}';
            }
            else if(opening=='['){                
                closing=']';
            }

            if(c!=closing){
                throw runtime_error("bracket matching issue");
            }
            if(decimal==true && digit==1){
                throw runtime_error("invalid operand,decimal without digit");
            }
            if(pre_digit==true){
                rank++;
                pre_digit=false;
                digit=0;
                decimal=false;
            }
            rank--;
        }
    }
    if(decimal==true && digit == 1){
        throw runtime_error("invalid operand,decimal without digit");
    }
    if(pre_digit==true){
        rank++;
    }

    if(opening_bracket.size()>1){
        throw runtime_error("bracket matching issue");
    }


    if(rank==1){
        return true;
    }
    else{
        throw runtime_error("invalid expression");
    }
}

/**
 * precedence - Returns operator precedence level
 * Higher number = higher precedence (evaluated first)
 * 
 * Precedence levels:
 * Brackets: 0 (no precedence, handled by algorithm)
 * +, -:    1 (lowest precedence)
 * *, /:    2 (medium precedence)
 * ^:       3 (highest precedence, right-associative)
 */
int precedence(char c)
{
    // All bracket types have no precedence (handled differently)
    if(c=='('||c=='{'||c=='['){
        return 0;
    }
    // Addition and subtraction have lowest precedence
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    // Multiplication and division have medium precedence
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    // Power has highest precedence
    else if (c == '^')
    {
        return 3;
    }
    return 4;  // Default (should not reach here)
}

/**
 * postfix - Converts infix expression to postfix (Reverse Polish Notation)
 * Uses the Shunting Yard algorithm by Dijkstra
 * 
 * Algorithm Overview:
 * 1. Validate input expression using isValid()
 * 2. For each digit: add to output
 * 3. For opening bracket: push to operator stack
 * 4. For closing bracket: pop operators until matching opening bracket found
 * 5. For operator: pop higher/equal precedence operators (except ^), then push current
 * 6. At end: pop all remaining operators to output
 * 
 * Example conversions:
 * Infix:  "2+3*4"      → Postfix: "2 3 4 * +" (result: 14)
 * Infix:  "(2+3)*4"    → Postfix: "2 3 + 4 *" (result: 20)
 * Infix:  "2^3^2"      → Postfix: "2 3 2 ^ ^" (right associative: 2^(3^2)=512)
 */
std::string postfix(std::string expression)
{
    // Validate expression first - throws error if invalid
    isValid(expression);

    stack<char> postfix;               // Stack for storing operators and brackets
    postfix.push('(');                 // Push sentinel '(' for algorithm termination
    std::string output;                // String to store postfix expression
    queue<char> number;                // Queue to temporarily store digits of number
    int digit=0;                       // Count digits in current number

    // Process each character in the validated expression
    for (char c : expression)
    {
        // CASE 1: Character is digit or decimal point
        if ((c >= 48 && c <= 57 )|| c=='.')
        {
            number.equeue(c);          // Add digit to current number queue
            digit++;                   // Increment digit count
        }

        // CASE 2: Character is opening bracket
        else if (c == '(' || c == '{' || c == '[')
        {   
            postfix.push(c);           // Push opening bracket to operator stack
        }

        // CASE 3: Character is closing bracket
        else if (c == ')' || c == '}' || c == ']')
        {
            // Add all digits of current number to output
            for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';               // Add space separator

            // Pop all operators until matching opening bracket found
            char temp1 = postfix.pop();
            while (temp1 != '(' && temp1 != '{' && temp1 != '[')
            {
                output+=temp1;         // Add operator to output
                output+=' ';           // Add space separator
                temp1 = postfix.pop();
            }
            // Opening bracket is discarded (not added to output)
        }
        // CASE 4: Character is operator
        else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
        {
            // Add all digits of current number to output
            for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';               // Add space separator

            /**
             * Pop operators from stack that have:
             * - Higher precedence than current operator, OR
             * - Equal precedence AND left-associative
             * Exception: ^ is right-associative (not popped for equal precedence)
             */
            while (precedence(c) <= precedence(postfix.top()) && c!='^')
            {
                char top = postfix.pop();
                output+=top;           // Add popped operator to output
                output+=' ';           // Add space separator
            }
            postfix.push(c);           // Push current operator to stack
        }
        else{
            // Invalid character found
             throw std::runtime_error("invalid operator or operend");
        }
    }

    // Add remaining digits to output
    for(int i=1;i<=digit;i++){
        char tempdigit=number.dequeue();
        output+=tempdigit;
    }
    output+=' ';
    digit=0;

    // Pop all remaining operators and add to output
    char temp2 = postfix.pop();
    while (temp2 != '(')                // Pop until sentinel '(' is reached
    {
        output+=temp2;                 // Add operator to output
        temp2 = postfix.pop();
        output+=' ';                   // Add space separator
    }

    return output;                     // Return postfix expression string
}

/**
 * calculate - Performs arithmetic operation on two operands
 * 
 * Parameters:
 * - op1: first operand (left side)
 * - c: operator character: +, -, *, /, ^
 * - op2: second operand (right side)
 * 
 * Returns: Result of (op1 c op2)
 * Throws: exception if division by zero or invalid operator encountered
 * 
 * Examples:
 * calculate(10, '+', 5) returns 15
 * calculate(10, '*', 5) returns 50
 * calculate(2, '^', 3) returns 8 (2^3)
 */
long double calculate(long double op1, char c, long double op2)
{
    switch (c)
    {
    case '+': // Addition
        return (op1 + op2);
    case '-': // Subtraction
        return (op1 - op2);
    case '*': // Multiplication
        return (op1 * op2);
    case '/': // Division (with zero check)
        if (op2 == 0.0)
        {
            throw std::runtime_error("division by zero");
        }
        else
        {
            return (op1 / op2);
        }
    case '^': // Power (exponential)
        return pow(op1, op2);          // Using cmath's pow function
    default: // Invalid operator
        throw std::runtime_error("invalid operator");
    }
}

/**
 * evaluate - Evaluates postfix expression and returns final numerical result
 * Converts infix to postfix, then evaluates postfix using a stack
 * 
 * Algorithm:
 * 1. Convert infix expression to postfix using postfix() function
 * 2. Parse postfix expression character by character
 * 3. For each number: parse and push to operand stack
 * 4. For each operator: pop two operands, calculate, push result back
 * 5. Final stack should have exactly one element (the answer)
 * 
 * Stack-based evaluation example for "2 3 4 * +":
 * Read 2:    stack = [2]
 * Read 3:    stack = [2, 3]
 * Read 4:    stack = [2, 3, 4]
 * Read *:    pop 4,3 → 3*4=12 → stack = [2, 12]
 * Read +:    pop 12,2 → 2+12=14 → stack = [14]
 * Result: 14
 * 
 * Supports decimal numbers: 3.14, 2.5, 0.001, etc.
 */
long double evaluate(std::string str)
{
    // Convert infix expression to postfix
    str = postfix(str);
    stack<long double> oper;           // Stack for storing operands
    long double result = 0;
    queue<char>number;                 // Queue to store digits of current number
    int digit=0;                       // Count of digits in current number
    long double op1;                   // First operand for operation
    long double op2;                   // Second operand for operation
    bool decimal=false;                // Flag: is there a decimal point?
    int dec_pos=0;                     // Position of decimal point in number

    // Process each character in postfix expression
    for (char c : str)
    {
        // CASE 1: Character is digit or decimal point
        if ((c >= 48 && c <= 57) || c=='.')
        {
            if(c=='.'){
                decimal=true;          // Mark decimal point found
                dec_pos=digit+1;       // Record position (1-indexed)
            }
            number.equeue(c);          // Store digit in queue
            digit++;                   // Increment digit count
        }
        
        // CASE 2: Space indicates end of current number
        else if(c==' ' && digit>0){
            
            long double num=0;
            
            // Parse number from queue of characters
            if(decimal==true){
                /**
                 * Decimal number parsing:
                 * Numbers stored as characters, convert to decimal value
                 * Example: "3.14" stored as ['3', '.', '1', '4']
                 * Parse as: 3 + 0.1 + 0.04 = 3.14
                 */
                for(int i=1;i<=digit;i++){
                    if(i<dec_pos){
                        // Before decimal point: add to integer part
                        int x=number.dequeue()-'0';
                        num=num*10+x;
                    }
                    else if(i==dec_pos){
                        // Skip the decimal point character
                        number.dequeue();
                    }
                    else if(i>dec_pos){
                        // After decimal point: add to fractional part
                        int x=number.dequeue()-'0';
                        num=num+x/(pow(10,i-dec_pos));
                    }
                }
            }
            else if(decimal==false){
                // Integer number parsing
                for(int i=0;i<digit;i++){
                    int x=number.dequeue()-'0';
                    num=num*10+x;
                }
            }
            
            // Reset counters for next number
            digit=0;
            dec_pos=0;
            decimal=false;
            
            oper.push(num);            // Push parsed number to operand stack
            num=0;
        }
        // CASE 3: Character is operator
        else if(c=='-'||
                c=='+'||
                c=='*'||
                c=='/'||
                c=='^')
        {
            // Check if there are enough operands for the operation
            if(oper.size()<2){
                throw runtime_error("invalid calculation");
            }
            
            // Pop two operands (ORDER MATTERS for - and /)
            op2 = oper.pop();          // Second operand (popped first)
            op1 = oper.pop();          // First operand (popped second)
            
            // Calculate result of operation
            long double evl = calculate(op1, c, op2);
            
            // Push result back to stack
            oper.push(evl);
        }
    }
    
    // Final validation: exactly one value should remain in stack
    if(oper.is_empty()==true || oper.size()!=1){
        throw runtime_error("invalid expression");
    }
    
    result = oper.pop();               // Get the final result
    return result;
}

