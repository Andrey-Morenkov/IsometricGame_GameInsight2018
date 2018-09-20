#pragma once
#include "Coordinate2D.h"

#define MAP_LEFT_DOWN_CORNER Coordinate2D(0, MAP_WIDTH_TILES - 1) /*don't touch*/
#define MAP_RIGHT_UP_CORNER Coordinate2D(MAP_HEIGHT_TILES - 1, 0) /*don't touch*/

// ---------- Main Settings ----------
#define MAIN_WINDOW_WIDTH 1280            /*changeable*/
#define MAIN_WINDOW_HEIGHT 720	          /*changeable*/

#define MAP_WIDTH_TILES 30				  /*changeable*/
#define MAP_HEIGHT_TILES 30			      /*changeable*/

//#define FLAG_WITHOUT_LOGS

#define MAX_FPS 30					      /*changeable*/
#define TICKRATE 120				      /*changeable*/
#define UPDATE_INPUT_RATE 50		      /*changeable*/
#define TICKS_PER_SECOND 1000.0		      /*don't touch*/
// ---------- /Main Settings ----------

// ---------- Game Settings ----------
#define WORLD_SCROLL_SPEED 20                /*changeable*/
#define IS_ALLOW_DIAGONAL_MOVEMENT true      /*changeable*/
#define MAP_START_POINT MAP_LEFT_DOWN_CORNER /*changeable*/
#define MAP_FINISH_POINT MAP_RIGHT_UP_CORNER /*changeable*/
#define PLAYER_SPEED 0.2                     /*changeable, less is faster*/
#define NPC_SPEED 0.5                        /*changeable, less is faster*/
#define FIREBALL_SPEED 0.1                   /*changeable, less is faster*/
#define CANNON_SHOTS_PER_MIN 20              /*changeable, less is faster*/
// ---------- /Game Settings ----------

// ---------- Texture Files Settings ---------- /*DON'T TOUCH ANYTHING*/
#define TILE_SIZE_IN_PIXELS (32)

#define TILE_TEXTURE_PATH "../MyGame/Textures/map_tiles.png"
#define MOUSE_TEXTURE_PATH "../MyGame/Textures/mouse_tiles.png"
#define WALL_TEXTURE_PATH "../MyGame/Textures/wall_tiles.png"
#define PLAYER_TEXTURE_PATH "../MyGame/Textures/player_tiles.png"
#define BARRIER_TEXTURE_PATH "../MyGame/Textures/barrier_tiles.png"
#define NPC_TEXTURE_PATH "../MyGame/Textures/npc_tiles.png"
#define CANNON_TEXTURE_PATH "../MyGame/Textures/cannon_tiles.png"
#define FIREBALL_TEXTURE_PATH "../MyGame/Textures/fireball_tiles.png"
#define SUCCESSFUL_SCREEN_TEXTURE_PATH "../MyGame/Textures/success.png"
#define DEAD_SCREEN_TEXTURE_PATH "../MyGame/Textures/dead.png"

#define DEAD_SCREEN_HIIGHT_IN_PIXELS (126)
#define DEAD_SCREEN_WIDTH_IN_PIXELS (566)

#define SUCCESSFUL_SCREEN_HIIGHT_IN_PIXELS (DEAD_SCREEN_HIIGHT_IN_PIXELS)
#define SUCCESSFUL_SCREEN_WIDTH_IN_PIXELS (DEAD_SCREEN_WIDTH_IN_PIXELS)

#define TILE_TEXTURE_HEIGHT_IN_PIXELS (TILE_SIZE_IN_PIXELS - 1)
#define TILE_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS * 2)

#define MOUSE_TEXTURE_HEIGHT_IN_PIXELS (TILE_TEXTURE_HEIGHT_IN_PIXELS)
#define MOUSE_TEXTURE_WIDTH_IN_PIXELS (TILE_TEXTURE_WIDTH_IN_PIXELS)

#define WALL_TEXTURE_HEIGHT_IN_PIXELS (100)
#define WALL_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS)

#define PLAYER_TEXTURE_HEIGHT_IN_PIXELS (102)
#define PLAYER_TEXTURE_WIDTH_IN_PIXELS (70)

#define NPC_TEXTURE_HEIGHT_IN_PIXELS (PLAYER_TEXTURE_HEIGHT_IN_PIXELS)
#define NPC_TEXTURE_WIDTH_IN_PIXELS (PLAYER_TEXTURE_WIDTH_IN_PIXELS)

#define BARRIER_TEXTURE_HEIGHT_IN_PIXELS (TILE_TEXTURE_HEIGHT_IN_PIXELS)
#define BARRIER_TEXTURE_WIDTH_IN_PIXELS (TILE_TEXTURE_WIDTH_IN_PIXELS)

#define CANNON_TEXTURE_HEIGHT_IN_PIXELS (WALL_TEXTURE_HEIGHT_IN_PIXELS)
#define CANNON_TEXTURE_WIDTH_IN_PIXELS (WALL_TEXTURE_WIDTH_IN_PIXELS)

#define FIREBALL_TEXTURE_HEIGHT_IN_PIXELS (116)
#define FIREBALL_TEXTURE_WIDTH_IN_PIXELS (TILE_TEXTURE_WIDTH_IN_PIXELS)
// ---------- /Texture Files Settings ----------