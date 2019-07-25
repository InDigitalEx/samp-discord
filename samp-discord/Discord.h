#pragma once
#include <discord_rpc.h>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

class Discord
{
private:
	DiscordRichPresence _presence;
public:
	Discord(const char* applicationId);
	~Discord();
	void Edit(const char* state, const char* details, const char* largeImageKey,
		const char* largeImageText, const char* smallImageKey, const char* smallImageText);
	void Clear();
	void Update();
	void UpdateTime(time_t time);
};

