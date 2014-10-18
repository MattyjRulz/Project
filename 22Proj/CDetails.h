/*
 CSCI 222
 DDMMN2014
 CDetails header file
 */

#ifndef CDETAILS_H
#define CDETAILS_H

#include <string>

class CDetails
{
public:
    
    CDetails(std::string _startTime,
             std::string _endTime,
             std::string _startCallForPapers,
             std::string _endCallForPapers,
             std::string _location);
    ~CDetails();
    
    std::string getStartTime();
    std::string getEndTime();
    std::string getStartCallForPapers();
    std::string getEndCallForPapers();
    std::string getLocation();
    
    void Display();
    
private:
    
    std::string startTime;
    std::string endTime;
    std::string startCallForPapers;
    std::string endCallForPapers;
    std::string location;
    
};

#endif
