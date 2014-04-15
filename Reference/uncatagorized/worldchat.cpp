//
// Created By Papou AKA Hamar
// http://cruel-wow.com - Where pvp never rests
// Credits: Parranoia - Helping with Namelinks
// Credits: Iconskater92 - Modified from his base script.
// Credits: LilleCarl - Provided Item link bug fix - Thousand thanks.
// Do Not Re-Release without asking me for my permission
#include "ScriptPCH.h"
#include "Chat.h"
#include "Player.h"
#include "SystemConfig.h"
#include "Config.h"
#include "WorldSession.h"
void stringReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
    size_t pos = 0;
    while((pos = str.find(oldStr, pos)) != std::string::npos)
    {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

std::string command = ConfigMgr::GetStringDefault("WorldChat.command", "world"); // Command name
std::string CreatePlayerChat(uint64 guid)
{
	// Getting player name as string.
	Player * player = ObjectAccessor::FindPlayer(guid);
	std::string _name = player->GetName();
	
	// Getting Map name as string.
	Map * map = player->GetMap();
	std::string map_name = map->GetMapName();

	// Getting area name as string.
	WorldSession * session = player->GetSession();
	AreaTableEntry const * areaEntry = GetAreaEntryByAreaID(player->GetAreaId());
	int locale = session->GetSessionDbcLocale();
	std::string area_name = areaEntry->area_name[locale];
	
	// Getting properties from worldconf file.
	std::string map_color = ConfigMgr::GetStringDefault("WorldChannel.Map.Color", "");
	std::string player_color = ConfigMgr::GetStringDefault("WorldChat.Player.color", "|c1f40af20");
	std::string channel_name = ConfigMgr::GetStringDefault("WorldChannel.name", "World");
	std::string channel_color = ConfigMgr::GetStringDefault("WorldChannel.name.color", "");
	std::string chat_color = ConfigMgr::GetStringDefault("WorldChat.text.color", "");
	if(player->isGameMaster())
		player_color = ConfigMgr::GetStringDefault("WorldChat.Staff.color", "|cff0404B4");
	

	if(sWorld->getIntConfig(CONFIG_WORLD_CHAT_MAP_ENABLED) == 0)
		return channel_color+"["+channel_name+"]|r|Hplayer:"+_name+"|h"+player_color+" ["+_name+"]|h|r says:"+chat_color;
	
	else if (sWorld->getIntConfig(CONFIG_WORLD_CHAT_MAP_ENABLED) == 2)
		return channel_color+"["+channel_name+"]|r "+map_color+"["+area_name+"]|r|Hplayer:"+_name+"|h"+player_color+" ["+_name+"]|h|r says: "+chat_color;
	
	else // We can assume that it's 1 or some other number.
		return channel_color+"["+channel_name+"]|r "+map_color+"["+map_name+"]|r|Hplayer:"+_name+"|h"+player_color+" ["+_name+"]|h|r says: "+chat_color;
}

class cs_world_chat : public CommandScript
{
public:
	cs_world_chat() : CommandScript("cs_world_chat"){}
	ChatCommand * GetCommands() const
	{
		static ChatCommand WorldChatCommandTable[] =
		{
			{command.c_str(),        SEC_PLAYER,             true,           &HandleWorldChatCommand,        "", NULL},
			{NULL,       0,                      false,          NULL,                           "", NULL}
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		if(sWorld->getIntConfig(CONFIG_WORLD_CHAT_ENABLED) == 0)
		{
			handler->PSendSysMessage("World chat is disabled");
			handler->SetSentErrorMessage(true);
			return false;
		}
		if (!handler->GetSession()->GetPlayer()->CanSpeak())
			return false;
		std::string temp = args;

		if (!args || temp.find_first_not_of(' ') == std::string::npos)
			return false;
		
		// Item link bug fix THANKS TO LILLECARL <3 <3 <3 <3
		std::string color_replace = ConfigMgr::GetStringDefault("WorldChat.text.color", "").c_str();
		stringReplace(temp, "|r", color_replace);

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();
		msg += CreatePlayerChat(player->GetGUID());
		msg += temp;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
		return true;
	}
};

void AddSC_custom_world_chat()
{
	new cs_world_chat();
}
