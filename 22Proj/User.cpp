//
//  User.cpp
//  22Proj

#include "User.h"
#include <iostream>

User* User::instance = 0;
// get user, but do not create
User* User::getInstance()
{
    if( instance == 0 )
    {
        instance = new User;
    }
    
    return instance;
}

const std::string &User::getName()
{
    return name;
}

const unsigned int &User::getType()
{
    return type;
}

void User::Logout()
{
    if( instance == 0 || loggedIn == false )
    {
        std::cout << "No user is currently logged in..." << std::endl;
    }
    else
    {
        loggedIn = false;
        std::cout << "You are now logged out." << std::endl;
    }
    
}

bool User::isLoggedIn()
{
    return loggedIn;
}

/*///////////////////////////////////////////////////////
     ___       _______  .___  ___.  __  .__   __.
    /   \     |       \ |   \/   | |  | |  \ |  |
   /  ^  \    |  .--.  ||  \  /  | |  | |   \|  |
  /  /_\  \   |  |  |  ||  |\/|  | |  | |  . `  |
 /  _____  \  |  '--'  ||  |  |  | |  | |  |\   |
/__/     \__\ |_______/ |__|  |__| |__| |__| \__|
 
///////////////////////////////////////////////////////*/
void Admin::registerParticipants()
{
    
}


