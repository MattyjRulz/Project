#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include "InternalMessage.h"
using namespace std;

InternalMessage::InternalMessage(string _address)
{
    address = _address;
}

InternalMessage::~InternalMessage()
{
    pastMSGs.clear();
}

void InternalMessage::sendMSG(string to, string message, string attachment = "")
{
    MessageType newMessage;
    newMessage.fromAddress = address;
    newMessage.toAddress = to;
    newMessage.message = message;
    newMessage.attachment = attachment;
    newMessage.isRead = false;
    //add message to the database
    
}

void InternalMessage::displayMSGs()
{
    // read messages from DB
    bool exit =false, innerExit;
    char command;
    int count = 1;
    vector<MessageType>::iterator itr = pastMSGs.begin();
    while(!exit)
    {
        cout << endl;
        if(!(*itr).isRead)
            cout << "New!!! " << endl;
        innerExit=false;
        cout << "Message " << count << " of " << getNumOfMessages() << endl;
        cout << "From: " << (*itr).fromAddress << endl;
        cout << "Message: " << endl;
        cout << (*itr).message << endl;
        cout << endl;
        cout << "(m)ark as read  ";
        itr++;
        if(itr!=pastMSGs.end())
            cout << "(n)ext  ";
        itr--;
        if(itr!=pastMSGs.begin())
            cout << "(p)revious  ";
        cout << "(e)xit" << endl;
        while(!innerExit)
        {
            cin >> command;
            cin.ignore(1000,'\n');
            switch(tolower(command))
            {
                case 'm':
                    innerExit=true;
                    (*itr).isRead=true;
                    break;
                case 'n':
                    itr++;
                    if(itr!=pastMSGs.end())
                    {
                        itr++;
                        count++;
                        innerExit=true;
                    }
                    itr--;
                    break;
                case 'p':
                    if(itr!=pastMSGs.begin())
                    {
                        itr--;
                        count--;
                        innerExit=true;
                    }
                    break;
                case 'e':
                    exit = true;
                    innerExit=true;
                    break;
                default:
                    break;
            }
        }
    }
    
}

int InternalMessage::getNumOfMessages()
{
    int numOfMessages = 0;
    
    vector<MessageType>::iterator itr = pastMSGs.begin();
    while(itr != pastMSGs.end())
    {
        numOfMessages++;
        itr++;
    }
    return numOfMessages;
}

int InternalMessage::getNumOfUnreadMessages()
{
    int numOfUnread = 0;
    vector<MessageType>::iterator itr = pastMSGs.begin();
    while(itr != pastMSGs.end())
    {
        if(!(*itr).isRead)
            numOfUnread++;
        itr++;
    }
    
    return numOfUnread;
}


void InternalMessage::addMessage(MessageType& _message)
{
    pastMSGs.push_back(_message);
}
