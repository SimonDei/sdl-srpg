#include "window.h"
#include "texture-manager.h"
#include "camera.h"
#include "gui.h"
#include "keycodes.h"
#include "sprite.h"
#include "texture.h"

int main(void) {
    Window* window = Window_Create(500, 200, 1600, 900, "SFML window");
    assert(window);

    Camera* camera = Camera_Create(0, 0, 1600, 900, 0);
    assert(camera);
    Camera_Use(camera);

    TextureManager* textureManager = TextureManager_Create();
    assert(textureManager);
    TextureManager_LoadTexture(textureManager, "guiBg", "gui/gui_bg.png");
    TextureManager_LoadTexture(textureManager, "guiFg", "gui/gui_fg.png");
    TextureManager_LoadTexture(textureManager, "ahri", "Ahri.tga");

    Sprite* ahri = Sprite_Create(TextureManager_GetTexture(textureManager, "ahri"), 100, 100);
    assert(ahri);

    Gui* gui = Gui_Create();
    assert(gui);

    const Texture* pHudBg = TextureManager_GetTexture(textureManager, "guiBg");
    GuiElement* hudBg = GuiImage_Create(pHudBg, 0, (FLOAT)Window_GetHeight() - pHudBg->fHeight);
    assert(hudBg);
    Gui_AddElement(gui, hudBg);

    const Texture* pHudFg = TextureManager_GetTexture(textureManager, "guiFg");
    GuiElement* hudFg = GuiImage_Create(pHudFg, 0, (FLOAT)Window_GetHeight() - pHudFg->fHeight);
    assert(hudFg);
    Gui_AddElement(gui, hudFg);

    while (Window_IsOpen(window)) {
        if (IsKeyDown(KEYCODE_W)) {
            Camera_MovePosition(camera, 0.0f, -0.2f * (FLOAT)GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_S)) {
            Camera_MovePosition(camera, 0.0f, 0.2f * (FLOAT)GetFrameTime());
        }

        if (IsKeyDown(KEYCODE_A)) {
            Camera_MovePosition(camera, -0.2f * (FLOAT)GetFrameTime(), 0.0f);
        }

        if (IsKeyDown(KEYCODE_D)) {
            Camera_MovePosition(camera, 0.2f * (FLOAT)GetFrameTime(), 0.0f);
        }

        Window_Clear(0, 0, 0);

        Sprite_Draw(ahri);

        Camera_Use(NULL);
        Gui_Draw(gui);

        Camera_Use(camera);

        Window_Display();
    }

    Sprite_Destroy(ahri);
    TextureManager_Destroy(textureManager);
    Camera_Destroy(camera);
    Gui_Destroy(gui);
    Window_Destroy(window);

    return 0;
}
