#include <iostream>
#include <raylib.h>

int main() 
{
  const int wWidth = 800;
  const int wHeight = 640;
  std::cout << "hello world!" << std::endl;

  InitWindow(wWidth, wHeight, "Grafos");

  SetTargetFPS(60);

  while(!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Test", 190, 200, 100, BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
