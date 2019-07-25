#include "discord.h"

Discord::Discord(const char* applicationId)
{
	Discord_Initialize(applicationId, NULL, 0, NULL);
	memset(&this->_presence, 0, sizeof(this->_presence));
}

Discord::~Discord()
{
	this->Clear();
	Discord_Shutdown();
}

void Discord::Edit(const char* state, const char* details, const char* largeImageKey,
	const char* largeImageText, const char* smallImageKey, const char* smallImageText)
{
	this->_presence.state = state;
	this->_presence.details = details;
	this->_presence.largeImageKey = largeImageKey;
	this->_presence.largeImageText = largeImageText;
	this->_presence.smallImageKey = smallImageKey;
	this->_presence.smallImageText = smallImageText;
}

void Discord::Clear()
{
	Discord_ClearPresence();
}

void Discord::Update()
{
	Discord_UpdatePresence(&this->_presence);
}

void Discord::UpdateTime(time_t time)
{
	this->_presence.startTimestamp = time;
}
