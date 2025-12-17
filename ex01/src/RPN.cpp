#include "../inc/RPN.hpp"

RPN::RPN()
{
    std::cout << GREEN << "RPN constructor!" << RESET << std::endl;
}

// RPN::RPN( const RPN &copy )
// {
//     std::cout << GREEN << "RPN copy constructor!" << RESET << std::endl;

// }

// RPN& RPN::operator=( const RPN &copy )
// {
//     std::cout << GREEN << "RPN assignment operator!" << RESET << std::endl;

// }

RPN::~RPN()
{
    std::cout << RED << "RPN destructor!" << RESET << std::endl;
}

int RPN::calc( const std::string &input )
{
    size_t pos = input.find_first_not_of( "0123456789+-/* " );
    if ( pos != std::string::npos )
    {
        std::cerr << RED "Error: input not allowed." << RESET << std::endl;
        return -1 ;
    }
    for ( size_t i = 0; i < input.length(); ++i )
    {
        if ( isdigit( input[ i ] ) )
            stack.push( input[ i ] - 48 ); 
        else if ( input[ i ] == ' ' )
            continue ;
        else
        {
            if ( stack.size() < 2 )
            {
                std::cerr << RED << "Error: bad input." << RESET << std::endl;
                return -1;
            }
            int second = stack.top();
            stack.pop();
            int first = stack.top();
            stack.pop();
            if ( input[ i ] == '+' )
                stack.push( first +second );
            else if ( input[ i ] == '-' )
                stack.push( first - second );
            else if ( input[ i ] == '*' )
                stack.push( first * second );
            else if ( input[ i ] == '/' )
            {
                if ( second == 0 )
                {
                    std::cerr << RED << "Error: bad input." << RESET << std::endl;
                    return -1;
                }
                stack.push( first /second );
            }
        }
    }
    if ( stack.size() > 1 )
    {
        std::cerr << RED << "Error: bad input." << RESET << std::endl;
        return -1;
    }
    if ( stack.top() > )
    std::cout << stack.top() << std::endl;
    return 0;
}   