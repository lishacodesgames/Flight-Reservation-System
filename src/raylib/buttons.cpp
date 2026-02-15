#include <raylib/raylib.h>

int main() {
  InitWindow(600, 600, "Buttons");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(PINK);
    
    EndDrawing();
  }

  CloseWindow();
}