#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <windows.h>
#include "evaluation.hpp"
#include "postfix_prefix.hpp"
using namespace std;

// Helper function to change console text color.
void setColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


int main()
{
    // Create and attach a console window.
    AllocConsole();
    
    // Connect standard input and output to this console.
    FILE* stream; // file pointer used for console redirection
    freopen_s(&stream, "CONOUT$", "w", stdout); // route cout to console
    freopen_s(&stream, "CONIN$", "r", stdin);    // route cin from console
    
    // Print calculator UI header.
    setColor(208); // black on light gray
    cout << "\n========================================\n";
    cout << "      EXPRESSION CALCULATOR V2.2        \n";
    cout << "========================================\n";

    setColor(1); // blue
    cout<<"--Enter 'exit' for stop calculation--"<<endl;
     cout << "--Note: (-3+4) type expression is not acceptable--\n";
    cout<<"--Enter expression without space--"<<endl;
    cout<<"--Can evaluate decimal number--"<<endl;
    setColor(6); // yellow
    cout << "////////available operator//////" << endl;

    setColor(5); // magenta
    cout << "********************" << endl;
    setColor(14); // bright yellow
    cout << "1. '-'=Subtract" << endl;
    cout << "2. '+'=Addition" << endl;
    cout << "3. '*'=Multiplication" << endl;
    cout << "4. '/'=Devide" << endl;
    cout << "5. '^'=Power" << endl;
    setColor(5); // magenta
    cout << "*******************" << endl;

    string str; // user input expression

    // Keep taking expressions until user types "exit".
    while(1){
        setColor(10); // bright green
        cout << ">>> ";
        cin >> str;
        if(str=="exit"){
            break; // stop calculator loop
        }
    try{
    
    setColor(9); // bright blue
    cout << "postfix expression: ";
    setColor(7); // light gray
    cout << postfix(str) << '\n';
    setColor(9); // bright blue
    cout << "prefix expression: " ;
    setColor(7); // light gray
    cout<< prefix(str) << '\n';
        // Evaluate expression and print final value.
        long double result = evaluate(str);
            setColor(9); // bright blue
        cout << "result>> ";
            setColor(7); // light gray
        cout<<fixed <<setprecision(10) <<result << '\n'; // fixed 10 decimal places
    }
    catch(runtime_error& e){
        setColor(12); // bright red
        cout << "Invalid argument: " ;
        setColor(7); // light gray
        cout << e.what() << endl;
    }
    }

    setColor(31); // bright white on blue
    cout << "Goodbye\n";
    setColor(8); // dark gray
    // Wait so user can read output before window closes.
    cout <<"press enter for closing window...";
    std::cin.ignore(); // clear leftover newline from input
    std::cin.get();    // wait for Enter key
    return 0;
}