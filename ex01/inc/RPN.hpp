#pragma once

#include <string>
#include <iostream>
#include <stack>
#include <exception>
#include <climits>

#define RED  "\033[31m"
#define ELEC_RED "\033[38;2;255;20;20m"
#define BLUE    "\033[34m"
#define GREEN  "\033[32m"
#define RESET  "\033[0m"
#define ORANGE  "\033[38;2;255;120;0m"

// input numbers less than 10 - as argv
// resutl to std::cout
// runtime error - appropriate error message
// + - / * only operators


class RPN
{
    private:
        std::stack<int> stack;
    public:
        RPN();
        RPN( const RPN &copy );
        RPN& operator=( const RPN &copy );
        ~RPN(); 

        int calc( const std::string &input );
};

// $> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
// 42
// $> ./RPN "7 7 * 7 -"
// 42
// $> ./RPN "1 2 * 2 / 2 * 2 4 - +"
    // 1*2 / 2 * 2 + 2 - 4

// 0
// $> ./RPN "(1 + 1)"
// Error
// $>