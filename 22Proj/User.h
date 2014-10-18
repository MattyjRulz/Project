//
//  User.h
//  22Proj

#ifndef ___2Proj__User__
#define ___2Proj__User__

#include <string>

#include "InternalMessage.h"
#include "Paper.h"

enum UserType
{
    ADMIN = 0,
    AUTHOR,                     // 1
    PARTICIPANT,                // 2
    PROGRAM_COMMITTEE,          // 3
    STEERING_COMMITTEE,         // 4
    PROGRAM_COMMITTEE_CHAIR,    // 5
    size                        // 6
};

// singleton, only 1 user per program
class User
{
public:
    
    static User* getInstance();
    
    const std::string& getName();
    
    const unsigned int& getType();
    
    void Logout();
    
    bool isLoggedIn();
    
    void setUpUser(const unsigned int &type, const std::string &name);
    
protected:
    
    //deconstructor
    ~User();
    
    //constructor
    User();
    
    // validate data before upload
    // update mysql
    void Update();
    
private:
    
    // do not implement
    User (User const &);
    void operator=(const User&);
    
    static User* instance;
    
    unsigned int type;
    
    std::string name;
    
    bool loggedIn;
    
    InternalMessage* msg;
};

//constructor
inline User::User()
{
    std::string tempEmail = "hey@lolmail.com";
    // get email from mysql
    msg = new InternalMessage(tempEmail);
}

inline void User::setUpUser(const unsigned int &type, const std::string &name)
{
    this->type = type;
    this->name = name;
    
    loggedIn = true;
}

// deconstructor
inline User::~User()
{
    if( instance != 0 )
    {
        delete instance;
        instance = 0;
    }
}

/*////////////////////////////////////////////////
   ,---.    ,--.        ,--.
  /  O  \ ,-|  ,--,--,--`--,--,--,
 |  .-.  ' .-. |        ,--|      \
 |  | |  \ `-' |  |  |  |  |  ||  |
 `--' `--'`---'`--`--`--`--`--''--'
*/////////////////////////////////////////////////

class Admin : public User
{
public:
    void registerParticipants();
    void setType();
private:
};


/*////////////////////////////////////////////////
 
   ,---.          ,--. ,--.
  /  O  \,--.,--,-'  '-|  ,---. ,---.,--.--.
 |  .-.  |  ||  '-.  .-|  .-.  | .-. |  .--'
 |  | |  '  ''  ' |  | |  | |  ' '-' |  |
 `--' `--'`----'  `--' `--' `--'`---'`--'
 
 */////////////////////////////////////////////////
class Author : public User
{
public:
protected:
    Author();
    ~Author();
private:
    
    Paper *paper;
};

inline Author::Author()
{
    paper = 0;
}

inline Author::~Author()
{
    if( paper != 0 )
    {
        delete paper;
        paper = 0;
    }
}


/*////////////////////////////////////////////////
 
 ,------.               ,--. ,--.    ,--.                     ,--.
 |  .--. ',--,--,--.--,-'  '-`--',---`--',---. ,--,--,--,--,,-'  '-.
 |  '--' ' ,-.  |  .--'-.  .-,--| .--,--| .-. ' ,-.  |      '-.  .-'
 |  | --'\ '-'  |  |    |  | |  \ `--|  | '-' \ '-'  |  ||  | |  |
 `--'     `--`--`--'    `--' `--'`---`--|  |-' `--`--`--''--' `--'
                                        `--'
 */////////////////////////////////////////////////
class Participant : public User
{
public:
private:
};


/*////////////////////////////////////////////////
 
 ,------.
 |  .--. ,--.--.,---. ,---.,--.--.,--,--,--,--,--.
 |  '--' |  .--| .-. | .-. |  .--' ,-.  |        |
 |  | --'|  |  ' '-' ' '-' |  |  \ '-'  |  |  |  |
 `--'    `--'   `---'.`-  /`--'   `--`--`--`--`--'
 
 ,-----.                       ,--. ,--.   ,--.
 '  .--./,---.,--,--,--,--,--,--`--,-'  '-,-'  '-.,---. ,---.
 |  |   | .-. |        |        ,--'-.  .-'-.  .-| .-. | .-. :
 '  '--'' '-' |  |  |  |  |  |  |  | |  |   |  | \   --\   --.
 `-----'`---'`--`--`--`--`--`--`--' `--'   `--'  `----'`----'
 
 */////////////////////////////////////////////////
class ProgramCommittee : public User
{
public:
protected:
    ProgramCommittee();
    ~ProgramCommittee();
private:
    
    Paper *paper;
};

inline ProgramCommittee::ProgramCommittee()
{
    paper = 0;
}

inline ProgramCommittee::~ProgramCommittee()
{
    if( paper != 0 )
    {
        delete paper;
        paper = 0;
    }
}


/*////////////////////////////////////////////////
 
 ,------.
 |  .--. ,--.--.,---. ,---.,--.--.,--,--,--,--,--.
 |  '--' |  .--| .-. | .-. |  .--' ,-.  |        |
 |  | --'|  |  ' '-' ' '-' |  |  \ '-'  |  |  |  |
 `--'    `--'   `---'.`-  /`--'   `--`--`--`--`--'
 
 ,-----.                       ,--. ,--.   ,--.
 '  .--./,---.,--,--,--,--,--,--`--,-'  '-,-'  '-.,---. ,---.
 |  |   | .-. |        |        ,--'-.  .-'-.  .-| .-. | .-. :
 '  '--'' '-' |  |  |  |  |  |  |  | |  |   |  | \   --\   --.
 `-----'`---'`--`--`--`--`--`--`--' `--'   `--'  `----'`----'
 
 ,-----,--.           ,--.
 '  .--.|  ,---. ,--,--`--,--.--.
 |  |   |  .-.  ' ,-.  ,--|  .--'
 '  '--'|  | |  \ '-'  |  |  |
 `-----`--' `--'`--`--`--`--'
 
 
 */////////////////////////////////////////////////
class ProgramCommitteeChair : public User
{
public:
private:
};


/*////////////////////////////////////////////////
 
 ,---.  ,--.                   ,--.
 '   .-,-'  '-.,---. ,---.,--.--`--,--,--, ,---.
 `.  `-'-.  .-| .-. | .-. |  .--,--|      | .-. |
 .-'    ||  | \   --\   --|  |  |  |  ||  ' '-' '
 `-----' `--'  `----'`----`--'  `--`--''--.`-  /
                                          `---'
 ,-----.                       ,--. ,--.   ,--.
 '  .--./,---.,--,--,--,--,--,--`--,-'  '-,-'  '-.,---. ,---.
 |  |   | .-. |        |        ,--'-.  .-'-.  .-| .-. | .-. :
 '  '--'' '-' |  |  |  |  |  |  |  | |  |   |  | \   --\   --.
 `-----'`---'`--`--`--`--`--`--`--' `--'   `--'  `----'`----'
 
 */////////////////////////////////////////////////
class SteeringCommittee : public User
{
public:
private:
};


#endif /* defined(___2Proj__User__) */
