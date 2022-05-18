#ifndef BUTTON_H
#define BUTTON_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Button : BaseObject
{
private:

	int buttonWidth, buttonHeight;
	int posX, posY;

public:

	Button(int x, int y);

	~Button() {};

	void SetXY(int x, int y);

	void SetUpFrame();

	bool LoadButton(string file_path, SDL_Renderer* screen);

	void RenderButton(SDL_Renderer* screen);

	void Free();

	bool isInside(SDL_Event* e);

	int status;
	SDL_Rect frameClip[BUTTON_SPRITES];

};

#endif