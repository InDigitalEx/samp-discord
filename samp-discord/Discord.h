#pragma once
#include <discord_rpc.h>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

class Discord
{
private:
	DiscordRichPresence presence;
public:
	Discord(const char* applicationId);
	~Discord();
	void edit(const char* state, const char* details, const char* largeImageKey,
		const char* largeImageText, const char* smallImageKey, const char* smallImageText);
	void clear();
	void update();
	void updateTime(time_t time);
};

