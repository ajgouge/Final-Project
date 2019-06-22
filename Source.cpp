#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <chrono>
#include <cassert>
#include <cmath>
#include <SDL_ttf.h>

/*
	
	To-do:
	# -> finished
	- -> backlog
	> -> current projects

	Important things to do first:
	#Fix unloading/loading (units can't be unloaded after being loaded)
	-Pressing tab takes you to a unit that hasn't moved yet that turn
	-Holding a button shows a unit's danger zone; another button toggles full danger zones on all enemy units
	-Fog of War
	>Add animation
	-Way to change the level that doesn't break the game (level map? level select?)
	-Change capture mechanics to be more tactical (buildings have health, can be captured when they have none)
	-Weird bug where some red units capture red buildings and make them blue / turn them into other buildings
	-Potential bug with movement (teleportation?)
	>GUI overhaul (add menus to replace pressing lshift all the time, info around the map you can see, more fluid moving animations, etc)
	-Add extra commands to other units
	-Add extra layers (sky, underground) to make the game stand out
	-New mechanics / ideas to keep this from being an advance wars clone
	-Upgrade assets (Xander?)
	-Bridges, rivers, coasts, roads, etc change direction as they should rather than be a single tile with no direction
	-Level editor that makes a level file and can read other level files
	-AI
	-Multiple different resolutions
	-Minimap
	-Zoom feature
	>Other bugs as they pop up
	-Codex of units, their attacks, and their features that can be brought up mid-game
	-Window confirming you want to end your turn
	-Title sceen
	-Options menu
	-Thorough playtesting and balancing
	-Camera can scroll left/right as well, to make maps bigger or longer

	Possible new ideas:
	-Multiple map layers
	-Unit upgrades? (Need resources to be captured to upgrade? Extra cost? Unit EXP?)
		-Perhaps the upgraded version is purchased for extra at barracks/port/etc and takes longer to come out, AND the port/etc can't make anything else while it works on the upgraded unit
	-Different armies have different signature units
	-Builders construct terrain for your advantage -- each army has its own unique terrain it can build
	-Natural disasters (Telegraphed well in advance so it doesn't feel like a screwjob)
	-Tie the number of terrains you can build and the number of cities you have to each other (cities own terrain you make, not you)
	-Workers are spawned from the city the terrain they make will be owned by
	-Losing a city with terrain also loses you the terrain
	-

	New unit ideas:
	-Units that can also spawn other units (At a cost? For free, but there are only so many? HP cost?)
	-Builder units
	-Invisible unit that is given objectives and then sent off (uncontrollable until it attacks / is attacked)
	-Mech that is manned, has abilities/stats that are affected by the unit manning it (think Robobot Suit from Kirby)
	-

	New terrain ideas:
	-Mine that can be triggered to explode (Maybe not a good idea -- it offers no risk and the opponent can't combat it)
	-Mine that automatically explodes (Better idea -- Opponent can sweep for it with weak units, player could get backed into it)
	-Barricade that is impassible (Effective water tile)
	-Gunner that can be manned, does heavy damage at a range, has a recharge, can be destroyed
	-Turret that attacks enemies that enter its range, low damage, can be destroyed
	-

 */

//camera Offest by y value
int cameraY = 0;

//double tempAtk[] = { <percents written as decimals showing the attack modifier> };
//Unit <name> = new Unit(-1, -1, -1, <movement points>, <attack range>, <movement type>, <cost>, tempAtk, NULL, -1);

/* Enums */
// Mov Types
enum TYPE {
	FOOT = 0,
	BOOTS = 1,
	TREADS = 2,
	TIRES = 3,
	AIR = 4,
	SEA = 5,
	NUM_TYPES = 6,
	ERROR = -1
};

// Terrain Types
enum TERRAIN_TYPE {
	GRASS = 0,
	BRIDGE = 1,
	MOUNTAIN = 2,
	WATER = 3,
	ROAD = 4,
	PORT = 5,
	HQ = 6,
	AIRPORT = 7,
	BASE = 8,
	CITY = 9,
	REEF = 10,
	TREE = 11,
	SHORE = 12,
	RIVER = 13,
	PORT_RED = 14,
	HQ_RED = 15,
	AIRPORT_RED = 16,
	BASE_RED = 17,
	CITY_RED = 18,
	PORT_BLUE = 19,
	HQ_BLUE = 20,
	AIRPORT_BLUE = 21,
	BASE_BLUE = 22,
	CITY_BLUE = 23,
	NUM_TERRAIN = 24,
	TERRAIN_ERROR = -1
};


// Unit Types
enum UNIT_TYPE {
	INFANTRY = 0,
	MECH = 1,
	RECON = 2,
	APC = 3,
	ANTI_AIR = 4,
	ARTILLERY = 5,
	MISSILE = 6,
	ROCKET = 7,
	L_TANK = 8,
	M_TANK = 9,
	H_TANK = 10,
	B_COPTER = 11,
	T_COPTER = 12,
	FIGHTER = 13,
	BOMBER = 14,
	BATTLESHIP = 15,
	CRUISER = 16,
	SUB = 17,
	LANDER = 18,
	CARRIER = 19,
	NUM_UNITS = 20,
	UNIT_ERROR = -1
};


enum TEXTURE {
	T_GRASS = 0,
	T_BRIDGE = 1,
	T_MOUNTAIN = 2,
	T_WATER = 3,
	T_ROAD = 4,
	T_PORT = 5,
	T_HQ = 6,
	T_AIRPORT = 7,
	T_BASE = 8,
	T_CITY = 9,
	T_REEF = 10,
	T_TREE = 11,
	T_SHORE = 12,
	T_RIVER = 13,
	T_INFANTRY = 14,
	T_MECH = 15,
	T_RECON = 16,
	T_APC = 17,
	T_ANTI_AIR = 18,
	T_ARTILLERY = 19,
	T_MISSILE = 20,
	T_ROCKET = 21,
	T_L_TANK = 22,
	T_M_TANK = 23,
	T_H_TANK = 24,
	T_B_COPTER = 25,
	T_T_COPTER = 26,
	T_FIGHTER = 27,
	T_BOMBER = 28,
	T_BATTLESHIP = 29,
	T_CRUISER = 30,
	T_SUB = 31,
	T_LANDER = 32,
	T_CARRIER = 33,
	T_RED = 34,
	T_BLUE = 35,
	T_CURSOR_RED = 36,
	T_SELECT_RED = 37,
	T_TARGET_RED = 38,
	T_NULL = 39,
	T_CURSOR_BLUE = 40,
	T_SELECT_BLUE = 41,
	T_TARGET_BLUE = 42,
	T_HP_20_RED = 43,
	T_HP_18_RED = 44,
	T_HP_16_RED = 45,
	T_HP_14_RED = 46,
	T_HP_12_RED = 47,
	T_HP_10_RED = 48,
	T_HP_8_RED = 49,
	T_HP_6_RED = 50,
	T_HP_4_RED = 51,
	T_HP_2_RED = 52,
	T_HP_20_BLUE = 53,
	T_HP_18_BLUE = 54,
	T_HP_16_BLUE = 55,
	T_HP_14_BLUE = 56,
	T_HP_12_BLUE = 57,
	T_HP_10_BLUE = 58,
	T_HP_8_BLUE = 59,
	T_HP_6_BLUE = 60,
	T_HP_4_BLUE = 61,
	T_HP_2_BLUE = 62,
	T_PORT_BLUE = 63,
	T_HQ_BLUE = 64,
	T_AIRPORT_BLUE = 65,
	T_BASE_BLUE = 66,
	T_CITY_BLUE = 67,
	T_PORT_RED = 68,
	T_HQ_RED = 69,
	T_AIRPORT_RED = 70,
	T_BASE_RED = 71,
	T_CITY_RED = 72,
	NUM_TEXTURES = 73,
	T_ERROR = -1
};


/* Constants */
const int SCREEN_WIDTH = (int)(960*1.5);
const int SCREEN_HEIGHT = (int)(540*1.5);
const int MAP_X = 0;
const int MAP_Y = SCREEN_HEIGHT / 10;
const int MAP_W = SCREEN_WIDTH;
const int MAP_H = SCREEN_HEIGHT * 7 / 10;
const int TILE_SIDE = (int)(32*1.5);
const int MAP_TILE_W = 30;
const int MAP_TILE_H = 20;
// Map initializer arrays
const TERRAIN_TYPE testMap1[30][20] = {
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,ROAD,ROAD,BRIDGE,BRIDGE,BRIDGE,BRIDGE,ROAD,ROAD,CITY,GRASS,GRASS,HQ_RED,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,ROAD,SHORE,WATER,WATER,WATER,GRASS,BASE_RED,CITY_RED,CITY_RED,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,PORT,CITY,BASE,CITY,BASE,CITY,PORT,WATER,WATER,WATER,GRASS,BASE_RED,CITY_RED,CITY_RED,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,AIRPORT_RED,GRASS,GRASS,GRASS,CITY,CITY,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,SHORE,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,SHORE,TREE,TREE,TREE,TREE,TREE,SHORE,WATER,REEF,WATER,WATER,WATER,REEF,WATER,WATER,WATER,REEF},
{WATER,WATER,WATER,SHORE,CITY,CITY,CITY,CITY,CITY,SHORE,WATER,WATER,WATER,REEF,WATER,WATER,WATER,REEF,WATER,WATER},
{WATER,WATER,WATER,SHORE,CITY,CITY,CITY,CITY,CITY,SHORE,WATER,WATER,WATER,REEF,WATER,WATER,WATER,REEF,WATER,WATER},
{WATER,WATER,WATER,SHORE,TREE,TREE,TREE,TREE,TREE,SHORE,WATER,REEF,WATER,WATER,WATER,REEF,WATER,WATER,WATER,REEF},
{WATER,WATER,WATER,SHORE,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,AIRPORT_BLUE,GRASS,GRASS,GRASS,CITY, CITY,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,PORT,CITY,BASE,CITY,BASE,CITY,PORT,WATER,WATER,WATER,GRASS,BASE_BLUE,CITY_BLUE,CITY_BLUE,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,ROAD,SHORE,WATER,WATER,WATER,GRASS,BASE_BLUE,CITY_BLUE,CITY_BLUE,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,GRASS,GRASS,SHORE,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,SHORE,GRASS,GRASS,ROAD,ROAD,ROAD,BRIDGE,BRIDGE,BRIDGE,BRIDGE,ROAD,ROAD,CITY,GRASS,GRASS,HQ_BLUE,GRASS},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS},
};

