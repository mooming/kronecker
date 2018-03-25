#pragma once

#include "../Math/UniformTransform.h"

#include "../System/MathUtil.h"
#include "../System/Optional.h"

#include <vector>

namespace HardBop
{

namespace Game
{

class GameObject;

template<typename Number>
class Transform final
{
public:
   using This = Transform;
   using Vec3 = Math::Vector3<Number>;
   using Quat = Math::Quaternion<Number>;
   using Mat3x3 = Math::Matrix3x3<Number>;
   using Mat4x4 = Math::Matrix4x4<Number>;
   using UTransform = Math::UniformTransform<Number>;

public:
   union
   {
      UTransform trs;
      struct
      {
         Quat rotation;
         Number scale;
         Vec3 translation;
      };
   };

   GameObject* gameObject;

private:
   Optional<UTransform> world;

   Transform* parent;
   std::vector<Transform*> children;

public:
   Transform(const Transform&) = delete;
   Transform& operator== (const Transform&) = delete;

public:
   Transform()
      : trs()
      , gameObject(nullptr)
      , world(nullptr)
      , parent(nullptr)
      , children()
   {
   }

   Transform(std::nullptr_t)
      : trs(nullptr)
      , gameObject(nullptr)
      , world(nullptr)
      , parent(nullptr)
      , children()
   {
   }

   Transform(const UTransform& trs)
      : trs(trs)
      , gameObject(nullptr)
      , world(nullptr)
      , parent(nullptr)
      , children()
   {
   }

   ~Transform()
   {
      if (parent)
      {
         parent->Detach(*this);
      }

      DetachAll();
   }

   void Attach(Transform& transform)
   {
      auto ptr = &transform;

      if (ptr == parent)
      {
         parent->Detach(*this);
      }

      if (std::find(children.begin(), children.end(), ptr) != children.end())
      {
         AssertMessage(transform.parent == this, "Parent-Child Inconsistency");
         return;
      }

      children.push_back(ptr);
      transform.parent = this;
   }

   Transform* GetParent() const { return parent; }

   void Detach(Transform& transform)
   {
      if (transform.parent != this)
         return;

      transform.parent = nullptr;

      auto ptr = &transform;
      auto it = std::find(children.begin(), children.end(), ptr);
      Assert(it != children.end());

      children.erase(it);
   }

   void DetachAll()
   {
      for (auto child : children)
      {
         AssertMessage(child->parent == this, "Parent-Child Inconsistency");
         child->parent = nullptr;
      }

      children.clear();
   }

   bool HasChild(const Transform& child) const
   {
      auto ptr = &child;
      return std::find(children.cbegin(), children.cend(), ptr) != children.cend();
   }

   Vector<Transform*>& GetChildren() { return children; }
   const Vector<Transform*>& GetChildren() const { return children; }

   void Invalidate()
   {
      if (!world)
         return;

      world = nullptr;
      for (auto child : children)
      {
         Assert(child);
         child->Invalidate();
      }
   }

   const UTransform& GetWorldTransform()
   {
      if (world)
         return *world;

      if (parent)
      {
         world = parent->GetWorldTransform() * trs;
         return *world;
      }

      return trs;
   }

   UTransform GetWorldTransform() const
   {
      if (world)
         return *world;

      if (parent)
      {
         return parent->GetWorldTransform() * trs;
      }

      return trs;
   }

   const UTransform& GetLocalTransform() const { return trs; }

   void Set(const Quat& r, Number s, const Vec3& t)
   {
      if (rotation == r && IsEqual(scale, s) && translation == t)
         return;

      rotation = r;
      scale = s;
      translation = t;

      Invalidate();
   }

   void Set(const Quat& r)
   {
      if (rotation == r)
         return;

      rotation = r;

      Invalidate();
   }

   void Set(Number s)
   {
      if (scale == s)
         return;

      scale = s;

      Invalidate();
   }

   void Set(const Vec3& t)
   {
      if (translation == t)
         return;

      translation = t;

      Invalidate();
   }
};

using FTransform = Transform<float>;
using DTransform = Transform<double>;

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Transform<T>& t)
{
   using namespace std;

   os << "Transform" << endl;
   os << t.trs << endl;

   auto parent = t.GetParent();
   os << "Parent: " << parent << endl;

   if (parent)
   {
      os << "World Transform" << endl;
      os << t.GetWorldTransform() << endl;
   }

   return os;
}

} // Game

} // HardBop

#ifdef __UNIT_TEST__

#include "System/TestCase.h"

namespace HardBop
{

namespace Math
{

class TransformTest : public TestCase
{
public:

  TransformTest() : TestCase("TransformTest")
  {
  }

protected:
  virtual bool DoTest() override;
};

} // Math

} // HardBop

#endif //__UNIT_TEST__
