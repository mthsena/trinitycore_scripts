#include "ServerAnnounce.h"

void ServerAnnounce::AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason)
{
        std::string author = tempAuthor;
        std::string reason = tempReason;
        std::string temp = "|cFFFF0000" + target + "|r was |cFFFF0000perma banhammered|r by |cFFFFFFFF" + author + "|r! Reason: " + reason;
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}

void ServerAnnounce::AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason, std::string duration)
{
        std::string author = tempAuthor;
        std::string reason = tempReason;
        std::string temp = "|cFFFF0000" + target + "|r was |cFFFF0000banhammered|r for |cFFFF0000" + duration + "|r by |cFFFFFFFF" + author + "|r! Reason: " + reason;
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}

void ServerAnnounce::AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason)
{
        std::string author = tempAuthor;
        std::string temp = "|cFFFF5900" + target + "|r was |cFFFF5900perma muted|r by |cFFFFFFFF" + author + "|r! Reason: " + reason;
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}

void ServerAnnounce::AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason, std::string duration)
{
        std::string author = tempAuthor;
        std::string temp = "|cFFFF5900" + target + "|r was |cFFFF5900muted|r for |cFFFF5900" + duration + "|r by |cFFFFFFFF" + author + "|r! Reason: " + reason;
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}

void ServerAnnounce::AnnounceKick(const char * tempAuthor, std::string & target)
{
        std::string author = tempAuthor;
        std::string temp = "|cFFFF7A00" + target + "|r was |cFFFF7A00kicked|r by |cFFFFFFFF" + author + "|r!";
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}

void ServerAnnounce::AnnounceKick(const char * tempAuthor, std::string & target, std::string & reason)
{
        std::string author = tempAuthor;
        std::string temp = "|cFFFFB300" + target + "|r was |cFFFFB300kicked|r by |cFFFFFFFF" + author + "|r! Reason: " + reason;
        sWorld->SendServerMessage(SERVER_MSG_STRING, temp.c_str());
}