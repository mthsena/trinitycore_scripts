#ifndef SERVER_ANNOUNCE_H_
#define SERVER_ANNOUNCE_H_
#include "Common.h"
#include "DatabaseEnv.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"

class ServerAnnounce
{
public:
/*
        static void AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason);
        static void AnnounceBan(const char * tempAuthor, std::string & target, const char * tempReason, std::string duration);
        static void AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason);
        static void AnnounceMute(const char * tempAuthor, std::string & target, std::string & reason, std::string duration);
        static void AnnounceKick(const char * tempAuthor, std::string & target);
        static void AnnounceKick(const char * tempAuthor, std::string & target, std::string & reason);
	*/
        static void AnnounceBan(const char* tempAuthor, std::string target, const char* tempReason);
        static void AnnounceBan(const char* tempAuthor, std::string target, const char* tempReason, std::string duration);
        static void AnnounceMute(const char* tempAuthor, std::string target, std::string reason);
        static void AnnounceMute(const char* tempAuthor, std::string target, std::string reason, std::string duration);
        static void AnnounceKick(const char* tempAuthor, std::string target);
        static void AnnounceKick(const char* tempAuthor, std::string target, std::string reason);
};
#endif