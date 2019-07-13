#include "discord.h"

Discord::Discord(const char* applicationId)
{
	Discord_Initialize(applicationId, NULL, 0, NULL);

	memset(&this->presence, 0, sizeof(this->presence));
}

Discord::~Discord()
{
	Discord_Shutdown();
}

void Discord::edit(const char* state, const char* details, const char* largeImageKey,
	const char* largeImageText, const char* smallImageKey, const char* smallImageText)
{
	this->presence.state = state;
	this->presence.details = details;
	this->presence.largeImageKey = largeImageKey;
	this->presence.largeImageText = largeImageText;
	this->presence.smallImageKey = smallImageKey;
	this->presence.smallImageText = smallImageText;
}

void Discord::clear()
{
	Discord_ClearPresence();
}

void Discord::update()
{
	Discord_UpdatePresence(&this->presence);
}

void Discord::updateTime(time_t time)
{
	this->presence.startTimestamp = time;
}
