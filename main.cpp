/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.


#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
    
    operator NumericType() const { return v }
    operator NumericType&() { return v }
private:
    static int counter;
    NumericType v;
};


 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.

template <typename NumericType>
int Temporary<NumericType>::counter {0};


 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:

namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}


 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
#include <cmath>
#include<functional>
#include<memory>

struct A {};

struct HeapA
{
    A* a; 

    HeapA() : a( new A ){}

    ~HeapA()
    {
        delete a;
        a = nullptr;
    }
};

template <typename NumericType>
struct Numeric
{
    using Type = NumericType;

    Numeric( Type val ) : value( std::make_unique<Type>(val)) {}

    operator NumericType() const { return *value; }
    operator NumericType&() { return *value; }

    template<typename OtherType>
    Numeric& operator+=(const OtherType& o) 
    { 
        *value += static_cast<NumericType>(o); 
        return *this; 
    }

    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }

    template<typename OtherType>
    Numeric& operator*=(const OtherType& o) 
    { 
        *value *= static_cast<NumericType>(o); 
        return *this; 
    }

    template<typename OtherType>
    Numeric& operator/=( OtherType& num )
    {
        if constexpr (std::is_same<Type, int>::value)
        {
            if constexpr (std::is_same<OtherType, int>::value)
            {
                if ( num == 0 )
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }

            else if ( std::abs(num) <  std::numeric_limits<OtherType>::epsilon())
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }   
        }

        else if ( std::abs(num) <  std::numeric_limits<OtherType>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }  

        if ( value != nullptr )
            *value /= num;
        return *this;
    }

    template<typename OtherType>
    Numeric& pow(const OtherType& ft)
    {
        *value = static_cast<Type>(std::pow( *value, static_cast<NumericType>(ft)));
        return *value;
    }

    template<typename Callable>
    Numeric& apply( Callable f )
    {
        f(value);
        return *this;
    }

    private:
        std::unique_ptr<Type> value;
};


template<typename NumericType>
void cube( std::unique_ptr<NumericType>& value)
{
    if (value != nullptr)
    {
        NumericType& i = *value;
        i = i * i * i;
    }
}

struct Point
{
    template<typename NumericType1, typename NumericType2>
    Point(const NumericType1& one, const NumericType2& two) : x(static_cast<float>(one)), y(static_cast<float>(two)) {}

    
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    template<typename NumericType>
    Point& multiply(NumericType& m)
    {
        return multiply(static_cast<float>(m));
    }

    void toString()
    {
        std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
    }
private:
    float x{0}, y{0};
};


int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}


/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
*/

