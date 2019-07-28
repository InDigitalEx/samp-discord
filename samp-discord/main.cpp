#include <Windows.h>
#include <time.h>
#include "Discord.h"
#include "ZoneManager.h"
#include "main.h"

using namespace std;

SAMPFUNCS* SF = new SAMPFUNCS();
Discord* discord;
ZoneManager* zone = new ZoneManager();

bool sfInitialized = false;
bool discordInitialized = false;
DWORD afkTimer = NULL;

const char* Weapons[] =
{
	{ "Fist" },
	{ "Brass Knuckles" },
	{ "Golf Club" },
	{ "Nitestick" },
	{ "Knife" },
	{ "Baseball Bat" },
	{ "Shovel" },
	{ "Pool Cue" },
	{ "Katana" },
	{ "Chainsaw" },
	{ "Dildo 1" },
	{ "Dildo 2" },
	{ "Vibe 1" },
	{ "Vibe 2" },
	{ "Flowers" },
	{ "Cane" },
	{ "Grenade" },
	{ "Teargas" },
	{ "Molotov Cocktail" },
	{ "NULL" },
	{ "NULL" },
	{ "NULL" },
	{ "Pistol" },
	{ "Silenced Pistol" },
	{ "Desert Eagle" },
	{ "Shotgun" },
	{ "Sawn-Off Shotgun" },
	{ "SPAZ12" },
	{ "Micro UZI" },
	{ "MP5" },
	{ "AK47" },
	{ "M4" },
	{ "Tech9" },
	{ "Country Rifle" },
	{ "Sniper Rifle" },
	{ "Rocket Launcher" },
	{ "Heat Seeking RPG" },
	{ "Flame Thrower" },
	{ "Minigun" },
	{ "Remote Explosives" },
	{ "Detonator" },
	{ "Spray Can" },
	{ "Fire Extinguisher" },
	{ "Camera" },
	{ "NV Goggles" },
	{ "IR Goggles" },
	{ "Parachute" }
};

