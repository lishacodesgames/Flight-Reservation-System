#include <raylib/raylib.h>

int main() {
  InitWindow(600, 600, "Buttons");
  SetTargetFPS(60);

  Texture2D background = LoadTexture("../graphics/bg.jpg");

  while(!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexture(background, 10, 10, WHITE);
    
    EndDrawing();
  }

  UnloadTexture(background);
  CloseWindow();
}