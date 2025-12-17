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
    if ( date.length() != 10 )
        return false;
    if ( date[ 4 ] != '-' || date[ 7 ] != '-' )
        return false;
    for ( size_t i = 0; i < date.length(); ++i )
    {
        if ( !isdigit( date[i] ) && date[i] != '-' ) // wenn andere zeihcen als zaheln oder '-' da sind
        {
            std::cout << "Error: Bad input!" << std::endl; // oder exception werfen   
            return false;
        }
    }

    int year = std::atoi( date.substr( 0, 4 ).c_str() );
    if ( year < 0 ) return false;

    int month = std::atoi( date.substr( 5, 2 ).c_str() );
    if ( month < 1 || month > 12 ) return false;

    int day = std::atoi( date.substr( 8, 2 ).c_str() );
    if ( day < 1 || day > 31 ) return false;
    // in int umwandeln und dann checken ob month>0 && month < 13
    // in int umwandeln und dann checken ob day > 0 && day < 32
    return true;
} 

bool validateValue( const std::string& value )
{
    int begin = 0;

    if ( value[0] == '-' )
        begin = 1;
    for ( size_t i = begin; i < value.length(); ++i )
    {
        if ( !isdigit( value[i] ) && value[i] != '.' ) // wenn andere zeihcen als zaheln oder '.' da sind
        {
            std::cout << "Error: Bad input!" << std::endl; // oder exception werfen   
            return false;
        }
    }

    int intValue = std::atoi( value.c_str() );
    if ( intValue < 0 )
    {
        std::cout << "\033[31mValue too small!\033[0m" << std::endl;//in int convertieren und checken ob zwischen 0 und 1000 ist... 
        return false;
    }
    else if ( intValue > 1000 )
    {
        std::cout << "\033[31mValue too big!\033[0m" << std::endl;//in int convertieren und checken ob zwischen 0 und 1000 ist... 
        return false;
    }
    return true;
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
        size_t delim = line.find( '|' );
        if ( delim == std::string::npos )
        {
            std::cout << "\033[31mError: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr( 0, delim - 1 );
        std::string valueStr = line.substr( delim + 2 );
        if ( !validateDate( date ) ) //TODO: validate date
            continue;
        if ( !validateValue( valueStr ) ) //TODO: validate valueStr - vor conversion validieren
            continue;
        float value = std::atof( valueStr.c_str() ) ; //conversion?
        //TOD: in database suchen
        //database.lower_bound(date) finds next date
        std::cout << date << " => " << value << " = " << "???" << std::endl;
    }
    file.close();
}