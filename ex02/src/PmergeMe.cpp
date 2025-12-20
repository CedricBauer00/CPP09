#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::~PmergeMe()
{
    std::cout << RED << "PmergeMe destrcutor!" << RESET << std::endl;
}

int PmergeMe::sortListIntoPairs()
{
    // for ( std::list<int>::iterator it = l.begin(); l.begin() != l.end(); ++it )
    // {
    //     std::vector<int> pair;

    // }
    return 0;
}

int PmergeMe::sortVectorIntoPairs()
{
    
    return 0;
}

int    PmergeMe::merge( const int argc, char **argv ) //konnte nicht const char **argv machen, warum?
{
    std::cout << GREEN << "start!" << RESET << std::endl; 

    for ( int i = 1; i < argc; ++i )
    {
        std::string arg = argv[ i ]; 

        size_t pos = arg.find_first_not_of( "0123456789 " ); // geht ueber alle args auch "12 23 3 4 5 "
        if ( pos != std::string::npos )
        {
            std::cerr << RED << "Error: bad input." << ": " << arg[ pos ] << RESET << std::endl;
            return -1;
        }

        std::istringstream ss( arg );
        
        std::string substr;

        while ( ss >> substr ) // teilt bei space; fuer den case "12 2 3 4 5"
        {
            this->l.push_back( std::stoi( substr ) );
            this->v.push_back( std::stoi( substr ) );
        }
    }

    {
        if ( !sortListIntoPairs() )
            return -1;// std::list container logic
    }

    {
        if ( !sortVectorIntoPairs() )
            return -1;// std::vector container logic
    }

    std::cout << GREEN << "List: " << RESET << std::endl;
    for ( std::list<int>::iterator it = l.begin(); it != l.end(); ++it )
    {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    std::cout << GREEN << "Vecotr: " << RESET << std::endl; 
    for ( std::vector<int>::iterator it = v.begin(); it != v.end(); ++it )
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

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