//
//  Conference.h
//  22Proj

#ifndef ___2Proj__Conference__
#define ___2Proj__Conference__

#include "User.h"
#include "CDetails.h"

// singleton, only 1 conference per program
class Conference
{
public:
    
    // getInstance, only way to create conference
    static Conference* getInstance();
    
    /////////////////////////////////
    // Conference Specific Methods
    //
    User* Login();
    
    void submitRegistration();
    
    void getCDetails();
    
    void formProgramCommittee();
    
    void displayMenu();
    
    void options();
    
    bool Run();
    
protected:
    
    //deconstructor
    ~Conference();
    
    //constructor
    Conference();
    
    // validate data before upload
    // update mysql
    void Update();
    
private:
    
    // do not implement
    Conference (Conference const &);
    void operator=(const Conference&);
    
    static Conference* instance;
    
    /////////////////////////////////
    // Conference Specific Data
    //
    CDetails* cdetails;
    bool running;
};

//constructor
inline Conference::Conference()
{
    running = true;
    cdetails = 0;
}

// deconstructor
inline Conference::~Conference()
{
    if( instance != 0 )
    {
        delete instance;
        instance = 0;
    }
    
    if( cdetails != 0 )
    {
        delete cdetails;
        cdetails = 0;
    }
}



#endif /* defined(___2Proj__Conference__) */
