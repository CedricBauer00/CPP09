#include <iostream>
#include <string>
#include <map> 
#include <fstream>
#include <cstdlib>

#define RED  "\033[31m"
#define ELEC_RED "\033[38;2;255;20;20m"
#define BLUE    "\033[34m"
#define GREEN  "\033[32m"
#define RESET  "\033[0m"
#define ORANGE  "\033[38;2;255;120;0m"

// from year 2009 until 2021; 
// 1 entry all 3 days;
// 1610 entries;
// leap years: 2012 2016 2020, ...

class BitcoinExchange
{
private:
    std::map<std::string, float> _database;
public:
    BitcoinExchange();
    BitcoinExchange( const BitcoinExchange& copy );
    BitcoinExchange& operator=( const BitcoinExchange& copy );
    ~BitcoinExchange();

    void    processInput( const std::string& inputFile );
    
};
