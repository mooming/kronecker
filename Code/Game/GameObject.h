#pragma once

#include "Transform.h"

#include <cstdint>
#include <string>
#include <vector>

namespace HardBop
{

namespace Game
{

class Component;

class GameObject final
{
   using Transform = DTransform;

private:
   std::string name;
   Transform transform;
   size_t pendingDeletes;
   std::vector<Component*> components;

public:
   GameObject();
   GameObject(const std::string& name);
   ~GameObject();

   const std::string& GetName() const;
   void SetName(const std::string& name);

   void Update(const float deltaTime);

   Component* FindComponent(const std::string& name);
   const Component* FindComponent(const std::string& name) const;

   template<typename T>
   void AddComponent()
   {
      auto component = new T();
      component->OnCreate(this);
      components.push_back(component);
   }

   void DeleteComponent(Component* component);

private:
   void RebuildCOmponents();
};

} // Game

} // HardBop