const char* Vehicles[] =
{
	{ "Landstalker" },
	{ "Bravura" },
	{ "Buffalo" },
	{ "Linerunner" },
	{ "Perrenial" },
	{ "Sentinel" },
	{ "Dumper" },
	{ "Firetruck" },
	{ "Trashmaster" },
	{ "Stretch" },
	{ "Manana" },
	{ "Infernus" },
	{ "Voodoo" },
	{ "Pony" },
	{ "Mule" },
	{ "Cheetah" },
	{ "Ambulance" },
	{ "Leviathan" },
	{ "Moonbeam" },
	{ "Esperanto" },
	{ "Taxi" },
	{ "Washington" },
	{ "Bobcat" },
	{ "MrWhoopee" },
	{ "BFInjection" },
	{ "Hunter" },
	{ "Premier" },
	{ "Enforcer" },
	{ "Securicar" },
	{ "Banshee" },
	{ "Predator" },
	{ "Bus" },
	{ "Rhino" },
	{ "Barracks" },
	{ "Hotknife" },
	{ "Trailer1" },
	{ "Previon" },
	{ "Coach" },
	{ "Cabbie" },
	{ "Stallion" },
	{ "Rumpo" },
	{ "RCBandit" },
	{ "Romero" },
	{ "Packer" },
	{ "Monster" },
	{ "Admiral" },
	{ "Squalo" },
	{ "Seasparrow" },
	{ "Pizzaboy" },
	{ "Tram" },
	{ "Trailer2" },
	{ "Turismo" },
	{ "Speeder" },
	{ "Reefer" },
	{ "Tropic" },
	{ "Flatbed" },
	{ "Yankee" },
	{ "Caddy" },
	{ "Solair" },
	{ "BerkleyRCVan" },
	{ "Skimmer" },
	{ "PCJ-600" },
	{ "Faggio" },
	{ "Freeway" },
	{ "RCBaron" },
	{ "RCRaider" },
	{ "Glendale" },
	{ "Oceanic" },
	{ "Sanchez" },
	{ "Sparrow" },
	{ "Patriot" },
	{ "Quad" },
	{ "Coastguard" },
	{ "Dinghy" },
	{ "Hermes" },
	{ "Sabre" },
	{ "Rustler" },
	{ "ZR-350" },
	{ "Walton" },
	{ "Regina" },
	{ "Comet" },
	{ "BMX" },
	{ "Burrito" },
	{ "Camper" },
	{ "Marquis" },
	{ "Baggage" },
	{ "Dozer" },
	{ "Maverick" },
	{ "NewsChopper" },
	{ "Rancher" },
	{ "FBIRancher" },
	{ "Virgo" },
	{ "Greenwood" },
	{ "Jetmax" },
	{ "Hotring" },
	{ "Sandking" },
	{ "Blista Compact" },
	{ "Police Maverick" },
	{ "Boxville" },
	{ "Benson" },
	{ "Mesa" },
	{ "RCGoblin" },
	{ "HotringRacer A" },
	{ "HotringRacer B" },
	{ "BloodringBanger" },
	{ "Rancher" },
	{ "SuperGT" },
	{ "Elegant" },
	{ "Journey" },
	{ "Bike" },
	{ "MountainBike" },
	{ "Beagle" },
	{ "Cropdust" },
	{ "Stunt" },
	{ "Tanker" },
	{ "Roadtrain" },
	{ "Nebula" },
	{ "Majestic" },
	{ "Buccaneer" },
	{ "Shamal" },
	{ "Hydra" },
	{ "FCR-900" },
	{ "NRG-500" },
	{ "HPV1000" },
	{ "CementTruck" },
	{ "TowTruck" },
	{ "Fortune" },
	{ "Cadrona" },
	{ "FBITruck" },
	{ "Willard" },
	{ "Forklift" },
	{ "Tractor" },
	{ "Combine" },
	{ "Feltzer" },
	{ "Remington" },
	{ "Slamvan" },
	{ "Blade" },
	{ "Freight" },
	{ "Streak" },
	{ "Vortex" },
	{ "Vincent" },
	{ "Bullet" },
	{ "Clover" },
	{ "Sadler" },
	{ "FiretruckLA" },
	{ "Hustler" },
	{ "Intruder" },
	{ "Primo" },
	{ "Cargobob" },
	{ "Tampa" },
	{ "Sunrise" },
	{ "Merit" },
	{ "Utility" },
	{ "Nevada" },
	{ "Yosemite" },
	{ "Windsor" },
	{ "MonsterA" },
	{ "MonsterB" },
	{ "Uranus" },
	{ "Jester" },
	{ "Sultan" },
	{ "Stratum" },
	{ "Elegy" },
	{ "Raindance" },
	{ "RC Tiger" },
	{ "Flash" },
	{ "Tahoma" },
	{ "Savanna" },
	{ "Bandito" },
	{ "FreightFlat" },
	{ "StreakCarriage" },
	{ "Kart" },
	{ "Mower" },
	{ "Duneride" },
	{ "Sweeper" },
	{ "Broadway" },
	{ "Tornado" },
	{ "AT-400" },
	{ "DFT-30" },
	{ "Huntley" },
	{ "Stafford" },
	{ "BF-400" },
	{ "Newsvan" },
	{ "Tug" },
	{ "Trailer 3" },
	{ "Emperor" },
	{ "Wayfarer" },
	{ "Euros" },
	{ "Hotdog" },
	{ "Club" },
	{ "FreightCarriage" },
	{ "Trailer3" },
	{ "Andromada" },
	{ "Dodo" },
	{ "RCCam" },
	{ "Launch" },
	{ "PoliceCar(LSPD)" },
	{ "PoliceCar(SFPD)" },
	{ "PoliceCar(LVPD)" },
	{ "PoliceRanger" },
	{ "Picador" },
	{ "S.W.A.T.Van" },
	{ "Alpha" },
	{ "Phoenix" },
	{ "Glendale" },
	{ "Sadler" },
	{ "LuggageTrailerA" },
	{ "LuggageTrailerB" },
	{ "StairTrailer" },
	{ "Boxville" },
	{ "FarmPlow" },
	{ "UtilityTrailer" }
};

int32_t GetAmmoInClip()
{
	return PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->GetAmmoInClip();
}

int32_t GetAmmoTotal()
{
	return PEDSELF->GetWeapon(PEDSELF->GetCurrentWeaponSlot())->GetAmmoTotal();
}