TERRAIN_TYPE testMap2[30][20] = {
{MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN},
{GRASS,GRASS,GRASS,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD, ROAD,ROAD,GRASS,GRASS,GRASS},
{CITY,GRASS,BASE,ROAD,SHORE,SHORE,SHORE,SHORE,SHORE,TREE,TREE,SHORE,SHORE,SHORE,SHORE,SHORE,ROAD,BASE,GRASS,CITY},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,TREE,TREE,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,CITY,CITY,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,REEF,WATER,WATER,AIRPORT,AIRPORT,WATER,WATER,REEF,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{CITY,GRASS,CITY,ROAD,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,CITY,GRASS,CITY},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,REEF,WATER,WATER,REEF,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,REEF,WATER,WATER,WATER,WATER,REEF,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,REEF,REEF,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{CITY,GRASS,BASE,ROAD,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,BASE,GRASS,CITY},
{GRASS,GRASS,GRASS,ROAD,PORT,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,PORT,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,ROAD,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,ROAD,ROAD,GRASS,GRASS,GRASS},
{CITY_RED,GRASS,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,CITY,GRASS,GRASS,CITY_BLUE},
{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,SHORE,SHORE,CITY,TREE,TREE,CITY,SHORE,SHORE,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS},
{BASE_RED,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,SHORE,TREE,GRASS,GRASS,TREE,SHORE,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,BASE_BLUE},
{HQ_RED,GRASS,GRASS,GRASS,CITY_RED,SHORE,WATER,SHORE,GRASS,BASE,BASE,GRASS,SHORE,WATER,SHORE,CITY_BLUE,GRASS,GRASS,GRASS,HQ_BLUE},
{BASE_RED,GRASS,GRASS,GRASS,GRASS,SHORE,WATER,SHORE,TREE,GRASS,GRASS,TREE,SHORE,WATER,SHORE,GRASS,GRASS,GRASS,GRASS,BASE_BLUE},
{GRASS,GRASS,GRASS,GRASS,GRASS,SHORE,SHORE,SHORE,CITY,TREE,TREE,CITY,SHORE,SHORE,SHORE,GRASS,GRASS,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{CITY_RED,GRASS,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,CITY,GRASS,GRASS,CITY_BLUE},
{GRASS,GRASS,GRASS,ROAD,ROAD,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,BRIDGE,ROAD,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,GRASS,GRASS,GRASS},
{CITY,GRASS,CITY,ROAD,SHORE,WATER,REEF,WATER,WATER,WATER,WATER,WATER,WATER,REEF,WATER,SHORE,ROAD,CITY,GRASS,CITY},
{GRASS,GRASS,GRASS,ROAD,SHORE,SHORE,SHORE,SHORE,SHORE,PORT,PORT,SHORE,SHORE,SHORE,SHORE,SHORE,ROAD,GRASS,GRASS,GRASS},
{GRASS,GRASS,GRASS,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD, ROAD,ROAD,GRASS,GRASS,GRASS},
{MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN, MOUNTAIN},
};

TERRAIN_TYPE testMap3[30][20] = {
{BASE_BLUE,CITY_BLUE,WATER,WATER,REEF,WATER,REEF,WATER,REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,PORT_BLUE,ROAD,HQ_BLUE},
{CITY_BLUE,PORT_BLUE,WATER,REEF,WATER,REEF,WATER,REEF,WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,BASE_BLUE,ROAD,BASE_BLUE},
{WATER,WATER,WATER,WATER,REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{REEF,REEF,WATER,REEF,WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,CITY,ROAD,CITY},
{REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,CITY,ROAD,CITY},
{WATER,WATER,WATER,WATER,PORT,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,GRASS},
{WATER,WATER,WATER,WATER,GRASS,ROAD,TREE,TREE,TREE,TREE,TREE,GRASS,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,WATER,CITY,ROAD,TREE,GRASS,GRASS,GRASS,TREE,SHORE,SHORE,SHORE,SHORE,SHORE,PORT,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,GRASS,ROAD,TREE,GRASS,CITY,GRASS,TREE,WATER,WATER,WATER,WATER,WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,BASE,ROAD,TREE,GRASS,AIRPORT,GRASS,TREE,WATER,WATER,WATER,WATER,WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,BASE,ROAD,TREE,GRASS,AIRPORT,GRASS,TREE,WATER,WATER,WATER,WATER,WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,GRASS,ROAD,TREE,GRASS,CITY,GRASS,TREE,WATER,WATER,WATER,WATER,WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,CITY,ROAD,TREE,GRASS,GRASS,GRASS,TREE,SHORE,SHORE,SHORE,SHORE,SHORE,PORT,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,GRASS,ROAD,TREE,TREE,TREE,TREE,TREE,GRASS,GRASS,CITY,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
{WATER,WATER,WATER,WATER,PORT,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,GRASS},
{WATER,WATER,WATER,WATER,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,CITY,ROAD,CITY},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,CITY,ROAD,CITY},
{REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{REEF,REEF,WATER,REEF,WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS},
{CITY_RED,PORT_RED,WATER,REEF,WATER,REEF,WATER,REEF,WATER,REEF,REEF,WATER,WATER,WATER,WATER,WATER,WATER,BASE_RED,ROAD,BASE_RED},
{BASE_RED,CITY_RED,WATER,WATER,REEF,WATER,REEF,WATER,REEF,WATER,REEF,REEF,REEF,WATER,WATER,WATER,WATER,PORT_RED,ROAD,HQ_RED},
};

TERRAIN_TYPE testMap4[30][20] = {
{CITY,CITY,ROAD,MOUNTAIN,RIVER,MOUNTAIN,GRASS,AIRPORT_RED,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,TREE,TREE,RIVER,TREE,GRASS,CITY},
{CITY,CITY,ROAD,GRASS,RIVER,GRASS,ROAD,ROAD,ROAD,SHORE,SHORE,SHORE,SHORE,ROAD,ROAD,ROAD,BRIDGE,ROAD,ROAD,CITY},
{MOUNTAIN,GRASS,ROAD,MOUNTAIN,RIVER,MOUNTAIN,ROAD,GRASS,SHORE,WATER,WATER,WATER,WATER,ROAD,TREE,TREE,RIVER,TREE,BASE,CITY},
{MOUNTAIN,MOUNTAIN,ROAD,GRASS,RIVER,GRASS,ROAD,GRASS,SHORE,WATER,REEF,WATER,WATER,BRIDGE,RIVER,RIVER,RIVER,TREE,GRASS,CITY},
{MOUNTAIN,MOUNTAIN,ROAD,MOUNTAIN,RIVER,MOUNTAIN,ROAD,GRASS,SHORE,WATER,WATER,WATER,WATER,ROAD,ROAD,TREE,RIVER,TREE,TREE,TREE},
{WATER,WATER,BRIDGE,WATER,WATER,WATER,BRIDGE,WATER,WATER,WATER,SHORE,WATER,WATER,HQ_RED,ROAD,TREE,RIVER,RIVER,RIVER,RIVER},
{WATER,WATER,BRIDGE,WATER,WATER,WATER,BRIDGE,SHORE,WATER,WATER,PORT,WATER,WATER,BASE_RED,ROAD,TREE,TREE,TREE,TREE,TREE},
{WATER,GRASS,ROAD,GRASS,GRASS,GRASS,ROAD,PORT,SHORE,WATER,SHORE,WATER,WATER,CITY_RED,ROAD,GRASS,GRASS,TREE,TREE,TREE},
{WATER,GRASS,ROAD,ROAD,ROAD,ROAD,ROAD,GRASS,SHORE,WATER,WATER,WATER,WATER,BASE_RED,ROAD,GRASS,CITY,GRASS,TREE,TREE},
{WATER,GRASS,GRASS,CITY,ROAD,CITY,GRASS,GRASS,SHORE,WATER,REEF,WATER,WATER,CITY_RED,ROAD, ROAD,ROAD,ROAD,ROAD,TREE},
{WATER,WATER,WATER,WATER,BRIDGE,SHORE,SHORE,SHORE,WATER,WATER,WATER,WATER,WATER,BASE_RED,GRASS,GRASS,GRASS,GRASS,ROAD,GRASS},
{WATER,WATER,WATER,WATER,BRIDGE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,SHORE,SHORE,SHORE,SHORE,BRIDGE,WATER},
{WATER,WATER,WATER,WATER,BRIDGE,SHORE,SHORE,WATER,WATER,SHORE,SHORE,WATER,WATER,WATER,WATER,WATER,WATER,WATER,BRIDGE,WATER},
{WATER,WATER,GRASS,GRASS,ROAD,ROAD,ROAD,BRIDGE,BRIDGE,ROAD,CITY,PORT,SHORE,WATER,WATER,WATER,WATER,WATER,BRIDGE, WATER},
{WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,WATER,WATER,ROAD,GRASS,GRASS,SHORE,SHORE,SHORE,SHORE,SHORE,SHORE,BRIDGE,WATER},
{WATER,WATER,GRASS,GRASS,GRASS,GRASS,MOUNTAIN,WATER,WATER,ROAD,GRASS,TREE,MOUNTAIN,GRASS,GRASS,TREE,GRASS,GRASS,ROAD,GRASS},
{WATER,WATER,RIVER,RIVER,CITY,GRASS,MOUNTAIN,WATER,WATER,ROAD,TREE,GRASS,GRASS,TREE,GRASS,GRASS,MOUNTAIN,GRASS,ROAD,GRASS},
{WATER,WATER,CITY,RIVER,RIVER,RIVER,RIVER,WATER,WATER,ROAD,CITY,GRASS,TREE,GRASS,TREE,GRASS,TREE,GRASS,ROAD,GRASS},
{WATER,WATER,GRASS,GRASS,GRASS,GRASS,MOUNTAIN,WATER,WATER,ROAD,GRASS,MOUNTAIN,GRASS,GRASS,MOUNTAIN,GRASS,MOUNTAIN,GRASS,ROAD,CITY},
{WATER,WATER,GRASS,GRASS,GRASS,GRASS,MOUNTAIN,WATER,WATER,ROAD,GRASS,GRASS,GRASS,TREE,GRASS,CITY,GRASS,GRASS,ROAD,GRASS},
{WATER,WATER,ROAD,ROAD,ROAD,ROAD,ROAD,BRIDGE,BRIDGE,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,GRASS},
{WATER,WATER,BRIDGE,WATER,WATER,WATER,WATER,WATER,WATER,GRASS,ROAD,GRASS,GRASS,GRASS,ROAD,GRASS,GRASS,GRASS,ROAD,TREE},
{WATER,WATER,BRIDGE,WATER,REEF,REEF,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,ROAD,GRASS,GRASS,GRASS,ROAD,TREE},
{WATER,WATER,BRIDGE,WATER,REEF,REEF,WATER,GRASS,CITY,MOUNTAIN,ROAD,MOUNTAIN,CITY,GRASS,ROAD,GRASS,TREE,TREE,ROAD,TREE},
{WATER,WATER,BRIDGE,WATER,WATER,WATER,WATER,GRASS,CITY,MOUNTAIN,ROAD,MOUNTAIN,CITY,GRASS,ROAD,TREE,RIVER,RIVER,BRIDGE,RIVER},
{GRASS,MOUNTAIN,ROAD,GRASS,MOUNTAIN,WATER,WATER,MOUNTAIN,MOUNTAIN,MOUNTAIN,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,ROAD,TREE,RIVER,TREE,ROAD,TREE},
{GRASS,GRASS,ROAD,MOUNTAIN,GRASS,WATER, WATER, GRASS,GRASS,GRASS,ROAD,GRASS,GRASS,GRASS,ROAD,TREE,RIVER,TREE,ROAD,CITY},
{MOUNTAIN,MOUNTAIN,ROAD,ROAD,ROAD,BRIDGE,BRIDGE,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,TREE,RIVER,TREE,ROAD,CITY},
{CITY,CITY,ROAD,GRASS,MOUNTAIN,WATER,WATER,BASE,GRASS,GRASS,ROAD,GRASS,GRASS,AIRPORT_BLUE,GRASS,TREE,RIVER,TREE,BASE,CITY},
{CITY,CITY,ROAD,MOUNTAIN,GRASS,WATER,WATER,GRASS,BASE_BLUE,CITY_BLUE,HQ_BLUE,CITY_BLUE,BASE_BLUE,GRASS,GRASS,TREE,RIVER,TREE,GRASS,CITY},
};

TERRAIN_TYPE testMap5[30][20] = {
{WATER,TREE,GRASS,GRASS,CITY,GRASS,TREE,WATER,WATER,WATER,GRASS,TREE,GRASS,TREE,TREE,GRASS,TREE,TREE,GRASS,CITY},
{GRASS,CITY,TREE,CITY,GRASS,TREE,TREE,GRASS,WATER,GRASS,TREE,GRASS,CITY,GRASS,TREE,GRASS,GRASS,CITY,GRASS,GRASS},
{CITY,GRASS,GRASS,TREE,TREE,CITY,GRASS,GRASS,TREE,GRASS,CITY,GRASS,TREE,GRASS,CITY,TREE,GRASS,GRASS,TREE,TREE},
{GRASS,GRASS,TREE,CITY,GRASS,GRASS,CITY,TREE,GRASS,GRASS,CITY,TREE,GRASS,CITY,GRASS,TREE,CITY,GRASS,CITY,CITY},
{GRASS,CITY,TREE,TREE,GRASS,MOUNTAIN,MOUNTAIN,MOUNTAIN,GRASS,TREE,GRASS,TREE,GRASS,TREE,GRASS,CITY,TREE,TREE,GRASS,GRASS},
{GRASS,GRASS,GRASS,GRASS,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,GRASS,GRASS,CITY,CITY,GRASS,CITY,GRASS,GRASS,GRASS,TREE,GRASS,},
{TREE,GRASS,CITY_RED,TREE,BASE_RED,BASE_RED,MOUNTAIN,MOUNTAIN,MOUNTAIN,GRASS,TREE,GRASS,GRASS,WATER,WATER,WATER,WATER,WATER,GRASS,CITY},
{GRASS,GRASS,TREE,GRASS,MOUNTAIN,MOUNTAIN,MOUNTAIN,HQ_RED,MOUNTAIN,GRASS,GRASS,CITY,TREE,GRASS,WATER,WATER,WATER,GRASS,TREE,GRASS},
{CITY,GRASS,CITY_RED,GRASS,MOUNTAIN,MOUNTAIN,MOUNTAIN,PORT_RED,SHORE,SHORE,SHORE,GRASS,GRASS,CITY,TREE,WATER,GRASS,TREE,GRASS,GRASS},
{SHORE,TREE,GRASS,GRASS,MOUNTAIN,MOUNTAIN,MOUNTAIN,WATER,WATER,WATER,WATER,SHORE,GRASS,TREE,GRASS,WATER,GRASS,GRASS,CITY,WATER},
{WATER,SHORE,SHORE,SHORE,MOUNTAIN,MOUNTAIN,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,TREE,CITY,GRASS},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,ROAD,TREE,GRASS,TREE,},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,ROAD,GRASS,CITY_BLUE,TREE},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,TREE,CITY_BLUE,GRASS,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,BASE_BLUE,BASE_BLUE,MOUNTAIN,MOUNTAIN,MOUNTAIN},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,MOUNTAIN,MOUNTAIN,MOUNTAIN,MOUNTAIN,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,ROAD,MOUNTAIN,MOUNTAIN,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,PORT_BLUE,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,HQ_BLUE,WATER,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,ROAD,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,ROAD,ROAD,WATER,WATER,WATER,WATER,WATER,WATER},
{WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,WATER,SHORE,AIRPORT,AIRPORT,WATER,WATER,WATER,WATER,WATER,WATER},
};


class Tile;
class Terrain;
class Unit;
class metaTile;
class Mover;

/* Prototypes */
SDL_Window* init(SDL_Window* window);
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);
void close(SDL_Window* window);
void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
void reLayer(int input[], char effect, char cursorType);
void reRender(metaTile* one, metaTile* two, bool skipSecond);
void setCoord(int x, int y, char dir);
void createMap(); //debug
void initTerrain();
void initUnit();
void initMap(int i, int j, Terrain* t);
void initSpritesGround(int i, int j, Unit* u);
void cameraMove(char direction);
void updateFunds();
void updateText();
TERRAIN_TYPE getNewCapture(TEXTURE t, int team);
int getNumUnits(int team);


