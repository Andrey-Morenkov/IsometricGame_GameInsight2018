#pragma once

// ---------- Main Settings ----------
#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720

#define MAP_WIDTH_TILES 30
#define MAP_HEIGHT_TILES 30

//#define FLAG_WITHOUT_LOGS

#define MAX_FPS 30
#define TICKRATE 100
// ---------- /Main Settings ----------

// ---------- Texture Files Settings ----------
#define TILE_SIZE_IN_PIXELS 32
#define TILE_TEXTURE_PATH "../MyGame/Textures/map_tiles.png"
#define MOUSE_TEXTURE_PATH "../MyGame/Textures/mouse_tiles.png"
#define WALL_TEXTURE_PATH "../MyGame/Textures/wall_tiles.png"
#define PLAYER_TEXTURE_PATH "../MyGame/Textures/player_tiles.png"

#define TILE_TEXTURE_HEIGHT_IN_PIXELS (TILE_SIZE_IN_PIXELS-1)
#define TILE_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS * 2)

#define WALL_TEXTURE_HEIGHT_IN_PIXELS 100
#define WALL_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS)

#define MOUSE_TEXTURE_HEIGHT_IN_PIXELS TILE_TEXTURE_HEIGHT_IN_PIXELS
#define MOUSE_TEXTURE_WIDTH_IN_PIXELS TILE_TEXTURE_WIDTH_IN_PIXELS

#define PLAYER_TEXTURE_HEIGHT_IN_PIXELS 102
#define PLAYER_TEXTURE_WIDTH_IN_PIXELS 70
// ---------- /Texture Files Settings ----------