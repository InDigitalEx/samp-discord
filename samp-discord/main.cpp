#include <Windows.h>
#include <time.h>
#include "Discord.h"
#include "main.h"

using namespace std;

SAMPFUNCS* SF = new SAMPFUNCS();
Discord* discord;

bool sfInitialized = false;
bool discordInitialized = false;

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

void GetGameStateName(string& name)
{
	switch (SF->getSAMP()->getInfo()->iGameState)
	{
	case GAMESTATE_WAIT_CONNECT: name = "Wait connect"; return;
	case GAMESTATE_DISCONNECTED: name = "Disconnected"; return;
	case GAMESTATE_CONNECTED: name = "Connected"; return;
	case GAMESTATE_AWAIT_JOIN: name = "Await join"; return;
	case GAMESTATE_RESTARTING: name = "Restarting"; return;
	default:
		name = "None";
		return;
	}
}

void GetStateText(string& state_text)
{
	// Get local vehicle id
	uint16_t playerVehId = SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID;

	// If in background
	if (!SF->getGame()->isGTAForeground() || SF->getGame()->isGTAMenuActive())
	{
		state_text = "AFK";
	}
	// if player in vehicle
	else if (
		SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped->state == 50 && // State 50 - Veh driver
		SF->getSAMP()->getVehicles()->pSAMP_Vehicle[playerVehId] != NULL &&
		SF->getSAMP()->getVehicles()->pSAMP_Vehicle[playerVehId]->pGTA_Vehicle != NULL)
	{
		// Get vehilce name
		string vehicle = Vehicles[SF->getSAMP()->getVehicles()->pSAMP_Vehicle[SF->getSAMP()->getPlayers()->pLocalPlayer->inCarData.sVehicleID]->pGTA_Vehicle->base.model_alt_id - 400];
		
		// Build string
		state_text = "In vehicle (" + vehicle + ")";
	}
	else GetGameStateName(state_text);
}

void GetLargeText(string& large_text)
{
	actor_info* ped = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;

	// Get server name
	large_text = SF->getSAMP()->getPlayers()->szLocalPlayerName;

	// Build string
	large_text +=	" (Health: " + to_string(static_cast<int>(ped->hitpoints)) +
					"/" + to_string(static_cast<int>(ped->hitpoints_max));
	if (ped->armor > 0)
		large_text += " Armor: " + to_string(static_cast<int>(ped->armor)) + "/100";
	large_text += ")";
}

void GetSmallText(string& small_text)
{
	actor_info* ped = SF->getSAMP()->getPlayers()->pLocalPlayer->pSAMP_Actor->pGTA_Ped;
	string weapon = Weapons[SF->getSAMP()->getPlayers()->pLocalPlayer->byteCurrentWeapon];

	//Build string
	small_text =
		"Weapon: " + weapon +
		" Score: " + to_string(SF->getSAMP()->getPlayers()->iLocalPlayerScore) +
		" Ping: " + to_string(SF->getSAMP()->getPlayers()->iLocalPlayerPing);
}

// Threads
static void DiscordThread()
{
	discord = new Discord(DISCORD_GAME_ID);

	while (true)
	{
		if (!sfInitialized)
			continue;

		if (!discordInitialized)
		{
			discord->updateTime(time(0));

			discordInitialized = true;
			Sleep(200);
		}
		string state, largeText, smallText;

		GetStateText(state);
		GetLargeText(largeText);
		GetSmallText(smallText);

		discord->edit(state.c_str(), SF->getSAMP()->getInfo()->szHostname,
			"sa_big_img", largeText.c_str(), "unlocked", smallText.c_str());

		discord->update();

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
			SF->getSAMP()->getChat()->AddChatMessage(0x086DCC, "Discord Additional by InDigital");
			return;
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		SF->initPlugin(MainLoop, hModule);
		return CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DiscordThread), 0, 0, 0) > 0;
	}

	if (dwReasonForCall == DLL_PROCESS_DETACH) {
		delete discord;
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	}
	return TRUE;
}