/* Classes */
// Tile class -- Used to store display information for each tile on the map
class Tile {
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* display = NULL;
	int x;
	int y;
	int terrain;
	int unit;
	TEXTURE source = T_ERROR;

public:
	Tile() : x(0), y(0), renderer(NULL), display(NULL), terrain(-1), unit(-1) {}
	Tile(int x, int y, SDL_Renderer* r, SDL_Texture* d) : x(x), y(y), renderer(r), display(d), terrain(-1), unit(-1) {}
	~Tile();

	void setTexture(SDL_Texture * tex);
	void setSource(TEXTURE src);
	TEXTURE getSource();
	void render();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setRenderer(SDL_Renderer* irenderer);
	SDL_Texture* getDisplay();
	void setT(int it);
	void setU(int iU);
	int getT();
	int getU();
};

// Simple mutators, accessors, and deconstructors
Tile::~Tile() {}
void Tile::setTexture(SDL_Texture* tex) {display = tex;}
void Tile::setX(int ix) { x = ix; }
void Tile::setY(int iy) { y = iy; }
void Tile::setRenderer(SDL_Renderer* irenderer) { renderer = irenderer; }
int Tile::getX() { return x; }
int Tile::getY() { return y; }
void Tile::setT(int it) { terrain = it; }
void Tile::setU(int iu) { unit = iu; }
int Tile::getT() { return terrain; }
int Tile::getU() { return unit; }
SDL_Texture* Tile::getDisplay() { return display; }
TEXTURE Tile::getSource() { return source; }
void Tile::setSource(TEXTURE src) { source = src; }

// 
void Tile::render() {
	if (x * TILE_SIDE + MAP_X > MAP_W || y * TILE_SIDE + MAP_Y > MAP_H)
		return;
	SDL_Rect dest = { x * TILE_SIDE + MAP_X, y * TILE_SIDE + MAP_Y, TILE_SIDE, TILE_SIDE };
	SDL_RenderCopy(renderer, display, NULL, &dest);
}


// Used to store both the display and other game info about different terrains in the map array
class Terrain {
private:
	int def = -1;
	// When mov is indexed by a TYPE, it returns the number of movement points a unit of that type must expend to enter that Terrain
	int* mov;
	bool canCapture;
	Tile* display;
	bool isReachable = false;
	bool isAttackable = false;
	double hp = 20;
	int team;
	TEXTURE type;

public:
	Terrain() : def(0), canCapture(false), display(NULL), isReachable(false), type(T_ERROR), team(2) { mov = new int[NUM_TYPES]; }
	Terrain(int d, int* m, bool c, Tile* di, TEXTURE t, int te = -1) : def(d), canCapture(c), display(di), isReachable(false), type(t), team(te) {
		mov = new int[NUM_TYPES];
		setMov(m);
	}
	~Terrain();
	// new Terrain(<defense>, movTemp, <isCaptureable>, NULL, )

	void setDisplay(TEXTURE src);
	void setDisplay(Tile* src);
	Tile* getDisplay();
	void setDef(int d);
	void setMov(int* m);
	void setCanCapture(bool c);
	void setIsReachable(bool r);
	void setIsAttackable(bool t);
	int getDef();
	double getHP();
	void setHP(double i);
	void heal(double h);
	void hit(double h);
	int* getMov();
	bool getCanCapture();
	bool getIsReachable();
	bool getIsAttackable();
	TEXTURE getType();
	int getTeam();
	void setTeam(int t);

};

// Simple mutators, accessors, and deconstructors
Terrain::~Terrain() { delete[] mov; }
void Terrain::setDisplay(TEXTURE src) {display->setSource(src);}
void Terrain::setDisplay(Tile* src) {display = src;}
Tile* Terrain::getDisplay() {return display;}
void Terrain::setDef(int d) {def = d;}
void Terrain::setCanCapture(bool c) { canCapture = c; }
int Terrain::getDef() { return def; }
int* Terrain::getMov() { return mov; }
bool Terrain::getCanCapture() { return canCapture; }
bool Terrain::getIsReachable() { return isReachable; }
void Terrain::setIsReachable(bool r) { isReachable = r; }
TEXTURE Terrain::getType() { return type; }
void Terrain::setIsAttackable(bool t) { isAttackable = t; }
bool Terrain::getIsAttackable() { return isAttackable; }
double Terrain::getHP() { return hp; }
void Terrain::setHP(double i) { hp = i; }
void Terrain::heal(double h) { hp += h; if (hp > 20) hp = 20; }
void Terrain::hit(double h) { hp -= h; }
int Terrain::getTeam() { return team; }
void Terrain::setTeam(int t) { team = t; }

void Terrain::setMov(int* m) {
	for (int i = 0; i < NUM_TYPES; ++i)
		mov[i] = m[i];
}

// Used to store both the display and other game information about the units in the spritesGround array
class Unit {
private:
	int x;
	int y;
	TEXTURE type;
	int mov;
	int minRange;
	int maxRange;
	TYPE movType;
	int cost;
	double* attack;
	Tile* display;
	int team;
	bool isMoved = false;
	bool hasAttacked = false;
	bool isLoadable = false;
	double hp = 20;
	UNIT_TYPE name;
	Unit* cargo1 = NULL;
	Unit* cargo0 = NULL;

public:
	Unit() : x(0), y(0), type(T_ERROR), mov(0), minRange(0), maxRange(0), movType(ERROR), cost(0), display(NULL), team(0), name(UNIT_ERROR) { attack = new double[NUM_UNITS]; }
	Unit(int x, int y, TEXTURE t, int m, int r1, int r2, TYPE mt, int c, double* atk, Tile* d, int te, UNIT_TYPE n) : x(x), y(y), type(t), mov(m), minRange(r1), maxRange(r2), movType(mt), cost(c), display(d), team(te), name(n) {
		attack = new double[NUM_UNITS];
		//if (atk == NULL) throw 5;
		setAttack(atk);
	}
	~Unit();

	void setX(int i);
	void setY(int i);
	void setDisplay(Tile* src);
	void setMov(int m);
	void setMovType(TYPE t);
	void setAttack(double* a);
	int getX();
	int getY();
	TYPE getMovType();
	TEXTURE getType();
	int getTeam();
	int getMov();
	int getMinRange();
	int getMaxRange();
	Tile* getDisplay();
	int getCost();
	UNIT_TYPE getName();
	void setType(TEXTURE it);
	void renderRange();
	bool renderAttack();
	void setTeam(int t);
	void setIsMoved(bool t);
	bool getIsMoved();
	double* getAttack();
	double getHP();
	void setHP(double i);
	void heal(double h);
	void hit(double h);
	void setHasAttacked(bool t);
	bool getHasAttacked();
	void setCargo(int i, Unit* c);
	Unit* getCargo(int i);
	bool getIsLoadable();
	void setIsLoadable(bool l);

};

//class metaTile {
//private:
//	Tile layers[4];
//	int x;
//	int y;
//
//public:
//	void setX(int ix);
//	void setY(int iy);
//	int getX();
//	int getY();
//	void setLayer(int layer, Tile input);
//	Tile getLayer(int layer);
//};

Terrain*** map;
Unit*** spritesGround;

// Simple mutators, accessors, and deconstructors
Unit::~Unit() {delete[] attack;}
void Unit::setDisplay(Tile* src) { display = src; }
void Unit::setMov(int m) { mov = m; }
void Unit::setMovType(TYPE t) { movType = t; }
TYPE Unit::getMovType() { return movType; }
int Unit::getTeam() { return team; }
void Unit::setX(int i) { x = i; }
void Unit::setY(int i) { y = i; }
int Unit::getX() { return x; }
int Unit::getY() { return y; }
TEXTURE Unit::getType() { return type; }
void Unit::setType(TEXTURE it) { type = it; }
int Unit::getMov() { return mov; }
int Unit::getMinRange() { return minRange; }
int Unit::getMaxRange() { return maxRange; }
Tile* Unit::getDisplay() { return display; }
int Unit::getCost() { return cost; }
void Unit::setTeam(int t) { team = t; }
void Unit::setIsMoved(bool t) { isMoved = t; }
bool Unit::getIsMoved() { return isMoved; }
double* Unit::getAttack() { return attack; }
double Unit::getHP() { return hp; }
void Unit::setHP(double i) { hp = i; }
void Unit::heal(double h) { hp += h; if (hp > 20) hp = 20; }
void Unit::hit(double h) { hp -= h; }
UNIT_TYPE Unit::getName() { return name; }
void Unit::setHasAttacked(bool t) { hasAttacked = t; }
bool Unit::getHasAttacked() { return hasAttacked; }
void Unit::setCargo(int i, Unit* c) {
	if (i)
		cargo1 = c;
	else
		cargo0 = c;
}
Unit* Unit::getCargo(int i) { return (i) ? cargo1 : cargo0; }
void Unit::setIsLoadable(bool l) { isLoadable = l; }
bool Unit::getIsLoadable() { return isLoadable; }

void Unit::setAttack(double* a) {
	for (int i = 0; i < NUM_UNITS; ++i)
		attack[i] = a[i];
}


// Used to store the different Tiles that need to be rendered to one 'metaTile' -- Up to four Tiles could render in one spot,
// layered on top of one another: Terrain, Unit, Effect, Cursor
class metaTile {
private:
	Tile **layers = NULL;
	int x;
	int y;

public:
	metaTile() : x(-1), y(-1) {
		layers = new Tile*[5];
		for (int i = 0; i < 5; ++i) setLayer(i, NULL);
	}
	metaTile(int x, int y, Tile** l) : x(x), y(y) {
		layers = new Tile*[5];
		for (int i = 0; i < 5; ++i) setLayer(i, l[i]);
	}
	~metaTile();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setLayer(int layer, Tile* input);
	Tile* getLayer(int layer);
};

metaTile::~metaTile() {
	// NOTE: THIS IS NOT A LEAK! The ONLY addresses stored in layers should already exist in the global textures array, so we
	// do NOT want to deallocate that memory yet. That is done in close().
	for (int i = 0; i < 5; ++i)
		layers[i] = NULL;
	delete[] layers;
	return;
}

void metaTile::setX(int ix) {x = ix;}
void metaTile::setY(int iy) {y = iy;}
int metaTile::getX() {return x;}
int metaTile::getY() {return y;}
void metaTile::setLayer(int layer, Tile *input) {layers[layer] = input;}
Tile* metaTile::getLayer(int layer) {return layers[layer];}

// Helper object used to determine movement range of Units -- Created by the Unit::renderRange() method and can propagate()
// causing it to attempt to make more Movers next to it, following the rules of movement. Also destroyed by Unit::renderRange().
class Mover {
public:
	int x;
	int y;
	int mov;
	int minRange;
	int maxRange;
	bool hasMoved;
	TYPE movType;
	int team;
	UNIT_TYPE name;

	Mover() : x(-1), y(-1), mov(-1), minRange(-1), maxRange(-1), movType(ERROR), hasMoved(false), team(-1), name(UNIT_ERROR) {}
	Mover(int ix, int iy, int m, int r1, int r2, TYPE t, int te, UNIT_TYPE n) : x(ix), y(iy), mov(m), minRange(r1), maxRange(r2), movType(t), hasMoved(false), team(te), name(n) {}
	~Mover();
	void propagate();
};

Mover*** movTemp;

Mover::~Mover() {}

void Mover::propagate() {
	if (hasMoved) return;

	for (int i = 0; i < 4; ++i) {
		int newX = x, newY = y;
		switch (i) {
		case 0:
			newX++;
			break;
		case 1:
			newX--;
			break;
		case 2:
			newY++;
			break;
		case 3:
			newY--;
			break;
		}
		if (newX < 0 || newY < 0 || newX >= MAP_TILE_W || newY >= MAP_TILE_H)
			continue;
		int movDiff = mov - map[newX][newY]->getMov()[movType];
		if (movDiff < 0)
			continue;
		if (spritesGround[newX][newY] != NULL && spritesGround[newX][newY]->getTeam() != team)
			continue;
		if (movTemp[newX][newY] != NULL)
			if (movTemp[newX][newY]->hasMoved)
				continue;
			else
				if (movDiff > movTemp[newX][newY]->mov) {
					movTemp[newX][newY]->mov = movDiff;
					continue;
				}
				else
					continue;
		movTemp[newX][newY] = new Mover(newX, newY, movDiff, minRange, maxRange, movType, team, name);
	}

	if (spritesGround[x][y] == NULL || ((name == INFANTRY || name == MECH) && (spritesGround[x][y]->getName() == T_COPTER || spritesGround[x][y]->getName() == APC)) || (name <= H_TANK && spritesGround[x][y]->getName() == LANDER) || (name > B_COPTER && name <= BOMBER && spritesGround[x][y]->getName() == CARRIER)) {
		if (spritesGround[x][y] != NULL && ((spritesGround[x][y]->getName() == T_COPTER || spritesGround[x][y]->getName() == APC) ? spritesGround[x][y]->getCargo(0) == NULL : spritesGround[x][y]->getCargo(1) == NULL)) {
			spritesGround[x][y]->setIsLoadable(true);
			map[x][y]->setIsReachable(true);
		}
		else if (spritesGround[x][y] == NULL)
			map[x][y]->setIsReachable(true);
	}
	hasMoved = true;
}

