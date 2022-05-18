#include "Map.h"

bool Map::LoadImgBackGround(SDL_Renderer* screen)
{
    bool success = 1;
    for (int i = 0; i < BACKGROUND_LAYER; i++)
    {
        success = backGround[i].LoadImg(Layer[i].c_str(), screen);
        if (!success)
            return success;
    }
    return success;
}

bool Map::LoadImgGround(string file_path, SDL_Renderer* screen)
{
    bool success = 1;
    success = Ground.LoadImg(file_path, screen);
    return success;
}
//offSetSpeed: posX cua cac Layer
void Map::RenderScrollingBackground(vector <double>& offSetSpeed, SDL_Renderer* screen)
{
    vector<double> layerSpeed;
    layerSpeed.push_back(LAYER_1_SPEED);
    layerSpeed.push_back(LAYER_2_SPEED);
    layerSpeed.push_back(LAYER_3_SPEED);
    layerSpeed.push_back(LAYER_4_SPEED);
    layerSpeed.push_back(LAYER_5_SPEED);
    layerSpeed.push_back(LAYER_6_SPEED);
    layerSpeed.push_back(LAYER_7_SPEED);
    layerSpeed.push_back(LAYER_8_SPEED);

    for (int i = 0; i < BACKGROUND_LAYER; i++)
    {
        offSetSpeed[i] = offSetSpeed[i] - layerSpeed[i];
        if (offSetSpeed[i] < -backGround[i].GetWidth())
            offSetSpeed[i] = 0;
        backGround[i].Render(offSetSpeed[i], 0, screen);
        backGround[i].Render(offSetSpeed[i] + backGround[i].GetWidth(), 0, screen);
    }
}
//posX
void Map::RenderScrollingGround(int& speed, int& acceleration, SDL_Renderer* screen)
{
    speed = speed - (GROUND_SPEED + acceleration);
    if (speed < -Ground.GetWidth())
        speed = 0;
    Ground.Render(speed, 0, screen);
    Ground.Render(speed + Ground.GetWidth(), 0, screen);
    return;
}

void Map::Free()
{
    Ground.Free();
    for (int i = 0; i < BACKGROUND_LAYER; i++)
        backGround[i].Free();
}
