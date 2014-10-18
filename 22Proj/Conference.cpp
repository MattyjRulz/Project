//
//  Conference.cpp
//  22Proj

#include <iostream>
#include <string>
#include <stdlib.h>     /* atoi */

#include "Conference.h"

#include "DatabaseManager.h"

Conference* Conference::instance = 0;

// online way to create or get conference
Conference* Conference::getInstance()
{
    if( instance == 0 )
    {
        sqlite3_stmt *stmt;
        int eVal = 0;
        instance = new Conference();
        
        // SET UP STATEMENT
        std::string Statement = "SELECT * FROM CDETAILS";
        
        // used to get results from sql
        std::vector<std::string> readIn;
        
        ////////////////////////////////////////////////
        // EXECUTE
        if(sqlite3_prepare_v2(DatabaseManager::getInstance()->getDb(),
                              Statement.c_str(),
                              -1,
                              &stmt,
                              NULL) == SQLITE_OK);
        {
            int cols = sqlite3_column_count(stmt);
            
            int result = 0;
            
            while( true )
            {
                result = sqlite3_step(stmt);
                if( result == SQLITE_ROW )
                {
                    for( int col = 0; col < cols; ++col )
                    {
                        // get all the columns from CDetails
                        readIn.push_back((char*)sqlite3_column_text(stmt, col));
                        std::cout << readIn.back() << std::endl;
                    }
                }
                else
                {
                    break; // no conference set up
                }
            }
            
        }
        sqlite3_finalize(stmt);
        // EXECUTE
        ////////////////////////////////////////////////
        
        // if the conference details were gathered successfully
        if( readIn.size() == 5 )
        {
            instance->cdetails = new CDetails(readIn[0],
                                              readIn[1],
                                              readIn[2],
                                              readIn[3],
                                              readIn[4]);
            
            // we're finished here
            return instance;
        }
        // OTHERWISE the conference has not been set up, so set it up
        
        std::cout << "No Conference has been created.\nWe just need to set up an Admin, and the Conference Details.\n\n";
        // you created conference, specify an admin
        std::string name;
        std::string pass;
        
        std::cout << "Admin Creation.\n";
        std::cout << "Please Enter a Name: ";
        std::cin >> name;
        
        std::cout << "Please Enter your Password: ";
        std::cin >> pass;
        
        // upload admin name and pass, he is our first user
        
        // create Conference Details
        std::cout << "Conference Details Creation.\n";
        
        std::string startTime;
        std::string endTime;
        std::string startCallForPapers;
        std::string endCallForPapers;
        std::string location;
        
        std::cout << "DATE (YYYY-MM-DD); Conference START: ";
        std::cin >> startTime;
        
        std::cout << "DATE (YYYY-MM-DD); Conference END: ";
        std::cin >> endTime;
        
        std::cout << "DATE (YYYY-MM-DD); Call For Papers START ";
        std::cin >> startCallForPapers;
        
        std::cout << "DATE (YYYY-MM-DD); Call For Papers END: ";
        std::cin >> endCallForPapers;
        
        std::cout << "STRING; Location of Conference: ";
        std::cin >> location;
        
        instance->cdetails = new CDetails(startTime,
                                endTime,
                                startCallForPapers,
                                endCallForPapers,
                                location);
        
        // upload Conference Details to mysql
        
        ////////////////////////////////////////////////
        // SET UP STATEMENT
        Statement =     "CREATE TABLE IF NOT EXISTS CDETAILS\n";
        Statement.append("(startTime DATE,\n");
        Statement.append("endTime DATE,\n");
        Statement.append("startCallForPapers DATE,\n");
        Statement.append("endCallForPapers DATE,\n");
        Statement.append("location VARCHAR(255)\n)\n");
        // SET UP STATEMENT
        ////////////////////////////////////////////////
        
        ////////////////////////////////////////////////
        // EXECUTE
        if(sqlite3_prepare_v2(DatabaseManager::getInstance()->getDb(),
                              Statement.c_str(),
                              -1,
                              &stmt,
                              NULL) == SQLITE_OK);
        {
            eVal = sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);
        // EXECUTE
        ////////////////////////////////////////////////
        
        ////////////////////////////////////////////////
        // SET UP STATEMENT
        Statement = "INSERT INTO CDETAILS (startTime, endTime, ";
        Statement.append("startCallForPapers, endCallForPapers, location) ");
        Statement.append("VALUES ('");
        Statement.append(startTime + "', '");
        Statement.append(endTime + "', '");
        Statement.append(startCallForPapers + "', '");
        Statement.append(endCallForPapers + "', '");
        Statement.append(location + "');");
        // SET UP STATEMENT
        ////////////////////////////////////////////////
        
        ////////////////////////////////////////////////
        // EXECUTE
        if(sqlite3_prepare_v2(DatabaseManager::getInstance()->getDb(),
                              Statement.c_str(),
                              -1,
                              &stmt,
                              NULL) == SQLITE_OK);
        {
            eVal = sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);
        // EXECUTE
        ////////////////////////////////////////////////
    }
    
    return instance;
}

