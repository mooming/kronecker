#pragma once

#include "GameObject.h"
#include "GameStatistics.h"

#include <vector>

namespace HardBop
{

namespace Game
{

class GameObject;

class GameEngine final
{
private:
   bool isRunning;
   GameStatistics statistics;

   std::vector<Component> components;
   std::vector<GameObject> gameObjects;


public:
   GameEngine(const GameEngine&) = delete;
   GameEngine& operator= (const GameEngine&) = delete;

   GameEngine();
   ~GameEngine();

   const GameStatistics& GetStatistics() const;

   void Run();
   void Stop();
   void Update(const float deltaTime);

};

} // Game

} // HardBop
