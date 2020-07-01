#pragma once

#include <atomic>
#include <iostream>

namespace juce
{
    namespace AtomicHelpers
    {
        template <typename T> struct DiffTypeHelper     { using Type = T; };
        template <typename T> struct DiffTypeHelper<T*> { using Type = std::ptrdiff_t; };
    }
    template <typename Type>
    struct Atomic  final
    {
        using DiffType = typename AtomicHelpers::DiffTypeHelper<Type>::Type;
        Atomic() noexcept  : value (Type()) {}
        Atomic (Type initialValue) noexcept  : value (initialValue) {}
        Atomic (const Atomic& other) noexcept  : value (other.get()) {}
        ~Atomic() noexcept
        {
#if __cpp_lib_atomic_is_always_lock_free
            static_assert (std::atomic<Type>::is_always_lock_free,
                           "This class can only be used for lock-free types");
#endif
        }
        Type get() const noexcept               { return value.load(); }
        void set (Type newValue) noexcept       { value = newValue; }
        Type exchange (Type newValue) noexcept  { return value.exchange (newValue); }
        bool compareAndSetBool (Type newValue, Type valueToCompare) noexcept
        {
            return value.compare_exchange_strong (valueToCompare, newValue);
        }
        
        Atomic<Type>& operator= (const Atomic& other) noexcept
        {
            value = other.value.load();
            return *this;
        }
        
        Atomic<Type>& operator= (Type newValue) noexcept
        {
            value = newValue;
            return *this;
        }
        Type operator+= (DiffType amountToAdd) noexcept { return value += amountToAdd; }
        Type operator-= (DiffType amountToSubtract) noexcept { return value -= amountToSubtract; }
        Type operator++() noexcept { return ++value; }
        Type operator--() noexcept { return --value; }
        void memoryBarrier() noexcept          { atomic_thread_fence (std::memory_order_seq_cst); }
        std::atomic<Type> value;
    };
} //end namespace juce