#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>
#include <sstream>
#include <chrono>

#define RED  "\033[31m"
#define ELEC_RED "\033[38;2;255;20;20m"
#define BLUE    "\033[34m"
#define GREEN  "\033[32m"
#define RESET  "\033[0m"
#define ORANGE  "\033[38;2;255;120;0m"

class PmergeMe
{
    private:
        std::list<int>      _l;
        std::vector<int>    _v;
        size_t              _biggestPair;
        std::vector<int>    _result;
        std::list<int>      _result_l;
    public:
        PmergeMe();
        PmergeMe( const PmergeMe &copy );
        PmergeMe& operator=( const PmergeMe &copy );
        ~PmergeMe();

        int     merge( const int argc, char **argv );
        
        void    sortVectorIntoPairs();
        void    initialisingVectors();
        void    insertVector( std::vector<std::vector<int>> main, std::vector<std::vector<int>> pend,
                std::vector<std::string> labelPend, std::vector<std::string> labelMain );
        int     binarySortVector( int value, int boundary, std::vector<std::vector<int>> main );
        void    appendRemainingVector( std::vector<std::vector<int>> main );
        


        void    sortListIntoPairs();
        void    appendRemainingList( std::list<std::list<int>> main );

        void    initialisingLists();
        void    insertList( std::list<std::list<int>> main, std::list<std::list<int>> pend, 
                    std::list<std::string> labelMain, std::list<std::string> labelPend );
        int     binarySortList( int value, int boundary, std::list<std::list<int>> main );
};
