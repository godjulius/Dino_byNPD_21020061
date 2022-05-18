#include "Main.h"

int main(int argv, char** args)
{
    if (!Init())
        return 0;
    if (!LoadMedia())
        return 0;
    Mix_PlayMusic(gMenuMusic, -1);
    while (BackToMain)
    {
        PlayAgain = false;
        PlayerName = "";
        HandleMenu(PlayAgain, GameOption);
        HandleChoosePlayer(CharOption);
        LoadCharacter(CharOption);
        PlayerName = InputText(gEvent, gName, gMenuName, gNameFont, gScreen, gClickMusic);

        while (PlayAgain)
        {
            vector <double> offSetSpeedBackGround(BACKGROUND_LAYER, BASE_OFFSET_SPEED); // Khoi tao posX backGround
            acceleration = 0;
            countFrame = 0;
            int speed = GROUND_SPEED; // posX cua ground
            score = 0;
            highScore = GetHighScore();
            Star.Rebuild(STAR);
            Ground1.Rebuild(ON_GROUND_ENEMY);
            Ground2.Rebuild(ON_GROUND_ENEMY);
            Air1.Rebuild(IN_AIR_ENEMY);
            Air2.Rebuild(IN_AIR_ENEMY);

            srand((int)time(NULL));
            Mix_ResumeMusic();
            QuitGame = false;
            while (!QuitGame)
            {
                Fps.start();
                UpdateScore(score, acceleration, countFrame, GameOption);  // update diem, gia toc
                while (SDL_PollEvent(&gEvent) != 0)
                {
                    if (gEvent.type == SDL_QUIT)
                    {
                        QuitGame = true;
                        PlayAgain = false;
                        BackToMain = false;
                    }
                    HandlePauseButton(&gEvent, PauseButton, ContinueButton, gScreen, gClickMusic);                    
                    Dino.HandleButton(gEvent, gScreen, gJumpMusic);
                }
                SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR,
                    RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); // clear scr
                SDL_RenderClear(gScreen);
                MapData.RenderScrollingBackground(offSetSpeedBackGround, gScreen);
                MapData.RenderScrollingGround(speed, acceleration, gScreen);
                Dino.Show(gScreen);
                Ground1.Move(acceleration, 0, 0);
                Ground1.RenderEnemy(gScreen);
                Air1.Move(acceleration, 0, 0);
                Air1.RenderEnemy(gScreen);
                int Ground1_xBack = Air1.GetXBack();
                Star.Move(acceleration, Ground1_xBack, STAR);
                Star.RenderEnemy(gScreen);
                // Game mode
                if (GameOption == MEDIUM_OPTION || GameOption == HARD_OPTION)
                {
                    int xBack = Ground1.GetXBack();
                    if (Ground2.Move(acceleration, xBack, 1))
                        Ground2.RenderEnemy(gScreen);

                    if (GameOption == HARD_OPTION)
                    {
                        int xBack = Air1.GetXBack();
                        if (Air2.Move(acceleration, xBack, 1))
                            Air2.RenderEnemy(gScreen);
                    }
                }
                if (CheckCollisionItem(Ground1, Star) || CheckCollisionItem(Air1, Star) || CheckCollisionItem(Air2, Star) || CheckCollisionItem(Ground2, Star))
                    Star.Rebuild(STAR);
                
                DrawPlayScore(gTextScore, gScore, gFont, textColor, score, gScreen);
                DrawPlayerHighScore(gTextHighScore, gHighScore, gFont, textColor, highScore, gScreen);
                SDL_Rect* currenClip = &PauseButton.frameClip[PauseButton.status];
                PauseButton.RenderButton(gScreen);
                if (CheckCollision(Dino, Star))
                {
                    Mix_PauseMusic();
                    Mix_PlayChannel(MIX_CHANNEL, gEarnStarMusic, 0);
                    Mix_ResumeMusic();
                    Star.Rebuild(STAR);
                    score += 50;
                }
                if (CheckCollision(Dino, Air1) || CheckCollision(Dino, Ground1))
                {
                    Mix_PauseMusic();
                    Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                    Mix_ResumeMusic();
                    UpdateHighScore(PlayerName, score, highScore, GameOption);
                    QuitGame = 1;
                }
                if (GameOption == MEDIUM_OPTION)
                {
                    if (CheckCollision(Dino, Ground2))
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                        Mix_ResumeMusic();
                        UpdateHighScore(PlayerName, score, highScore, GameOption);
                        QuitGame = 1;
                    }
                    if (CheckCollision(Dino, Air2))
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                        Mix_ResumeMusic();
                        UpdateHighScore(PlayerName, score, highScore, GameOption);
                        QuitGame = 1;
                    }
                }
                else if (GameOption == HARD_OPTION)
                {
                    if (CheckCollision(Dino, Ground2))
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                        Mix_ResumeMusic();
                        UpdateHighScore(PlayerName, score, highScore, GameOption);
                        QuitGame = 1;
                    }
                    if (CheckCollision(Dino, Air2))
                    {
                        Mix_PauseMusic();
                        Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                        Mix_ResumeMusic();
                        UpdateHighScore(PlayerName, score, highScore, GameOption);
                        QuitGame = 1;
                    }
                }
                SDL_RenderPresent(gScreen);

                double realTime = Fps.getTick();
                double ms = (double)1000 / FRAME_PER_SECOND;
                if (realTime < ms)
                {
                    double delayTime = ms - realTime;
                    SDL_Delay(delayTime);
                }
                UpdateHighScore(PlayerName, score, highScore, UPDATE_HIGHT_SCORE_REAL_TIME);
            }
            DrawLoseGame(gTextBackToMenu, gLose, &gEvent, PlayAgain, BackToMain, gScreen);
        }
    }
    Close();
	return 0;
}

