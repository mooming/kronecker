#pragma once

#include "Allocator.h"

namespace HardBop
{
	template <typename T>
	class HardbopAllocator final
	{
	public:
		typedef T value_type;

	public:
		HardbopAllocator() = default;

		template<typename U>
		HardbopAllocator(const HardbopAllocator<U>& rhs)
		{
		}

		T* allocate(std::size_t n)
		{
			if (auto ptr = Allocate<T>(n))
				return ptr;

			throw std::bad_alloc();
		}

		void deallocate(T* ptr, std::size_t) noexcept
		{
			Deallocate(ptr);
		}
	};

	template <class T, class U>
	bool operator==(const HardbopAllocator<T>&, const HardbopAllocator<U>&)
	{
		return true;
	}

	template <class T, class U>
	bool operator!=(const HardbopAllocator<T>&, const HardbopAllocator<U>&)
	{
		return false;
	}
}

#ifdef __UNIT_TEST__

#include "System/TestCase.h"

namespace HardBop
{

   namespace Test
   {
      class HardbopAllocatorTest : public TestCase
      {
      public:

         HardbopAllocatorTest() : TestCase("HardbopAllocatorTest")
         {
         }

      protected:
         virtual bool DoTest() override;
      };
   } // Test

}
#endif //__UNIT_TEST__
