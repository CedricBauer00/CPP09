#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::~PmergeMe()
{
    std::cout << RED << "PmergeMe destrcutor!" << RESET << std::endl;
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

// int    PmergeMe::binarySortVector( int value, int boundary, std::vector<std::vector<int>> main )
// {
//     // std::cout << "Value to look for: " << ORANGE << value << RESET << std::endl;
//     // std::cout << "size of v: " << v.size() << std::endl;

//     std::vector<std::vector<int>>::iterator start = main.begin();
//     std::vector<std::vector<int>>::iterator end = main.begin() + boundary;

//     while ( start != end ) // solange searching area nicht leer ist
//     {
//         // std::cout << GREEN <<  "\nstart: " << *start << RESET <<  std::endl;
//         // std::cout << RED << "end value: " << *(end - 1) << RED << std::endl;
        
//         // getting middle iterator
//         std::vector<std::vector<int>>::iterator mid = start + ( end - start ) / 2;
//         // std::cout << BLUE << "mid: " << *mid << RESET << std::endl;

//         std::vector<int> pair = main[ mid - main.begin() ]; //getting index
//         if ( pair[ pair.size() - 1 ] < value ) // wenn in der linken haelfte liegt 
//         {
//             start = mid + 1; // neue border
//             // std::cout << "in der rechten seite!" << std::endl;
//         }
//         else
//         {
//             end = mid;
//             // std::cout << "in der Linken seite!" << std::endl;
//         }
//     }    
//     // std::cout << ELEC_RED << "Insert position: " << ( start - _v.begin() ) << ORANGE << " next bigger value: " << *start << RESET << std::endl;
//     return ( end - main.begin() );
// }

int    PmergeMe::binarySortVector( int value, int boundary, std::vector<std::vector<int>> main )
{
    int start = 0;
    int biggestPair = main[ start ].size() - 1; //groesse des aktullen pairs
    
    
    if ( value < main[ start ][ biggestPair ])
    {
        return start;
    }

    while ( start < boundary - 1 ) // start == boundary -1 exit, sonst infite loop
    {
        int mid = (( boundary - start ) / 2 ) + start; // + start damit wir index bekommen 

        if ( value > main[ mid ][ biggestPair ] )
        {
            start = mid;
        }
        else
        {
            boundary = mid;
        }

    }

    return boundary;    
}

void    PmergeMe::binarySortList( int value )
{
    std::list<int>::iterator start = _l.begin();
    std::list<int>::iterator end = _l.end();
    
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
    _l.insert( start, value );
}

int getBoundaryPos( std::vector<std::string> labelMain, std::string label )
{
    label[ 0 ] = 'a';
    
    int i = 0;

    for ( std::string temp : labelMain )
    {
        // std::cout << "cur_main: "<< temp << std::endl;
        if ( temp == label )
        {
            return i;
        }
        ++i;
    }

    return i - 1;
}

void    PmergeMe::appendRemainingVector(std::vector<std::vector<int>> main)
{
    for ( std::vector<int> pairs : main )
    {
        for ( int value : pairs )
        {
            _result.push_back( value );
        }
    }

    for ( size_t i = _result.size(); i < _v.size(); ++i ) // saving remainder
    {
        _result.push_back( _v[ i ] );
    }
    
    _v = _result;
    
    _result.clear(); // to be reinitialised //would keep saved memory and just append to the end further
}

void    PmergeMe::insertVector( std::vector<std::vector<int>> main, std::vector<std::vector<int>> pend,
                std::vector<std::string> labelMain, std::vector<std::string> labelPend )
{
    static size_t jacobCur = 3;
    static size_t jacobPrev = 1;

    while ( !pend.empty() )
    {
        ssize_t startPos = jacobCur - jacobPrev; //starting posiint    PmergeMe::binarySortVector( int value, int boundary, std::vector<std::vector<int>> main ) tion of which element to push 
        
        if ( ( size_t )startPos > pend.size() ) // for when there are less elements than jacpobstahal number existent
        {
            startPos = pend.size();
            jacobCur = 3;
            jacobPrev = 1;
        }
        --startPos; //for index

        while ( startPos >= 0 ) //durch einzelne elemente durchgehen
        {
            int boundary = getBoundaryPos( labelMain, labelPend[ startPos ] );
            // std::cout << "boundary: " << boundary << std::endl;
            
            int insertPos = binarySortVector( pend[ startPos ][ pend[ startPos ].size() - 1], boundary, main ); //
            // std::cout << "insertPos: " << insertPos << std::endl;
            
            main.insert( main.begin() + insertPos, pend[ startPos ] );
            labelMain.insert( labelMain.begin() + insertPos, labelPend[ startPos ] );
            
            pend.erase( pend.begin() + startPos );
            labelPend.erase( labelPend.begin() + startPos );
            
            --startPos;
            // std::cout << "startPos: " << startPos << std::endl;
        }

        jacobCur = jacobCur + ( jacobPrev * 2 );
        jacobPrev = jacobCur - ( jacobPrev * 2 );
    }

    appendRemainingVector( main );
}

void    PmergeMe::initialisingVectors()
{
    //     std::cout << GREEN << "Vecotr: " << RESET << std::endl; 
    // for ( std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it )
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    while ( _biggestPair > 0 )
    {
        std::vector<std::vector<int>>   main; //declaration in loop, to not needing to reinitialise them always
        std::vector<std::vector<int>>   pend;
        std::vector<std::string>        labelPend;
        std::vector<std::string>        labelMain;
        size_t m_index = 0;
        size_t p_index = 0;

        for ( size_t i = 0; i < _v.size(); i += _biggestPair )
        {
            if ( i + _biggestPair - 1 >= _v.size() )
                break;
            for ( size_t j = 0; j < _biggestPair; ++j )
            {
                if ( i / _biggestPair == 0 ) // immer nur beim ersten mal - condition fuer i = 0 
                {
                    if ( m_index >= main.size() )
                    {
                        main.push_back( std::vector<int>() );
                    }
                    main[ m_index ].push_back( _v[ i + j ] );
                    
                    if ( j % _biggestPair == _biggestPair - 1 ) // um nur einmal zu machn - geht nur rein bei letzter iteration von einem Pair
                    {
                        labelMain.push_back( "b1" );
                        ++m_index;
                    }
                }
                else if ( i / _biggestPair % 2 == 1 )
                {
                    if ( m_index >= main.size() )
                    {
                        main.push_back( std::vector<int>() );
                    }
                    main[ m_index ].push_back( _v[ i + j ] );
                    
                    if ( j % _biggestPair == _biggestPair - 1 )
                    {
                        labelMain.push_back( "a" + std::to_string( m_index ) );
                        ++m_index;
                    }
                }
                else if ( i / _biggestPair % 2 == 0)
                {
                    if ( p_index >= pend.size() )
                    {
                        pend.push_back( std::vector<int>() );
                    }
                    pend[ p_index ].push_back( _v[ i + j ] );
                    
                    if ( j % _biggestPair == _biggestPair -1 )
                    {
                        labelPend.push_back( "b" + std::to_string( p_index + 2 ) );
                        ++p_index;
                    }
                }
            }
            
            // std::cout << "printing" << std::endl;
            // for ( size_t i = 0; i < main.size(); ++i)
            // {
            //     for ( size_t j = 0; j < main[i].size(); ++j)
            //     {
            //         std::cout << main[i][j] << " ";
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << std::endl;
        }
        // for (std::string tmp : labelMain ) {
        //     std::cout << "maintmp: " << tmp << std::endl;
        // }
        // for (std::string tmp : labelPend ) {
        //     std::cout << "pendtmp: " << tmp << std::endl;
        // }
        insertVector( main, pend, labelMain, labelPend );
        _biggestPair /= 2;
    }
}

void    PmergeMe::sortListIntoPairs()
{
    int pNum = 1;
    size_t pairs = _l.size();

    
    while ( pairs > 1 )
    {
        std::list<int>::iterator it = _l.begin();

        for ( int i = 1; i < pNum && it != _l.end(); ++i ) // i = 1 weil iterator auch bei index 1 startet
        {
            ++it; //getting end of first pair compononent
        }
        while ( it != _l.end() )
        {
            std::list<int>::iterator first = it;
            std::list<int>::iterator sec = it;

            for ( int i = 0; i < pNum && sec != _l.end(); ++i )
            {
                ++sec;
            }
            if ( sec == _l.end() )
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
            for ( int i = 0; i < 2 * pNum && it != _l.end(); ++i )
            {
                ++it;
            }
            
            // auto b = _l.begin();
            // while ( b != _l.end() )
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

void    PmergeMe::initialisingLists()
{
    while ( _biggestPair > 0 )
    {
        std::list<std::list<int>> main;
        std::list<std::list<int>> pend;
        std::list<std::string> labelMain;
        std::list<std::string> labelPend;
        size_t m_index = 0;
        // size_t p_index = 0;

        for ( size_t i = 0; i < _l.size(); i += _biggestPair )
        {
            if ( i + _biggestPair - 1 >= _l.size() )
                break;
            for ( size_t j = 0; j < _biggestPair; ++j )
            {
                if ( i / _biggestPair == 0 )
                {
                    if ( m_index >= main.size() )
                    {
                        main.push_back( std::list<int>() );
                    }
                    std::list<std::list<int>>::iterator it = main.begin();
                    std::advance( it, m_index );
                    std::list<int>::iterator it2 = _l.begin();
                    std::advance( it2, i + j );
                    it->push_back( *it2 );
                    // int index = 0;
                    // for ( auto it2 = main.begin(); it2 != main.end(); ++it2 )
                    // {
                    //     if ( it2 == it )
                    //         break;
                    //     index++;
                    // }
                    // std::cout << "index: " << index <<std::endl;
                    if ( j % _biggestPair == _biggestPair - 1 )
                    {
                        labelMain.push_back( "b1" );
                        ++m_index;
                    }
                }
                else if ( i / _biggestPair % 2 == 1 )
            }

        }
    }
}

int    PmergeMe::merge( const int argc, char **argv ) //konnte nicht const char **argv machen, warum?
{
    // std::cout << GREEN << "start!" << RESET << std::endl; 

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
            this->_l.push_back( std::stoi( substr ) );
            this->_v.push_back( std::stoi( substr ) );
        }
    }
// check fuer 3000 nummbers

    {
        sortVectorIntoPairs(); // std::vector container logic
        initialisingVectors();

    }

    {
        sortListIntoPairs(); //std::list container logic
        initialisingLists();

    }
    // for ( std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it )
    // {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;


    // binarySortList( 6 );

    // std::cout << GREEN << "List: " << RESET << std::endl;
    // for ( std::list<int>::iterator it = _l.begin(); it != _l.end(); ++it )
    // {
    //     std::cout << *it << " ";
    // } 
    // std::cout << std::endl;

    std::cout << GREEN << "Vecoter: " << RESET << std::endl; 
    for ( std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it )
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