bool Init()
{
    int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);

    if (sdlInit < 0)
        return 0;

    gWindow = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
        return 0;

    gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gScreen == NULL)
        return 0;

    SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR,
        RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) && imgFlags))
        return 0;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        return 0;

    if (TTF_Init() == -1)
        return 0;

    return 1;
}

bool LoadMedia()
{
    if (!MapData.LoadImgGround("imgs/background/ground.png", gScreen))
        return 0;
    if (!MapData.LoadImgBackGround(gScreen))
        return 0;

    if (!Star.LoadImg(gScreen))
        return 0;

    if (!Ground1.LoadImg(gScreen))
        return 0;
    if (!Ground2.LoadImg(gScreen))
        return 0;

    if (Air1.LoadImg(gScreen))
        Air1.SetUpFrame();

    if (Air2.LoadImg(gScreen))
        Air2.SetUpFrame();

    if (!gLose.LoadImg("imgs/background/lose.png", gScreen))
        return 0;

    gMenuMusic = Mix_LoadMUS("sound/TheNights_Avicii.wav");
    if (gMenuMusic == nullptr)
        return 0;

    gClickMusic = Mix_LoadWAV("sound/mouse_click.wav");
    if (gClickMusic == nullptr)
        return 0;

    gJumpMusic = Mix_LoadWAV("sound/jump_sound.wav");
    if (gJumpMusic == nullptr)
        return 0;

    gEarnStarMusic = Mix_LoadWAV("sound/earn_star.wav");
    if (gEarnStarMusic == nullptr)
        return 0;

    gLoseMusic = Mix_LoadWAV("sound/lose_sound.wav");
    if (gLoseMusic == nullptr)
        return 0;

    gFont = TTF_OpenFont("font/pixel_font.ttf", SIZE_OF_PIXEL_FONT);
    if (gFont == nullptr)
        return 0;

    gNameFont = TTF_OpenFont("font/segoeui.ttf", SIZE_OF_SEGOEUI_FONT);
    if (gFont == nullptr)
        return 0;

    if (!EasyButton.LoadButton("imgs/button/easy.png", gScreen))
        return 0;
    EasyButton.SetUpFrame();

    if (!MediumButton.LoadButton("imgs/button/medium.png", gScreen))
        return 0;
    MediumButton.SetUpFrame();

    if (!HardButton.LoadButton("imgs/button/hard.png", gScreen))
        return 0;
    HardButton.SetUpFrame();

    if (!PlayButton.LoadButton("imgs/button/play_button.png", gScreen))
        return 0;
    PlayButton.SetUpFrame();

    if (!PauseButton.LoadButton("imgs/button/pause_button.png", gScreen))
        return 0;
    PauseButton.SetUpFrame();

    if (!ContinueButton.LoadButton("imgs/button/continue_button.png", gScreen))
        return 0;
    ContinueButton.SetUpFrame();

    if (!HelpButton.LoadButton("imgs/button/help_button.png", gScreen))
        return 0;
    HelpButton.SetUpFrame();

    if (!HighscoreButton.LoadButton("imgs/button/highscore_button.png", gScreen))
        return 0;
    HighscoreButton.SetUpFrame();

    if (!BackButton.LoadButton("imgs/button/back_button.png", gScreen))
        return 0;
    BackButton.SetUpFrame();

    if (!ExitButton.LoadButton("imgs/button/exit_button.png", gScreen))
        return 0;
    ExitButton.SetUpFrame();

    if (!gMenu.LoadImg("imgs/background/menuplus.png", gScreen))
        return 0;

    if (!gInstruction.LoadImg("imgs/background/instruction.png", gScreen))
        return 0;

    if (!gMenuChar.LoadImg("imgs/background/menuChar.png", gScreen))
        return 0;

    if (!gMenuName.LoadImg("imgs/background/menuName.png", gScreen))
        return 0;

    if (!gMenuHighScore.LoadImg("imgs/background/highscore.png", gScreen))
        return 0;

    if (!gTextScore.LoadText("Your Score: ", gFont, textColor, gScreen))
        return 0;
    if (!gTextBackToMenu.LoadText("B to back to Main Menu!", gFont, { 255,255,255 }, gScreen))
        return 0;
    if (!gTextHighScore.LoadText("High Score: ", gFont, textColor, gScreen))
        return 0;
    DinoBlue.status = ONE_SPIRTES;
    if (!DinoBlue.LoadButton("imgs/character/Blue.png", gScreen))
        return 0;

    DinoRed.status = ONE_SPIRTES;
    if (!DinoRed.LoadButton("imgs/character/Red.png", gScreen))
        return 0;

    DinoGreen.status = ONE_SPIRTES;
    if (!DinoGreen.LoadButton("imgs/character/Green.png", gScreen))
        return 0;

    DinoGold.status = ONE_SPIRTES;
    if (!DinoGold.LoadButton("imgs/character/Gold.png", gScreen))
        return 0;

    return 1;
}

