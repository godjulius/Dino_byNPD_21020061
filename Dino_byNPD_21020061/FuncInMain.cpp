#include "FuncInMain.h"

void HandlePlayButton(SDL_Event* e, BaseObject& gMenu,
    Button& PlayButton, Button& EasyButton,
    Button& MediumButton, Button& HardButton,
    int& GameOption, bool& QuitMenu,
    bool& PlayGame, SDL_Renderer* screen,
    Mix_Chunk* gClickMusic)
{

    if (PlayButton.isInside(e))
    {
        if (e->type == SDL_MOUSEMOTION)
            PlayButton.status = BUTTON_MOUSE_DOWN;
        else if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
            PlayButton.status = BUTTON_MOUSE_DOWN;
            bool QuitOption = false;
            while (!QuitOption)
            {
                while (SDL_PollEvent(e) != 0)
                {
                    if (e->type == SDL_QUIT)
                        exit(0);
                    if (EasyButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                            EasyButton.status = BUTTON_MOUSE_DOWN;
                        else if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            EasyButton.status = BUTTON_MOUSE_DOWN;
                            QuitOption = true;
                            QuitMenu = true;
                            GameOption = EASY_OPTION;
                        }
                    }
                    else
                        EasyButton.status = BUTTON_MOUSE_UP;

                    if (MediumButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                            MediumButton.status = BUTTON_MOUSE_DOWN;
                        else if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            MediumButton.status = BUTTON_MOUSE_DOWN;
                            QuitOption = true;
                            QuitMenu = true;
                            GameOption = MEDIUM_OPTION;
                        }
                    }
                    else
                        MediumButton.status = BUTTON_MOUSE_UP;

                    if (HardButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                            HardButton.status = BUTTON_MOUSE_DOWN;
                        else if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            HardButton.status = BUTTON_MOUSE_DOWN;
                            QuitOption = true;
                            QuitMenu = true;
                            GameOption = HARD_OPTION;
                        }
                    }
                    else
                        HardButton.status = BUTTON_MOUSE_UP;

                    gMenu.Render(0, 0, screen);

                    EasyButton.RenderButton(screen);

                    MediumButton.RenderButton(screen);

                    HardButton.RenderButton(screen);

                    SDL_RenderPresent(screen);
                }
            }
            PlayGame = true;
        }
    }
    else
        PlayButton.status = BUTTON_MOUSE_UP;
}
void HandleHelpButton(SDL_Event* e,
    Button& HelpButton, Button& BackButton,
    bool& QuitGame, BaseObject& gInstruction,
    SDL_Renderer* screen, Mix_Chunk* gClickMusic)
{

    if (HelpButton.isInside(e))
    {
        if (e->type == SDL_MOUSEMOTION)
            HelpButton.status = BUTTON_MOUSE_DOWN;
        else if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
            HelpButton.status = BUTTON_MOUSE_DOWN;

            bool backMenu = false;
            while (!backMenu)
            {
                gInstruction.Render(0, 0, screen);

                BackButton.RenderButton(screen);

                SDL_RenderPresent(screen);
                while (SDL_PollEvent(e) != 0)
                {
                    if (e->type == SDL_QUIT)
                    {
                        backMenu = true;
                        QuitGame = true;
                    }
                    else if (BackButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                        {
                            BackButton.status = BUTTON_MOUSE_DOWN;
                        }
                        else if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            BackButton.status = BUTTON_MOUSE_DOWN;
                            backMenu = true;
                        }
                    }
                    else
                    {
                        BackButton.status = BUTTON_MOUSE_UP;
                    }
                    

                }
            }
        }
    }
    else
    {
        HelpButton.status = BUTTON_MOUSE_UP;
    }
}

void RenderHighScore(SDL_Renderer* screen, TTF_Font* gFont)
{
    ifstream ip("highscore.txt", ifstream::in);

    int HEIGHT_COLUMN = 48;
    int MID_ROW = 200;
    int SECOND_COLUMN_POSX = 300;
    int THIRD_COLUMN_POSX = 640;
    SDL_Color textColorName = { 255, 255, 255, 255 };
    BaseObject gNameList, gScoreList;

    int cnt = NUMBER_RANK;

    string HighScore;
    string name;

    int xName = SECOND_COLUMN_POSX;
    int yName = 175;
    int xScore = THIRD_COLUMN_POSX;
    int yScore = 175;

    while (cnt--)
    {
        ip >> name >> HighScore;

        xName = SECOND_COLUMN_POSX + MID_ROW - (name.size() * SIZE_OF_PIXEL_FONT) / 2;
        xScore = THIRD_COLUMN_POSX + 50 - (HighScore.size() * SIZE_OF_PIXEL_FONT) / 2;


        gNameList.LoadText(name, gFont, textColorName, screen);
        gScoreList.LoadText(HighScore, gFont, textColorName, screen);
        gNameList.Render(xName, yName, screen);
        gScoreList.Render(xScore, yScore, screen);

        yName += HEIGHT_COLUMN;
        yScore += HEIGHT_COLUMN;

    }
    SDL_RenderPresent(gScreen);
    gNameList.Free();
    gScoreList.Free();
    ip.close();
}

