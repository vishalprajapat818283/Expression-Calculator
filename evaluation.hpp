#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"
#include "postfix_prefix.hpp"
// using namespace std;

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

long double evaluate(std::string str)
{
    str = postfix(str);
    stack<long double> oper;
    long double result = 0;
    queue<char>number;
    int digit=0;
    long double op1;
    long double op2;
    bool decimal=false;
    int dec_pos=0;

    for (char c : str)
    {

        if ((c >= 48 && c <= 57) || c=='.')
        {
            if(c=='.'){
                decimal=true;
                dec_pos=digit+1;
            }
            number.equeue(c);
            digit++;
        }
        
        else if(c==' ' && digit>0){
            
            long double num=0;
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
            oper.push(num);
            num=0;
        }
        else if(c=='-'||
                c=='+'||
                c=='*'||
                c=='/'||
                c=='^')
        {
            if(oper.size()<2){
                throw std::runtime_error("invalid calculation");
            }
            op2 = oper.pop();
            op1 = oper.pop();
            long double evl = calculate(op1, c, op2);
            oper.push(evl);
        }
    }
    if(oper.is_empty()==true || oper.size()!=1){
        throw std::runtime_error("invalid expression");
    }
    result = oper.pop();
    return result;
    
}

