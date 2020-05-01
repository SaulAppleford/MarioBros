#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <iostream>
#include <string>

using namespace::std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Mix_Music* gMusic = NULL;

Uint32 gOldTime;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string);

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly.
	if(InitSDL())
	{
		//Set up game screen manager - Start on Menu
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);

		gOldTime = SDL_GetTicks();
		
		//Flag to check if we wish to quit.
		bool quit = false;

		LoadMusic("Music/Mario.mp3");

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}

		//Game Loop.
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	
	//Close window and free resources.
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initalise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Initialisation success. Attempt creation of window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//Check to see if window successfully created.
		if (gWindow == NULL)
		{
			//Nah :/
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			//Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initalised. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		//Initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initalise. Error: " << Mix_GetError();
			return false;
		}
	}

	return true;

}

void CloseSDL()
{
	//Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release music.
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	//Get the new time.
	Uint32 newTime = SDL_GetTicks();
	
	//Event Handler.
	SDL_Event e;

	//Get events from SDL.
	SDL_PollEvent(&e);

	//Handle any events.
	switch (e.type)
	{
		//Click 'X' to quit.
	case SDL_QUIT:
		return true;
	break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//Set current time to old time.
	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear the screen.
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//Update the screen.
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}