#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

#define HEIGHT 320*2
#define WIDTH 640

#define spPath "C:\\Users\\studentcoll\\source\\repos\\rpg\\sdl_rpg\\x64\\Debug\\tastSprite.bmp"
 

struct Sprite
{
    SDL_Texture* sprite;
    int width;
    int height;
};

static Sprite sp;


//Code from stackoverflow
//Slightly modified
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

//Also Stackoverflow https://stackoverflow.com/questions/20070155/how-to-set-a-pixel-in-a-sdl-surface
//Slightly modified
void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    Uint32* const target_pixel = (Uint32*)((Uint8*)surface->pixels
        + y * surface->pitch
        + x * SDL_BYTESPERPIXEL(surface->format));
    *target_pixel = pixel;
}

// Failure
//void clear_bg(SDL_Texture* texture, SDL_Surface* surf)
//{
//
//    Uint32* pix = nullptr;
//    int pitch = 0;
//
//    SDL_PixelFormat format = texture->format;
//
//    float w, h;
//    SDL_GetTextureSize(texture, &w, &h);
//
//
//    if (!SDL_LockTexture(texture, nullptr, (void**)pix, &pitch))
//    {
//        SDL_Log("The Cock Was Not Locked: %s", SDL_GetError());
//        return;
//    }
//
//    for (int y = 0; y <= h; y++)
//    {
//        for (int x = 0; x <= w; x++)
//        {
//            Uint32 pos = getpixel(surf, x, y);
//            std::cout << pos << std::endl;
//        }
//    }
//
//
//}

void clear_surface(SDL_Surface* surf)
{
    Uint32* pix = (Uint32*)surf->pixels;
    Uint32 col = SDL_MapRGBA(
        SDL_GetPixelFormatDetails(surf->format), 
        SDL_GetSurfacePalette(surf),
        0, 0, 0, 0);

    Uint32 white = SDL_MapRGB(SDL_GetPixelFormatDetails(surf->format), NULL,
        255, 
        255, 
        255);

    for (int h = 0; h < surf->h; h++)
    {
        for (int w = 0; w < surf->h; w++)
        {
            if (getpixel(surf, w, h) == white)
            { 
            set_pixel(surf, w, h, col);
               }
            

        }
    }

}

SDL_Texture* get_clear_texture(SDL_Renderer* renderer, SDL_Surface* surf)
{
    //clear_surface(surf);

    SDL_SetSurfaceColorKey(surf, true,
        SDL_MapRGB(
            SDL_GetPixelFormatDetails(surf->format),
            SDL_GetSurfacePalette(surf),
            255, 255, 255
        )
    );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    


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
    if (!SDL_CreateWindowAndRenderer("Texture Test", WIDTH, HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //surface
    SDL_Log(SDL_GetBasePath());
    SDL_asprintf(&bmp_path, spPath);
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


    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, std::rand(), std::rand(), std::rand(), 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i <=10; i++)
    {
        SDL_FRect rect;
        rect.x = 16*i;
        rect.y = 16*i;
        rect.w = (float)sp.width;
        rect.h = (float)sp.height;
        SDL_SetRenderScale(renderer, std::rand() %20, std::rand()%20);
        SDL_RenderTexture(renderer, sp.sprite, NULL, &rect);
    }

    SDL_Delay(std::rand() % 200);

    SDL_SetWindowSize(window, std::rand()%1000, std::rand()%1000);
    SDL_SetWindowPosition(window, std::rand() % 1000, std::rand() % 1000);


    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}