User* Conference::Login()
{
    // get the name and password from the user
    std::string name;
    std::string pass;
    
    std::cout << "Please Enter a Name: ";
    std::cin >> name;
    
    std::cout << "Please Enter your Password: ";
    std::cin >> pass;
    
    // validate with mysql
    User* myUser = User::getInstance();
    
    std::string testName;
    std::string testPass;
    
    unsigned int type = 0; // get from mysql
    
    // error checking, something at fault with database
    if( type >= UserType::size )
    {
        std::cout << "Fault with values stored in database, USER_TYPE = ";
        std::cout << type << ", Highest value is: " << UserType::size-1 << "\n";
    }
    
    // if user valid
    myUser->setUpUser(type, name);
    
    std::cout << "You are now logged in as: " << User::getInstance()->getName() << std::endl;
    
    return myUser;
}

void Conference::submitRegistration()
{
    // get the name and password from the user
    std::string name;
    std::string pass;
    std::string email;
    
    std::cout << "Please Enter a Name: ";
    std::cin >> name;
    
    std::cout << "Please Enter your Password: ";
    std::cin >> pass;
    
    std::cout << "Please Enter a valid Email Address: ";
    std::cin >> email;
    
    // submit these details to mysql registration table
    // when an admin logs in, he will be notified of requests
    // and then will need to set up that user, and manually email
    // him
}

void Conference::getCDetails()
{
    // retrive CDetails from mysql
}

void Conference::formProgramCommittee()
{
    // validate user, only an SC can activate this
    if( User::getInstance()->getType() != UserType::STEERING_COMMITTEE )
    {
        std::cout << "Only a Steering Committee member can use this function.\n";
        return;
    }
    
    // how do we form the program committee again?
}

void Conference::displayMenu()
{
    // useruser has not been created yet, or not logged in
    if( User::getInstance() == 0 || !User::getInstance()->isLoggedIn() )
    {
        std::cout   << "1. Login.\n"
                    << "2. Submit Registration.\n"
                    << "3. Quit Program.\n";
    }
    else // user is logged in
    {
        switch(User::getInstance()->getType())// what type of user
        {
            case UserType::ADMIN:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            case UserType::AUTHOR:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            case UserType::PARTICIPANT:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            case UserType::PROGRAM_COMMITTEE:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            case UserType::PROGRAM_COMMITTEE_CHAIR:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            case UserType::STEERING_COMMITTEE:
            {
                std::cout << "1. Logout.\n";
                break;
            }
            default:
            {
                // Undefined User Type - error
                std::cout << "Conference::displayMenu - Undefined User Type: " << User::getInstance()->getType() << "\n";
            }
        }// switch(user type)
    }// logged in
}

void Conference::options()
{
    unsigned int choice;
    
    std::cout << "Select a function to perform: ";
    
    std::string sChoice;
    
    std::cin >> sChoice;
    
    if( isnumber(sChoice[0]) )
    {
        char number = sChoice[0];
        choice = atoi(&number);
    }
    else
    {
        std::cout << "Input must be a positive integer.\n";
        return;
    }
    // useruser has not been created yet, or not logged in
    if( User::getInstance() == 0 || !User::getInstance()->isLoggedIn() )
    {
        switch(choice)
        {
            case 1:
            {
                Login();
                break;
            }
            case 2:
            {
                submitRegistration();
                break;
            }
            case 3:
            {
                running = false;
                break;
            }
            default:
            {
                std::cout << "Invalid Selection: " << choice << std::endl;
            }
        }
    }
    else // user is logged in
    {
        switch(User::getInstance()->getType()) // what type of user
        {
            case UserType::ADMIN:
            {
                // all ADMIN methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                
                break;
            }
            case UserType::AUTHOR:
            {
                // all AUTHOR methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                break;
            }
            case UserType::PARTICIPANT:
            {
                // all PARTICIPANT methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                break;
            }
            case UserType::PROGRAM_COMMITTEE:
            {
                // all PROGRAM_COMMITTEE methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                break;
            }
            case UserType::PROGRAM_COMMITTEE_CHAIR:
            {
                // all PROGRAM_COMMITTEE_CHAIR methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                break;
            }
            case UserType::STEERING_COMMITTEE:
            {
                // all STEERING_COMMITTEE methods
                switch(choice)
                {
                    case 1:
                    {
                        User::getInstance()->Logout();
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid Selection: " << choice << std::endl;
                    }
                }
                break;
            }
            default:
            {
                // Undefined User Type - error
                std::cout << "Conference::options - Undefined User Type: " << User::getInstance()->getType() << "\n";
            }
        }// switch(user type)
    }// logged in
}

bool Conference::Run()
{
    displayMenu();
    options();
    
    return running;
}

