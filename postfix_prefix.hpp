#ifndef POSTFIX_PREFIX_HPP
#define POSTFIX_PREFIX_HPP
#include <iostream>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"

// Reverse full string and swap bracket directions.
std::string reverse(std::string str){
    stack<char> tempstr;      // temporary stack for reversing
    std::string revstr;       // final reversed string

    // Push all characters, then pop to get reverse order.
    for(char c : str){
        tempstr.push(c);
    }

    int size=tempstr.size();
    for(int i=0;i<size;i++){

        char temp=tempstr.pop();
        // Ignore one leading space if reverse output starts with it.
        if(i==0 && temp==' ' ){
            continue;
        }

        // Swap bracket direction after reversing.
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

// Validate expression using rank rules and bracket matching.
bool isValid(std::string str){
    int rank=0;  // rank must end at 1 for a valid expression
    // Sentinel value keeps stack non-empty for safe checks.
    stack<char> opening_bracket;
    opening_bracket.push('N');
    bool pre_digit=false; // true if we are reading an operand
    bool decimal=false;   // true if current operand already has '.'
    int digit=0;          // number of chars in current operand

    for(char c: str){
        // Operand character (digit or decimal point).
        if((c>=48 && c<=57)||c=='.'){
            if(c=='.'){
                // One operand cannot have multiple decimal points.
                if(decimal==true){
                    throw std::runtime_error("Too many decimal in one operand,like->1.2.3");
                }
                decimal=true;
            }
            digit++;
            pre_digit=true;
        }

        // Opening bracket handling.
        else if(c=='('||c=='{'||c=='['){

            if(decimal==true && digit==1){
              throw std::runtime_error("invalid operand,decimal without digit");
            }

            opening_bracket.push(c);
            if(pre_digit==true){
                rank++;         // close current operand before bracket
                pre_digit=false;
                digit=0;
                decimal=false;
            }
            rank++; // opening bracket adds one pending unit
        }

        // Operator handling.
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
            rank--; // operator combines two parts into one
        }

        // Closing bracket handling.
        else if(c==')'||c=='}'||c==']'){

            if(opening_bracket.size()==1){
                throw std::runtime_error("bracket matching issue");
            }
            char opening=opening_bracket.pop(); // latest opening bracket
            char closing; // expected closing bracket

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
            rank--; // a full bracket group acts like one operand
        }
    }

    // Expression cannot end with incomplete decimal like "1.".
    if(decimal==true && digit == 1){
        throw std::runtime_error("invalid operand,decimal without digit");
    }

    // If expression ends with a number, add it to rank once.
    if(pre_digit==true){
        rank++;
    }

    // If stack has extra opening brackets, matching failed.
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

// Return precedence value for operators and brackets.
int precedence(char c)
{

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
    // Non-operator fallback value.
    return 4;
}

// Convert infix expression to space-separated postfix form.
std::string postfix(std::string expression)
{

    // Ensure expression is valid before conversion.
    isValid(expression);

    stack<char> postfix; // stores operators and opening brackets
    postfix.push('(');   // sentinel for final flush
    std::string output;  // final postfix string

    queue<char> number; // stores digits of current operand
    int digit=0;

    for (char c : expression)
    {
        // Collect digits of one number (supports decimals).
        if ((c >= 48 && c <= 57 )|| c=='.')
        {
            number.equeue(c);
            digit++;
        }

        // Push opening bracket.
        else if (c == '(' || c == '{' || c == '[')
        {   
            postfix.push(c);
        }

        // Closing bracket: flush number and pop until opening bracket.

        else if (c == ')' || c == '}' || c == ']')
        {
             for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';

            // Pop operators until matching opening bracket appears.
            char temp1 = postfix.pop();
            while (temp1 != '(' && temp1 != '{' && temp1 != '[')
            {
                output+=temp1;
                output+=' ';
                temp1 = postfix.pop();
            }
        }
        // For operator: flush number, then pop higher/equal precedence operators.
        else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
        {

            for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
            }
            digit=0;
            output+=' ';

            // '^' is right-associative, so avoid popping equal '^'.
            while (precedence(c) <= precedence(postfix.top()) && c!='^')
            {
                char top = postfix.pop();
                output+=top;
                output+=' ';
            }
            postfix.push(c);
        }
        else{
             // Any other symbol is invalid in this expression format.
             throw std::runtime_error("invalid operator or operend");
        }
    }

    // Flush trailing operand after loop ends.
    for(int i=1;i<=digit;i++){
                char tempdigit=number.dequeue();
                output+=tempdigit;
    }
    output+=' ';
    digit=0;

    // Pop remaining operators.
    char temp2 = postfix.pop();
    while (temp2 != '(')
    {
        output+=temp2;
        temp2 = postfix.pop();
        output+=' ';
    }

    return output;
}

// Convert infix to prefix by reverse -> postfix -> reverse.
std::string prefix(std::string str){

    str=reverse(str); // reverse and swap brackets
    str=postfix(str); // convert to postfix
    str=reverse(str); // reverse again to get prefix order
    str+=' ';         // keep consistent space-separated output

    return str;
}


#endif