#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << GREEN << "Default Bitcoin constructor. Database is empty!" << RESET << std::endl;
}

BitcoinExchange::BitcoinExchange( const std::string& inputData )
{
    std::cout << GREEN << "Bitcoin Constructor!" << RESET << std::endl;
   
    std::ifstream file( inputData.c_str() ); //c_str wandelt c++ string (std::string) in const char* um, brauchen wir fuer std::atof() - erwaratet string der mit '\0' endet
    
    if ( !file.is_open() )
        throw std::runtime_error("Could not open file!");
    
    std::string line;
    while ( std::getline( file, line ) )
    {
        size_t delim = line.find(',');
        if ( delim == std::string::npos ) // wenn kein Comma gefunden wurde ueberstring diese Zeile
            continue ;
        
        std::string date = line.substr( 0, delim );
        float value = std::atof( line.substr( delim + 1 ).c_str());
        _database[ date ] = value;
    }
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange& copy )
{
    std::cout << GREEN << "Bitcoin copy constructor called!" << RESET << std::endl;
    *this = copy;
}

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& copy )
{
    if ( this != &copy )
    {
        _database = copy._database;
    }
    return *this ;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << RED << "Bitcoin Destructor!" << RESET << std::endl;
}

bool isLeapYear( const int year )
{
    if ( year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 ) )
        return true ;
    return false ;
}

bool validateDate( const std::string& date )
{
    if ( date.length() != 10 )
        return false ;
    if ( date[ 4 ] != '-' || date[ 7 ] != '-' )
        return false ;
    for ( size_t i = 0; i < date.length(); ++i )
    {
        if ( !isdigit( date[i] ) && date[i] != '-' ) return false; // wenn andere zeihcen als zaheln oder '-' da sind
    }

    int year = std::atoi( date.substr( 0, 4 ).c_str() );
    if ( year < 0 ) return false ;

    int month = std::atoi( date.substr( 5, 2 ).c_str() );
    if ( month < 1 || month > 12 ) return false ;

    int day = std::atoi( date.substr( 8, 2 ).c_str() );
    if ( day < 1 || day > 31 ) return false ;
    
    if ( (month == 4 || month == 6 || month == 9 || month == 11 ) && day > 30 ) return false ;

    if ( month == 2 ) //Schaltjahr case
    {
        if ( isLeapYear( year ) )
        {
            if ( day > 29 ) return false ;
        }
        else
        {
            if ( day > 28 ) return false ;
        }
    }

    return true ;
} 

bool validateValue( const std::string& value )
{
    int begin = 0;

    if ( value[0] == '-' )
        begin = 1;
    for ( size_t i = begin; i < value.length(); ++i )
    {
        if ( !isdigit( value[i] ) && value[i] != '.' ) return false ;// wenn andere zeihcen als zaheln oder '.' da sind   
    }

    return true ;
}

void    BitcoinExchange::processInput( const std::string& inputFile )
{
    std::ifstream file( inputFile.c_str() );
    if ( !file.is_open() )
    {
        std::cout << RED << "Error: could not open file." << RESET << std::endl;
        return ;
    }
    std::string line;
    std::getline( file, line ); // skip erste line
     
    while ( std::getline( file, line ) )
    {
        size_t delim = line.find( '|' );
        if ( delim == std::string::npos )
        {
            std::cout << RED << "Error: bad input => " << line << "" << RESET << std::endl;
            continue ;
        }

        if ( line.length() < delim + 2 )
        {
            std::cout << RED << "Error: bad input => " << line << RESET << std::endl;
            continue ;
        }

        std::string date = line.substr( 0, delim - 1 );
        std::string valueStr = line.substr( delim + 2 );

        if ( !validateDate( date ) )
        {
            std::cout << RED << "Error: bad input => " << date << RESET << std::endl;
            continue ;
        }
        if ( !validateValue( valueStr ) )
        {
            std::cout << RED << "Error: bad input => " << valueStr << RESET << std::endl;
            continue ;
        }

        float value = std::atof( valueStr.c_str() ) ; //conversion?
        if ( value < 0 )
        {
            std::cout << RED << "Error: not a positive number." << RESET << std::endl;//in int convertieren und checken ob zwischen 0 und 1000 ist... 
            continue ;
        }
        else if ( value > 1000 )
        {
            std::cout << RED << "Error: too large number." << RESET << std::endl;//in int convertieren und checken ob zwischen 0 und 1000 ist... 
            continue ;
        }

        //TOD: in database suchen falls date nicht existiert
        //database.lower_bound(date) finds next date
        std::map<std::string, float>::iterator it = _database.lower_bound( date ); //wenn date existiert, dann iterator auf genau diese element gesetzt, wenn nicht, iterator auf den next bigger gesetzt

        if ( it == _database.begin() && it->first != date )
        {
            std::cout << RED << "Error: date too early." << RESET << std::endl;
            continue ;
        }

        if ( it == _database.end() || it->first != date ) //falls iterator das letzte element ist it-- damit auf das letzte valide element zeigt; und wenn date nicht gefunden wurde it-- um auf kleineres zu zeigen
            it--;

        std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
    file.close();
}