void GetStateText(string& state_text)
{
	if (SF->getSAMP()->getPlayers()->pLocalPlayer->iIsActorAlive)
	{
		if (SF->getSAMP()->getPlayers()->pLocalPlayer->byteCurrentInterior != 0)
		{
			state_text = "In interior";
		}
		else
		{
			CVector* pos = PEDSELF->GetPosition();
			state_text = zone->GetCity(pos->fX, pos->fY, pos->fZ) + " | " + zone->GetZone(pos->fX, pos->fY, pos->fZ);
		}

		stSAMPVehicle* playerVehicle = SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID];
		
		// If player in vehicle
		if (SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->state == 50 // 50 is the position in car
			&& playerVehicle != NULL && playerVehicle->pGTA_Vehicle != NULL)
		{
			string vehicleName = Vehicles[playerVehicle->pGTA_Vehicle->base.model_alt_id - 400]; // 400 is an offset
			state_text += " (Drive " + vehicleName + ")";
		}
	}
	// Show connect statement
	else
	{
		switch (SF->getSAMP()->getInfo()->iGameState)
		{
		case GAMESTATE_WAIT_CONNECT: state_text = "Wait connect"; return;
		case GAMESTATE_DISCONNECTED: state_text = "Disconnected"; return;
		case GAMESTATE_CONNECTED: state_text = "Connected"; return;
		case GAMESTATE_AWAIT_JOIN: state_text = "Await join"; return;
		case GAMESTATE_RESTARTING: state_text = "Restarting"; return;
		default: {
			state_text = "None";
			return;
		}
		}
	}

	// If in background
	if (!SF->getGame()->isGTAForeground() || SF->getGame()->isGTAMenuActive())
	{
		// If before game was active - set timer to current time
		if (afkTimer == NULL)
		{
			afkTimer = GetTickCount();
		}
		state_text.insert(0, "[AFK " + to_string((GetTickCount() - afkTimer) / 1000) + " s.] ");
	}
	else
	{
		// Else game is active - reset timer
		afkTimer = NULL;
	}
}

void GetLargeText(string& large_text)
{
	// Declare a local ped for quick reference
	actor_info* ped = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;

	// Get local player name
	large_text = SF->getSAMP()->getPlayers()->szLocalPlayerName;

	// Gamestate is connected because ped isn't yet spawned
	if (SF->getSAMP()->getInfo()->iGameState == GAMESTATE_CONNECTED)
	{
		large_text +=
			"[" + to_string(SF->getSAMP()->getPlayers()->sLocalPlayerID) + "]" +
			" (Health: " + to_string(static_cast<int>(ped->hitpoints)) +
			"/" + to_string(static_cast<int>(ped->hitpoints_max));

		if (ped->armor > 0)
		{
			large_text += " Armor: " + to_string(static_cast<int>(ped->armor)) + "/100";
		}
		large_text += ")";
	}
}

void GetSmallText(string& small_text)
{
	actor_info* ped = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;
	string pedWeapon = Weapons[SF->getSAMP()->getPlayers()->pLocalPlayer->byteCurrentWeapon];

	small_text = ""; // Nullified because the text will be displayed
	if (SF->getSAMP()->getInfo()->iGameState == GAMESTATE_CONNECTED)
	{
		small_text = "Active weapon: " + pedWeapon;

		int32_t ammoClip = GetAmmoInClip();
		int32_t	ammoTotal = GetAmmoTotal();

		if (ammoClip > 0 || ammoTotal > 0)
		{
			// If weapon is single-shot
			if (ammoClip == 1)
			{
				small_text += "(" + to_string(ammoTotal) + ")";
			}
			// With clip
			else
			{
				small_text += "(" + to_string(ammoTotal-ammoClip) + "/" + to_string(ammoClip) + ")";
			}
		}
			
	}
}

// Threads
static void DiscordThread()
{
	discord = new Discord(DISCORD_GAME_ID);

	while (true)
	{
		if (!sfInitialized) {
			Sleep(100); // Waiting for initialization
			continue;
		}
			

		if (!discordInitialized)
		{
			discord->UpdateTime(time(0));

			discordInitialized = true;
			Sleep(200); // For reliability
		}

		string stateText, largeText, smallText;
		GetStateText(stateText);
		GetLargeText(largeText);
		GetSmallText(smallText);

		discord->Edit(
			stateText.c_str(),
			SF->getSAMP()->getInfo()->szHostname,
			"sa_big_img",
			largeText.c_str(),
			"unlocked",
			smallText.c_str());

		discord->Update();
		Sleep(500);
	}
}

void __stdcall MainLoop()
{
	if (!sfInitialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			sfInitialized = true;
			SF->getSAMP()->getChat()->AddChatMessage(0xFF0000, "Discord {FF7F00}Additional {FFFF00}by {00FF00}InDigital");
			return;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) {
		SF->initPlugin(MainLoop, hModule);
		return CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DiscordThread), 0, 0, 0) > 0;
	}

	if (dwReasonForCall == DLL_PROCESS_DETACH) {
		delete discord;
		TerminateThread(DiscordThread, EXIT_SUCCESS);
	}
	return TRUE;
}
