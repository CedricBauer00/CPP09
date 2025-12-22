#include "../inc/PmergeMe.hpp"

int main( int argc, char **argv )
{
    if ( argc > 1 )
    {
        PmergeMe obj1;
        PmergeMe obj2; 

        obj2 = obj1;

        PmergeMe algo( obj2 );

        algo.merge( argc, argv );
        return 0;

    }
    else
    {
        std::cerr << RED << "Error: too little arguments." << RESET << std::endl;
        return -1;
    }
    return 0;
}