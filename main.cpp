#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include "stack.hpp"
#include "evaluation.hpp"

using namespace std;

// Sets the console text color for a clearer command-line interface.
void setColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Shows the calculator title and available operator instructions to the user.
void printHeader() {
    setColor(11); // light cyan
    cout << "\n========================================\n";
    cout << "        EXPRESSION CALCULATOR\n";
    cout << "========================================\n";
    setColor(7);

    cout << "Enter 'exit' to stop calculation.\n";
    cout << "Enter expression without spaces.\n\n";

    setColor(10); // light green
    cout << "Available operators:\n";
    setColor(7);
    cout << "  +  Addition\n";
    cout << "  -  Subtraction\n";
    cout << "  *  Multiplication\n";
    cout << "  /  Division\n";
    cout << "  ^  Power\n\n";
}

// Displays the input prompt shown before each expression is typed.
void printPrompt() {
    setColor(14); // yellow
    cout << ">>> ";
    setColor(7);
}

// Prints a formatted error message when an invalid expression is entered.
void printError(const string& msg) {
    setColor(12); // light red
    cout << "Error: " << msg << "\n";
    setColor(7);
}

// Shows the final evaluated result in a readable, formatted style.
void printResult(long double result) {
    setColor(10); // light green
    cout << "Result: ";
    setColor(15); // bright white
    cout << fixed << setprecision(6) << result << "\n";
    setColor(7);
}

// Displays the postfix form of the entered expression.
void printPostfix(const string& expr) {
    setColor(9); // light blue
    cout << "Postfix: ";
    setColor(15);
    cout << postfix(expr) << "\n";
    setColor(7);
}

// Main loop for the expression calculator application.
int main() {
    AllocConsole();

    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONIN$", "r", stdin);

    printHeader();

    string str;
    while (true) {
        printPrompt();
        cin >> str;

        if (str == "exit") {
            break;
        }

        try {
            printPostfix(str);
            long double result = evaluate(str);
            printResult(result);
            cout << "\n";
        }
        catch (const runtime_error& e) {
            printError(e.what());
            cout << "\n";
        }
    }

    setColor(7);
    cout << "Goodbye.\n";
    std::cin.ignore();
    std::cin.get();
    return 0;
}