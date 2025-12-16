#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "Default Bitcoin constructor. Database is empty!" << std::endl;
}

BitcoinExchange::BitcoinExchange( const std::string& inputData )
{
    std::cout << "\033[32mBitcoin Constructor!\033[0m" << std::endl;
    std::ifstream file( inputData.c_str() ); //c_str wandelt c++ string (std::string) in const char* um, brauchen wir fuer std::atof() - erwaratet string der mit '\0' endet
    if ( !file.is_open() )
    {
        throw std::runtime_error("Could not open file!");
    }
    
    std::string line;
    size_t delim;
    while ( std::getline( file, line ) )
    {
        delim = line.find(',');
        if ( delim == std::string::npos ) // wenn kein Comma gefunden wurde ueberstring diese Zeile
            continue;
        
        std::string date = line.substr( 0, delim );
        float value = std::atof( line.substr( delim + 1 ).c_str());
        _database[ date ] = value;
    }
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& copy )
{
    std::cout << "Bitcoin copy constructor called!" << std::endl;
    *this = copy;
}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& copy )
{
    if ( this != &copy )
    {
        _database = copy._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "\033[31mbitcoin Destructor!\033[0m" << std::endl;
}

bool validateDate( const std::string& date )
{
    for ( size_t i = 0; i < date.length(); ++i )
    {
        if ( !isdigit( date[i] ) || date[i] != '-' ) // wenn andere zeihcen als zaheln oder '-' da sind
        {
            std::cout << "Invalid date!" << std::endl; // oder exception werfen   
            return ;
        }
    }
    if ( date.length() != 10 )
        return false;
    if ( date[3] != '-' && date[6] != '-' )
        return false;
    std::string month = date.substr( 6, 7 );
    // in int umwandeln und dann checken ob month>0 && month < 13
    std::string day = date.substr( 8, 9 )
    // in int umwandeln und dann checken ob day > 0 && day < 32

} 

bool validateValue( const std::string& value )
{
    for ( size_t i = 0; i < value.length(); ++i )
    {
        if ( !(value[i] >= '0' && value[i] <= '9') ||  value[i] == '.') // wenn andere zeihcen als zaheln oder '.' da sind
        {
            std::cout << "Invalid value!" << std::endl; // oder exception werfen   
            return ;
        }
    }
    //in int convertieren und checken ob zwischen 0 und 1000 ist... 
}

void    BitcoinExchange::processInput( const std::string& inputFile )
{
    std::ifstream file( inputFile.c_str() );
    if ( !file.is_open() )
    {
        std::cout << "Error: cannot open file!" << std::endl;
        return ;
    }
    std::string line;
    std::getline( file, line ); // skip erste line
     
    while ( std::getline( file, line ) )
    {
        size_t delim = inputFile.find( '|' );
        if ( delim == std::string::npos )
        {
            std::cout << "\033[31mError: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr( 0, delim - 1 );
        std::string valueStr = line.substr( delim + 2 );
        if ( !validateDate( date ) ) //TODO: validate date
        
        if ( !valdiateValue( valueStr ) ) //TODO: validate valueStr - vor conversion validieren
        float value = std::atof( valueStr.c_str() ) ; //conversion?
        //TOD: in database suchen
        //database.lower_bound(date) finds next date
        std::cout << date << " => " << value << " = " << "???" << std::endl;
    }
    file.close();
}