void Unit::renderRange() {

	if (isMoved)
		return;

	movTemp[x][y] = new Mover(x, y, mov, minRange, maxRange, movType, team, name);

	for (int d = mov+1; d > 0; --d) {
		for (int i = 0; i < MAP_TILE_W; ++i)
			for (int j = 0; j < MAP_TILE_H; ++j) {
				if (movTemp[i][j] != NULL)
					movTemp[i][j]->propagate();
			}
	}
	
	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (map[i][j]->getIsReachable()) {
				int temp[] = { i,j,-1,-1 };
				reLayer(temp, 'r', NULL);
			}
	}
	int temp[] = { x, y, -1, -1 };
	reLayer(temp, 'r', 's');
	map[x][y]->setIsReachable(true);
	isLoadable = false;

	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (movTemp[i][j] != NULL) {
				delete movTemp[i][j];
				movTemp[i][j] = NULL;
			}

}

// Keeps addresses of units that can be attacked by the selected unit for rendering
Unit** targets;
int targetsSize = 0;
int coords[4]; //temp coords array
int targetsIndex;

bool Unit::renderAttack() {

	//map[x][y]->setIsReachable(true);

	int numTargets = 0;

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (spritesGround[i][j] != NULL && spritesGround[i][j]->getTeam() != team) {
				if (std::abs(x - i) + std::abs(y - j) <= maxRange && std::abs(x - i) + std::abs(y - j) >= minRange) {
					numTargets++;
					map[i][j]->setIsAttackable(true);
				}
			}
		}
	}

	if (numTargets == 0)
		return false;

	int tempNum = numTargets;
	targets = new Unit * [numTargets];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (map[i][j]->getIsAttackable()) {
				targets[--tempNum] = spritesGround[i][j];
				map[i][j]->setIsAttackable(false);
			}
		}
	}

	int temp2[] = { coords[0],coords[1],-1,-1 };
	reLayer(temp2, NULL, NULL);

	coords[0] = targets[0]->getX();
	coords[1] = targets[0]->getY();

	targetsIndex = 0;

	int temp1[] = { coords[0],coords[1],-1,-1 };
	reLayer(temp1, 'b', 't');

	for (int i = 1; i < numTargets; ++i) {
		bool shouldDisplay = true;
		int temp[] = { targets[i]->getX(), targets[i]->getY(), -1, -1 };
			reLayer(temp, 'b', NULL);
	}

	targetsSize = numTargets;

	return true;

}


/* Globals */
bool w;
bool s;
bool a;
bool d;
bool shift;
bool ctrl;
bool space;
bool enter = false;
bool isRunning = true;
bool catalogIsOpen = false;
std::vector<UNIT_TYPE> catalog(11);
int catalogIndex = 0;
char catalogMode = 'l';
int blueFunds = 0;
int redFunds = 0;
std::vector<Unit*> cargoBay(2);
int cargoIndex = 0;
bool unloading = false;
std::vector<int> dropX(4);
std::vector<int> dropY(4);
int dropIndex = 0;
int winningTeam = -1;
bool gameOver = false;
int mapNo = 0;
SDL_Window* window;
// Tracks whether a unit is selected or not (c for not, s for selecting)
char moveMode = 'c';
// Keeps a copy of the currently selected unit
Unit* selUnit;
//fill in when map is created
SDL_Renderer* renderer = NULL;
SDL_Surface* screenSurface = NULL;
int turn = 0; // odd is red, even is blue
// Points to all loaded png assets
SDL_Texture** textures = NULL;
// Points to Tile versions of these assets
Tile** spritesheet = NULL;
// Points to initial states of all terrain
Terrain** terrainsheet = NULL;
// Points to initial states of all units
Unit** unitsheet = NULL;
// true when the player just moved a unit, false after that unit does an action
bool openMenu = false;
//animated tiles vector
std::vector<metaTile> animatedTiles;
//frame for animation
int frame = 1;
//int timer for animate delay
int seconds;
//metaTile map for camera and animation
metaTile*** demTiles;
//Null Tile and MetaTile for passthrough
Tile nullTile;
metaTile nullMetaTile;
//SDL Text Font
TTF_Font* Sans;
SDL_Color Blue = {51, 204, 255};
SDL_Rect Blue_message; //create a rect
SDL_Color Red = { 230, 40, 40 };
SDL_Rect Red_message; //create a rect
SDL_Rect End_message;

