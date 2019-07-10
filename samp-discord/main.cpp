#include <Windows.h>
#include <time.h>
#include <string.h>
#include <discord_rpc.h>
#include <discord_register.h>
#include "main.h"

using namespace std;

SAMPFUNCS *SF = new SAMPFUNCS();

bool sfInitialized = false;
bool threadInitialized = false;

static void DiscordThread()
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	while (true)
	{
		if (sfInitialized)
		{
			if (!threadInitialized)
			{
				Discord_Initialize(DISCORD_GAME_ID, NULL, 0, NULL);
				discordPresence.startTimestamp = time(0);
				threadInitialized = true;
				Sleep(200);
			}
			else
			{
				if (SF->getSAMP()->getInfo()->iGameState == GAMESTATE_CONNECTED)
				{
					// Получаем адрес сервера
					string serverAddress = static_cast<string>(SF->getSAMP()->getInfo()->szIP) + ":" + to_string(SF->getSAMP()->getInfo()->ulPort);

					// Записываем в структуру
					discordPresence.details = SF->getSAMP()->getInfo()->szHostname;
					discordPresence.largeImageText = serverAddress.c_str();
					discordPresence.smallImageKey = "unlocked";
					discordPresence.smallImageText = "";
				}
				else
				{
					discordPresence.details = "Waiting for connection...";
					discordPresence.largeImageText = "";
					discordPresence.smallImageKey = "locked";
					discordPresence.smallImageText = "";
				}

				discordPresence.largeImageKey = "sa_big_img";
				discordPresence.state = SF->getSAMP()->getPlayers()->szLocalPlayerName;

				Discord_UpdatePresence(&discordPresence);
				Sleep(15000); // Ждем, т.к инфа передается раз в 15 сек
			}
		}
	}
}

void __stdcall mainloop()
{
	if (!sfInitialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			sfInitialized = true;
			SF->getSAMP()->getChat()->AddChatMessage(0x086DCC, "Discord Additional by InDigital");
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		SF->initPlugin(mainloop, hModule);
		return CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DiscordThread), 0, 0, 0) > 0;
	}

	if (dwReasonForCall == DLL_PROCESS_DETACH) {
		Discord_Shutdown();
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	}
	return TRUE;
}
