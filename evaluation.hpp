#pragma once
#include <iostream>
#include <cmath>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

// Validates syntax using bracket matching and rank rules.
bool isValid(std::string str){
    int rank=0;
    stack<char> bracket;
    bracket.push('N');
    bool pre_digit=false;

    for(char c: str){
        if(c>=48 && c<=57){
            pre_digit=true;
        }

        else if(c=='('||c=='{'||c=='['){
            bracket.push(c);
            if(pre_digit==true){
                rank++;
                pre_digit=false;
            }
            rank++;
        }

        else if(c=='+'||c=='-'||c=='/'||c=='*'||c=='^'){
            
            if(pre_digit==true){
                rank++;
                pre_digit=false;
            }
            rank--;
        }

        else if(c==')'||c=='}'||c==']'){
            char opening=bracket.pop();
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
                return false;
            }

            if(pre_digit==true){
                rank++;
                pre_digit=false;
            }
            rank--;
        }
    }
    if(pre_digit==true){
        rank++;
    }
    if(rank==1){
        return true;
    }
    else{
        return false;
    }
}

// Returns operator precedence for infix-to-postfix conversion.
int precedence(char c)
{
    if (c == '(')
    {
        return -2;
    }
    else if (c == '{')
    {
        return -1;
    }
    else if (c == '[')
    {
        return 0;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '^')
    {
        return 3;
    }
    return 4;
}

// Converts infix expression into space-separated postfix expression.
std::string postfix(std::string expression)
{
    // Validate expression before conversion.
    if(isValid(expression)==false){
        throw std::runtime_error("invalid expression");
    }

    stack<char> postfix; // stores operators and opening brackets
    postfix.push('(');
    std::string output; // postfix output string

    queue<char> number; // temporary digit buffer for one number
    int digit=0;

    for (char c : expression)
    {
        // Collect one numeric token.
        if (c >= 48 && c <= 57 )
        {
            number.equeue(c);
            digit++;
        }

        // Push opening bracket as scope marker.
        else if (c == '(' || c == '{' || c == '[')
        {   
            postfix.push(c);
        }

        // Closing bracket: flush number and pop operators until opening bracket.

        else if (c == ')' || c == '}' || c == ']')
        {
             for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';

            char temp1 = postfix.pop();
            while (temp1 != '(' && temp1 != '{' && temp1 != '[')
            {
                output+=temp1;
                output+=' ';
                temp1 = postfix.pop();
            }
        }
        // Operator: flush number, pop higher/equal precedence operators.
        else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
        {

            for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';

            while (precedence(c) <= precedence(postfix.top()) && c!='^')
            {
                char top = postfix.pop();
                output+=top;
                output+=' ';
            }
            postfix.push(c);
        }
        else{
             throw std::runtime_error("invalid operator or operend");
        }
    }

    for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
    }
    output+=' ';
    digit=0;

    // Pop any remaining operators.
    char temp2 = postfix.pop();
    while (temp2 != '(')
    {
        output+=temp2;
        temp2 = postfix.pop();
        output+=' ';
    }

    return output;
}

// Applies one arithmetic operator to two operands.
long double calculate(long double op1, char c, long double op2)
{
    switch (c)
    {
    case '+':
        return (op1 + op2);
    case '-':
        return (op1 - op2);
    case '*':
        return (op1 * op2);
    case '/':
        if (op2 == 0.0)
        {
            throw std::runtime_error("division by zero");
        }
        else
        {
            return (op1 / op2);
        }
    case '^':
        return pow(op1, op2);
    default:
        throw std::runtime_error("invalid operator");
    }
}

// Evaluates an infix expression via postfix conversion.
long double evaluate(std::string str)
{
    str = postfix(str);
    // Operand stack used during postfix scan.
    stack<long double> oper;
    long double result = 0;
    // Buffer for multi-digit numbers.
    queue<char>number;
    int digit=0;

    for (char c : str)
    {
        long double op1;
        long double op2;
        if (c >= 48 && c <= 57)
        {
            number.equeue(c);
            digit++;
        }
        
        // Space means one complete number token.
        else if(c==' ' && digit>0){
            
            long double num=0;
            for(int i=0;i<digit;i++){
                int x=number.dequeue()-'0';
                num=num*10+x;
            }
            digit=0;
            oper.push(num);
        }
        // Operator consumes two operands and pushes back one result.
        else if(c=='-'||
                c=='+'||
                c=='*'||
                c=='/'||
                c=='^')
        {
            op2 = oper.pop();
            op1 = oper.pop();
            long double evl = calculate(op1, c, op2);
            oper.push(evl);
        }
    }
    result = oper.pop();
    return result;
}