int main(int argc, char* argv[])
{
	//Null Objects allocation
	nullMetaTile.setLayer(0, &nullTile);

	window = NULL;
	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		int x = 0;
		int y = 0;

		coords[0] = 15;
		coords[1] = 5;

		std::cout << "About to make the map\n";

		//debug
		initTerrain();
		initUnit();
		createMap();

		std::cout << "Made the map, getting ready to render it\n";

		for (int lolz = 0; lolz < MAP_TILE_W; lolz++) {
			for (int yeetus = 0; yeetus < MAP_TILE_H; yeetus++) {
				int tempInputter[4] = { lolz, yeetus, -1, -1 };
				if (!((yeetus - cameraY) < 0))
					reLayer(tempInputter, NULL, NULL);
			}
		}
		SDL_RenderPresent(renderer);

		std::cout << "Map Created!";

		updateFunds();

		//Text debug
		updateText();
		SDL_RenderPresent(renderer);

		while (isRunning) {
			SDL_Event scanner;
			while (SDL_PollEvent(&scanner)) {

				//mouse scanner
				if (scanner.type == SDL_MOUSEBUTTONDOWN) {
					x = scanner.button.x;
					y = scanner.button.y;

					switch (scanner.button.button) {
					case SDL_BUTTON_LEFT:
						std::cout << "Clicked Left! ";
						whatClicked(x, y, 1);
						break;
					case SDL_BUTTON_RIGHT:
						std::cout << "Clicked Right! ";
						whatClicked(x, y, 2);
						break;
					case SDL_BUTTON_MIDDLE:
						std::cout << "Clicked middle! ";
						whatClicked(x, y, 3);
						break;
					}
				}

				if (scanner.type == SDL_KEYDOWN) {
					keyStatesDown(scanner.key.keysym.sym);
				}

				if (scanner.type == SDL_KEYUP) {
					keyStatesUp(scanner.key.keysym.sym);
				}

				//game changing stuff
				if (w == true) {
					if (coords[1] == 0)
						break;
					if (unloading) {
						int dx = dropX.at(dropIndex), dy = dropY.at(dropIndex);

						unloading = false;
						selUnit->setCargo(0, cargoBay.at(0));
						if (cargoBay.size() > 1)
							selUnit->setCargo(1, cargoBay.at(1));
						else
							selUnit->setCargo(1, NULL);

						selUnit = NULL;

						delete spritesGround[dx][dy];
						spritesGround[dx][dy] = NULL;

						for (int i = 0; i < dropX.size(); ++i) {
							int temp[] = { dropX.at(i), dropY.at(i), -1, -1 };
							reLayer(temp, NULL, NULL);
						}

						for (int i = 0; i < cargoBay.size(); ++i)
							cargoBay.at(i) = NULL;
						cargoBay.clear();
						dropX.clear();
						dropY.clear();
						cargoIndex = 0;
						dropIndex = 0;
					}
					if ((moveMode == 's' /*&& map[coords[0]][coords[1] - 1]->getIsReachable())*/) || moveMode == 'c') {
						if (catalogIsOpen) {
							delete spritesGround[coords[0]][coords[1]];
							spritesGround[coords[0]][coords[1]] = NULL;
							int temp[] = { coords[0], coords[1], -1, -1 };
							reLayer(temp, NULL, NULL);
							catalogIsOpen = false;
							catalogIndex = 0;
							catalog.clear();
						}
						setCoord(coords[0], coords[1], 'w');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						cameraMove('w');
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					w = false;
				}
				if (a == true) {
					if (coords[0] == 0)
						break;
					if (unloading) {
						if (--dropIndex < 0) dropIndex = dropX.size() - 1;
						coords[2] = coords[0];
						coords[3] = coords[1];
						coords[0] = dropX.at(dropIndex);
						coords[1] = dropY.at(dropIndex);
						delete spritesGround[coords[2]][coords[3]];
						spritesGround[coords[2]][coords[3]] = NULL;
						initSpritesGround(coords[0], coords[1], cargoBay.at(cargoIndex));
						int temp[] = { coords[0], coords[1], -1, -1 };
						reLayer(temp, 'r', 'c');
						int temp2[] = { coords[2], coords[3], -1, -1 };
						reLayer(temp2, 'r', NULL);
						SDL_RenderPresent(renderer);
					}
					else if ((moveMode == 's' /*&& map[coords[0] - 1][coords[1]]->getIsReachable())*/) || moveMode == 'c') {
						if (catalogIsOpen) {
							delete spritesGround[coords[0]][coords[1]];
							spritesGround[coords[0]][coords[1]] = NULL;
							int temp[] = { coords[0], coords[1], -1, -1 };
							reLayer(temp, NULL, NULL);
							catalogIsOpen = false;
							catalogIndex = 0;
							catalog.clear();
						}
						setCoord(coords[0], coords[1], 'a');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					else if (moveMode == 't') {
						if (targetsIndex == 0)
							targetsIndex = targetsSize;
						targetsIndex--;
						coords[2] = coords[0];
						coords[3] = coords[1];
						coords[0] = targets[targetsIndex]->getX();
						coords[1] = targets[targetsIndex]->getY();
						reLayer(coords, 'b', moveMode);
						SDL_RenderPresent(renderer);
					}
					a = false;
				}
				if (s == true) {
					if (coords[1] == MAP_TILE_H-1)
						break;
					if (unloading) {
						int dx = dropX.at(dropIndex), dy = dropY.at(dropIndex);

						unloading = false;
						selUnit->setCargo(0, cargoBay.at(0));
						if (cargoBay.size() > 1)
							selUnit->setCargo(1, cargoBay.at(1));
						else
							selUnit->setCargo(1, NULL);

						selUnit = NULL;

						delete spritesGround[dx][dy];
						spritesGround[dx][dy] = NULL;

						for (int i = 0; i < dropX.size(); ++i) {
							int temp[] = { dropX.at(i), dropY.at(i), -1, -1 };
							reLayer(temp, NULL, NULL);
						}

						for (int i = 0; i < cargoBay.size(); ++i)
							cargoBay.at(i) = NULL;
						cargoBay.clear();
						dropX.clear();
						dropY.clear();
						cargoIndex = 0;
						dropIndex = 0;
					}
					if ((moveMode == 's' /*&&*/ /*map[coords[0]][coords[1] + 1]->getIsReachable())*/) || moveMode == 'c') {
						if (catalogIsOpen) {
							delete spritesGround[coords[0]][coords[1]];
							spritesGround[coords[0]][coords[1]] = NULL;
							int temp[] = { coords[0], coords[1], -1, -1 };
							reLayer(temp, NULL, NULL);
							catalogIsOpen = false;
							catalogIndex = 0;
							catalog.clear();
						}
						setCoord(coords[0], coords[1], 's');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						cameraMove('s');
						SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					s = false;
				}
				if (d == true) {
					if (coords[0] == MAP_TILE_W-1)
						break;
					if (unloading) {
						if (++dropIndex == dropX.size()) dropIndex = 0;
						coords[2] = coords[0];
						coords[3] = coords[1];
						coords[0] = dropX.at(dropIndex);
						coords[1] = dropY.at(dropIndex);
						delete spritesGround[coords[2]][coords[3]];
						spritesGround[coords[2]][coords[3]] = NULL;
						initSpritesGround(coords[0], coords[1], cargoBay.at(cargoIndex));
						int temp[] = { coords[0], coords[1], -1, -1 };
						reLayer(temp, 'r', 'c');
						int temp2[] = { coords[2], coords[3], -1, -1 };
						reLayer(temp2, 'r', NULL);
						SDL_RenderPresent(renderer);
					}
					else if ((moveMode == 's' /*&&*/ /*map[coords[0] + 1][coords[1]]->getIsReachable())*/) || moveMode == 'c') {
						if (catalogIsOpen) {
							delete spritesGround[coords[0]][coords[1]];
							spritesGround[coords[0]][coords[1]] = NULL;
							int temp[] = { coords[0], coords[1], -1, -1 };
							reLayer(temp, NULL, NULL);
							catalogIsOpen = false;
							catalogIndex = 0;
							catalog.clear();
						}
						setCoord(coords[0], coords[1], 'd');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					else if (moveMode == 't') {
						if (targetsIndex == targetsSize-1)
							targetsIndex = 0;
						else
							targetsIndex++;
							coords[2] = coords[0];
							coords[3] = coords[1];
							coords[0] = targets[targetsIndex]->getX();
							coords[1] = targets[targetsIndex]->getY();
							reLayer(coords, 'b', moveMode);
							SDL_RenderPresent(renderer);
					}
					d = false;
				}
				if (space == true) {
					// coords[0],coords[1] == coordinates of cursor currently
					if (unloading) {
						// WIP
						int dx = dropX.at(dropIndex), dy = dropY.at(dropIndex);

						unloading = false;
						if (cargoBay.size() != 1) {
							Unit* repop = cargoBay.at((cargoIndex == 0) ? 1 : 0);
							selUnit->setCargo(0, repop);
							selUnit->setCargo(1, NULL);
							std::cout << "lol";
							repop = NULL;
						}
						else {
							selUnit->setCargo(0, NULL);
							selUnit->setCargo(1, NULL);
						}

						selUnit = NULL;

						for (int i = 0; i < dropX.size(); ++i) {

							int temp[] = { dropX.at(i), dropY.at(i), -1, -1 };
							if (dropX.at(i) == dx && dropY.at(i) == dy)
								reLayer(temp, NULL, 'c');
							else
								reLayer(temp, NULL, NULL);
						}

						spritesGround[dx][dy]->setIsMoved(true);
						spritesGround[dx][dy]->setHasAttacked(true);

						for (int i = 0; i < cargoBay.size(); ++i)
							cargoBay.at(i) = NULL;
						cargoBay.clear();
						dropX.clear();
						dropY.clear();
						cargoIndex = 0;
						dropIndex = 0;

					}
					else if (spritesGround[coords[0]][coords[1]] != NULL && spritesGround[coords[0]][coords[1]]->getTeam() == turn % 2 && moveMode == 'c' && !catalogIsOpen)
					{
						if (!spritesGround[coords[0]][coords[1]]->getIsMoved()) {
							moveMode = 's';
							selUnit = spritesGround[coords[0]][coords[1]];
							reLayer(coords, NULL, moveMode);
							selUnit->renderRange();
							SDL_RenderPresent(renderer);
						}
						else {
							if (spritesGround[coords[0]][coords[1]]->getHasAttacked())
								break;
							selUnit = spritesGround[coords[0]][coords[1]];
							bool success = selUnit->renderAttack();
							if (!success)
								break;
							moveMode = 't';
							//reLayer(coords, 'b', moveMode);
							SDL_RenderPresent(renderer);
						}
					}
					else if (moveMode == 's') {
						moveMode = 'c';
						if (map[coords[0]][coords[1]]->getIsReachable()) {
							if (spritesGround[coords[0]][coords[1]] != NULL && spritesGround[coords[0]][coords[1]]->getIsLoadable()) {
								spritesGround[selUnit->getX()][selUnit->getY()] = NULL;
								int temp[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
								reLayer(temp, NULL, NULL);
								spritesGround[coords[0]][coords[1]]->setIsLoadable(false);
								if ((spritesGround[coords[0]][coords[1]]->getName() == LANDER || spritesGround[coords[0]][coords[1]]->getName() == CARRIER) && spritesGround[coords[0]][coords[1]]->getCargo(0) != NULL) {
									spritesGround[coords[0]][coords[1]]->setCargo(1, selUnit);
								}
								else
									spritesGround[coords[0]][coords[1]]->setCargo(0, selUnit);
								//
								std::cout << "Loaded unit type " << selUnit->getName() << " into unit type " << spritesGround[coords[0]][coords[1]]->getName() << ".\n";
								//
								selUnit = NULL;
							}
							else if (coords[0] != selUnit->getX() || coords[1] != selUnit->getY()) {
								initSpritesGround(coords[0], coords[1], selUnit);
								spritesGround[selUnit->getX()][selUnit->getY()] = NULL;
								int temp[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
								reLayer(temp, NULL, NULL);
								delete selUnit;
							}
							spritesGround[coords[0]][coords[1]]->setIsMoved(true);

							if (map[coords[0]][coords[1]]->getCanCapture() && spritesGround[coords[0]][coords[1]]->getTeam() != map[coords[0]][coords[1]]->getTeam() && (spritesGround[coords[0]][coords[1]]->getName() == INFANTRY || spritesGround[coords[0]][coords[1]]->getName() == MECH)) {
								TERRAIN_TYPE newT = getNewCapture(map[coords[0]][coords[1]]->getType(), turn % 2);
								delete map[coords[0]][coords[1]];
								initMap(coords[0], coords[1], terrainsheet[newT]);
							}
						}
						for (int i = 0; i < MAP_TILE_W; ++i)
							for (int j = 0; j < MAP_TILE_H; ++j) {
								if (map[i][j]->getIsReachable()) {
									map[i][j]->setIsReachable(false);
									int temp[] = { i, j, -1, -1 };
									reLayer(temp, NULL, NULL);
								}
							}
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
					}
					else if (moveMode == 't') {
						moveMode = 'c';
						int tX = targets[targetsIndex]->getX();
						int tY = targets[targetsIndex]->getY();
						spritesGround[tX][tY]->hit(selUnit->getAttack()[targets[targetsIndex]->getName()] * 10.0 * (selUnit->getHP() / 20.0));
						int temp2[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
						selUnit->setHasAttacked(true);
						reLayer(temp2, NULL, NULL);
						selUnit = NULL;
						if (spritesGround[tX][tY]->getHP() <= 0) {
							delete spritesGround[tX][tY];
							spritesGround[tX][tY] = NULL;
						}
						int temp[] = { tX, tY, -1, -1 };
						reLayer(temp, NULL, 'c');
						for (int i = 0; i < targetsSize; ++i) {
							if (i == targetsIndex)
								continue;
							int temp1[] = { targets[i]->getX(), targets[i]->getY(), -1, -1 };
							reLayer(temp1, NULL, NULL);
						}
						for (int i = 0; i < targetsSize; ++i)
							targets[i] = NULL;
						delete[] targets;
						targets = NULL;
					}
					else if ((map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_AIRPORT_RED : T_AIRPORT_BLUE) || map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_PORT_RED : T_PORT_BLUE) || map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_BASE_RED : T_BASE_BLUE)) && moveMode == 'c' && spritesGround[coords[0]][coords[1]] == NULL && !catalogIsOpen) {
						
						catalog.clear();
						catalogIndex = 0;

						if (map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_AIRPORT_RED : T_AIRPORT_BLUE)) {
							for (int i = 11; i < 15; ++i) { // range of air units on list
								if (unitsheet[i]->getCost() <= ((turn % 2) ? redFunds : blueFunds))
									catalog.push_back((UNIT_TYPE)i);
							}
							catalogMode = 'a';
						}
						else if (map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_PORT_RED : T_PORT_BLUE)) {
							for (int i = 15; i < 20; ++i) { // range of sea units
								if (unitsheet[i]->getCost() <= ((turn % 2) ? redFunds : blueFunds))
									catalog.push_back((UNIT_TYPE)i);
							}
							catalogMode = 's';
						}
						else if (map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_BASE_RED : T_BASE_BLUE)) {
							for (int i = 0; i < 11; ++i) { // range of ground units
								if (unitsheet[i]->getCost() <= ((turn % 2) ? redFunds : blueFunds))
									catalog.push_back((UNIT_TYPE)i);
							}
							catalogMode = 'l';
						}

						if (catalog.size() == 0)
							break;

						catalogIsOpen = true;

						initSpritesGround(coords[0], coords[1], unitsheet[catalog[0]]);
						spritesGround[coords[0]][coords[1]]->setTeam(turn % 2);
						int temp[] = { coords[0], coords[1], -1, -1 };
						reLayer(temp, 'r', 'c');

					}
					else if ((map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_AIRPORT_RED : T_AIRPORT_BLUE) || map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_PORT_RED : T_PORT_BLUE) || map[coords[0]][coords[1]]->getType() == ((turn % 2) ? T_BASE_RED : T_BASE_BLUE)) && moveMode == 'c' && catalogIsOpen) {
						
						catalogIsOpen = false;
						spritesGround[coords[0]][coords[1]]->setIsMoved(true);
						spritesGround[coords[0]][coords[1]]->setHasAttacked(true);
						catalog.clear();
						catalogIndex = 0;

						if (turn % 2)
							redFunds -= spritesGround[coords[0]][coords[1]]->getCost();
						else
							blueFunds -= spritesGround[coords[0]][coords[1]]->getCost();

						updateText();

						int temp[] = { coords[0], coords[1], -1, -1 };
						reLayer(temp, NULL, 'c');

					}
					SDL_RenderPresent(renderer);
					space = !space;
				}
				if (shift == true) {

					if (catalogIsOpen) {

						if (catalogIndex == catalog.size() - 1)
							catalogIndex = 0;
						else
							catalogIndex++;

						delete spritesGround[coords[0]][coords[1]];
						spritesGround[coords[0]][coords[1]] = NULL;
						initSpritesGround(coords[0], coords[1], unitsheet[catalog[catalogIndex]]);
						spritesGround[coords[0]][coords[1]]->setTeam(turn % 2);

						int temp[] = { coords[0], coords[1], -1, -1 };
						reLayer(temp, 'r', 'c');

					}
					else if (unloading) {

						// browse unloading WIP
						if (cargoBay.size() > 1) {
							delete spritesGround[dropX.at(dropIndex)][dropY.at(dropIndex)];
							if (++cargoIndex == cargoBay.size()) cargoIndex = 0;
							initSpritesGround(dropX.at(dropIndex), dropY.at(dropIndex), cargoBay.at(cargoIndex));
							int temp[] = {dropX.at(dropIndex), dropY.at(dropIndex), -1, -1};
							reLayer(temp, 'r', 'c');
						}

					}
					else if (spritesGround[coords[0]][coords[1]] != NULL && spritesGround[coords[0]][coords[1]]->getCargo(0) != NULL) {
						// WIP
						selUnit = spritesGround[coords[0]][coords[1]];
						std::cout << "Unloading a unit!\n";
						unloading = true;
						for (int i = 0; i < cargoBay.size(); ++i)
							cargoBay.at(i) = NULL;
						cargoBay.clear();
						dropX.clear();
						dropY.clear();
						cargoIndex = 0;
						dropIndex = 0;

						cargoBay.push_back(spritesGround[coords[0]][coords[1]]->getCargo(0));
						if (spritesGround[coords[0]][coords[1]]->getCargo(1) != NULL)
							cargoBay.push_back(spritesGround[coords[0]][coords[1]]->getCargo(1));

						for (int i = 0; i < 4; ++i) {
							int x = coords[0], y = coords[1];
							if (i == 0) x--;
							if (i == 1) y--;
							if (i == 2) x++;
							if (i == 3) y++;
							if (map[x][y]->getMov()[cargoBay.at(cargoIndex)->getMovType()] == 10)
								continue;
							if (spritesGround[x][y] != NULL)
								continue;
							dropX.push_back(x);
							dropY.push_back(y);
						}

						if (dropX.size() == 0) {
							for (int i = 0; i < cargoBay.size(); ++i)
								cargoBay.at(i) = NULL;
							cargoBay.clear();
							dropX.clear();
							dropY.clear();
							cargoIndex = 0;
							dropIndex = 0;
							unloading = false;
							break;
						}

						initSpritesGround(dropX.at(0), dropY.at(0), cargoBay.at(0));
						//int temp[] = { dropX.at(0), dropY.at(0), -1, -1 };
						// Clear the unit's cargo to be repopulated from the remnants of cargoBay after unloading
						spritesGround[coords[0]][coords[1]]->setCargo(0, NULL);
						spritesGround[coords[0]][coords[1]]->setCargo(1, NULL);
						coords[2] = coords[0];
						coords[3] = coords[1];
						coords[0] = dropX.at(0);
						coords[1] = dropY.at(0);
						reLayer(coords, 'r', 'c');

						for (int i = 1; i < dropX.size(); ++i) {
							int temp1[] = { dropX.at(i), dropY.at(i), -1, -1 };
							reLayer(temp1, 'r', NULL);
						}

					}

					SDL_RenderPresent(renderer);

				}
				if (enter == true) {
					if (gameOver) {
						isRunning = false;
						break;
					}
					if (moveMode != 'c') {
						enter = !enter;
						break;
					}
					for (int i = 0; i < MAP_TILE_W; ++i) {
						for (int j = 0; j < MAP_TILE_H; ++j) {
							if (spritesGround[i][j] != NULL) {
								spritesGround[i][j]->setHasAttacked(false);
								spritesGround[i][j]->setIsMoved(false);
							}
						}
					}
					turn++;
					updateFunds();
					enter = !enter;
					int temp[] = { coords[0], coords[1], -1, -1 };
					reLayer(temp, NULL, 'c');
					if (turn > 5) {
						int numRed = getNumUnits(1);
						int numBlue = getNumUnits(0);

						if (numRed == 0)
							winningTeam = 0;
						else if (numBlue == 0)
							winningTeam = 1;


					}

					int numRedHQ = 0;
					for (int i = 0; i < MAP_TILE_W; ++i) {
						for (int j = 0; j < MAP_TILE_H; ++j) {
							if (map[i][j]->getType() == T_HQ_RED)
								numRedHQ++;
						}
					}
					if (numRedHQ == 0)
						winningTeam = 0;
					else if (numRedHQ == 2)
						winningTeam = 1;

					updateText();
					SDL_RenderPresent(renderer);
				}
				if (ctrl == true) {
					close(window);
					ctrl = false;
					mapNo++;
					if (mapNo == 5)
						mapNo = 0;

					blueFunds = 0;
					redFunds = 0;
					winningTeam = -1;
					gameOver = false;
					turn = 0;

					return main(0, NULL);

				}
			}



			if (isRunning == false)
				break;
		}	

		//close
		close(window);

		return 0;

	}

	return 0;
}

