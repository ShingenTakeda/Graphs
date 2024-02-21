#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <raylib.h>

#include "queue.hpp"

struct Node
{
  int id;
  Vector3 pos = {0};
  Vector3 scale = {1, 1, 1};
  Color color = RED;
  std::vector<Node*> connections;
};

void init_nodes(std::vector<Node> &vector_of_nodes, int num_of_nodes)
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10);
  for(int i = 0; i < num_of_nodes; i++)
  {
    Node node;
    node.id = i;
    node.pos.x = dist(rng);
    node.pos.y = dist(rng);
    node.pos.z = dist(rng);

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
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    
    for(int i = 0; i < nodes.size();i++)
    {
      DrawCube(nodes[i].pos, nodes[i].scale.x, nodes[i].scale.x, nodes[i].scale.x, nodes[i].color);
    }

    DrawGrid(30, 1);

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