void HandleHighScoreButton(SDL_Event* e,
    Button& HighScoreButton, Button& BackButton,
    bool& QuitGame, BaseObject& gMenuHighScore,
    SDL_Renderer* screen, Mix_Chunk* gClickMusic, TTF_Font* gFont)
{
    if (HighScoreButton.isInside(e))
    {
        if (e->type == SDL_MOUSEMOTION)
            HighScoreButton.status = BUTTON_MOUSE_DOWN;
        else if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
            HighScoreButton.status = BUTTON_MOUSE_DOWN;

            bool backMenu = false;
            while (!backMenu)
            {
                while (SDL_PollEvent(e) != 0)
                {
                    if (e->type == SDL_QUIT)
                    {
                        exit(0);
                        backMenu = true;
                        QuitGame = true;
                    }
                    else if (BackButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                        {
                            BackButton.status = BUTTON_MOUSE_DOWN;
                        }
                        else if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            BackButton.status = BUTTON_MOUSE_DOWN;
                            backMenu = true;
                        }
                    }
                    else
                    {
                        BackButton.status = BUTTON_MOUSE_UP;
                    }
                    gMenuHighScore.Render(0, 0, screen);

                    RenderHighScore(screen, gFont);

                    BackButton.RenderButton(screen);

                    SDL_RenderPresent(screen);

                }
            }
        }
    }
    else
        HighScoreButton.status = BUTTON_MOUSE_UP;
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& QuitGame, Mix_Chunk* gClickMusic)
{
    if (ExitButton.isInside(e))
    {
        if (e->type == SDL_MOUSEMOTION)
            ExitButton.status = BUTTON_MOUSE_DOWN;
        else if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
            ExitButton.status = BUTTON_MOUSE_DOWN;
            QuitGame = true;
        }
    }
    else
        ExitButton.status = BUTTON_MOUSE_UP;
}

string InputText(SDL_Event e,
    BaseObject& gName, BaseObject& gMenuName,
    TTF_Font* gNameFont, SDL_Renderer* screen,
    Mix_Chunk* gClickMusic)
{
    bool quit = false;
    SDL_Color textColorName = { 0, 0, 0, 0 };
    string inputText = "";
    gName.LoadText(inputText, gNameFont, textColorName, screen); // khong nhap gi
    SDL_StartTextInput();

    while (!quit)
    {
        bool renderText = false;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                exit(0);
            if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) // Enter
                quit = true;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                    inputText.pop_back();
                    renderText = true;
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {               
                Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                inputText += e.text.text;
                renderText = true;
            }
        }

        gMenuName.Render(screen);
        if (renderText)
        {
            if (inputText != "")
                gName.LoadText(inputText.c_str(), gNameFont, textColorName, screen);
            else
                gName.LoadText(" ", gNameFont, textColorName, screen); // tranh TH nhap roi xoa het bi loi
        }

        gName.Render(182, 304, screen);
        SDL_RenderPresent(screen);
    }
    return inputText;
}

int GetHighScore()
{
    ifstream infile("highscore.txt", ifstream::in);

    string name;
    int HighScore;
    infile >> name >> HighScore;
    infile.close();
    if (name == "")
        return 0;
    return HighScore;
}

void UpdateScore(int& score, int& acceleration, int& countFrame, const int& GameOption)
{
    const int updateAccelerationTime = 8;
    const int updateScorePerFrame = 5; // Score update every 5 frames
    if (countFrame == updateAccelerationTime * FRAME_PER_SECOND)
    {
        acceleration += GameOption; 
    }
    if (countFrame > updateAccelerationTime * FRAME_PER_SECOND) countFrame = 0;
    if (countFrame % updateScorePerFrame == 0)
        score += GameOption;
    countFrame++;
    if (acceleration >= MAX_ACCELERATION)
        acceleration = 0;
}

void HandlePauseButton(SDL_Event* e,
    Button& PauseButton, Button& ContinueButton,
    SDL_Renderer* screen, Mix_Chunk* gClickMusic)
{
    if (PauseButton.isInside(e))
    {
        if (e->type == SDL_MOUSEMOTION)
            PauseButton.status = BUTTON_MOUSE_DOWN;
        else if (e->type == SDL_MOUSEBUTTONDOWN)
        {
            PauseButton.status = BUTTON_MOUSE_DOWN;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
            //Mix_PauseMusic();
            bool continueGame = false;
            while (!continueGame)
            {
                while (SDL_PollEvent(e) != 0)
                {
                    if (e->type == SDL_QUIT)
                        exit(0);
                    if (ContinueButton.isInside(e))
                    {
                        if (e->type == SDL_MOUSEMOTION)
                            ContinueButton.status = BUTTON_MOUSE_DOWN;
                        if (e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                            Mix_ResumeMusic();
                            ContinueButton.status = BUTTON_MOUSE_DOWN;
                            continueGame = true;
                        }
                    }
                    else
                        ContinueButton.status = BUTTON_MOUSE_UP;

                    ContinueButton.RenderButton(screen);
                    SDL_RenderPresent(screen);
                }
            }
        }
    }
    else
        PauseButton.status = BUTTON_MOUSE_UP;
}

