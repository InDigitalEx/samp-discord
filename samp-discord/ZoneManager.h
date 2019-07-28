#pragma once
#include <vector>
#include <string>

using namespace std;

struct Area
{
	float aX;
	float aY;
	float aZ;
	float bX;
	float bY;
	float bZ;
};

class ZoneManager
{
private:
	vector<string> _cityName;
	vector<Area> _cityCoords;
	vector<string> _zoneName;
	vector<Area> _zoneCoords;
public:
	ZoneManager();
	void AddCity(string name, float aX, float aY, float aZ, float bX, float bY, float bZ);
	void AddZone(string name, float aX, float aY, float aZ, float bX, float bY, float bZ);
	string GetCity(float x, float y, float z);
	string GetZone(float x, float y, float z);
};

