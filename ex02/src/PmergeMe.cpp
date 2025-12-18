#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::~PmergeMe()
{
    std::cout << RED << "PmergeMe destrcutor!" << RESET << std::endl;
}

int sortList()
{
    return 0;
}

int sortVector()
{
    return 0;
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

    {
        if ( !sortList() )// std::list container logic
            return -1;
    }

    {
        if ( sortVector() )// std::vector container logic
            return -1;
    }

    std::cout << GREEN << "Done!" << RESET << std::endl; 
    return 0;
}

// sort number of sequence into pairs of numbers, then in pairs of pairs, then into pairs of pairs of pairs, ... until there is nothing to still pair

// if number of elements is uneven, let the last one be

// create a sequence out of smallest element (b) of smallest pair (b1) and the rest of a's
// => the main

// create a sequence out of rest of b's and IF  there is a odd element, this as well, if not then not.
// => the pend

// binary insert elements form pend into the main; numbers are based on jacobsthal numbers???

// insert them in reverse order if not able to do the jacobsthal numbers anymore

// 