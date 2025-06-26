
## Overview

### Generic

#### Enums:

- Inputs (INP_DOWN,
INP_RIGHT,
INP_LEFT,
INP_UP,
INP_CONFIRM,
INP_RETURN)
- DirectionEnum (DIR_DOWN,
DIR_RIGHT,
DIR_LEFT,
DIR_UP)

#### Vectors

- Vector2: int x, int y
- Vector2u: unsigned x, unsigned y

#### Controller
Class that handles inputs

Methods:
Controller(std::shared_ptr<Player> player) - Constructor with player init
Controller () - Constructor without player init

init (std::shared_ptr<Player> player) - For late init, if the latter constructor was used

input(Inputs in) - Handles inputs, moves player accordingly

### Grafics (I know it's a typo, just ignore it)

#### Graphics.h
Contains declarations for: 
SPRITESIZE, SCALE - Used in Sprite Rendering
HEIGHT, WIDTH - Used for window creation


#### Pixels.h 
Deprecated, but is kept for the lulz

#### Sprite.h
Wrapper for SDL_Texture

##### Fields
  int h, w; (get)
  Vector2 scale; (get, set)
  Vector2 pos; (get, set)
Used for rendering

  const char* path;
  SDL_Texture* texture;
The texture and the file path, mostly for internal use

##### Methods

 Sprite(){} - default constructor
 Sprite(const char* spritePath, SDL_Renderer* renderer) - creates sprite from path
 Sprite(SDL_Texture* spriteTexture, int spriteWidth, int spriteHeight) - creates Sprite from Texture

 void init(const char* spritePath, SDL_Renderer* renderer) - For late init

 void render(SDL_Renderer* renderer) - renders, parametres(scale, pos) must be set before rendering

#### SpritePath.h
Use SpritePath::get_sprite_path() for easy access to the Sprite folder and that OOP Vibe

#### Spritesheet.h
Wrapper for Sprite

Allows to get multiple sprites from a single file/texture/surface
Sheet must always be square

All the same methods and fields as Sprite, except:
unsigned sprite (get, set);
Used to mark the needed sprite
Indexes go like so:
0 1 2
3 4 5
6 7 8

### Overworld

#### Tiles

##### Tile.h
Litteraly just Sprite, needs to be put down

##### TileGrid.h
Grid for all the tiles, base for the other Grid
Always a Square

###### Fields
Vector2 basePos = Vector2(); (get, set) - the top-left corner of the grid 
Vector2 scale = Vector2(1,1); (get, set) - scale 
unsigned size - Side of the Grid Square

std::vector<Tile> tileSet; - Tiles used in the Grid
std::shared_ptr<std::shared_ptr<unsigned[]>[]> grid; - matrix of the TileIds, Filled with 0 during init

###### Methods

TileGrid(){} - default constructor
TileGrid(unsigned gridSize, std::vector<Tile> tiles, Vector2 posVec = Vector2()) - constructor with instant init

init (unsigned gridSize, std::vector<Tile> tiles, Vector2 posVec = Vector2()) - for late init

get/set_tile() - for editing the matrix manually (plz dont use)

void render(SDL_Renderer* renderer) - i think we can guess what this does

bool is_inbounds(Vector2u pos) checks if pos is on the grid