// Called on startup to initialized both SDL and the relevant global arrays and textures
SDL_Window* init(SDL_Window* window) {
	SDL_DestroyWindow(window);
	window = NULL;

	// SDL and window
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return NULL;
		}
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return NULL;
			}

		}
	}

	// global data arrays
	map = new Terrain ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		map[i] = new Terrain * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			map[i][j] = NULL;
	}
	spritesGround = new Unit ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		spritesGround[i] = new Unit * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			spritesGround[i][j] = NULL;
	}
	movTemp = new Mover ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		movTemp[i] = new Mover * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			movTemp[i][j] = NULL;
	}
	demTiles = new metaTile ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		demTiles[i] = new metaTile * [MAP_TILE_H];

	// surface and renderer
	screenSurface = SDL_GetWindowSurface(window);
	printf("Got the window surface\n");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	printf("Renderer initialized\n");

	//Init ttf
	TTF_Init();
	Sans = TTF_OpenFont("segoeui.ttf", 30);

	/*enum TEXTURE {
	T_ROAD = 4,
	T_PORT = 5,
	T_HQ = 6,
	T_AIRPORT = 7,
	T_BASE = 8,
	T_CITY = 9,
	T_REEF = 10,
	T_TREE = 11,
	T_SHORE = 12,
	T_RIVER = 13,
	T_INFANTRY = 14, R
	T_MECH = 15, R
	T_RECON = 16,R
	T_ANTI_AIR = 18, R
	T_ARTILLERY = 19,R
	T_MISSILE = 20,R
	T_ROCKET = 21,R
	T_L_TANK = 22,R
	T_M_TANK = 23,R
	T_H_TANK = 24,R
	T_B_COPTER = 25,R
	T_T_COPTER = 26,R
	T_FIGHTER = 27,R
	T_BOMBER = 28,R
	T_BATTLESHIP = 29,R
	T_CRUISER = 30,R
	T_SUB = 31,R
	T_LANDER = 32,R
	T_CARRIER = 33,R
	};*/

	// textures
	textures = new SDL_Texture*[NUM_TEXTURES];
	if (!loadTexture(renderer, &textures[T_GRASS], "assets/Grass.png"))
		std::cout << "Texture \"grass\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_APC], "assets/apc/1.png"))
		std::cout << "Texture \"apc\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BLUE], "assets/blue_tint_overlay.png"))
		std::cout << "Texture \"blue_tint\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_RED], "assets/red_tint_overlay.png"))
		std::cout << "Texture \"red_tint\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CURSOR_RED], "assets/red_cursor.png"))
		std::cout << "Texture \"red_cursor\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SELECT_RED], "assets/red_select.png"))
		std::cout << "Texture \"red_select\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TARGET_RED], "assets/target_red.png"))
		std::cout << "Texture \"red_target\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_NULL], "assets/null.png"))
		std::cout << "Texture \"null\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BRIDGE], "assets/bridge.png"))
		std::cout << "Texture \"bridge\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_MOUNTAIN], "assets/mountains1.png"))
		std::cout << "Texture \"mountain\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_WATER], "assets/sea1.png"))
		std::cout << "Texture \"sea\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CURSOR_BLUE], "assets/blue_cursor.png"))
		std::cout << "Texture \"blue_cursor\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SELECT_BLUE], "assets/blue_select.png"))
		std::cout << "Texture \"blue_select\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TARGET_BLUE], "assets/target_blue.png"))
		std::cout << "Texture \"blue_target\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_20_RED], "assets/hp/19-20 hp red.png"))
		std::cout << "Texture \"hp_20_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_18_RED], "assets/hp/17-18 hp red.png"))
		std::cout << "Texture \"hp_18_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_16_RED], "assets/hp/15-16 hp red.png"))
		std::cout << "Texture \"hp_16_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_14_RED], "assets/hp/13-14 hp red.png"))
		std::cout << "Texture \"hp_14_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_12_RED], "assets/hp/11-12 hp red.png"))
		std::cout << "Texture \"hp_12_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_10_RED], "assets/hp/9-10 hp red.png"))
		std::cout << "Texture \"hp_10_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_8_RED], "assets/hp/7-8 hp red.png"))
		std::cout << "Texture \"hp_8_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_6_RED], "assets/hp/5-6 hp red.png"))
		std::cout << "Texture \"hp_6_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_4_RED], "assets/hp/3-4 hp red.png"))
		std::cout << "Texture \"hp_4_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_2_RED], "assets/hp/1-2 hp red.png"))
		std::cout << "Texture \"hp_2_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_20_BLUE], "assets/hp/19-20 hp blue.png"))
		std::cout << "Texture \"hp_20_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_18_BLUE], "assets/hp/17-18 hp blue.png"))
		std::cout << "Texture \"hp_18_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_16_BLUE], "assets/hp/15-16 hp blue.png"))
		std::cout << "Texture \"hp_16_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_14_BLUE], "assets/hp/13-14 hp blue.png"))
		std::cout << "Texture \"hp_14_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_12_BLUE], "assets/hp/11-12 hp blue.png"))
		std::cout << "Texture \"hp_12_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_10_BLUE], "assets/hp/9-10 hp blue.png"))
		std::cout << "Texture \"hp_10_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_8_BLUE], "assets/hp/7-8 hp blue.png"))
		std::cout << "Texture \"hp_8_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_6_BLUE], "assets/hp/5-6 hp blue.png"))
		std::cout << "Texture \"hp_6_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_4_BLUE], "assets/hp/3-4 hp blue.png"))
		std::cout << "Texture \"hp_4_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_2_BLUE], "assets/hp/1-2 hp blue.png"))
		std::cout << "Texture \"hp_2_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_ROAD], "assets/ROAD.png")) // NEW
		std::cout << "Texture \"road\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_PORT], "assets/neutral anchor.png"))
		std::cout << "Texture \"neutral port\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HQ], "assets/Neutral HQ.png"))
		std::cout << "Texture \"neutral HQ\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_AIRPORT], "assets/neurtal airport.png")) // The filename is misspelled for some reason
		std::cout << "Texture \"neutral airport\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BASE], "assets/Neurtal base.png")) // Again
		std::cout << "Texture \"neutral base\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CITY], "assets/Neutral city.png"))
		std::cout << "Texture \"neutral city\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_REEF], "assets/reef1.png"))
		std::cout << "Texture \"reef\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TREE], "assets/forest2.png"))
		std::cout << "Texture \"forest\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SHORE], "assets/Shore.png"))
		std::cout << "Texture \"shore\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_RIVER], "assets/river.png"))
		std::cout << "Texture \"river\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_INFANTRY], "assets/infantry/1.png"))
		std::cout << "Texture \"infantry\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_MECH], "assets/mech/1.png"))
		std::cout << "Texture \"mech\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_RECON], "assets/recon/1.png"))
		std::cout << "Texture \"recon\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_ANTI_AIR], "assets/anti_air/1.png"))
		std::cout << "Texture \"anti air\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_ARTILLERY], "assets/artillery/1.png"))
		std::cout << "Texture \"artillery\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_MISSILE], "assets/missile/1.png"))
		std::cout << "Texture \"missile\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_ROCKET], "assets/rocket/1.png"))
		std::cout << "Texture \"rocket\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_L_TANK], "assets/light_tank/1.png"))
		std::cout << "Texture \"light tank\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_M_TANK], "assets/medium_tank/1.png"))
		std::cout << "Texture \"medium tank\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_H_TANK], "assets/heavy_tank/1.png"))
		std::cout << "Texture \"heavy tank\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_B_COPTER], "assets/battle_copter/1.png"))
		std::cout << "Texture \"battle copter\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_T_COPTER], "assets/transport_copter/1.png"))
		std::cout << "Texture \"transport copter\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_FIGHTER], "assets/fighter/1.png"))
		std::cout << "Texture \"fighter\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BOMBER], "assets/bomber/1.png"))
		std::cout << "Texture \"bomber\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BATTLESHIP], "assets/battleship/1.png"))
		std::cout << "Texture \"battleship\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CRUISER], "assets/cruiser/1.png"))
		std::cout << "Texture \"cruiser\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SUB], "assets/submarine/1.png"))
		std::cout << "Texture \"submarine\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_LANDER], "assets/lander/1.png"))
		std::cout << "Texture \"lander\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CARRIER], "assets/carrier/1.png"))
		std::cout << "Texture \"carrier\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_PORT_BLUE], "assets/Blue anchor.png")) //
		std::cout << "Texture \"blue port\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HQ_BLUE], "assets/Blue HQ.png"))
		std::cout << "Texture \"blue HQ\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_AIRPORT_BLUE], "assets/Blue airport.png")) 
		std::cout << "Texture \"blue airport\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BASE_BLUE], "assets/Blue base.png")) 
		std::cout << "Texture \"blue base\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CITY_BLUE], "assets/Blue city.png"))
		std::cout << "Texture \"blue city\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_PORT_RED], "assets/Red port.png"))
		std::cout << "Texture \"red port\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HQ_RED], "assets/Red HQ.png"))
		std::cout << "Texture \"red HQ\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_AIRPORT_RED], "assets/Red airport.png")) 
		std::cout << "Texture \"red airport\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BASE_RED], "assets/Red base.png")) 
		std::cout << "Texture \"red base\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CITY_RED], "assets/Red city.png"))
		std::cout << "Texture \"red city\" failed to load!\n";

	// Tiles
	spritesheet = new Tile * [NUM_TEXTURES];
	for (int i = 0; i < NUM_TEXTURES; ++i)
		spritesheet[i] = new Tile(0, 0, renderer, textures[i]);

	return window;
}

// Takes in a source string and renderer and saves the resulting texture to the address of a SDL_Texture**. Returns whether
// loading the texture was successful.
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src) {
	// Make surface
	SDL_Surface* surface = IMG_Load(src);
	if (surface == NULL) {
		printf("Source image for texture @ %s failed to load! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}

	// Turn that surface into a texture
	*tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL) {
		printf("Texture @ %s failed to initialize! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}
	SDL_FreeSurface(surface);

	return true;
}

// Called on termination to deallocate globals and close SDL
void close(SDL_Window* window) {

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (map[i][j] != NULL)
				delete map[i][j];
			if (spritesGround[i][j] != NULL)
				delete spritesGround[i][j];
			if (movTemp[i][j] != NULL)
				delete movTemp[i][j];
			if (demTiles[i][j] != NULL)
				delete demTiles[i][j];
		}
		delete[] map[i];
		delete[] spritesGround[i];
		delete[] movTemp[i];
		delete[] demTiles[i];
	}
	delete[] map;
	delete[] spritesGround;
	delete[] movTemp;
	delete[] demTiles;

	for (int i = 0; i < NUM_TERRAIN; ++i)
		delete terrainsheet[i];
	for (int i = 0; i < NUM_UNITS; ++i)
		delete unitsheet[i];
	delete[] terrainsheet;
	delete[] unitsheet;

	if (targets != NULL) {
		for (int i = 0; i < targetsSize; ++i)
			targets[i] = NULL;
		targetsSize = 0;
		delete[] targets;
	}

	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete spritesheet[i];
		SDL_DestroyTexture(textures[i]);
	}
	delete[] spritesheet;
	delete[] textures;

	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);

	TTF_CloseFont(Sans);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// Debug function
void whatClicked(int x, int y, int mouse){
	std::cout << "X position: " << x;
	std::cout << "Y position: " << y;
}

// Updates the key globals to match the current keystates. Used when a key is pressed.
void keyStatesDown(SDL_Keycode input){
	switch (input) {
	case SDLK_w:
		//std::cout << "W!";
		w = true;
		break;
	case SDLK_s:
		//std::cout << "S!";
		s = true;
		break;
	case SDLK_d:
		//std::cout << "D!";
		d = true;
		break;
	case SDLK_a:
		//std::cout << "A!";
		a = true;
		break;
	case SDLK_SPACE:
		//std::cout << "SPACE!";
		space = true;
		break;
	case SDLK_LSHIFT:
		//std::cout << "LEFT SHIFT!";
		shift = true;
		break;
	case SDLK_LCTRL:
		//std::cout << "LEFT CTRL!";
		ctrl = true;
		break;
	case SDLK_RETURN:
		std::cout << "Finish Turn!";
		enter = true;
		break;
	case SDLK_ESCAPE:
		isRunning = false;
		break;
	}
}

// Like keyStatesDown, but called when a key is released
void keyStatesUp(SDL_Keycode input) {
	switch (input) {
	case SDLK_w:
		//std::cout << "W!";
		w = false;
		break;
	case SDLK_s:
		//std::cout << "S!";
		s = false;
		break;
	case SDLK_d:
		//std::cout << "D!";
		d = false;
		break;
	case SDLK_a:
		//std::cout << "A!";
		a = false;
		break;
	case SDLK_SPACE:
		//std::cout << "SPACE!";
		space = false;
		break;
	case SDLK_LSHIFT:
		//std::cout << "LEFT SHIFT!";
		shift = false;
		break;
	case SDLK_LCTRL:
		//std::cout << "LEFT CTRL!";
		ctrl = false;
		break;
	}
}

