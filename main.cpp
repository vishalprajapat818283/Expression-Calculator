#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "stack.hpp"
#include "evaluation.hpp"
using namespace std;

/**
 * MAIN PROGRAM - Expression Evaluation Calculator
 * 
 * Features:
 * - Accepts mathematical expressions with operators: +, -, *, /, ^
 * - Supports nested brackets: (), {}, []
 * - Supports decimal numbers: 3.14, 2.5, etc.
 * - Shows both postfix notation and final result
 * - Comprehensive error messages for invalid input
 */
int main()
{
    // Display usage instructions to user
    cout<<"--Enter 'exit' for stop calculation--"<<endl;
    cout<<"--Enter expression without space--"<<endl;
    cout<<"--Can evaluate decimal number--"<<endl;
    cout<<"--(-3+4) type expression is not acceptable (unary minus not supported)--"<<endl;
    
    // Display available operators
    cout << "////////available operator//////" << endl;
    cout << "********************" << endl;
    cout << "1. '-'=Subtract" << endl;
    cout << "2. '+'=Addition" << endl;
    cout << "3. '*'=Multiplication" << endl;
    cout << "4. '/'=Divide" << endl;
    cout << "5. '^'=Power" << endl;
    cout << "*******************" << endl;
    
    std::string str;
    
    // Main loop: keeps running until user enters "exit"
    while(1){
        cout << ">>> ";                 // Prompt for user input
        cin >> str;                     // Read expression string
        
        // Check if user wants to exit the program
        if(str=="exit"){
            break;                      // Exit the loop and end program
        }
    
    try{
        // Process the expression
        
        // Step 1: Convert infix to postfix and display
        cout << "postfix expression: " << postfix(str) << '\n';
        
        // Step 2: Evaluate expression to get numerical result
        long double result = evaluate(str);
        
        // Step 3: Display result with fixed-point notation (6 decimal places by default)
        // cout << "result> "<<fixed <<setprecision(5)<< result << '\n';
        cout << "result> "<<fixed << result << '\n';
    }
    catch(std::runtime_error& e){
        // Catch any runtime errors (validation failures, division by zero, etc.)
        cout << "Invalid argument: " << e.what() << endl;  // Display descriptive error message
    }
    }

    return 0;  // Program ends successfully
}