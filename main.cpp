   /*
Project 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by <REFERENCE>...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */
 
#include <iostream>
#include <cmath>
#include <memory>
#include <functional>

#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have? - CONST
     */
    operator NumericType() const 
    {
        return v;   /* read-only function */ 
    }
    operator NumericType& ()
    {
        return v;   /* read/write function */
    }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/
template<typename NumericType>
int Temporary<NumericType>::counter { 0 };


/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
// namespace example
// {
// template<typename NumericType>
// struct Numeric
// {
//     //snip
//     template<typename OtherType>
//     Numeric& operator-=(const OtherType& o) 
//     { 
//         *value -= static_cast<NumericType>(o); 
//         return *this; 
//     }
//     //snip
// };
// }

/*
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




struct Point
{
    Point(float a, float b) : x(a), y(b) { }

    
    template<typename TemplatedType>
    Point(TemplatedType& a, TemplatedType& b) : 
    Point(static_cast<float>(a), static_cast<float>(b)) { }  

    template<typename TemplatedType>
    Point& multiply(TemplatedType& m)
    {
        return multiply(static_cast<float>(m));
    }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    
    void toString()
    {
        std::cout << "Point " <<"{ x: " << x << ", y: " << y << " }" <<std::endl;
    }
private:
    float x{0};
    float y{0};
};


// //POINT IMPLEMENTAION++++++++++++++
// Point::Point(FloatType& a, FloatType& b) : Point(static_cast<float>(a), static_cast<float>(b) ) {}
// Point::Point(DoubleType& a, DoubleType& b): Point(static_cast<float>(a), static_cast<float>(b) ) {}
// Point::Point(IntType& a, IntType& b): Point(static_cast<float>(a), static_cast<float>(b) ) {}

// Point& Point::multiply(IntType& m)
// {
//     return multiply(static_cast<float>(m));
// }
// Point& Point::multiply(FloatType& m)
// {
//     return multiply(static_cast<float>(m));
// }
// Point& Point::multiply(DoubleType& m)
// {
//     return multiply(static_cast<float>(m));
// }
// Point& Point::multiply(float m)
// {
//     x *= m;
//     y *= m;
//     return *this;
// }
//===================================================================================


template <typename TemplatedType>

struct Numeric
{
    using Type = Temporary<TemplatedType>;
    
    Numeric(Type v) : un( new Type(v)) { }
    Numeric() : Numeric(0) {}

    ~Numeric()
    {
        un = nullptr;
    }

    // Numeric& operator = (const Numeric&) {return *this;} 
    // to avoid error: main.cpp:694:8: error: object of type 'Numeric<float>' cannot be assigned
    //   because its copy assignment operator is implicitly deleted
    // ft = ft.pow(4);
    

    operator TemplatedType() const
    {
        return *un;
    }
    operator TemplatedType&()
    {
        return *un;
    }

    template <typename OtherTT>
    Numeric& operator = (const OtherTT& t)
    {
        *un = static_cast<TemplatedType>(t);
        return *this;
    }

    template <typename OtherTT>
    Numeric& operator += (const OtherTT& t)
    {
        *un += static_cast<TemplatedType>(t);
        return *this;
    }

    template <typename OtherTT>
    Numeric& operator -= (const OtherTT& t)
    {
        *un -= static_cast<TemplatedType>(t);
        return *this;
    }

    template <typename OtherTT>
    Numeric& operator *= (const OtherTT& t)
    {
        *un *= static_cast<TemplatedType>(t);
        return *this;
    }
    
    template <typename OtherTT>
    Numeric& operator /= (const OtherTT& t)
    {
        if constexpr (std::is_same<TemplatedType, int>::value)
        {
            if constexpr (std::is_same<decltype(t), const int>::value)
            {
                if ( t == 0)
                {
                    std::cout << "can't divide integers by zero!\n";
                    return *this;
                }
            }
            else if (t < std::numeric_limits<OtherTT>::epsilon() )
            {
                std::cout << "can't divide integers by zero!\n";
                return *this;
            }
        }
        else if (t < std::numeric_limits<OtherTT>::epsilon() )
        {
            std::cout << "warning: trying to divide by zero!\n";
        }
        *un /= static_cast<TemplatedType>(t);
        return *this;
    }

    
    Numeric& apply( std::function<Numeric&(std::unique_ptr<Type>&)> callable)   
    {
        // std::cout << "std::function<>" << std::endl;
        if( callable )
        {
            return callable(un);  
        }
        return *this;
    }
        
        
    template <typename OtherTT>
    Numeric& pow(const OtherTT& x) 
    {
        if(un != nullptr)
        {
            *un = static_cast<Type>(std::pow(*un, static_cast<const TemplatedType>(x)) );

        }
        return *this; 
    }

    template <typename Callable>
    Numeric& apply (Callable callableFunc)
    {
        callableFunc(un);
        return *this; 
    }

private:
    std::unique_ptr<Type> un { new Type() };
    // Numeric& powInternal(const Type x)
    // {
    //     if(un != nullptr)
    //     {
    //         *un = static_cast<Type>(std::pow(*un, x) );
    //     }
    //     return *this;
    // }
};


//+++++++++++++++++++++++++

///CUBE FUNCTION///
template <typename TemplatedType>
void cube (std::unique_ptr<TemplatedType>& un)
{
    *un = (*un) * (*un) * (*un);
}

// Free Functions    
// template <typename NumericType>
// void myNumericFreeFunct(std::unique_ptr<NumericType>& value)
// {
//     *value += 7;
// }


/*
template<>
struct Numeric<double>
{
    using Type = double;

    Numeric(Type v) : un( std::make_unique<Type>(v) ) { }
    Numeric() : Numeric(0) {}

    ~Numeric()
    {
        un = nullptr;
    }

    operator Type() const { return *un; }

    Numeric& operator += (const Type t)
    {
        *un += t;
        return *this;
    }
    Numeric& operator -= (const Type t)
    {
        *un -= t;
        return *this;
    }
    Numeric& operator *= (const Type t)
    {
        *un *= t;
        return *this;
    }
    Numeric& operator /= (const Type t)
    {
        if(t==0.0)
        {
            std::cout << "warning: floating point division by zero!\n";
        }
        *un /= t;
        return *this;
    }
    template<class C>
    Numeric& apply(C callable)
    {
        callable(un);
        return *this;
    }

    Numeric& pow(Type pwr) 
    {
        *un = powInternal(pwr);
        return *this;
    }

private:
    Type powInternal(const Type power)
    {
        return static_cast<Type>(std::pow(*un, power));
    }
    std::unique_ptr<Type> un = nullptr;
};

*/





