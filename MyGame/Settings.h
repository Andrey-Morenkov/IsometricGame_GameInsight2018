#pragma once

// ---------- Main Settings ----------
#define MAIN_WINDOW_WIDTH 1280
#define MAIN_WINDOW_HEIGHT 720

#define MAP_WIDTH_TILES 30
#define MAP_HEIGHT_TILES 30

//#define FLAG_WITHOUT_LOGS

#define TICKRATE 120
#define UPDATE_INPUT_RATE 50
#define TICKS_IN_SECOND 1000.0
// ---------- /Main Settings ----------

// ---------- Game Settings ----------
#define MAX_FPS 30
#define WORLD_SCROLL_SPEED 20
#define ALLOW_DIAGONAL_MOVEMENT true
// ---------- /Game Settings ----------

// ---------- Texture Files Settings ----------
#define TILE_SIZE_IN_PIXELS 32

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

#define DEAD_SCREEN_HIIGHT_IN_PIXELS 126
#define DEAD_SCREEN_WIDTH_IN_PIXELS 566

#define SUCCESSFUL_SCREEN_HIIGHT_IN_PIXELS DEAD_SCREEN_HIIGHT_IN_PIXELS
#define SUCCESSFUL_SCREEN_WIDTH_IN_PIXELS DEAD_SCREEN_WIDTH_IN_PIXELS

#define TILE_TEXTURE_HEIGHT_IN_PIXELS (TILE_SIZE_IN_PIXELS - 1)
#define TILE_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS * 2)

#define MOUSE_TEXTURE_HEIGHT_IN_PIXELS TILE_TEXTURE_HEIGHT_IN_PIXELS
#define MOUSE_TEXTURE_WIDTH_IN_PIXELS TILE_TEXTURE_WIDTH_IN_PIXELS

#define WALL_TEXTURE_HEIGHT_IN_PIXELS (100)
#define WALL_TEXTURE_WIDTH_IN_PIXELS (TILE_SIZE_IN_PIXELS)

#define PLAYER_TEXTURE_HEIGHT_IN_PIXELS (102)
#define PLAYER_TEXTURE_WIDTH_IN_PIXELS (70)

#define BARRIER_TEXTURE_HEIGHT_IN_PIXELS TILE_TEXTURE_HEIGHT_IN_PIXELS
#define BARRIER_TEXTURE_WIDTH_IN_PIXELS TILE_TEXTURE_WIDTH_IN_PIXELS


// ---------- /Texture Files Settings ----------