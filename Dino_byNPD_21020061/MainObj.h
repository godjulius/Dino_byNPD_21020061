#ifndef MAIN_OBJ_H
#define MAIN_OBJ_H
#include "BaseObj.h"
#include "CommonFunc.h"

class MainObject : BaseObject
{
private:

    double xPos, yPos;

    int widthFrame, heightFrame;

    SDL_Rect frameClip[CHARACTER_SPRITES];

    int frame, status;

public:

    MainObject();

    ~MainObject() { ; };

    bool LoadImg(string file_path, SDL_Renderer* screen);

    void SetUpFrame();

    void HandleButton(SDL_Event event, SDL_Renderer* screen, Mix_Chunk* gJumpMusic);

    void Show(SDL_Renderer* des);

    void Move();

    bool isOnGround() { return (yPos == GROUND); }

    int GetXPos() { return xPos; };

    int GetYPos() { return yPos; };

    int GetWidth_() { return widthFrame; };

    int GetHeight_() { return heightFrame; };

    int GetStatus() { return status; };

    void Free();

};

#endif