// Creates two metaTiles (one for the old position, one for the new one) based on the current condition of the map and
// spritesGround arrays, as well as whether an effect or cursor should be applied. These metaTiles are then reRender()-ed.
void reLayer(int input[], char effect, char cursorType) {

	//std::cout << "Rendering a tile\n";

	//breakdown
	int x = input[0];
	int y = input[1];
	int xOld = input[2];
	int yOld = input[3];

	//metaTile
	metaTile* metaOne = new metaTile();
	metaOne->setX(x);
	metaOne->setY(y);

	//map layer 0 (terrain)
	metaOne->setLayer(0, spritesheet[map[x][y]->getType()]);

	//sprites layer 1 (units)
	if (spritesGround[x][y] != NULL)
		metaOne->setLayer(1, spritesheet[spritesGround[x][y]->getType()]);
	else
		metaOne->setLayer(1, spritesheet[T_NULL]);

	//effect layer 2 (shading)
	if (map[x][y]->getIsReachable())
		effect = 'r';
	switch (effect) {
		case NULL:
			metaOne->setLayer(2, spritesheet[T_NULL]);
			break;
		case 'r':
			metaOne->setLayer(2, spritesheet[T_BLUE]);
			break;
		case 'b':
			metaOne->setLayer(2, spritesheet[T_RED]);
			break;
	}
	

	//sprites layer 3 (cursor)
	switch (cursorType) {
		case 'c': //cursor
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_CURSOR_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_CURSOR_BLUE]);			
			break;
		case 's': //select Unit
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_SELECT_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_SELECT_BLUE]);			
			break;
		case 't': //target enemy
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_TARGET_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_TARGET_BLUE]);
			break;
		case NULL: //no cursor
			metaOne->setLayer(3, spritesheet[T_NULL]);
			break;
	}

	//sprites layer 4 (hp and team)
	if (spritesGround[x][y] != NULL) {
		int currentTeam = spritesGround[x][y]->getTeam();
		switch ((int)spritesGround[x][y]->getHP()) {
		case 20:
		case 19:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_20_RED : T_HP_20_BLUE]);
			break;
		case 18:
		case 17:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_18_RED : T_HP_18_BLUE]);
			break;
		case 16:
		case 15:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_16_RED : T_HP_16_BLUE]);
			break;
		case 14:
		case 13:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_14_RED : T_HP_14_BLUE]);
			break;
		case 12:
		case 11:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_12_RED : T_HP_12_BLUE]);
			break;
		case 10:
		case 9:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_10_RED : T_HP_10_BLUE]);
			break;
		case 8:
		case 7:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_8_RED : T_HP_8_BLUE]);
			break;
		case 6:
		case 5:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_6_RED : T_HP_6_BLUE]);
			break;
		case 4:
		case 3:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_4_RED : T_HP_4_BLUE]);
			break;
		case 2:
		case 1:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_2_RED : T_HP_2_BLUE]);
			break;
		}
	}
	else
		metaOne->setLayer(4, spritesheet[T_NULL]);


	metaTile* metaTwo = new metaTile();
	metaTwo->setX(xOld);
	metaTwo->setY(yOld);

	//Relayer Old tile
	if (xOld != -1 && yOld != -1) {

		//map layer 0 (terrain)
		metaTwo->setLayer(0, spritesheet[map[xOld][yOld]->getType()]);

		//sprites layer 1 (units)
		if (spritesGround[xOld][yOld] != NULL)
			metaTwo->setLayer(1, spritesheet[spritesGround[xOld][yOld]->getType()]);
		else
			metaTwo->setLayer(1, spritesheet[T_NULL]);
		
		//effect layer 2 (shading)
		if (map[xOld][yOld]->getIsReachable())
			effect = 'r';
		else
			effect = NULL;
		switch (effect) {
		case NULL:
			metaTwo->setLayer(2, spritesheet[T_NULL]);
			break;
		case 'b':
			metaTwo->setLayer(2, spritesheet[T_RED]);
			break;
		case 'r':
			metaTwo->setLayer(2, spritesheet[T_BLUE]);
			break;
		}

		//sprite layer 3 (cursor) -- for metaTwo, this is always null
		metaTwo->setLayer(3, spritesheet[T_NULL]);

		//sprites layer 4 (hp and team)
		if (spritesGround[xOld][yOld] != NULL) {
			int currentTeam = spritesGround[xOld][yOld]->getTeam();
			switch ((int)spritesGround[xOld][yOld]->getHP()) {
			case 20:
			case 19:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_20_RED : T_HP_20_BLUE]);
				break;
			case 18:
			case 17:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_18_RED : T_HP_18_BLUE]);
				break;
			case 16:
			case 15:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_16_RED : T_HP_16_BLUE]);
				break;
			case 14:
			case 13:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_14_RED : T_HP_14_BLUE]);
				break;
			case 12:
			case 11:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_12_RED : T_HP_12_BLUE]);
				break;
			case 10:
			case 9:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_10_RED : T_HP_10_BLUE]);
				break;
			case 8:
			case 7:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_8_RED : T_HP_8_BLUE]);
				break;
			case 6:
			case 5:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_6_RED : T_HP_6_BLUE]);
				break;
			case 4:
			case 3:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_4_RED : T_HP_4_BLUE]);
				break;
			case 2:
			case 1:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_2_RED : T_HP_2_BLUE]);
				break;
			}
		}
		else
			metaTwo->setLayer(4, spritesheet[T_NULL]);
			demTiles[xOld][yOld] = metaTwo;
	}

	demTiles[x][y] = metaOne;
		reRender(metaOne, metaTwo, false);

	return;
}

// Calls the render() method of each Tile in a metaTile in the correct order.
void reRender(metaTile* one, metaTile* two, bool skipSecond) {
	for (int i = 0; i < 5; i++) {
		Tile* pointerOne = one->getLayer(i);
		if (pointerOne != NULL) {
			pointerOne->setX(one->getX());
			pointerOne->setY(one->getY() - cameraY);
			if (!((one->getY() - cameraY) < 0))
				pointerOne->render();
		}

		if (skipSecond == false) {
			Tile* temp2 = two->getLayer(i);
			if (temp2 != NULL) {
				temp2->setX(two->getX());
				temp2->setY(two->getY() - cameraY);
				if (!((two->getY() - cameraY) < 0))
					temp2->render();
			}

			temp2 = NULL;
		}
		pointerOne = NULL;
		
	}

	return;
}

// Updates the coords[] array when up, down, left, or right is pressed
void setCoord(int x, int y, char dir) {
	switch (dir) {
	case 'w':
		coords[0] = x;
		coords[1] = y - 1;
		coords[2] = x;
		coords[3] = y;
		break;
	case 's':
		coords[0] = x;
		coords[1] = y + 1;
		coords[2] = x;
		coords[3] = y;
		break;
	case 'd':
		coords[0] = x + 1;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y;
		break;
	case 'a':
		coords[0] = x - 1;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y;
		break;
	return;
	}
}

