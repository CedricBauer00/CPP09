#include "../inc/BitcoinExchange.hpp"

int main( int argc, char **argv )
{
    try
    {
        if ( argc == 2 )
        {
            std::cout << "Hello\rhere!" << std::endl;
            BitcoinExchange data;
            data.processInput( argv[1] );
        }
    }
    catch( std::exception &e )
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}