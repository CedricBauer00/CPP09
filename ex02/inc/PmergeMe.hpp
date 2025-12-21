#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>
#include <sstream>

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

        int     merge( const int argc, char **argv ); //konnte nicht const char **argv machen, warum?
        
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
        int     binarySortList( int value, int boundary, std::list<std::list<int>> main ); // needs rework
};

// handles positive range of integers
// must use the Ford Johnson algo - Merge insertion??
// if error occurs during runtime, appropriate error message on std::cerr
// use 2 different containers 
// program must be able to use at least 300 different integers
// implement algo for each container
// avoid using generic functions
// output:
// 1 line: explicit text, unsorted positive int sequence
// 2 line: explicit text, sorted positive int sequence 
// 3 line: explicit message indicating the time the algo took - specifying FIRST container
// 3 line: explicit message indicating the time the algo took - specifying SECOND container

// format of time display is free - difference between container time must be visible though
// operation time includes all ops - sorting and data management
// no std::map or std::stack
// "The management of errors related to duplicates is left to your discretion."