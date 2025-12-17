#include "../inc/RPN.hpp"


int main( int argc, char **argv )
{
    if ( argc == 2)
    {
        RPN stack;
        stack.calc( argv[ 1 ] );
        return 0;
    }
}