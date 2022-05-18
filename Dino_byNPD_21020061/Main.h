#ifndef MAIN_H
#define MAIN_H
#include "CommonFunc.h"
#include "BaseObj.h"
#include "MainObj.h"
#include "Map.h"
#include "Timer.h"
#include "EnemyObj.h"
#include "Button.h"
#include "FuncInMain.h"
Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button HighscoreButton(HIGH_SCORE_BUTTON_POSX, HIGH_SOCRE_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button EasyButton(EASY_BUTON_POSX, EASY_BUTTON_POSY);
Button MediumButton(MEDIUM_BUTTON_POSX, MEDIUM_BUTTON_POSY);
Button HardButton(HARD_BUTTON_POSX, HARD_BUTTON_POSY);

TTF_Font* gFont = nullptr;
TTF_Font* gNameFont = nullptr;

Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClickMusic = nullptr;
Mix_Chunk* gJumpMusic = nullptr;
Mix_Chunk* gLoseMusic = nullptr;
Mix_Chunk* gEarnStarMusic = nullptr;

BaseObject gInstruction;
BaseObject gMenuChar;
static BaseObject gMenu;
BaseObject gTextBackToMenu;
BaseObject gTextScore;
BaseObject gScore;
BaseObject gTextHighScore;
BaseObject gHighScore;
BaseObject gLose;
BaseObject gMenuName;
BaseObject gName;
BaseObject gMenuHighScore;

Button DinoBlue(BLUE_DINO_POSX, BLUE_DINO_POSY);
Button DinoGreen(GREEN_DINO_POSX, GREEN_DINO_POSY);
Button DinoRed(RED_DINO_POSX, RED_DINO_POSY);
Button DinoGold(GOLD_DINO_POSX, GOLD_DINO_POSY);

Enemy Ground1(ON_GROUND_ENEMY);
Enemy Ground2(ON_GROUND_ENEMY);
Enemy Air1(IN_AIR_ENEMY);
Enemy Air2(IN_AIR_ENEMY);
Enemy Star(STAR);
MainObject Dino;

Map MapData;

Timer Fps;

SDL_Color textColor = { 255, 255, 255 };

bool BackToMain = true;
string PlayerName = "";
bool PlayAgain = false;
int GameOption = EASY_OPTION;
int CharOption = BLUE_OPTION;
bool QuitGame;
int acceleration;
int countFrame;
int speed;
int score;
int highScore;


bool Init();

bool LoadMedia();

void HandleMenu(bool& PlayAgain, int& GameOption);

void HandleChoosePlayer(int& CharOption);

void LoadCharacter(int CharOption);

void Close();


#endif