/*
void part3()
{
    Numeric<float> ft( 5.5f );
    Numeric<double> dt( 11.1 );
    Numeric<int> it ( 34 );
    Numeric<double> pi( 3.14 );

    ft *= ft; // here
    ft *= ft;
    ft /= it;
    std::cout << "The result of FloatType^3 divided by IntType is: " << ft << std::endl;
    

    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

    it /= static_cast<int>(pi);
    it *= static_cast<int>(dt);
    it -= static_cast<int>(ft);
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it << std::endl;

    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    
    it *= it;
    it /=0;
    it /=0.0f;
    it /=0.0;
    std::cout << it <<std::endl;
    
    it *= static_cast<int>(ft);
    std::cout << "FloatType x IntType  =  " << it << std::endl;
    
    it += static_cast<int>(dt);
    it += static_cast<int>(ft);
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
}
*/
/*

void part4()
{
    Numeric<float> ft1(2.0f);
    Numeric<double> dt1(2.0);
    Numeric<int> it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    Numeric<float> ftExp(2.0f);
    Numeric<double> dtExp(2.0);
    Numeric<int> itExp(2);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(static_cast<float>(dtExp))  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(static_cast<double>(ftExp))  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(static_cast<int>(ftExp)) << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(static_cast<int>(dtExp))  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    Numeric ft2(3.0f);
    Numeric dt2(4.0);
    Numeric it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;
}
*/

/*
void part7()
{
    Numeric ft3(3.0f);
    Numeric dt3(4.0);
    Numeric it3(5);
    
    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    {
        using FloatType = decltype(ft3);
        ft3.apply( [&ft3](std::unique_ptr<FloatType::Type>& f) -> FloatType&

        {
            *f += 7.0f;
            return ft3;
        });
    }
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;

    {
        using DoubleType = decltype(dt3);
        dt3.apply( [&dt3](std::unique_ptr<DoubleType::Type>& d) -> DoubleType&
        {
            *d += 6.0;
            return dt3;
        } ); // This calls the templated apply fcn
    }
    
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;

    {
        using IntType = decltype(it3);
        it3.apply( [&it3](std::unique_ptr<IntType::Type>& i) -> IntType&
        {
            *i += 5;
            return it3;
        } );
    }
    std::cout << "it3 after: " << it3 << std::endl;

    std::cout << "Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}
*/

