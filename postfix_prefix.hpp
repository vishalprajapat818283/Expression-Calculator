#ifndef POSTFIX_PREFIX_HPP
#define POSTFIX_PREFIX_HPP
#include <iostream>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"

std::string reverse(std::string str){
    stack<char> tempstr;
    std::string revstr;
    for(char c : str){
        tempstr.push(c);
    }
    int size=tempstr.size();
    for(int i=0;i<size;i++){

        char temp=tempstr.pop();
        if(i==0 && temp==' ' ){
            continue;
        }

        switch (temp){
            case '(':temp=')';
            break;
            case ')':temp='(';
            break;
            case '{':temp='}';
            break;
            case '}':temp='{';
            break;
            case '[':temp=']';
            break;
            case ']':temp='[';
            break;
        }
        revstr+=temp;
    }

    return revstr;
}

//expression validation function
bool isValid(std::string str){
    int rank=0;
    stack<char> opening_bracket;
    opening_bracket.push('N');
    bool pre_digit=false;
    bool decimal=false;
    int digit=0;

    for(char c: str){
        if((c>=48 && c<=57)||c=='.'){
            if(c=='.'){
                if(decimal==true){
                    throw std::runtime_error("Too many decimal in one operand,like->1.2.3");
                }
                decimal=true;
            }
            digit++;
            pre_digit=true;
        }

        else if(c=='('||c=='{'||c=='['){

            if(decimal==true && digit==1){
              throw std::runtime_error("invalid operand,decimal without digit");
            }

            opening_bracket.push(c);
            if(pre_digit==true){
                rank++;
                pre_digit=false;
                digit=0;
                decimal=false;
            }
            rank++;
        }

        else if(c=='+'||c=='-'||c=='/'||c=='*'||c=='^'){

            if(decimal==true && digit==1){
                throw std::runtime_error("invalid operand,decimal without digit");
            }
            
            if(pre_digit==true){
                rank++;
                pre_digit=false;
                decimal=false;
                digit=0;
            }
            rank--;
        }

        else if(c==')'||c=='}'||c==']'){

            if(opening_bracket.size()==1){
                throw std::runtime_error("bracket matching issue");
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
                throw std::runtime_error("bracket matching issue");
            }
            if(decimal==true && digit==1){
                throw std::runtime_error("invalid operand,decimal without digit");
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
        throw std::runtime_error("invalid operand,decimal without digit");
    }
    if(pre_digit==true){
        rank++;
    }

    if(opening_bracket.size()>1){
        throw std::runtime_error("bracket matching issue");
    }


    if(rank==1){
        return true;
    }
    else{
        throw std::runtime_error("invalid expression");
    }
}
//preceddence function
int precedence(char c)
{
    // if (c == '(')
    // {
    //     return -2;
    // }
    // else if (c == '{')
    // {
    //     return -1;
    // }
    // else if (c == '[')
    // {
    //     return 0;
    // }
    if(c=='('||c=='{'||c=='['){
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

//postfix function
std::string postfix(std::string expression)
{
    //validating expression
    // if(isValid(expression)==false){
    //     throw std::std::runtime_error("invalid expression");
    // }
    isValid(expression);

    stack<char> postfix; //stack for storing operator and opening_brackets
    postfix.push('(');
    std::string output; //string for storing output string

    queue<char> number; //stack for storing number
    int digit=0;

    for (char c : expression)
    {
        //digit
        if ((c >= 48 && c <= 57 )|| c=='.')
        {
            number.equeue(c);
            digit++;
            // output+=c;
        }

        //opening opening_bracket
        else if (c == '(' || c == '{' || c == '[')
        {   
            postfix.push(c);
        }

        //opening opening_bracket

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
        //operator
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

    //poping remaining operator
    char temp2 = postfix.pop();
    while (temp2 != '(')
    {
        output+=temp2;
        temp2 = postfix.pop();
        output+=' ';
    }

    return output;
}

std::string prefix(std::string str){

    str=reverse(str);
    str=postfix(str);
    str=reverse(str);
    str+=' ';

    return str;
}


#endif