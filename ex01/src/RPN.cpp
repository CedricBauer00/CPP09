#include "../inc/RPN.hpp"

RPN::RPN()
{
    std::cout << GREEN << "RPN constructor!" << RESET << std::endl;
}

RPN::RPN( const RPN &copy ) : _stack( copy._stack )
{
    std::cout << GREEN << "RPN copy constructor!" << RESET << std::endl;
}

RPN& RPN::operator=( const RPN &copy )
{
    std::cout << GREEN << "RPN assignment operator!" << RESET << std::endl;
    if ( this != &copy )
    {
        this->_stack = copy._stack;
    }
    return *this ;
}

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
            _stack.push( input[ i ] - 48 ); 
        else if ( input[ i ] == ' ' )
            continue ;
        else
        {
            if ( _stack.size() < 2 ) //wenn in _stack weniger als 2 zahlen in _stack  "1 -" 
            {
                std::cerr << RED << "Error: bad input." << RESET << std::endl;
                return -1;
            }
            
            long second = _stack.top(); // long statt int weil int konveritert value um in bounds zu bleiben 
            _stack.pop();
            long first = _stack.top();
            _stack.pop();
            
            long result = 0;
            
            if ( input[ i ] == '+' )
                result =  first + second;
            else if ( input[ i ] == '-' )
                result =  first - second;
            else if ( input[ i ] == '*' )
                result =  first * second;
            else if ( input[ i ] == '/' )
            {
                if ( second == 0 )
                {
                    std::cerr << RED << "Error: bad input." << RESET << std::endl;
                    return -1;
                }
                result =  first /second;
            }

            if ( result > INT_MAX || result < INT_MIN )
            {
                std::cerr << RED << "Error: result too large." << RESET << std::endl;
                return -1;
            }
            
            _stack.push( ( int )result );
        }
    }
    
    if ( _stack.size() > 1 ) // "1 1" kein operator
    {
        std::cerr << RED << "Error: bad input." << RESET << std::endl;
        return -1;
    }
    
    std::cout << _stack.top() << std::endl;
    
    return 0;
}   
