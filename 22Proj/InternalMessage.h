#include <vector>
#include <string>
#ifndef __INTERNAL_MESSAGE_
#define __INTERNAL_MESSAGE_

struct MessageType
{
    std::string fromAddress;
    std::string toAddress;
    std::string message;
    std::string attachment;
    bool isRead;
};
class InternalMessage
{
public:
    InternalMessage(std::string _address);
    ~InternalMessage();
    void sendMSG(std::string , std::string ,std::string );
    // Get number of messages
    int getNumOfMessages();
    // Get number of unread messages
    int getNumOfUnreadMessages();
    // from most recent to oldest
    // press a key to mark as read
    // press a key to go to next
    // escape at any time by pressing esc?
    void displayMSGs();
    // Add a message type to pastMSGs
    void addMessage(MessageType& );
private:
    std::string address;
    std::vector<MessageType> pastMSGs;
};

#endif 

