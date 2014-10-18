//
//  main.cpp
//  22Proj

#include <iostream>

#include "Conference.h"

int main(int argc, const char * argv[])
{
    while( Conference::getInstance()->Run() == true ) {}
        
    return 0;
}