bool CheckCollision(MainObject& Dino, Enemy& Enem)
{
    bool check = false;
    SDL_Rect DinoChar = { Dino.GetXPos() + 15, Dino.GetYPos() + 15, Dino.GetWidth_() - 25, Dino.GetHeight_() - 35 };
    SDL_Rect Enemy = { Enem.GetXPos() + 10, Enem.GetYPos() + 10 , Enem.GetWidth_() - 15 , Enem.GetHeight_() - 15 };
    check = SDL_HasIntersection(&DinoChar, &Enemy);
    return check;
}

bool CheckCollisionItem(Enemy& Item, Enemy& Enem)
{
    bool check = false;
    SDL_Rect ItemRect = { Item.GetXPos(), Item.GetYPos(), Item.GetWidth_() + 15, Item.GetHeight_() + 15 };
    SDL_Rect Enemy = { Enem.GetXPos(), Enem.GetYPos(), Enem.GetWidth_() + 15, Enem.GetHeight_() + 15 };
    check = SDL_HasIntersection(&ItemRect, &Enemy);
    return check;
}

void DrawPlayScore(BaseObject& gTextScore, BaseObject& gScore,
    TTF_Font* gFont, SDL_Color& textColor,
    int& score, SDL_Renderer* screen)
{
    gTextScore.Render(TEXT_SCORE_X, TEXT_SCORE_Y, screen);
    if (gScore.LoadText(to_string(score), gFont, textColor, screen))
        gScore.Render(SCORE_X, SCORE_Y, screen);
    gScore.Free();
}

void DrawPlayerHighScore(BaseObject& gTextHighScore, BaseObject& gHighScore,
    TTF_Font* gFont, SDL_Color& textColor,
    int& highScore, SDL_Renderer* screen)
{
    gTextHighScore.Render(TEXT_HIGH_SCORE_X, TEXT_HIGH_SCORE_Y, screen);
    if (gHighScore.LoadText(to_string(highScore), gFont, textColor, screen))
        gHighScore.Render(HIGH_SCORE_X, HIGH_SCORE_Y, screen);
    gHighScore.Free();
}

void UpdateHighScore(string& curName, int& score, int& oldHighScore, int type)
{
    ifstream ip("highscore.txt", ifstream::in);

    string name;
    int HighScore;
    int cnt = NUMBER_RANK;
    vector<pair<int, string>> gList;

    while (cnt--)
    {
        ip >> name >> HighScore;
        gList.push_back({ HighScore, name });
    }
    gList.push_back({ score, curName });
    sort(gList.begin(), gList.end(), greater< pair<int, string> >());
    ip.close();

    if (score == gList[0].first)
        oldHighScore = score;

    if (type == EASY_OPTION || type == MEDIUM_OPTION || type == HARD_OPTION)
    {
        ofstream op("highscore.txt", ofstream::out);
        cnt = 0;
        while (cnt < NUMBER_RANK)
        {
            if (gList[cnt].first >= 0)
                op << gList[cnt].second << " " << gList[cnt].first << "\n";
            else
                op << "Invalid" << ' ' << 0 << '\n';
            cnt++;
        }
        op.close();
    }
}

void DrawLoseGame(BaseObject& gTextBackToMain, BaseObject& gLose, SDL_Event* e, bool& PlayAgain, bool& BackToMain, SDL_Renderer* screen)
{
    bool EndGame = false;

    if (!PlayAgain) return;
    while (!EndGame)
    {
        while (SDL_PollEvent(e) != 0)
        {
            if (e->type == SDL_QUIT)
            {
                BackToMain = false;
                exit(0);
            }
            if (e->type == SDL_KEYDOWN)
            {
                switch (e->key.keysym.sym)
                {
                case SDLK_SPACE:
                    EndGame = true;
                    BackToMain = false;
                    PlayAgain = true;
                    break;
                case SDLK_ESCAPE:
                    EndGame = true;
                    PlayAgain = false;
                    BackToMain = false;
                    break;
                case SDLK_b:
                    EndGame = true;
                    PlayAgain = false;
                    BackToMain = true;
                    break;
                case SDLK_UP:
                    EndGame = true;
                    BackToMain = false;
                    PlayAgain = true;
                }
            }
        }
        gLose.Render(screen);
        gTextBackToMain.Render(260, 280, screen);
        SDL_RenderPresent(screen);
    }
}