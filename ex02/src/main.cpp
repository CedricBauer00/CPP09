#include "../inc/PmergeMe.hpp"

int main( int argc, char **argv )
{
    if ( argc > 1 )
    {
        PmergeMe obj;
    
        obj.merge( argc, argv );
        return 0;

    }
    else
    {
        std::cerr << RED << "Error: too little arguments." << RESET << std::endl;
        return -1;
    }
    return 0;
}