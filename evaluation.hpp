#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"
#include "postfix_prefix.hpp"
// using namespace std;

// Perform one arithmetic operation on two operands.
long double calculate(long double op1, char c, long double op2)
{
    // Select operation based on operator symbol.
    switch (c)
    {
    case '+':
        return (op1 + op2);
    case '-':
        return (op1 - op2);
    case '*':
        return (op1 * op2);
    case '/':
        // Division by zero is not allowed.
        if (op2 == 0.0)
        {
            throw std::runtime_error("division by zero");
        }
        else
        {
            return (op1 / op2);
        }
    case '^':
        // Use pow for exponent operation.
        return pow(op1, op2);
    default:
        throw std::runtime_error("invalid operator");
    }
}

// Evaluate infix expression by converting it to postfix first.
long double evaluate(std::string str)
{
    // This conversion step also validates the expression format.
    str = postfix(str);

    // Stack stores numbers while scanning postfix tokens.
    stack<long double> oper;
    long double result = 0;

    // Queue temporarily stores digits of the current number.
    queue<char>number; // stores chars of one numeric token
    int digit=0;       // length of current token
    long double op1;   // first operand for operation
    long double op2;   // second operand for operation
    bool decimal=false; // true if token contains decimal point
    int dec_pos=0;      // position of '.' inside token

    for (char c : str)
    {
        // Read one number token character by character.
        if ((c >= 48 && c <= 57) || c=='.')
        {
            if(c=='.'){
                decimal=true;      // mark decimal number
                dec_pos=digit+1;   // save decimal index
            }
            number.equeue(c);
            digit++;
        }
        
        // Space means current number token is complete.
        else if(c==' ' && digit>0){
            
            long double num=0; // converted numeric value
            // Convert queued characters into numeric value.
            if(decimal==true){
                for(int i=1;i<=digit;i++){
                    if(i<dec_pos){
                    int x=number.dequeue()-'0';
                    num=num*10+x;
                    }
                    else if(i==dec_pos){
                        number.dequeue();
                    }
                    else if(i>dec_pos){
                    int x=number.dequeue()-'0';
                    num=num+x/(pow(10,i-dec_pos));  
                    }
                }

            }
            else if(decimal==false){

                for(int i=0;i<digit;i++){
                    int x=number.dequeue()-'0';
                    num=num*10+x;
                }
            }
            digit=0;
            dec_pos=0;
            decimal=false;
            oper.push(num); // push completed number token
            num=0;
        }
        // Operator uses top two operands from stack.
        else if(c=='-'||
                c=='+'||
                c=='*'||
                c=='/'||
                c=='^')
        {
            // Need at least two values for binary operator.
            if(oper.size()<2){
                throw std::runtime_error("invalid calculation");
            }
            op2 = oper.pop();
            op1 = oper.pop();
            long double evl = calculate(op1, c, op2);
            oper.push(evl); // push intermediate result
        }
    }
    // A valid expression leaves exactly one value in stack.
    if(oper.is_empty()==true || oper.size()!=1){
        throw std::runtime_error("invalid expression");
    }
    result = oper.pop();
    return result;
}

