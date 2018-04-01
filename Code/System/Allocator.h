// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#ifndef Allocator_h
#define Allocator_h

#include "Types.h"
#include "TestCase.h"

#include <memory>

namespace HardBop
{
    class Allocator
    {
    private:
        AllocatorId id;

    public:
        enum : AllocatorId
        {
            INVALID_ALLOCATOR_ID,
            NATIVE_ALLOCATOR_ID
        };

    public:
        Allocator();
        Allocator(AllocatorId id);
        virtual ~Allocator();

    public:
        const AllocatorId Id() const
        {
            return id;
        }

        void SetId(const AllocatorId id)
        {
            Allocator::id = id;
        }

        virtual Pointer Allocate(size_t size) = 0;
        virtual void Deallocate(const Pointer ptr) = 0;
        virtual size_t GetSize(const Pointer ptr) const = 0;

        virtual size_t Usage() const = 0;
        virtual size_t Available() const = 0;
    };

    class AllocatorScope
    {
    public:
        AllocatorScope(AllocatorId id);
        ~AllocatorScope();

    private:
        AllocatorId previous;
    };

    template <typename T, typename ... Types>
    static inline T* Construct(void* ptr, Types&& ... args)
    {
        return new (ptr) T(std::forward<Types>(args) ...);
    }

    extern Allocator& GetAllocator();
    extern Allocator& GetAllocator(AllocatorId id);
    extern Pointer Allocate(size_t size);
    extern Pointer Allocate(AllocatorId id, size_t size);
    extern void Deallocate(const Pointer ptr);
    extern size_t GetSize(const Pointer ptr);

    inline size_t GetMemUsage() { return GetAllocator().Usage(); }
    inline size_t GetMemAvailable() { return GetAllocator().Available(); }

    template <typename Type>
    inline Type* Allocate(size_t size)
    {
        return static_cast<Type*>(Allocate(size * sizeof(Type)));
    }

    template <typename Type>
    inline Type* Allocate(AllocatorId id, size_t size)
    {
        return static_cast<Type*>(Allocate(id, size * sizeof(Type)));
    }

    template <typename Type, typename ... Types>
    inline Type* New(Types&& ... args)
    {
        return Construct<Type>(Allocate(sizeof(Type)), std::forward<Types>(args) ...);
    }

    template <typename Type>
    inline Type* NewArray(Index size)
    {
        auto ptr = reinterpret_cast<Type*>(Allocate(sizeof(Type) * size));
        for (Index i = 0; i < size; ++i)
        {
            Construct<Type>(ptr[i]);
        }

        return ptr;
    }

    template <typename Type>
    inline void DeleteComponents(Type* ptr)
    {
        ptr->~Type();
        Deallocate(ptr);
    }

    template <typename Type>
    inline void DeleteArray(Type* ptr)
    {
        // TODO TODO
	}
} // HardBop

#ifdef __UNIT_TEST__
namespace HardBop
{
   namespace Test
   {
      class AllocatorTest : public TestCase
      {
      public:
         AllocatorTest() : TestCase("AllocatorTest") {}

      protected:
         virtual bool DoTest() override;
      };
   } // Test

} // HardBop

#endif //__UNIT_TEST__

#endif /* Allocator_h */
