#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe() : _biggestPair( 0 )
{
    std::cout << GREEN << "PmergeMe default constructor!" << RESET << std::endl; 
}

PmergeMe::PmergeMe( const PmergeMe &copy ) : _l( copy._l ), _v( copy._v ), _biggestPair( copy._biggestPair ),
                                            _result( copy._result ), _result_l( copy._result_l)
{
    std::cout << GREEN << "PmergeMe copy constructor!" << RESET << std::endl; 
}

PmergeMe&   PmergeMe::operator=( const PmergeMe &copy )
{
    std::cout << GREEN << "PmergeMe assignment operator!" << RESET << std::endl; 

    if ( this != &copy )
    {
        this->_l = copy._l;
        this->_v = copy._v;
        this->_biggestPair = copy._biggestPair;
        this->_result = copy._result;
        this->_result_l = copy._result_l;
    }

    return *this;
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
    { 
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
        
        pNum *= 2;
        pairs /= 2;
    }

    _biggestPair = pNum /= 2;
}

int    PmergeMe::binarySortVector( int value, int boundary, std::vector<std::vector<int>> main )
{
    int start = 0;
    int biggestPair = main[ start ].size() - 1;
    
    
    if ( value < main[ start ][ biggestPair ])
    {
        return 0;
    }
    
    if ( value > main[ boundary ][ biggestPair ] )
    {
        return -1;
    }

    while ( start < boundary - 1 )
    {
        int mid = (( boundary - start ) / 2 ) + start;

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

int getBoundaryPosV( std::vector<std::string> labelMain, std::string label )
{
    label[ 0 ] = 'a';
    
    int i = 0;

    for ( std::string temp : labelMain )
    {
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

    for ( size_t i = _result.size(); i < _v.size(); ++i )
    {
        _result.push_back( _v[ i ] );
    }
    
    _v = _result;
    
    _result.clear();
}

void    PmergeMe::insertVector( std::vector<std::vector<int>> main, std::vector<std::vector<int>> pend,
                std::vector<std::string> labelMain, std::vector<std::string> labelPend )
{
    static size_t jacobCur = 3;
    static size_t jacobPrev = 1;

    while ( !pend.empty() )
    {
        ssize_t startPos = jacobCur - jacobPrev;
        
        if ( ( size_t )startPos >= pend.size() )
        {
            startPos = pend.size();
            jacobCur = 3;
            jacobPrev = 1;
        }
        --startPos;

        while ( startPos >= 0 )
        {
            int boundary = getBoundaryPosV( labelMain, labelPend[ startPos ] );
            
            int insertPos = binarySortVector( pend[ startPos ][ pend[ startPos ].size() - 1 ], boundary, main );

            if ( insertPos >= 0 )
            {
                main.insert( main.begin() + insertPos, pend[ startPos ] );
                labelMain.insert( labelMain.begin() + insertPos, labelPend[ startPos ] );
            }
            else
            {
                main.push_back( pend[ startPos ] );
                labelMain.push_back( labelPend[ startPos ] );
            }
            
            pend.erase( pend.begin() + startPos );
            labelPend.erase( labelPend.begin() + startPos );
            
            --startPos;
        }

        if ( !pend.empty() )
        {
            jacobCur = jacobCur + ( jacobPrev * 2 );
            jacobPrev = jacobCur - ( jacobPrev * 2 );
        }
    }

    appendRemainingVector( main );
}

void    PmergeMe::initialisingVectors()
{

    while ( _biggestPair > 0 )
    {
        std::vector<std::vector<int>>   main;
        std::vector<std::vector<int>>   pend;
        std::vector<std::string>        labelPend;
        std::vector<std::string>        labelMain;
        size_t m_index = 0;
        size_t p_index = 0;

        for ( size_t i = 0; i < _v.size(); i += _biggestPair )
        {
            if ( i + _biggestPair - 1 >= _v.size() )
            {
                break;
            }
            for ( size_t j = 0; j < _biggestPair; ++j )
            {
                if ( i / _biggestPair == 0 )
                {
                    if ( m_index >= main.size() ) 
                    {
                        main.push_back( std::vector<int>() );
                    }
                    main[ m_index ].push_back( _v[ i + j ] );
                    
                    if ( j % _biggestPair == _biggestPair - 1 )
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
        }

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

        for ( int i = 1; i < pNum && it != _l.end(); ++i )
        {
            ++it;
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
        }

        pNum *= 2;
        pairs /= 2;
    }

    _biggestPair = pNum /= 2;
}

int getBoundaryPosL( std::list<std::string> labelMain, std::string label )
{
    label[ 0 ] = 'a';
    
    int i = 0;

    for ( std::string temp : labelMain )
    {
        if ( temp == label )
        {
            return i;
        }
        ++i;
    }

    return i - 1;
}

int PmergeMe::binarySortList( int value, int boundary, std::list<std::list<int>> main )
{
    int start = 0;

    std::list<std::list<int>>::iterator lists = main.begin();
    std::list<int>::iterator            lastOfPair = lists->begin();
    
    std::advance( lastOfPair, lists->size() - 1);
    
    int _biggestPair = lists->size() - 1;
    
    if ( value < *lastOfPair )
    {
        return 0;
    }

    std::advance( lists, boundary );
    std::list<int>::iterator lastOfPair2 = lists->begin();
    
    std::advance( lastOfPair2, lists->size() - 1 );
    if ( value > *lastOfPair2 )
    {
        return -1;
    }

    while ( start < boundary - 1 )
    {
        int mid = ( ( boundary - start) / 2 ) + start;

        lists = main.begin();
        std::advance( lists, mid );

        lastOfPair = lists->begin();
        std::advance( lastOfPair, _biggestPair );
        
        if ( value > *lastOfPair )
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

void    PmergeMe::appendRemainingList( std::list<std::list<int>> main )
{
    for ( std::list<int> pairs : main )
    {
        for ( int value : pairs )
        {
            _result_l.push_back( value );
        }
    }
    
    std::list<int>::iterator it = _l.begin();
    std::advance( it, _result_l.size() );

    while ( it != _l.end() )
    {
        _result_l.push_back( *it );
        ++it;
    }

    _l = _result_l;

    _result_l.clear();
}

void    PmergeMe::insertList( std::list<std::list<int>> main, std::list<std::list<int>> pend, 
                    std::list<std::string> labelMain, std::list<std::string> labelPend )
{
    static size_t jacobCur = 3;
    static size_t jacobPrev = 1;

    while ( !pend.empty() )
    {
        ssize_t startPos = jacobCur - jacobPrev;

        if ( ( size_t )startPos >= pend.size() )
        {
            startPos = pend.size();
            jacobCur = 3;
            jacobPrev = 1;
        }
        --startPos;

        while ( startPos >= 0 )
        {
            std::list<std::string>::iterator itLabelPend = labelPend.begin();
            std::advance( itLabelPend, startPos );            
            int boundary = getBoundaryPosL( labelMain, *itLabelPend );
            
            std::list<std::list<int>>::iterator itPend = pend.begin();
            std::advance( itPend, startPos );
            std::list<int>::iterator itPairIndex = itPend->begin();
            std::advance( itPairIndex, itPend->size() - 1);
            int insertPos = binarySortList( *itPairIndex, boundary, main );
         
            if ( insertPos >= 0 )
            {
                std::list<std::list<int>>::iterator itMain = main.begin();
                std::advance( itMain, insertPos );
                main.insert( itMain, *itPend );
                
                std::list<std::string>::iterator itLabelMain = labelMain.begin();
                std::advance( itLabelMain, insertPos );            
                labelMain.insert( itLabelMain, *itLabelPend );
            }
            else
            {
                main.push_back( *itPend );
                labelMain.push_back( *itLabelPend );
            }

            pend.erase( itPend );
            labelPend.erase( itLabelPend );
            
            --startPos;
        }
        
        if ( !pend.empty() )
        {
            jacobCur = jacobCur + ( jacobPrev * 2 );
            jacobPrev = jacobCur - ( jacobPrev * 2 );
        }
    }

    appendRemainingList( main );
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
        size_t p_index = 0;

        for ( size_t i = 0; i < _l.size(); i += _biggestPair )
        {
            if ( i + _biggestPair - 1 >= _l.size() )
            {
                break;
            }
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

                    if ( j % _biggestPair == _biggestPair - 1 )
                    {
                        labelMain.push_back( "b1" );
                        ++m_index;
                    }
                }
                else if ( i / _biggestPair % 2 == 1 )
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
                        pend.push_back( std::list<int>() );
                    }

                    std::list<std::list<int>>::iterator it = pend.begin();
                    std::advance( it, p_index );
                    std::list<int>::iterator it2 = _l.begin();
                    std::advance( it2, i + j );
                    it->push_back( *it2 );
                    
                    if ( j % _biggestPair == _biggestPair -1 )
                    {
                        labelPend.push_back( "b" + std::to_string( p_index + 2 ) );
                        ++p_index;
                    }
                }            
            }

        }
        insertList( main, pend, labelMain, labelPend );
        _biggestPair /= 2;
    }
}

int    PmergeMe::merge( const int argc, char **argv )
{
    for ( int i = 1; i < argc; ++i )
    {
        std::string arg = argv[ i ]; 

        size_t pos = arg.find_first_not_of( "0123456789 " );
        if ( pos != std::string::npos )
        {
            std::cerr << RED << "Error: bad input." << ": " << arg[ pos ] << RESET << std::endl;
            return -1;
        }

        std::istringstream ss( arg );
        std::string substr;

        while ( ss >> substr )
        {
            this->_l.push_back( std::stoi( substr ) );
            this->_v.push_back( std::stoi( substr ) );
            if ( _v.size() > 3000 )
            {
                std::cerr << RED << "Error: input too big." << RESET << std::endl;
                return -1;
            }
        }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        sortVectorIntoPairs();
        initialisingVectors();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Vector time: " << duration.count() << "; microseconds." << std::endl;

    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        sortListIntoPairs();
        initialisingLists();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "List time: " << duration.count() << "; microseconds." << std::endl;
    }

    std::cout << GREEN << "List: " << RESET << std::endl;
    for ( std::list<int>::iterator it = _l.begin(); it != _l.end(); ++it )
    {
        std::cout << *it << " ";
    } 
    std::cout << std::endl;

    bool check = 0;
    int i = 1;
    std::list<int>::iterator compare = _l.begin();
    for ( std::list<int>::iterator it2 = std::next( _l.begin(), 1 ); it2 != _l.end(); ++it2 )
    {
        if ( *compare > *it2 )
        {
            std::cout << ELEC_RED << "Error: Is not sorted!\nIndex: " << i << "; Value: " << *it2 << RESET << std::endl;
            check = 1;
            break;
        }
        ++compare;
        ++i;
    }
    if ( !check )
    {
        std::cout << GREEN << "Success!!: List is sorted!" << std::endl;
    }

    std::cout << GREEN << "Vecoter: " << RESET << std::endl; 
    for ( std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it )
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    check = 0;
    for ( size_t i = 1; i < _v.size(); ++i )
    {
        if ( _v [ i - 1 ] > _v [ i ] )
        {
            std::cout << ELEC_RED << "Error: Is not sorted! Index: " << i << "; Value: " << _v[ i ] << RESET << std::endl;
            check = 1;
            break;
        }
    }
    if ( !check )
    {
        std::cout << GREEN << "Success!!: Vector is sorted!" << std::endl;
    }

    std::cout << GREEN << "Done!" << RESET << std::endl; 
   
    return 0;
}
