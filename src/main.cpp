#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "queue.hpp"

struct Node
{
  bool isCurrent = false;
  int id;
  Vector2 screenPos = {0};
  Vector3 pos = {0};
  Vector3 scale = {1, 1, 1};
  Color color = RED;
  std::vector<Node*> connections;
};

struct InspectPanel
{

};

void init_nodes(std::vector<Node> &vector_of_nodes, int num_of_nodes)
{
  std::random_device dev;
  std::uniform_int_distribution<int> dist(-10, 10);

  for(int i = 0; i < num_of_nodes; i++)
  {
    Node node;
    node.id = i;
    node.pos.x = dist(dev);
    node.pos.y = dist(dev);
    node.pos.z = dist(dev);

    vector_of_nodes.push_back(node);
  }
}


int main() 
{
  std::vector<Node> nodes;
  init_nodes(nodes, 15);

  for(int i = 0; i < nodes.size(); i++)
  {
    std::cout << "node:" << nodes[i].id << "|x: " << 
      nodes[i].pos.x << "|y: " << 
      nodes[i].pos.y << "|z: " << 
      nodes[i].pos.z << "\n";
  }

  Camera3D camera = { 0 };
  camera.position = (Vector3){ 20.0f, 20.0f, 20.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;   

  const int wWidth = 800;
  const int wHeight = 640;

  InitWindow(wWidth, wHeight, "Grafos");

  DisableCursor(); 

  SetTargetFPS(60);

  while(!WindowShouldClose())
  {
    UpdateCamera(&camera, CAMERA_FREE);

    for(int i = 0; i < nodes.size();i++)
    {
      nodes[i].screenPos = GetWorldToScreen(Vector3{nodes[i].pos.x, nodes[i].pos.y + 2.5f, nodes[i].pos.z}, camera);
    }

    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode3D(camera);
    
        for(int i = 0; i < nodes.size();i++)
        {
          DrawCube(nodes[i].pos, nodes[i].scale.x, nodes[i].scale.x, nodes[i].scale.x, nodes[i].color);
        }

        DrawGrid(30, 1);

      EndMode3D();

     for(int i = 0; i < nodes.size();i++)
     {
      DrawText(TextFormat("ID: %i", nodes[i].id), 
          (int)nodes[i].screenPos.x - MeasureText("ID: XX", 10) / 2, 
          (int)nodes[i].screenPos.y,
          10, BLACK);

      if(nodes[i].isCurrent == false)
      {
        DrawText(TextFormat("SELECTED: %s", nodes[i].isCurrent ? "YES" : "NO"), 
          (int)nodes[i].screenPos.x - MeasureText("SELECTED: YES", 10) / 2, 
          (int)nodes[i].screenPos.y + 10.0f,
          10, GRAY);
      }
      else 
      {
        DrawText(TextFormat("SELECTED: %s", nodes[i].isCurrent ? "YES" : "NO"), 
          (int)nodes[i].screenPos.x - MeasureText("SELECTED: YES", 10) / 2, 
          (int)nodes[i].screenPos.y + 10.0f,
          10, GREEN);
      }
     }
     

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
