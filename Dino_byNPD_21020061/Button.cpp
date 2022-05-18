#include "Button.h"

Button::Button(int x, int y)
{
	posX = x;
	posY = y;
	status = BUTTON_MOUSE_UP;
}

void Button::SetXY(int x, int y)
{
	posX = x;
	posY = y;
}

bool Button::LoadButton(string file_path, SDL_Renderer* screen)
{
	bool succes = BaseObject::LoadImg(file_path.c_str(), screen);
	if (status == ONE_SPIRTES)
		buttonWidth = bRect.w;
	else
		buttonWidth = bRect.w / 2;
	buttonHeight = bRect.h;
	return succes;
}

void Button::SetUpFrame()
{
	frameClip[0].w = buttonWidth;
	frameClip[0].h = buttonHeight;
	for (int i = 1; i < BUTTON_SPRITES; i++)
	{
		frameClip[i].x = frameClip[i - 1].x + buttonWidth;
		frameClip[i].y = 0;
		frameClip[i].w = buttonWidth;
		frameClip[i].h = buttonHeight;
	}
}

bool Button::isInside(SDL_Event* e)
{
	int currentX, currentY;
	bool isinside = true;
	if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&currentX, &currentY);
		if (currentX < posX)
			isinside = false;
		else if (currentX > posX + buttonWidth)
			isinside = false;
		else if (currentY < posY)
			isinside = false;
		else if (currentY > posY + buttonHeight)
			isinside = false;
		return isinside;
	}
	return isinside;
}

void Button::RenderButton(SDL_Renderer* screen)
{
	if (status == ONE_SPIRTES)
	{
		BaseObject::Render(posX, posY, screen);
		return;
	}
	SDL_Rect* clip = &frameClip[status];
	BaseObject::Render(posX, posY, screen, clip);
}

void Button::Free()
{
	BaseObject::Free();
}