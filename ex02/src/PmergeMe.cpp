#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::~PmergeMe()
{
    std::cout << RED << "PmergeMe destrcutor!" << RESET << std::endl;
}

int    PmergeMe::merge( const int argc, char **argv ) //konnte nicht const char **argv machen, warum?
{
    for ( int i = 1; i < argc; ++i )
    {
        std::string arg = argv[ i ]; 
        size_t pos = arg.find_first_not_of( "0123456789" );
        
        if ( pos != std::string::npos )
        {
            std::cerr << RED << "Error: bad input." << ": " << arg[ pos ] << RESET << std::endl;
            return -1;
        }

    }

    //sorting logic
    std::cout << GREEN << "Done!" << RESET << std::endl; 
    return 0;
}