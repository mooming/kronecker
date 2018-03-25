#pragma once

namespace HardBop
{
   namespace Game
   {
      class GameStatistics
      {
      public:
         float frameTime;
         float fps;
         float usedMemory;
         size_t numberOfGameObjects;
         size_t numberOfComponents;
         uint64_t frameCount;
      };
   } // Game
} // HardBop
