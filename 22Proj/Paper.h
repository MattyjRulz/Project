/*
 CSCI222
 DDMMN2014
 paper header file
 */

#ifndef PAPER_H
#define PAPER_H

#include <vector>
#include <string>

class Paper
{
public:
    
    //      uniqueID set inside, check with the database how many
    //          papers there are already
    //      outcome set to false
    //      set dateSubmitted within function (dateSubmitted = getDate();)
    //      validate withHeader, and withoutHeader (valid files and such)
    // store the hashed username with the paper submission for validation later
    // if someone other than the author of the paper tries to submit a final
    // copy it should be stopped.
    Paper(std::string WHeader, std::string WOHeader);
    ~Paper();
    
    // the PC Chairs are the only people who have access to this
    // validate them inside the function
    void setOutcome(bool _outcome);
    
    // reviewees should not be the author
    // a reviewee is reviewing this paper, and submitting a review
    // a reviewer will have a uniquePaperID to use to submit a comment
    void submitReviewComment(std::string review);
    
    // check author with database, author username should be stored
    //      with paper for validation
    // author calls User::submitFinalCopy(string withHeader)
    // display error if the submit happens after endCallForPapers
    //      and do not submit
    void submitFinalCopy(std::string _finalCopy);
    
private:
    
    std::string withHeader;
    std::string withoutHeader;
    std::string finalCopy;
    
    std::vector<std::string> keywords;
    std::vector<std::string> reviewsComments;
    std::string dateSubmitted;
    bool outcome;
    
    unsigned int uniqueID;
};

#endif
