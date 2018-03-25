#include "Component.h"
#include "Component.h"
#include "Component.h"

#include "GameObject.h"

#include "../System/Debug.h"

using namespace HardBop::Game;

static constexpr Component::ComponentState StateNone = 0;
static constexpr Component::ComponentState StateCreated = 1;
static constexpr Component::ComponentState StateEnabled = 2;
static constexpr Component::ComponentState StatePendingDestroy = 4;
static constexpr Component::ComponentState StateDestroyed = 8;

Component::Component() : state(StateNone)
{
}

const std::string& Component::GetName() const
{
   static std::string defaultComponent = "Default";
   return defaultComponent;
}

bool Component::IsCreated() const
{
   return (state & StateCreated) != 0;
}

bool Component::IsEnabled() const
{
   return (state & StateEnabled) != 0;
}

bool Component::IsPendingDestroy() const
{
   return (state & StatePendingDestroy) != 0;
}

bool Component::IsDestroyed() const
{
   return (state & StateDestroyed) != 0;
}

void Component::SetEnabled(bool isEnabled)
{
   if (IsEnabled() == isEnabled)
      return;

   if (isEnabled)
   {
      state |= StateEnabled;
   }
   else
   {
      state &= ~StateEnabled;
   }
}

void Component::Update(GameObject* object, const float deltaTime)
{
   AssertMessage(object != nullptr, "Null object. Component name is ", GetName(), ".");
   AssertMessage(IsEnabled(), "Component(", GetName(), ") of ", object->GetName(), " is not enabled.");
   AssertMessage(deltaTime > 0.0f, "Component(", GetName(), ") of ", object->GetName()
      , " : deltaTime should be greater than zero, but ", deltaTime, ".");
}

void Component::OnCreate(GameObject* object)
{
   MarkCreated();
}

void Component::OnDestroy(GameObject* object)
{
}

void Component::OnEnabled(GameObject* object)
{
}

void Component::OnDisabled(GameObject* object)
{
}

void HardBop::Game::Component::MarkCreated()
{
   state |= StateCreated;
}

void HardBop::Game::Component::MarkDelete()
{
   state |= StatePendingDestroy;
}

void HardBop::Game::Component::MarkDestroyed()
{
   state |= StateDestroyed;
}
