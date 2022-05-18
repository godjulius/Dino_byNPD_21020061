#ifndef MAP_H
#define MAP_H
#include "BaseObj.h"
#include "CommonFunc.h"

class Map : BaseObject
{
private:

	BaseObject backGround[BACKGROUND_LAYER];
	BaseObject Ground;

public:

	Map() {};
	~Map() {};

	bool LoadImgBackGround(SDL_Renderer* screen);

	bool LoadImgGround(string file_path, SDL_Renderer* screen);

	void RenderScrollingBackground(vector <double>& offSetSpeed, SDL_Renderer* screen);

	void RenderScrollingGround(int& speed, int& acceleration, SDL_Renderer* screen);

	void Free();
};

#endif