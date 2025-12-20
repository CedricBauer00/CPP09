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
    std::cout << "Here1" << std::endl;
    return 0;
}

int PmergeMe::sortVectorIntoPairs()
{
    
    std::cout << "Here" << std::endl;

    return 0;
}

void    PmergeMe::binarySortVector( int value )
{
    // std::cout << "Value to look for: " << ORANGE << value << RESET << std::endl;
    // std::cout << "size of v: " << v.size() << std::endl;

    std::vector<int>::iterator start = v.begin();
    std::vector<int>::iterator end = v.end();
    std::vector<int>::iterator mid;

    while ( start != end ) // solange searching area nicht leer ist
    {
        // std::cout << GREEN <<  "\nstart: " << *start << RESET <<  std::endl;
        // std::cout << RED << "end value: " << *(end - 1) << RED << std::endl;
        
        // getting middle iterator
        mid = start + ( end - start ) / 2;
        // std::cout << BLUE << "mid: " << *mid << RESET << std::endl;

        if ( *mid < value ) // wenn in der linken haelfte liegt 
        {
            start = mid + 1; // neue border
            // std::cout << "in der rechten seite!" << std::endl;
        }
        else
        {
            end = mid;
            // std::cout << "in der Linken seite!" << std::endl;
        }
    }
    
    // std::cout << ELEC_RED << "Insert position: " << ( start - v.begin() ) << ORANGE << " next bigger value: " << *start << RESET << std::endl;
    v.insert( start, value );
}
//  1 2 5 7 11 24 44 66
void    PmergeMe::binarySortList( int value )
{
    std::list<int>::iterator start = l.begin();
    std::list<int>::iterator end = l.end();
    
    while ( std::distance( start, end ) > 0) // distance wird immer kleiner, bis 0
    {
        size_t dist = std::distance( start, end );
        
        std::list<int>::iterator mid = start;
        std::advance( mid, dist / 2 );

        if ( *mid < value ) // in rechter seite muss start = mid + 1;
        {
            start = mid;
            ++start;
        }
        else //bei in linker seite muss end = mid;
        {
            end = mid;
        }
    }
    l.insert( start, value );
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
        if ( sortListIntoPairs() != 0 )
            return -1;// std::list container logic
    }

    {
        if ( sortVectorIntoPairs() != 0 )
            return -1;// std::vector container logic
    }

    binarySortVector( 6 ); // falls wir value schon haben den wir einsortieren wollen
    binarySortList( 6 );

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