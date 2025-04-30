#include "window.h"
#include "texture-manager.h"
#include "camera.h"
#include "tilemap-manager.h"
#include "tilemap.h"
#include "animated-sprite.h"
#include "keycodes.h"
#include "unit.h"

int main(void) {
    Window* window = Window_Create(500, 200, 1024, 768, "SDL3 window");
    assert(window);

    TextureManager* textureManager = TextureManager_Create();
    assert(textureManager);
    TextureManager_LoadTexture(textureManager, "spritesheet", "basictiles.tga");
    TextureManager_LoadTexture(textureManager, "character", "character.tga");
    TextureManager_LoadTexture(textureManager, "hero1", "peopleA1.png");

    TilemapManager* tilemapManager = TilemapManager_Create();
    Tilemap* level1Tilemap = TilemapManager_AddTilemap(tilemapManager, "level1", 16, 16);
    Tilemap_LoadLayer(level1Tilemap, "level1_layer1.txt");
    Tilemap_LoadLayer(level1Tilemap, "level1_layer2.txt");
    Tilemap_LoadLayer(level1Tilemap, "level1_layer3.txt");
    Tilemap_LoadLayer(level1Tilemap, "level1_layer4.txt");
    Tilemap_SetTexture(level1Tilemap, TextureManager_GetTexture(textureManager, "spritesheet"));

    AnimatedSprite* character = AnimatedSprite_Create(TextureManager_GetTexture(textureManager, "character"), 16, 16);
    assert(character);
    AnimatedSprite_AddAnimation(character, "forward", 16, 16, 0, 4, 300);
    AnimatedSprite_SetActiveAnimation(character, "forward");

    AnimatedSprite* hero1 = AnimatedSprite_Create(TextureManager_GetTexture(textureManager, "hero1"), 32, 32);
    assert(hero1);
    AnimatedSprite_SetScale(hero1, 0.33f);
    AnimatedSprite_LoadAnimationsFromFile(hero1, "hero-animation.xml");
    AnimatedSprite_SetActiveAnimation(hero1, "left");

    Unit* player = Unit_CreateFromAnimatedSprite(&character, 1, 1);
    assert(player);

    Camera camera = Camera_Create(0, 0, 400, 400, 0, 4);
    Camera_Use(&camera);
    
    while (Window_IsOpen(window)) {
        if (IsKeyDown(KEYCODE_W)) {
            Camera_MovePosition(&camera, 0, -100 * GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_S)) {
            Camera_MovePosition(&camera, 0, 100 * GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_A)) {
            Camera_MovePosition(&camera, -100 * GetFrameTime(), 0);
        }

        if (IsKeyDown(KEYCODE_D)) {
            Camera_MovePosition(&camera, 100 * GetFrameTime(), 0);
        }

        Window_Clear(0, 0, 0);

        Tilemap_Draw(level1Tilemap);
        //DrawUnit(player, level1Tilemap);
        AnimatedSprite_Draw(hero1);

        Window_Display();

        AnimatedSprite_Update(hero1);
    }

    Unit_Destroy(player);
    AnimatedSprite_Destroy(hero1);
    TilemapManager_Destroy(tilemapManager);
    TextureManager_Destroy(textureManager);
    Window_Destroy(window);

    return 0;
}
