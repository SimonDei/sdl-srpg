#include "window.h"
#include "texture-manager.h"
#include "camera.h"
#include "tilemap-manager.h"
#include "tilemap.h"
#include "animated-sprite.h"
#include "keycodes.h"
#include "unit.h"

int main(void) {
    Window* window = CreateWindow(500, 200, 1024, 768, "Allegro window");
    assert(window);

    TextureManager* textureManager = CreateTextureManager();
    assert(textureManager);
    LoadTexture(textureManager, "spritesheet", "basictiles.tga");
    LoadTexture(textureManager, "character", "character.tga");

    TilemapManager* tilemapManager = CreateTilemapManager();
    Tilemap* level1Tilemap = AddTilemap(tilemapManager, "level1", 16, 16);
    LoadTilemapLayer(level1Tilemap, "level1_layer1.txt");
    LoadTilemapLayer(level1Tilemap, "level1_layer2.txt");
    LoadTilemapLayer(level1Tilemap, "level1_layer3.txt");
    LoadTilemapLayer(level1Tilemap, "level1_layer4.txt");
    SetTilemapTexture(level1Tilemap, GetTexture(textureManager, "spritesheet"));

    AnimatedSprite* character = CreateAnimatedSprite(GetTexture(textureManager, "character"), 16, 16);
    assert(character);
    AddAnimatedSpriteAnimation(character, "forward", 0, 4, 300);
    SetActiveAnimatedSpriteAnimation(character, "forward");

    Unit* player = CreateUnitFromAnimatedSprite(&character, 1, 1);
    assert(player);

    Camera camera = CreateCamera(0, 0, 400, 400, 0, 4);
    UseCamera(&camera);
    
    while (IsWindowOpen(window)) {
        if (IsKeyDown(KEYCODE_W)) {
            MoveCameraPosition(&camera, 0, -100 * GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_S)) {
            MoveCameraPosition(&camera, 0, 100 * GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_A)) {
            MoveCameraPosition(&camera, -100 * GetFrameTime(), 0);
        }

        if (IsKeyDown(KEYCODE_D)) {
            MoveCameraPosition(&camera, 100 * GetFrameTime(), 0);
        }

        ClearWindow(0, 0, 0);

        DrawTilemap(level1Tilemap);
        DrawUnit(player, level1Tilemap);

        DisplayWindow();
    }

    DestroyUnit(player);
    DestroyTilemapManager(tilemapManager);
    DestroyTextureManager(textureManager);
    DestroyWindow(window);

    return 0;
}
