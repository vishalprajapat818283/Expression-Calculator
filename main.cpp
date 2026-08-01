#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "evaluation.hpp"
#include "postfix_prefix.hpp"
// using namespace std;
int main()
{
    std::cout<<"--Enter 'exit' for stop calculation--"<<std::endl;
    std::cout<<"--Enter expression without space--"<<std::endl;
    std::cout<<"--Can evaluate decimal number--"<<std::endl;
    std::cout<<"--(-3+4) type expression is not acceptable"<<std::endl;
    std::cout << "////////available operator//////" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "1. '-'=Subtract" << std::endl;
    std::cout << "2. '+'=Addition" << std::endl;
    std::cout << "3. '*'=Multiplication" << std::endl;
    std::cout << "4. '/'=Devide" << std::endl;
    std::cout << "5. '^'=Power" << std::endl;
    std::cout << "*******************" << std::endl;

    std::string str;
    while(1){
        std::cout << ">>> ";
        std::cin >> str;
        if(str=="exit"){
            break;
        }
    try{

    std::cout << "postfix expression: " << postfix(str) << '\n';
    std::cout << "prefix expression: " << prefix(str) << '\n';
        long double result = evaluate(str);
        // std::cout << "result>> "<<std::fixed << result << '\n';
        std::cout << "result>> "<<std::fixed <<std::setprecision(10) <<result << '\n';
    }
    catch(std::runtime_error& e){
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
    }

    return 0;
}