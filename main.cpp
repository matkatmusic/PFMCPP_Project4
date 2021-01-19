/*
Project 4: Part 9 / 9
 video: Chapter 5 Part 8

Create a branch named Part9

 Rule of 3-5-0 and S.R.P.
 
 DO NOT EDIT YOUR PREVIOUS main(). 
 
 1) add the Leak Detector files from Project5
 
 2) move these macros after the JUCE_LEAK_DETECTOR macro :
 */

#define JUCE_DECLARE_NON_COPYABLE(className) \
            className (const className&) = delete;\
            className& operator= (const className&) = delete;

#define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
            JUCE_DECLARE_NON_COPYABLE(className) \
            JUCE_LEAK_DETECTOR(className)

/*
 3) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary) to the end of the  Temporary<> struct
 
 4) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric) to the end of the Numeric<> struct
 
 if you compile it, you'll see lots of errors about deleted functions.
 
 5) Implement the Rule of 5 on Numeric<> and Temporary<> to fix this.
 
 You should end up with the same program output as Part 8's task if you did it right.
 */

/*
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

template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    
    operator NumericType() const { return v; }
    operator NumericType&() { return v; }
private:
    static int counter;
    NumericType v;
};

template <typename NumericType>
int Temporary<NumericType>::counter {0};

template <typename NumericType>
struct Numeric
{
    using Type = Temporary<NumericType>;

    Numeric( Type val ) : value( std::make_unique<Type>(val)) {}

    operator NumericType() const { return *value; }
    operator NumericType&() { return *value; }

    template<typename OtherType>
    Numeric& operator= (const OtherType& o )
    {
        if (value != nullptr)
            *value = static_cast<NumericType>(o);
        return *this;
    }

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
    Numeric& operator/= ( const OtherType& num )
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
            *value /= static_cast<NumericType>(num);
        return *this;
    }

    template<typename OtherType>
    Numeric& pow(const OtherType& ft)
    {
        *value = static_cast<Type>(std::pow( *value, static_cast<NumericType>(ft)));
        return *this;
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

