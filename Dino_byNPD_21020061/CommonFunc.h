#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
static SDL_Window* gWindow;
static SDL_Renderer* gScreen;
static SDL_Event gEvent;

const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;
const int GROUND = 430; // yPos cua ground
const int SCREEN_BPP = 64;

const int RENDER_DRAW_COLOR = 255;

const int CHARACTER_SPRITES = 6;
const int ENEMY_SPRITES = 5;
const int JUMP = 64;
const int FALL = 204;
const int MAX_JUMP = 240;

const int BASE_OFFSET_SPEED = 0;
const int JUMP_POW = 18;
const int GRAVITY_FALL = 19;
const int GROUND_SPEED = 8;
const int MAX_ACCELERATION = 9;

const int ENEMY_SPEED = 8;
const int IN_AIR_ENEMY = 1;
const int ON_GROUND_ENEMY = 2;
const int STAR = 3;
const int ENEMY_RANGE = 240;
const int MIN_HEIGHT = 360;
const int MAX_HEIGHT = 330;
const int GRASS_HEIGHT = 8;

const int MIX_CHANNEL = -1;

const int BUTTON_SPRITES = 2;
const int BUTTON_MOUSE_DOWN = 0;
const int BUTTON_MOUSE_UP = 1;
const int ONE_SPIRTES = 3;
const int SMALL_BUTTON = 1;
const int COMMON_BUTTON = 2;

const int SIZE_OF_PIXEL_FONT = 36;
const int SIZE_OF_SEGOEUI_FONT = 55;
const int NUMBER_RANK = 7;

const int PLAY_BUTON_POSX = 390;
const int PLAY_BUTTON_POSY = 180;
const int HELP_BUTTON_POSX = 315;
const int HELP_BUTTON_POSY = 290;
const int HIGH_SCORE_BUTTON_POSX = 465;
const int HIGH_SOCRE_BUTTON_POSY = 290;
const int EXIT_BUTTON_POSX = 390;
const int EXIT_BUTTON_POSY = 400;
const int BACK_BUTTON_POSX = 15;
const int BACK_BUTTON_POSY = 15;
const int PAUSE_BUTTON_POSX = 30;
const int PAUSE_BUTTON_POSY = 30;
const int CONTINUE_BUTTON_POSX = 30;
const int CONTINUE_BUTTON_POSY = 30;

const int EASY_BUTON_POSX = 389;
const int EASY_BUTTON_POSY = 180;
const int MEDIUM_BUTTON_POSX = 389;
const int MEDIUM_BUTTON_POSY = 290;
const int HARD_BUTTON_POSX = 389;
const int HARD_BUTTON_POSY = 400;

const int GREEN_DINO_POSX = 145;
const int GREEN_DINO_POSY = 312;
const int BLUE_DINO_POSX = 315;
const int BLUE_DINO_POSY = 312;
const int GOLD_DINO_POSX = 486;
const int GOLD_DINO_POSY = 312;
const int RED_DINO_POSX = 655;
const int RED_DINO_POSY = 312;

const int EASY_OPTION = 1;
const int MEDIUM_OPTION = 2;
const int HARD_OPTION = 3;

const int BLUE_OPTION = 1;
const int RED_OPTION = 2;
const int GOLD_OPTION = 3;
const int GREEN_OPTION = 4;

const int TEXT_SCORE_X = 630;
const int TEXT_SCORE_Y = 20;
const int TEXT_HIGH_SCORE_X = 630;
const int TEXT_HIGH_SCORE_Y = 80;
const int SCORE_X = 830;
const int SCORE_Y = 20;
const int HIGH_SCORE_X = 830;
const int HIGH_SCORE_Y = 80;
const int UPDATE_HIGHT_SCORE_REAL_TIME = 0;

const string GAME_NAME = "Dino Jump";
const double LAYER_1_SPEED = 0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.50;
const double LAYER_8_SPEED = 1.75;
const int BACKGROUND_LAYER = 8;
const string Layer[BACKGROUND_LAYER] = {
	"imgs/background/sky.png",
	"imgs/background/clouds_1.png",
	"imgs/background/rocks.png",
	"imgs/background/clouds_2.png",
	"imgs/background/ground_1.png",
	"imgs/background/ground_2.png",
	"imgs/background/ground_3.png",
	"imgs/background/plant.png",
};

#endif