#ifndef FUNCTION_IN_MAIN_H
#define FUNCTION_IN_MAIN_H
#include "CommonFunc.h"
#include "BaseObj.h"
#include "MainObj.h"
#include "Map.h"
#include "Timer.h"
#include "EnemyObj.h"
#include "Button.h"

void HandlePlayButton(SDL_Event* e, BaseObject& gMenu,
    Button& PlayButton, Button& EasyButton,
    Button& MediumButton, Button& HardButton,
    int& GameOption, bool& QuitMenu,
    bool& PlayGame, SDL_Renderer* screen,
    Mix_Chunk* gClickMusic);

void HandleHelpButton(SDL_Event* e,
    Button& HelpButton, Button& BackButton,
    bool& QuitGame, BaseObject& gInstruction,
    SDL_Renderer* screen, Mix_Chunk* gClick);

void RenderHighScore(SDL_Renderer* screen, TTF_Font* gFont);

void HandleHighScoreButton(SDL_Event* e,
    Button& HighScoreButton, Button& BackButton,
    bool& QuitGame, BaseObject& gMenuHighScore,
    SDL_Renderer* screen, Mix_Chunk* gClickMusic, TTF_Font* gFont);

void HandleExitButton(SDL_Event* e, Button& ExitButton,
    bool& QuitGame, Mix_Chunk* gClickMusic);

string InputText(SDL_Event e,
    BaseObject& gName, BaseObject& gMenuName,
    TTF_Font* gNameFont, SDL_Renderer* screen,
    Mix_Chunk* gClickMusic);

int GetHighScore();

void UpdateScore(int& score, int& acceleration, int& countFrame, const int& GameOption);

void HandlePauseButton(SDL_Event* e,
    Button& PauseButton, Button& ContinueButton,
    SDL_Renderer* screen, Mix_Chunk* gClickMusic);

bool CheckCollision(MainObject& Dino, Enemy& Enem);

bool CheckCollisionItem(Enemy& Item, Enemy& Enem);

void DrawPlayScore(BaseObject& gTextScore, BaseObject& gScore,
    TTF_Font* gFont, SDL_Color& textColor,
    int& score, SDL_Renderer* screen);

void DrawPlayerHighScore(BaseObject& gTextHighScore, BaseObject& gHighScore,
    TTF_Font* gFont, SDL_Color& textColor,
    int& highscore, SDL_Renderer* screen);

void UpdateHighScore(string& curName, int& score, int& oldHighScore, int type);

void DrawLoseGame(BaseObject& gTextBackToMain, BaseObject& gLose, SDL_Event* e, bool& PlayAgain, bool& BackToMain, SDL_Renderer* screen);

#endif