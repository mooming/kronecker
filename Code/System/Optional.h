// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#pragma once

#include "Debug.h"
#include "StdUtil.h"
#include "Types.h"

#include <utility>

namespace HardBop
{
    template <typename Type>
    class Optional
    {
    public:
        bool hasValue;
        Byte value[sizeof(Type)];

    public:
        inline Optional() : hasValue(false)
        {
        }

        inline Optional(const Type& value) : hasValue(true)
        {
            Value() = value;
        }

        inline Optional(const Optional& rhs)
        {
            if (rhs.hasValue)
            {
                Value() = rhs.value;
            }
            else if (hasValue)
            {
                Destroy(typename IsReferenceType<Type>::Result());
            }
        }

        inline Optional(Optional&& rhs)
        {
            if (rhs.hasValue)
            {
                Value() = std::move(rhs.value);
            }
            else
            {
                Destroy(typename IsReferenceType<Type>::Result());
            }
        }

        inline Optional(std::nullptr_t) : hasValue(false)
        {
        }

        inline ~Optional()
        {
            Destroy(typename IsReferenceType<Type>::Result());
        }

        inline Optional& operator= (const Type& value)
        {
            if (hasValue)
            {
                Destroy(typename IsReferenceType<Type>::Result());
            }

            Value() = value;
            hasValue = true;

            return *this;
        }

        inline Optional& operator= (const Optional& rhs)
        {
            if (rhs.hasValue)
            {
                Value() = rhs.value;
                hasValue = rhs.hasValue;
            }
            else
            {
                Destroy(typename IsReferenceType<Type>::Result());
            }

            return *this;
        }

        inline Optional& operator= (Optional&& rhs)
        {
            if (rhs.hasValue)
            {
                Value() = std::move(rhs.value);
                hasValue = rhs.hasValue;
            }
            else
            {
                Destroy(typename IsReferenceType<Type>::Result());
            }

            return *this;
        }

        inline Optional& operator= (std::nullptr_t)
        {
            Destroy(typename IsReferenceType<Type>::Result());

            return *this;
        }

        inline operator bool() const
        {
            return hasValue;
        }

        inline Type& operator* ()
        {
            Assert(hasValue);
            return Value();
        }

        inline const Type& operator* () const
        {
            Assert(hasValue);
            return Value();
        }

        inline Type& Value()
        {
            return reinterpret_cast<Type&>(value[0]);
        }

        inline const Type& Value() const
        {
            return reinterpret_cast<const Type&>(value[0]);
        }

    private:
        inline void Destroy(True_t)
        {
            hasValue = false;
        }

        inline void Destroy(False_t)
        {
            if (hasValue)
            {
                Value().~Type();
            }

            hasValue = false;
        }
    };
}

#ifdef __UNIT_TEST__
#include "TestCase.h"
namespace HardBop
{
   namespace Test
   {
      class OptionalTest : public TestCase
      {
      public:
         OptionalTest() : TestCase("OptionalTest") {}

      protected:
         virtual bool DoTest() override;
      };
   } // Test

} // HardBop
#endif //__UNIT_TEST__
