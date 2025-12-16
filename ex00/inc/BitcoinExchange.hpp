#include <iostream>
#include <string>
#include <map> 
#include <fstream>
#include <cstdlib>

// takes csv files as database
// csv files geht von 2009 bis 2021; jeder Eintrag ist + 3 Tage; 1610 einträge
// input will be second database "storing the different prices/dates to evaluate."

//rules to respect
// takes file as argument
// checking for "date|value" format
// valid date ONLY: Year-Month-Day
// valid value ONLY: flaot && positive integer between 0-1000
// appropriate error message

//map stack pair

class BitcoinExchange
{
private:
    std::map<std::string, float> _database;
public:
    BitcoinExchange();
    BitcoinExchange( const std::string& inputData );
    BitcoinExchange( const BitcoinExchange& copy );
    BitcoinExchange& operator=( const BitcoinExchange& copy );
    ~BitcoinExchange();

    void    processInput( const std::string& inputFile );
    
};
