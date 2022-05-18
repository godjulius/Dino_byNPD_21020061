#include "MainObj.h"

MainObject::MainObject()
{
    xPos = (double)SCREEN_WIDTH / 3;
    yPos = (double)GROUND;
    widthFrame = heightFrame = 0;
    frame = 0;
    status = 0;
    return;
}
bool MainObject::LoadImg(string file_path, SDL_Renderer* screen)
{
    bool Character = BaseObject::LoadImg(file_path, screen);
    if (Character)
    {
        widthFrame = bRect.w / CHARACTER_SPRITES; // load frame dau tien cua anh
        heightFrame = bRect.h;
    }
    return Character;
}
// setup rect{x,y,w,h} cho cac frame
void MainObject::SetUpFrame()
{
    frameClip[0].w = widthFrame;
    frameClip[0].h = heightFrame;
    for (int i = 1; i < CHARACTER_SPRITES; i++)
    {
        frameClip[i].x = frameClip[i - 1].x + widthFrame;
        frameClip[i].y = 0;
        frameClip[i].w = widthFrame;
        frameClip[i].h = heightFrame;
    }
}
void MainObject::Move()
{
    if (status == JUMP && yPos >= (double)MAX_JUMP)
        yPos -= (double)JUMP_POW;
    else if (yPos <= (double)MAX_JUMP)
        status = FALL;
    if (status == FALL && yPos <= (double)GROUND)
    {
        yPos += GRAVITY_FALL;
        yPos = min(yPos, (double)GROUND); //##
    }
    if (isOnGround()) status = 0;
}
// hien thi object ra man hinh
void MainObject::Show(SDL_Renderer* Destination)
{
    Move();
    if (isOnGround())
    {
        frame++;
    }
    else
        frame = 0;
    if (frame >= CHARACTER_SPRITES) frame = 0;
    bRect.x = xPos;
    bRect.y = yPos;
    SDL_Rect* currentClip = &frameClip[frame];
    SDL_Rect renderQuad = { bRect.x, bRect.y, widthFrame, heightFrame };
    SDL_RenderCopy(Destination, bTexture, currentClip, &renderQuad);
}

void MainObject::HandleButton(SDL_Event gEvent, SDL_Renderer* screen, Mix_Chunk* gJumpMusic)
{
    if (gEvent.type == SDL_KEYDOWN && gEvent.key.repeat == 0)
    {
        if (gEvent.key.keysym.sym == SDLK_UP || gEvent.key.keysym.sym == SDLK_SPACE)
        {
            if (isOnGround())
            {
                Mix_PlayChannel(MIX_CHANNEL, gJumpMusic, 0);
                status = JUMP;
                return;
            }
        }
        else if (gEvent.key.keysym.sym = SDLK_DOWN)
        {
            status = FALL;
        }
    }
    return;
}

void MainObject::Free()
{
    BaseObject::Free();
}