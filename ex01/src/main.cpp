#include "../inc/RPN.hpp"


int main( int argc, char **argv )
{
    if ( argc == 2)
    {
        RPN stack;

        RPN copy( stack );
        RPN third;
        third = copy;
        stack.calc( argv[ 1 ] );
        copy.calc( argv[ 1 ] );
        third.calc( argv[ 1 ] );
        return 0;
    }
}