/*
your program should generate the following output.   The output should have zero warnings.


FloatType add result=4
FloatType subtract result=2
FloatType multiply result=4
FloatType divide result=0.25

DoubleType add result=4
DoubleType subtract result=2
DoubleType multiply result=4
DoubleType divide result=0.8

IntType add result=4
IntType subtract result=2
IntType multiply result=4
IntType divide result=1

Chain calculation = 590
New value of ft = (ft + 3.0f) * 1.5f / 5.0f = 0.975
---------------------

Initial value of dt: 0.8
Initial value of it: 590
Use of function concatenation (mixed type arguments) 
New value of dt = (dt * it) / 5.0f + ft = 95.375
---------------------

Intercept division by 0 
New value of it = it / 0 = can't divide integers by zero!
590
New value of ft = ft / 0 = inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

The result of FloatType^4 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
can't divide integers by zero!
can't divide integers by zero!
can't divide integers by zero!
505521
FloatType x IntType  =  13143546
(IntType + DoubleType + FloatType) x 24 = 315447336
Power tests with FloatType 
pow(ft1, floatExp) = 2^2 = 4
pow(ft1, itExp) = 4^2 = 16
pow(ft1, ftExp) = 16^2 = 256
pow(ft1, dtExp) = 256^2 = 65536
---------------------

Power tests with DoubleType 
pow(dt1, doubleExp) = 2^2 = 4
pow(dt1, itExp) = 4^2 = 16
pow(dt1, ftExp) = 16^2 = 256
pow(dt1, dtExp) = 256^2 = 65536
---------------------

Power tests with IntType 
pow(it1, intExp) = 2^2 = 4
pow(it1, itExp) = 4^2 = 16
pow(it1, ftExp) = 16^2 = 256
pow(it1, dtExp) = 256^2 = 65536
===============================

Point tests with float argument:
Point { x: 3, y: 6 }
Multiplication factor: 6
Point { x: 18, y: 36 }
---------------------

Point tests with FloatType argument:
Point { x: 3, y: 3 }
Multiplication factor: 3
Point { x: 9, y: 9 }
---------------------

Point tests with FloatType argument:
Point { x: 3, y: 4 }
Multiplication factor: 4
Point { x: 12, y: 16 }
---------------------

Point tests with IntType argument:
Point { x: 3, y: 4 }
Multiplication factor: 5
Point { x: 15, y: 20 }
---------------------

Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:
ft3 before: 3
ft3 after: 10
Calling Numeric<float>::apply() twice using a free function (adds 7.0f) and void as return type:
ft3 before: 10
ft3 after: 24
---------------------

Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:
dt3 before: 4
dt3 after: 10
Calling Numeric<double>::apply() twice using a free function (adds 7.0) and void as return type:
dt3 before: 10
dt3 after: 24
---------------------

Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:
it3 before: 5
it3 after: 10
Calling Numeric<int>::apply() twice using a free function (adds 7) and void as return type:
it3 before: 10
it3 after: 24
---------------------

good to go!


Use a service like https://www.diffchecker.com/diff to compare your output. 
*/



int main() // NEW MAIN
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
int main() // OLD MAIN
{   

    Numeric<int> it(2);
    Numeric<float> ft(2.0f);
    Numeric<double> dt(2.0);
    
    // std::cout << "NumericWrapper: " << it << std::endl;
    
    // using NumericType = decltype(it)::Type;                          // #4)
    // using ReturnType = decltype(it);

    // using NumericType = decltype(ft)::Type;
    // using NumericType = decltype(dt)::Type;


    // using FloatType = decltype(ft);
    // using DoubleType = decltype(dt);
    // using IntType = decltype(it);

    // FloatType ft ( 2.0f );
    // DoubleType dt ( 2 );
    // IntType it ( 2 ) ;

    ft += 2.0f;
    std::cout << "FloatType add result=" << ft << std::endl;
    
    ft -= 2.0f;
    std::cout << "FloatType subtract result=" << ft << std::endl;

    ft *= 2.0f;
    std::cout << "FloatType multiply result=" << ft << std::endl;
  
    ft /= 16.f;
    std::cout << "FloatType divide result=" << ft << std::endl << std::endl;


    dt += 2.0;
    std::cout << "DoubleType add result=" << dt << std::endl;

    dt -= 2.0;
    std::cout << "DoubleType subtract result=" << dt << std::endl;

    dt *= 2.0;
    std::cout << "DoubleType multiply result=" << dt << std::endl;
    
    dt /= 5.0;
    std::cout << "DoubleType divide result=" << dt << std::endl << std::endl;
     //why do I get 20 instead of 0.8 ?! 

    it += 2;
    std::cout << "IntType add result=" << it << std::endl;

    it -= 2;
    std::cout << "IntType subtract result=" << it << std::endl;

    it *= 2;
    std::cout << "IntType multiply result=" << it << std::endl;

    it /= 3;
    std::cout << "IntType divide result=" << it << std::endl;

    it *= 1000;
    it /= 2;
    it -= 10;
    it += 100;
    std::cout << "\nChain calculation = " << it << std::endl;

        // FloatType object instanciation and method tests
    // --------
    ft += 3.0f;
    ft *= 1.5f;
    ft /= 5.0f;
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
   
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    dt *= it;
    dt /= 5.0;
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
 
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.operator/=(0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.operator/=(0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.operator/=(0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    part3();
    part4();
    // part6();
    part7();
    std::cout << "good to go!\n";

    return 0;
}

*/

