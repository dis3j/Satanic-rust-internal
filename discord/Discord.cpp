#include "Discord.h"
#include <time.h>
#include <lmcons.h>
#include <string>
#include "disrpc/Includes/discord_rpc.h"
//#include <vars.h>
void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("1118099595248017408", &Handle, 1, NULL);
}


void Discord::Update()
{
    char name[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(name, &username_len);
    std::string winname = name;

    std::string secret = "User: ";

    std::string state = secret + winname/*"Playing Rust"*/;
    DiscordRichPresence discord;
    memset(&discord, 0, sizeof(discord));



    discord.details = state.c_str()/*"Playing Rust"*/;
    discord.state = "Playing Rust";
    discord.startTimestamp = time(0);
    discord.largeImageKey = "Satanicplimordial";
    discord.largeImageText = "discord.gg/VezxSmUMsn";
    discord.smallImageKey = "rust_icon";//Satanic
    Discord_UpdatePresence(&discord);
}
//Discord_Shutdown
void Discord::Shutdown()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Shutdown();
}