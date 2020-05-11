//
// Created by Roberto Di Rienzo on 18/02/2020.
//

#ifndef T2CWL_ECHOSTDOUT_HPP
#define T2CWL_ECHOSTDOUT_HPP


#include <iostream>
#include <functional>

#define OUT(T) std::cout << T << "\n"
#define ERR(T) std::cerr << T << "\n"
#define LOGALL(T) std::cerr << T << "\n"
//#define LOGALL(T) std::clog << T << " [" << __FILE__<< "->" << __PRETTY_FUNCTION__ << "->" << __LINE__  <<"]"<<"\n"
//#define LOG(T) std::clog << T << " [" << __PRETTY_FUNCTION__ << "->" << __LINE__  <<"]"<<"\n"



#endif  // T2CWL_ECHOSTDOUT_HPP
