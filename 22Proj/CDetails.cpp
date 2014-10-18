/*
 CSCI 222
 DDMMN2014
 CDetails header file
 */

#include "CDetails.h"
#include <iostream>

CDetails::CDetails(std::string _startTime, std::string _endTime, std::string _startCallForPapers, std::string _endCallForPapers, std::string _location)
{
    startTime = _startTime;
    endTime = _endTime;
    startCallForPapers = _startCallForPapers;
    endCallForPapers = _endCallForPapers;
    location = _location;
}

CDetails::~CDetails()
{
    
}

std::string CDetails::getStartTime()
{
    return startTime;
}

std::string CDetails::getEndTime()
{
    return endTime;
}
std::string CDetails::getStartCallForPapers()
{
    return startCallForPapers;
}

std::string CDetails::getEndCallForPapers()
{
    return endCallForPapers;
}

std::string CDetails::getLocation()
{
    return location;
}
