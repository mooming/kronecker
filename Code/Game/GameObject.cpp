#pragma once

#include "GameObject.h"

#include "Component.h"
#include "../System/Debug.h"

using namespace HardBop::Game;
using namespace HardBop::Math;

GameObject::GameObject() : name(), transform()
{
}

GameObject::GameObject(const std::string& name) : name(name), transform()
{
}

GameObject::~GameObject()
{
}

const std::string& GameObject::GetName() const
{
   return name;
}

void GameObject::SetName(const std::string& name)
{
   GameObject::name = name;
}

void GameObject::Update(const float deltaTime)
{
   for (auto component : components)
   {
      component->Update(this, deltaTime);
   }

   if (pendingDeletes > 0)
   {
      RebuildCOmponents();
   }
}

Component* GameObject::FindComponent(const std::string& name)
{
   for (auto component : components)
   {
      if (component->GetName() == name)
         return component;
   }

   return nullptr;
}

const Component* GameObject::FindComponent(const std::string& name) const
{
   for (auto component : components)
   {
      if (component->GetName() == name)
         return component;
   }

   return nullptr;
}

void GameObject::DeleteComponent(Component* component)
{
   if (component == nullptr)
   {
      AssertMessage(component != nullptr
         , "GameObject(", GetName(), ") : ", __func__, " : null component.");
      return;
   }

   component->MarkDelete();
   ++pendingDeletes;
}

void GameObject::RebuildCOmponents()
{
   std::vector<Component*> newComponents;
   newComponents.reserve(components.size() - pendingDeletes);

   for (auto component : components)
   {
      if (component->IsPendingDestroy())
      {
         component->OnDestroy(this);
         delete component;

         continue;
      }

      newComponents.push_back(component);
   }

   std::swap(components, newComponents);
   pendingDeletes = 0;
}
