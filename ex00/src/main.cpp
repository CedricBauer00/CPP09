#include "../inc/BitcoinExchange.hpp"

int main( int argc, char **argv )
{
    if ( argc == 2 )
    {
        std::cout << "Hello\rhere!" << std::endl;
        BitcoinExchange data("data.csv");
        data.processInput( argv[1] );
        // std::map<std::string, float> btcPrices;
        // btcPrices["2022-01-01"] = 46000.50;
        
        // std::string searchDate = "2022-01-01";
        // std::map<std::string, float>::iterator it = btcPrices.find(searchDate);
        // if ( it != btcPrices.end() )
        // {
        //     std::cout << "Preis am " << it->first << ": " << it->second << std::endl;
        // }
        // else
        // {
        //     std::cout << "Date not found!" << std::endl;
        // }
        // for ( std::map<std::string, float>::iterator it = btcPrices.begin(); it != btcPrices.end(); ++it )
        // {
        //     std::cout << "Datum " << it->first << " -> Preis: " << it->second << std::endl;
        // }
    }
    return 0;
}