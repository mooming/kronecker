#pragma once

#include <cstdint>

namespace HardBop
{

namespace Game
{

class GameObject;
class Component
{
public:
   using ComponentState = uint8_t;

private:
   ComponentState state;

public:
   Component();
   virtual ~Component() = default;

   const std::string& GetName() const;
   bool IsCreated() const;
   bool IsEnabled() const;
   bool IsPendingDestroy() const;
   bool IsDestroyed() const;

   void SetEnabled(bool isEnabled);

   virtual void Update(GameObject* object, const float deltaTime);

   virtual void OnCreate(GameObject* object);
   virtual void OnDestroy(GameObject* object);

   virtual void OnEnabled(GameObject* object);
   virtual void OnDisabled(GameObject* object);

   void MarkCreated();
   void MarkDelete();
   void MarkDestroyed();
};

} // Game

} // HardBop
