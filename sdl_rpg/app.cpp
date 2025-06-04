/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;



#define WHEIGHT 600
#define WWIDTH 800


struct Sprite
{
    SDL_Texture* sprite;
    int width;
    int height;
};

static Sprite sp;


Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = SDL_BYTESPERPIXEL(surface->format);
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


void clear_bg(SDL_Texture* texture, SDL_Surface* surf)
{

    Uint32* pix = nullptr;
    int pitch = 0;

    SDL_PixelFormat format = texture->format;

    float w, h;
    SDL_GetTextureSize(texture, &w, &h);


    if (!SDL_LockTexture(texture, nullptr, (void**)pix, &pitch))
    {
        SDL_Log("The Cock Was Not Locked: %s", SDL_GetError());
        return;
    }

    for (int y = 0; y <= h; y++)
    {
        for (int x = 0; x <= w; x++)
        {
            Uint32 pos = getpixel(surf, x, y);
            std::cout << pos << std::endl;
        }
    }


}

SDL_Texture* get_clear_texture(SDL_Renderer* renderer, SDL_Surface* surf)
{
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    


    clear_bg(texture, surf);


    return texture;

}








/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{

    SDL_Surface* surface = NULL;
    char* bmp_path = NULL;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Texture Test", WWIDTH, WHEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //surface
    SDL_Log(SDL_GetBasePath());
    SDL_asprintf(&bmp_path, "D:\\!ShoolSchit\\Projects\\RPGGAME\\sdl_rpg\\x64\\Debug\\testSprite1.bmp");
    surface = SDL_LoadBMP(bmp_path);

    if (!surface) {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_free(bmp_path);

    sp.height = surface->h;
    sp.width = surface->w;

    //sprite
    sp.sprite = get_clear_texture(renderer, surface);
    
    if (!sp.sprite) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}


/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}




/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    SDL_FRect rect;





    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    SDL_RenderClear(renderer);


    rect.x = (100.0f );
    rect.y = 100.0f ;
    rect.w = (float)sp.width;
    rect.h = (float)sp.height;
    SDL_SetRenderScale(renderer, 3, 3);
    SDL_RenderTexture(renderer, sp.sprite, NULL, &rect);




    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}
