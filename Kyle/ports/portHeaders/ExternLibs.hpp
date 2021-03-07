//
//  loadPortData.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

// NOTE: 'ports.csv' came from https://github.com/maraisr/ports-list/blob/master/all.csv

#ifndef ExternLib_hpp
#define ExternLib_hpp

#include <iostream> // std::exception, std::cout, std::cin, std::endl
#include <string> // std::string, std::stoi, std::to_string
#include <vector> // std::vector
#include <fstream> // std::ios::in
#include <map> // std::map

#if defined(_WIN32) || defined(_WIN64)
#ifndef CLEAR_SCREEN_KEY
#define CLEAR_SCREEN_KEY "cls"
#endif
#ifndef WAIT_FOR_USER
#define WAIT_FOR_USER "pause"
#endif
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(linux) || defined(__linux)
#ifndef CLEAR_SCREEN_KEY
#define CLEAR_SCREEN_KEY "clear"
#endif
#ifndef WAIT_FOR_USER
#define WAIT_FOR_USER "read"
#endif
#else
#define UNSUPPORTED_OS UNKNOWN // was not caught by one of the above cases.
#endif

// define using statements
using std::exception;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;
using std::stoi;
using std::to_string;
using std::map;

// define inline functions:
inline bool isYes(string str) {
    return str == "y" || str == "Y" || str == "yes" || str == "Yes" || str == "yEs" || str == "yeS" || str == "YEs" || str == "yES" || str == "YeS"  || str == "YES";
}

inline bool isNo(string str) {
    return str == "no" || str == "n" || str == "NO" || str == "No" || str == "nO";
}

#endif /* ExternLib_hpp */