void initTerrain() {

	/*
	enum TERRAIN_TYPE {
	GRASS = 0,
	BRIDGE = 1,
	MOUNTAIN = 2,
	WATER = 3,
	ROAD = 4,
	PORT = 5,
	HQ = 6,
	AIRPORT = 7,
	BASE = 8,
	CITY = 9,
	REEF = 10,
	TREE = 11,
	SHORE = 12,
	RIVER = 13,
	NUM_TERRAIN = 14,
	TERRAIN_ERROR = -1
	};
	*/

	terrainsheet = new Terrain * [NUM_TERRAIN];
	int tempMov1[] = { 1, 1, 1, 2, 1, 10 };
	terrainsheet[GRASS] = new Terrain(1, tempMov1, false, spritesheet[T_GRASS], T_GRASS);
	int tempMov2[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[BRIDGE] = new Terrain(0, tempMov2, false, spritesheet[T_BRIDGE], T_BRIDGE);
	int tempMov3[] = { 2, 1, 10, 10, 1, 10 };
	terrainsheet[MOUNTAIN] = new Terrain(4, tempMov3, false, spritesheet[T_MOUNTAIN], T_MOUNTAIN);
	int tempMov4[] = { 10, 10, 10, 10, 1, 1 };
	terrainsheet[WATER] = new Terrain(0, tempMov4, false, spritesheet[T_WATER], T_WATER);
	int tempMov5[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[ROAD] = new Terrain(0, tempMov5, false, spritesheet[T_ROAD], T_ROAD);
	int tempMov6[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[PORT] = new Terrain(3, tempMov6, true, spritesheet[T_PORT], T_PORT, 2);
	int tempMov7[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[HQ] = new Terrain(4, tempMov7, true, spritesheet[T_HQ], T_HQ, 2);
	int tempMov8[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[AIRPORT] = new Terrain(3, tempMov8, true, spritesheet[T_AIRPORT], T_AIRPORT, 2);
	int tempMov9[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[BASE] = new Terrain(3, tempMov9, true, spritesheet[T_BASE], T_BASE, 2);
	int tempMov10[] = { 1, 1, 1, 1, 1, 10 };
	terrainsheet[CITY] = new Terrain(3, tempMov10, true, spritesheet[T_CITY], T_CITY, 2);
	int tempMov11[] = { 10, 10, 10, 10, 1, 2 };
	terrainsheet[REEF] = new Terrain(1, tempMov11, false, spritesheet[T_REEF], T_REEF);
	int tempMov12[] = { 1, 1, 2, 3, 1, 10 };
	terrainsheet[TREE] = new Terrain(2, tempMov12, false, spritesheet[T_TREE], T_TREE);
	int tempMov13[] = { 1, 1, 1, 2, 1, 2 };
	terrainsheet[SHORE] = new Terrain(0, tempMov13, false, spritesheet[T_SHORE], T_SHORE);
	int tempMov14[] = { 2, 1, 10, 10, 1, 10 };
	terrainsheet[RIVER] = new Terrain(0, tempMov14, false, spritesheet[T_RIVER], T_RIVER);
	terrainsheet[PORT_RED] = new Terrain(3, tempMov6, true, spritesheet[T_PORT_RED], T_PORT_RED, 1); // 
	terrainsheet[HQ_RED] = new Terrain(4, tempMov7, true, spritesheet[T_HQ_RED], T_HQ_RED, 1);
	terrainsheet[AIRPORT_RED] = new Terrain(3, tempMov8, true, spritesheet[T_AIRPORT_RED], T_AIRPORT_RED, 1);
	terrainsheet[BASE_RED] = new Terrain(3, tempMov9, true, spritesheet[T_BASE_RED], T_BASE_RED, 1);
	terrainsheet[CITY_RED] = new Terrain(3, tempMov10, true, spritesheet[T_CITY_RED], T_CITY_RED, 1);
	terrainsheet[PORT_BLUE] = new Terrain(3, tempMov6, true, spritesheet[T_PORT_BLUE], T_PORT_BLUE, 0);
	terrainsheet[HQ_BLUE] = new Terrain(4, tempMov7, true, spritesheet[T_HQ_BLUE], T_HQ_BLUE, 0);
	terrainsheet[AIRPORT_BLUE] = new Terrain(3, tempMov8, true, spritesheet[T_AIRPORT_BLUE], T_AIRPORT_BLUE, 0);
	terrainsheet[BASE_BLUE] = new Terrain(3, tempMov9, true, spritesheet[T_BASE_BLUE], T_BASE_BLUE, 0);
	terrainsheet[CITY_BLUE] = new Terrain(3, tempMov10, true, spritesheet[T_CITY_BLUE], T_CITY_BLUE, 0);
	/*
	int temp1[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[GRASS] = new Terrain(0, temp1, false, spritesheet[T_GRASS], T_GRASS);
	int temp2[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[BRIDGE] = new Terrain(0, temp2, false, spritesheet[T_BRIDGE], T_BRIDGE);
	int temp3[] = { 3, 3, 3, 3, 3, 3 };
	terrainsheet[MOUNTAIN] = new Terrain(0, temp3, false, spritesheet[T_MOUNTAIN], T_MOUNTAIN);
	int temp4[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[WATER] = new Terrain(0, temp4, false, spritesheet[T_WATER], T_WATER);*/

	//for (int i = 0; i <= WATER; i++) {
	//	Tile tempTerrain;
	//	tempTerrain.setT(terrainsheet[i]->getType());  //defunct?
	//	tempTerrain.setSource(terrainsheet[i]->getType);
	//}

}
//void animateRender() {
//
//	for (int i = 0; i < animatedTiles.size(); i++) {
//		Tile animate = animatedTiles.at(i).getLayer(1);
//		int unit = animate.getT();
//		int x = animatedTiles.at(i).getX();
//		int y = animatedTiles.at(i).getY();
//
//		std::string finalTotal;
//		const char* base = setAsset(unit, false, true);
//		const char* type = ".png";
//		std::string tempAdd = std::to_string(frame);
//		const char* addon = tempAdd.c_str();
//
//		finalTotal.append(base);
//		finalTotal.append(addon);
//		finalTotal.append(type);
//
//		const char* full = finalTotal.c_str();
//
//
//}
//		animate.setSource(full);
//		demTiles[x][y].setLayer(1, animate);
//
//		if (frame < 4) {
//			frame++;
//		}
//		else {
//			frame = 1;
//		}
//
//		reRender(demTiles[x][y], nullMetaTile, 0, true);
//	}

void initUnit() {

	/*
	enum UNIT_TYPE {
		APC = 0,
		NUM_UNITS = 1,
		UNIT_ERROR = -1
	};
	*/

	unitsheet = new Unit * [NUM_UNITS];
	// Unit(x, y, texture, mov, minRange, maxRange, movType, cost, atk, display, team, name);
	double tempAtk1[] = { 1.0,0.5,0.5,0.5,0.0,0.5,0.5,0.5,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	// Can capture and load into anything
	unitsheet[INFANTRY]= new Unit(0, 0, T_INFANTRY, 3, 1, 1, FOOT, 1000, tempAtk1, spritesheet[T_INFANTRY], 0, INFANTRY);
	double tempAtk2[] = { 1.5,1.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.5,0.0,0.5,0.5,0.0,0.0,0.5,0.5,0.0,0.5,0.5 };
	// can capture and load into anything
	unitsheet[MECH] = new Unit(0, 0, T_MECH, 2, 1, 1, BOOTS, 3000, tempAtk2, spritesheet[T_MECH], 0, MECH);
	double tempAtk3[] = { 1.5,1.0,1.0,1.0,0.5,0.5,0.5,0.5,0.5,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	// can load into landers
	unitsheet[RECON] = new Unit(0, 0, T_RECON, 8, 1, 1, TIRES, 4000, tempAtk3, spritesheet[T_RECON], 0, RECON);
	double tempAtk4[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	// can load into landers and unload things
	unitsheet[APC] = new Unit(0, 0, T_APC, 6, 0, 0, TREADS, 3000, tempAtk4, spritesheet[T_APC], 0, APC);
	double tempAtk5[] = { 2.5,2.0,1.5,1.0,1.0,1.0,1.0,1.0,0.5,0.0,0.0,2.0,2.0,1.5,1.5,0.5,0.5,0.0,0.5,0.5 };
	// can load into landers
	unitsheet[ANTI_AIR] = new Unit(0, 0, T_ANTI_AIR, 6, 1, 1, TREADS, 8000, tempAtk5, spritesheet[T_ANTI_AIR], 0, ANTI_AIR);
	double tempAtk6[] = { 1.5,1.5,1.5,1.5,1.5,1.0,1.0,1.0,1.5,1.0,0.5,0.0,0.0,0.0,0.0,1.0,1.0,0.0,1.0,1.0 };
	// can load into landers
	unitsheet[ARTILLERY] = new Unit(0, 0, T_ARTILLERY, 5, 2, 3, TREADS, 6000, tempAtk6, spritesheet[T_ARTILLERY], 0, ARTILLERY);
	double tempAtk7[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 1.5, 1.5, 0.0, 0.0, 0.0, 0.0, 0.0};
	// can load into landers
	unitsheet[MISSILE] = new Unit(0, 0, T_MISSILE, 4, 3, 5, TIRES, 12000, tempAtk7, spritesheet[T_MISSILE], 0, MISSILE);
	double tempAtk8[] = { 2.0,2.0,2.0,2.0,2.0,1.5,1.5,1.5,2.0,1.5,1.0,0.0,0.0,0.0,0.0,1.5,1.5,0.5,1.5,1.5 };
	// can load into landers
	unitsheet[ROCKET] = new Unit(0, 0, T_ROCKET, 5, 3, 5, TIRES, 15000, tempAtk8, spritesheet[T_ROCKET], 0, ROCKET);
	double tempAtk9[] = { 1.5,1.0,1.5,1.0,1.5,1.0,1.0,1.0,1.0,0.5,0.0,0.5,0.5,0.0,0.0,0.5,0.5,0.0,0.5,0.5 };
	// can load into landers
	unitsheet[L_TANK] = new Unit(0, 0, T_L_TANK, 6, 1, 1, TREADS, 7000, tempAtk9, spritesheet[T_L_TANK], 0, L_TANK);
	double tempAtk10[] = { 2.0,1.5,2.0,1.5,2.0,1.5,1.5,1.5,1.5,1.0,0.5,1.0,1.0,0.0,0.0,1.0,1.0,0.0,1.0,1.0 };
	// can load into landers
	unitsheet[M_TANK] = new Unit(0, 0, T_M_TANK, 5, 1, 1, TREADS, 16000, tempAtk10, spritesheet[T_M_TANK], 0, M_TANK);
	double tempAtk11[] = { 2.5,2.0,2.5,2.0,2.5,2.0,2.0,2.0,2.0,1.5,1.0,1.5,1.5,0.0,0.0,1.5,1.5,0.5,1.5,1.5 };
	// can load into landers
	unitsheet[H_TANK] = new Unit(0, 0, T_H_TANK, 4, 1, 1, TREADS, 22000, tempAtk11, spritesheet[T_H_TANK], 0, H_TANK);
	double tempAtk12[] = { 1.5,1.0,1.0,1.0,0.5,1.0,1.0,1.0,1.0,0.5,0.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,1.0,1.0 };
	// can load into carriers
	unitsheet[B_COPTER] = new Unit(0, 0, T_B_COPTER, 6, 1, 1, AIR, 9000, tempAtk12, spritesheet[T_B_COPTER], 0, B_COPTER);
	double tempAtk13[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	// can load into carriers and unload things
	unitsheet[T_COPTER] = new Unit(0, 0, T_T_COPTER, 6, 0, 0, AIR, 5000, tempAtk13, spritesheet[T_T_COPTER], 0, T_COPTER);
	double tempAtk14[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,2.0,1.5,1.5,0.0,0.0,0.0,0.0,0.0 };
	// can load into carriers
	unitsheet[FIGHTER] = new Unit(0, 0, T_FIGHTER, 9, 1, 1, AIR, 20000, tempAtk14, spritesheet[T_FIGHTER], 0, FIGHTER);
	double tempAtk15[] = { 2.5,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,1.5,1.0,0.0,0.0,0.0,0.0,1.5,1.5,0.5,1.5,1.5 };
	// can load into carriers
	unitsheet[BOMBER] = new Unit(0, 0, T_BOMBER, 7, 1, 1, AIR, 22000, tempAtk15, spritesheet[T_BOMBER], 0, BOMBER);
	double tempAtk16[] = { 2.0, 2.0, 2.0, 2.0, 2.0, 1.5, 1.5, 1.5, 2.0, 1.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.5, 1.5, 0.5, 1.5, 1.5};
	// can do nothing
	unitsheet[BATTLESHIP] = new Unit(0, 0, T_BATTLESHIP, 5, 3, 5, SEA, 25000, tempAtk16, spritesheet[T_BATTLESHIP], 0, BATTLESHIP);
	double tempAtk17[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,2.0,1.5,1.5,0.0,0.0,1.5,0.0,0.0 };
	// can do nothing
	unitsheet[CRUISER] = new Unit(0, 0, T_CRUISER, 6, 1, 1, SEA, 18000, tempAtk17, spritesheet[T_CRUISER], 0, CRUISER);
	double tempAtk18[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,0.5,1.0,1.0,1.0 };
	// can do nothing
	unitsheet[SUB] = new Unit(0, 0, T_SUB, 5, 1, 1, SEA, 20000, tempAtk18, spritesheet[T_SUB], 0, SUB);
	double tempAtk19[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	// can unload things
	unitsheet[LANDER] = new Unit(0, 0, T_LANDER, 6, 0, 0, SEA, 12000, tempAtk19, spritesheet[T_LANDER], 0, LANDER);
	double tempAtk20[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,2.0,2.0,1.5,1.5,0.0,0.0,0.0,0.0,0.0 };
	// can unload things
	unitsheet[CARRIER] = new Unit(0, 0, T_CARRIER, 5, 3, 5, SEA, 25000, tempAtk20, spritesheet[T_CARRIER], 0, CARRIER);

}

void initMap(int i, int j, Terrain* t) {
	map[i][j] = new Terrain(t->getDef(), t->getMov(), t->getCanCapture(), t->getDisplay(), t->getType());
}

void initSpritesGround(int i, int j, Unit* u) {
	spritesGround[i][j] = new Unit(i, j, u->getType(), u->getMov(), u->getMinRange(), u->getMaxRange(), u->getMovType(), u->getCost(), u->getAttack(), u->getDisplay(), u->getTeam(), u->getName());
	spritesGround[i][j]->setCargo(0, u->getCargo(0));
	spritesGround[i][j]->setCargo(1, u->getCargo(1));
}

//temp debug -- initializes the map[] and spritesGround[] and movTemp[] arrays
void createMap() {

	for (int i = 0; i < MAP_TILE_W; i++) {
		for (int j = 0; j < MAP_TILE_H; j++) {
			if (mapNo == 0)
				initMap(i, j, terrainsheet[testMap1[i][j]]);
			else if (mapNo == 1)
				initMap(i, j, terrainsheet[testMap2[i][j]]);
			else if (mapNo == 2)
				initMap(i, j, terrainsheet[testMap3[i][j]]);
			else if (mapNo == 3)
				initMap(i, j, terrainsheet[testMap4[i][j]]);
			else if (mapNo == 4)
				initMap(i, j, terrainsheet[testMap5[i][j]]);
		}
	}
	
	// DEBUG
	/*for (int i = 0; i < NUM_UNITS/2; ++i)
		initSpritesGround(6+i, 5, unitsheet[i]);
	for (int i = NUM_UNITS/2; i < NUM_UNITS; ++i) 
		initSpritesGround(6+i-NUM_UNITS/2, 6, unitsheet[i]);*/
	//initSpritesGround(12, 3, unitsheet[APC]);
	//initSpritesGround(11, 2, unitsheet[APC]);

	//spritesGround[10][5]->setTeam(1);

	//add test units to animate render vector

	//Tile unit1;
	//unit1.setT(spritesGround[10][5]->getType);
	//unit1.setSource(T_APC);
	//unit1.setX(10);
	//unit1.setY(5);



	//animatedTiles.push_back();
}

void cameraMove(char direction) {
	int difference;

	switch (direction) {
	case 'w':
		difference = coords[1] - cameraY;
		if (difference < 1 && coords[1] >= 1) {
			cameraY--;
			for (int i = 0; i < MAP_TILE_W; ++i) {
				for (int j = 0; j < MAP_TILE_H; ++j) {
					if (j >= cameraY)
						reRender(demTiles[i][j], &nullMetaTile, true);
				}
			}
		}
		break;
	case 's':
		difference = coords[1] - cameraY;
		if (difference > 9 && coords[1] <= 18) {
			cameraY++;
			for (int i = 0; i < MAP_TILE_W; ++i) {
				for (int j = 0; j < MAP_TILE_H; ++j) {
					if (j >= cameraY)
						reRender(demTiles[i][j], &nullMetaTile, true);
				}
			}

		}
		break;
	}
}

void updateFunds() {

	int numCities = 0;

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (map[i][j]->getType() == ((turn % 2) ? T_CITY_RED : T_CITY_BLUE))
				++numCities;
		}
	}

	for (int i = 0; i < numCities; ++i)
		if (turn % 2)
			redFunds += 1000;
		else
			blueFunds += 1000;

	std::cout << redFunds << blueFunds;

}

void updateText() {
	//Blue team
	Blue_message.x = SCREEN_WIDTH / 10 * 7;  //controls the rect's x coordinate 
	Blue_message.y = SCREEN_HEIGHT * 7 / 10 + 50; // controls the rect's y coordinte
	Blue_message.w = 160; // controls the width of the rect
	Blue_message.h = 30;

	//Red team
	Red_message.x = SCREEN_WIDTH / 10 * 1;  //controls the rect's x coordinate 
	Red_message.y = SCREEN_HEIGHT * 7 / 10 + 50; // controls the rect's y coordinte
	Red_message.w = 160; // controls the width of the rect
	Red_message.h = 30;

	//End Message
	End_message.x = SCREEN_WIDTH / 2 - 100;
	End_message.y = SCREEN_HEIGHT / 2 - 50;
	End_message.w = 200;
	End_message.h = 100;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, ("Blue Funds: " + std::to_string(blueFunds)).c_str(), Blue); 
	SDL_Texture* Message_blue = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

	SDL_Surface* surfaceMessageR = TTF_RenderText_Solid(Sans, ("Red Funds: " + std::to_string(redFunds)).c_str(), Red);
	SDL_Texture* Message_red = SDL_CreateTextureFromSurface(renderer, surfaceMessageR);

	SDL_Surface* surfaceMessageE = TTF_RenderText_Solid(Sans, "END", ((winningTeam) ? Red : Blue));
	SDL_Texture* Message_end = SDL_CreateTextureFromSurface(renderer, surfaceMessageE);
	
	SDL_FreeSurface(surfaceMessage);
	SDL_FreeSurface(surfaceMessageR);
	SDL_FreeSurface(surfaceMessageE);

	SDL_RenderClear(renderer);
	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			reRender(demTiles[i][j], NULL, true);
	SDL_RenderCopy(renderer, Message_blue, NULL, &Blue_message);
	SDL_RenderCopy(renderer, Message_red, NULL, &Red_message);
	if (winningTeam != -1) {
		SDL_RenderCopy(renderer, Message_end, NULL, &End_message);
		gameOver = true;
	}

	SDL_DestroyTexture(Message_blue);
	SDL_DestroyTexture(Message_red);
	SDL_DestroyTexture(Message_end);

	//std::cout << "Text set!?\n";
}

TERRAIN_TYPE getNewCapture(TEXTURE t, int team) {

	if (team == 0) {
		switch (t) {
		case T_AIRPORT:
		case T_AIRPORT_RED:
			return AIRPORT_BLUE;
		case T_BASE:
		case T_BASE_RED:
			return BASE_BLUE;
		case T_PORT:
		case T_PORT_RED:
			return PORT_BLUE;
		case T_HQ:
		case T_HQ_RED:
			return HQ_BLUE;
		case T_CITY:
		case T_CITY_RED:
			return CITY_BLUE;
		}
	}
	else {
		switch (t) {
		case T_AIRPORT:
		case T_AIRPORT_BLUE:
			return AIRPORT_RED;
		case T_BASE:
		case T_BASE_BLUE:
			return BASE_RED;
		case T_PORT:
		case T_PORT_BLUE:
			return PORT_RED;
		case T_HQ:
		case T_HQ_BLUE:
			return HQ_RED;
		case T_CITY:
		case T_CITY_BLUE:
			return CITY_RED;
		}
	}

	return TERRAIN_ERROR;

}

int getNumUnits(int team) {

	int ret = 0;

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (spritesGround[i][j] != NULL && spritesGround[i][j]->getTeam() == team)
				ret++;
		}
	}
	
	return ret;

}
