#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::~PmergeMe()
{
    std::cout << RED << "PmergeMe destrcutor!" << RESET << std::endl;
}

void    PmergeMe::sortListIntoPairs()
{
    int pNum = 1;
    size_t pairs = l.size();

    
    while ( pairs > 1 )
    {
        std::list<int>::iterator it = l.begin();

        for ( int i = 1; i < pNum && it != l.end(); ++i ) // i = 1 weil iterator auch bei index 1 startet
        {
            ++it; //getting end of first pair compononent
        }

        while ( it != l.end() )
        {
            std::list<int>::iterator first = it;
            std::list<int>::iterator sec = it;

            for ( int i = 0; i < pNum && sec != l.end(); ++i )
            {
                ++sec;
            }
            if ( sec == l.end() )
            {
                break;
            }
            if ( *first > *sec )
            {
                for ( int i = 0; i < pNum; ++i )
                {
                    std::iter_swap( first, sec );
                    --first;
                    --sec;
                }
            }
            for ( int i = 0; i < 2 * pNum && it != l.end(); ++i )
            {
                ++it;
            }
            
            // auto b = l.begin();
            // while ( b != l.end() )
            // {
            //     std::cout << ELEC_RED << *b << " " << RESET;
            //     ++b;
            // }
            // std::cout << std::endl;
        }
        pNum *= 2;
        pairs /= 2;
    }
    _biggestPair = pNum /= 2; //weil pNum ist schon bei size von nur noch einem pair, was die loop beendet
}

void    PmergeMe::sortVectorIntoPairs()
{
    int pNum = 1;
    size_t pairs = _v.size();

    while ( pairs > 1 )
    { // pNum = 1; i =0;  pNum = 2; i = 1; pNum = 4; i = 3; 8 7; 16; 15 
        for ( size_t i = pNum - 1 ; i + pNum < _v.size(); i += 2 * pNum )
        {
            if ( _v[ i ]  > _v[ i + pNum ] )
            {
                for ( int j = 0; j < pNum; ++j )
                {
                    std::swap( _v[ i - j ], _v[ i + pNum - j ] );
                }
            }
        }
        // for ( std::vector<int>::iterator it = v.begin(); it != v.end(); ++it )
        // {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;
        pNum *= 2;
        pairs /= 2;
    }
    _biggestPair = pNum /= 2; //weil pNum ist schon bei size von nur noch einem pair, was die loop beendet
}

void    PmergeMe::binarySortVector( int value )
{
    // std::cout << "Value to look for: " << ORANGE << value << RESET << std::endl;
    // std::cout << "size of v: " << v.size() << std::endl;

    std::vector<int>::iterator start = v.begin();
    std::vector<int>::iterator end = v.end();

    while ( start != end ) // solange searching area nicht leer ist
    {
        // std::cout << GREEN <<  "\nstart: " << *start << RESET <<  std::endl;
        // std::cout << RED << "end value: " << *(end - 1) << RED << std::endl;
        
        // getting middle iterator
        std::vector<int>::iterator mid = start + ( end - start ) / 2;
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
        else //bei in linker seite muss end = mid;6
        {
            end = mid;
        }
    }
    l.insert( start, value );
}

void    PmergeMe::insertLogicList()
{
    
}

void    PmergeMe::insertLogicVector()
{
    std::vector<std::vector<int>>   main;
    std::vector<std::vector<int>>   pend;
    std::vector<std::string>        labelPend;
    std::vector<std::string>        labelMain;
    while ( _biggestPair > 0 )
    {
        int m_index = 0;
        int p_index = 0;
        
        for ( int i = 0; i < _v.size(); i += _biggestPair )
        {
            
            for ( int j = 0; j < _biggestPair; ++j )
            {
                if ( i / _biggestPair == 0 ) // immer nur beim ersten mal - condition fuer i = 0 
                {
                    main[ m_index ][ j ] = _v[ i + j ];
                    
                    if ( j % _biggestPair == _biggestPair - 1 ) // um nur einmal zu machn - geht nur rein bei letzter iteration von einem Pair
                    {
                        ++m_index;
                        labelMain.push_back( "b1" );
                    } 
                }
                else if ( i / _biggestPair % 2 == 1 )
                {
                    main[ m_index ][ j ] = _v[ i + j ];
                    
                    if ( j % _biggestPair == _biggestPair - 1 )
                    {
                        ++m_index;
                        labelMain.push_back( "a" + std::to_string( m_index ) );
                    }
                }
                else if ( i / _biggestPair % 2 == 0)
                {
                    pend[ p_index ][ j ] = _v[ i + j ];
                    
                    if ( j % _biggestPair == _biggestPair -1 )
                    {
                        ++p_index;
                        labelMain.push_back( "b" + std::to_string( p_index ) );
                    }
                }
            }
        }

        _biggestPair /= 2;
    }
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
        sortListIntoPairs(); //std::list container logic
        insertLogicList();

    }

    {
        sortVectorIntoPairs(); // std::vector container logic
        insertLogicVector();

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