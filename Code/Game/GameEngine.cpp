#include "GameEngine.h"

#include "GameObject.h"
#include "../System/Time.h"

using namespace HardBop::Game;

GameEngine::GameEngine()
   : isRunning(false)
{

}

GameEngine::~GameEngine()
{
}

const GameStatistics& GameEngine::GetStatistics() const
{
   return statistics;
}

void HardBop::Game::GameEngine::Run()
{
   isRunning = true;

   float deltaTime = 0.0f;
   float frameTime = 0.0f;

   float fpsTimer;
   uint64_t fpsFrameCount;

   while (isRunning)
   {

      {
         Time::MeasureSec secMeasure(frameTime);
         Update(deltaTime);
      }

      deltaTime = frameTime;
      statistics.frameTime = frameTime;
      statistics.numberOfGameObjects = gameObjects.size();
      statistics.numberOfComponents = components.size();

      ++statistics.frameCount;
      ++fpsFrameCount;

      fpsTimer += frameTime;
      if (fpsTimer > 1.0f)
      {
         statistics.fps = (float)fpsFrameCount / fpsTimer;
         fpsFrameCount = 0;
         fpsTimer = 0.0f;
      }
   }
}

void GameEngine::Stop()
{
   isRunning = false;
}

void GameEngine::Update(const float deltaTime)
{
   // Sync with physics engine
   // - fetch physics events

   // Process received data

   // Run GameLogics
   for (auto& obj : gameObjects)
   {
      obj.Update(deltaTime);
   }

   // Start physics simulation (Fully Async)
   // - Multiple steps for a while
   // - Stack physics events; move, collision, etc ...

   // Process Console Commands

   // Draw renderables (Sync & Async)
   // - Process Animations
   // - Process Custom-Pose-Modifier
   // - Wait for ready
   // - Update matrices
   // - Render
   // - Wait for done
}
