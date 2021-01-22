#pragma once

#include "Atomic.h"
#include <cassert>

namespace juce
{
    template <class OwnerClass>
    class LeakedObjectDetector
    {
    public:
        //==============================================================================
        LeakedObjectDetector() noexcept                                 { ++(getCounter().numObjects); }
        LeakedObjectDetector (const LeakedObjectDetector&) noexcept     { ++(getCounter().numObjects); }
        
        ~LeakedObjectDetector()
        {
            if (--(getCounter().numObjects) < 0)
            {
                std::cout << "*** Dangling pointer deletion! Class: " << getLeakedObjectClassName() << std::endl;
                assert(false);
            }
        }
        
    private:
        //==============================================================================
        class LeakCounter
        {
        public:
            LeakCounter() = default;
            
            ~LeakCounter()
            {
                if (numObjects.value > 0)
                {
                    std::cout << "*** Leaked objects detected: " << numObjects.value << " instance(s) of class " << getLeakedObjectClassName() << std::endl;
                    assert(false);
                }
            }
            
            Atomic<int> numObjects;
        };
        
        static const char* getLeakedObjectClassName()
        {
            return OwnerClass::getLeakedObjectClassName();
        }
        
        static LeakCounter& getCounter() noexcept
        {
            static LeakCounter counter;
            return counter;
        }
    };
}

#define JUCE_JOIN_MACRO_HELPER(a, b) a ## b
#define JUCE_JOIN_MACRO(item1, item2)  JUCE_JOIN_MACRO_HELPER (item1, item2)
#define JUCE_LEAK_DETECTOR(OwnerClass) \
friend class juce::LeakedObjectDetector<OwnerClass>; \
static const char* getLeakedObjectClassName() noexcept { return #OwnerClass; } \
juce::LeakedObjectDetector<OwnerClass> JUCE_JOIN_MACRO (leakDetector, __LINE__);
