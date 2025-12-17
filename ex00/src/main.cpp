#include "../inc/BitcoinExchange.hpp"

int main( int argc, char **argv )
{
    if ( argc == 2 )
    {
        std::cout << "Hello\rhere!" << std::endl;
        BitcoinExchange data("data.csv");
        data.processInput( argv[1] );
    }
    return 0;
}