void HandleMenu(bool& PlayAgain, int& GameOption)
{
    bool QuitMenu = false;
    bool QuitGame = false;
    while (!QuitMenu)
    {
        while (SDL_PollEvent(&gEvent) != 0)
        {
            if (gEvent.type == SDL_QUIT)
            {
                QuitGame = true;
            }
            HandlePlayButton(&gEvent, gMenu, PlayButton, EasyButton, MediumButton, HardButton, GameOption, QuitMenu, PlayAgain, gScreen, gClickMusic);
            if (QuitMenu)
                break;
            HandleHelpButton(&gEvent, HelpButton, BackButton, QuitGame, gInstruction, gScreen, gClickMusic);

            HandleHighScoreButton(&gEvent, HighscoreButton, BackButton, QuitGame, gMenuHighScore, gScreen, gClickMusic, gFont);

            HandleExitButton(&gEvent, ExitButton, QuitGame, gClickMusic);
        }
        if (QuitGame)
            exit(0);
        if (QuitMenu)
            break;
        gMenu.Render(gScreen);

        PlayButton.RenderButton(gScreen);
        HelpButton.RenderButton(gScreen);
        HighscoreButton.RenderButton(gScreen);
        ExitButton.RenderButton(gScreen);
        SDL_RenderPresent(gScreen);
    }
}

