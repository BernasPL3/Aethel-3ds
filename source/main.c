#include <3ds.h>
#include <citro2d.h>

int main()
{
    // Inicializa serviços do 3DS
    gfxInitDefault();
    romfsInit();
    C3D_Init();
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

    C2D_SceneBegin(C2D_BOTTOM);

    // Cria target de render
    C2D_Target* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    // Carrega textura do ROMFS
    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/assets/player.t3x");

    if (!sheet) {
        consoleInit(GFX_BOTTOM, NULL);
        printf("Erro ao carregar sprite!\n");
        while (1) gspWaitForVBlank();
    }

    C2D_Sprite spr;
    C2D_SpriteFromSheet(&spr, sheet, 0);

    float x = 100.0f;
    float y = 100.0f;

    while (aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START)
            break;

        // Movimento simples
        u32 kHeld = hidKeysHeld();

        if (kHeld & KEY_LEFT)  x -= 2;
        if (kHeld & KEY_RIGHT) x += 2;
        if (kHeld & KEY_UP)    y -= 2;
        if (kHeld & KEY_DOWN)  y += 2;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0, 0, 0, 255));
        C2D_SceneBegin(top);

        C2D_DrawSprite(&spr, x, y, 0.5f, 1.0f, 1.0f);

        C3D_FrameEnd(0);
    }

    // Cleanup
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    romfsExit();

    return 0;
}