void HandleChoosePlayer(int& CharOption)
{
    bool choosePlayer = true;

    while (choosePlayer)
    {
        while (SDL_PollEvent(&gEvent) != 0)
        {
            gMenuChar.Render(gScreen);
            if (gEvent.type == SDL_QUIT)
                exit(0);

            if (DinoBlue.isInside(&gEvent))
            {
                if (gEvent.type == SDL_MOUSEMOTION)
                    DinoBlue.RenderButton(gScreen);
                if (gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                    DinoBlue.RenderButton(gScreen);
                    CharOption = BLUE_OPTION;
                    choosePlayer = false;
                }
            }

            if (DinoRed.isInside(&gEvent))
            {
                if (gEvent.type == SDL_MOUSEMOTION)
                    DinoRed.RenderButton(gScreen);
                if (gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                    DinoRed.RenderButton(gScreen);
                    CharOption = RED_OPTION;
                    choosePlayer = false;
                }
            }

            if (DinoGreen.isInside(&gEvent))
            {
                if (gEvent.type == SDL_MOUSEMOTION)
                    DinoGreen.RenderButton(gScreen);
                if (gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                    DinoGreen.RenderButton(gScreen);
                    CharOption = GREEN_OPTION;
                    choosePlayer = false;
                }
            }

            if (DinoGold.isInside(&gEvent))
            {
                if (gEvent.type == SDL_MOUSEMOTION)
                    DinoGold.RenderButton(gScreen);
                if (gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0);
                    DinoGold.RenderButton(gScreen);
                    CharOption = GOLD_OPTION;
                    choosePlayer = false;
                }
            }

            SDL_RenderPresent(gScreen);
        }
    }
}

void LoadCharacter(int CharOption)
{
    if (CharOption == BLUE_OPTION)
    {
        if (Dino.LoadImg("imgs/character/DinoBlue.png", gScreen))
            Dino.SetUpFrame();
    }
    if (CharOption == GREEN_OPTION)
    {
        if (Dino.LoadImg("imgs/character/DinoGreen.png", gScreen))
            Dino.SetUpFrame();
    }
    if (CharOption == RED_OPTION)
    {
        if (Dino.LoadImg("imgs/character/DinoRed.png", gScreen))
            Dino.SetUpFrame();
    }
    if (CharOption == GOLD_OPTION)
    {
        if (Dino.LoadImg("imgs/character/DinoGold.png", gScreen))
            Dino.SetUpFrame();
    }
}

void Close()
{
    TTF_CloseFont(gFont);
    TTF_CloseFont(gNameFont);

    PlayButton.Free();
    PauseButton.Free();
    ContinueButton.Free();
    HelpButton.Free();
    HighscoreButton.Free();
    BackButton.Free();
    ExitButton.Free();
    EasyButton.Free();
    MediumButton.Free();
    HardButton.Free();

    DinoBlue.Free();
    DinoGreen.Free();
    DinoRed.Free();
    DinoGold.Free();

    gInstruction.Free();
    gMenuChar.Free();
    gMenu.Free();
    gTextScore.Free();
    gScore.Free();
    gTextHighScore.Free();
    gHighScore.Free();
    gLose.Free();
    gMenuName.Free();
    gName.Free();
    gMenuHighScore.Free();

    Star.Free();
    Ground1.Free();
    Ground2.Free();
    Air1.Free();
    Air2.Free();

    Dino.Free();

    MapData.Free();

    Mix_FreeMusic(gMenuMusic);
    gMenuMusic = NULL;

    Mix_FreeChunk(gClickMusic);
    gClickMusic = NULL;

    Mix_FreeChunk(gJumpMusic);
    gJumpMusic = NULL;

    Mix_FreeChunk(gEarnStarMusic);
    gEarnStarMusic = NULL;

    Mix_FreeChunk(gLoseMusic);
    gLoseMusic = NULL;

    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}