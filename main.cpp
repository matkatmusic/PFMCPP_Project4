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
 */

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
     hint: what qualifier do read-only functions usually have?
     */
    operator ___() { /* read-only function */ }
    operator ___() { /* read/write function */ }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
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

#include <iostream>
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
    
    operator Type() const
    {
        return *value;
    }

    Numeric& operator+= ( Type num )
    {
        if ( value != nullptr )
            *value += num;
        return *this;
    }

    Numeric& operator-=( Type num )
    {
        if ( value != nullptr )
            *value -= num;
        return *this;
    }

    Numeric& operator*=( Type num )
    {
        if (value != nullptr )
            *value *= num;
        return *this;
    }
    template<typename DivType>

    Numeric& operator/=( DivType num )
    {
        if constexpr (std::is_same<Type, int>::value)
        {
            if constexpr (std::is_same<DivType, int>::value)
            {
                if ( num == 0 )
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl;
                    return *this;
                }
            }

            else if ( std::abs(num) <  std::numeric_limits<DivType>::epsilon())
            {
                std::cout << "can't divide integers by zero!" << std::endl;
                return *this;
            }   
        }

        else if ( std::abs(num) <  std::numeric_limits<DivType>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }  

        if ( value != nullptr )
            *value /= num;
        return *this;
    }

    Numeric& pow(const Type& ft)
    {
        return powInternal(ft);
    }

    Numeric& apply( std::function<Numeric&( std::unique_ptr<Type>& )> f )
    {
        if ( f )
            return f(value);
        return *this;
    }
    
    Numeric& apply( void( *f )( std::unique_ptr<Type>& ) )
    {
        if ( f )
            f(value);
        return *this;
    }

    private:
        std::unique_ptr<Type> value;
        Numeric& powInternal(Type ft)
        {
            if (value != nullptr)
                *value = static_cast<Type>(std::pow( *value, ft ));
            return *this;
        }

};

template <>
struct Numeric<double>
{
    using Type = double;

    Numeric( Type val ) : value( std::make_unique<Type>(val)) {}
    
    operator Type() const
    {
        return *value;
    }

    Numeric& operator+= ( Type num )
    {
        if ( value != nullptr )
            *value += num;
        return *this;
    }

    Numeric& operator-=( Type num )
    {
        if ( value != nullptr )
            *value -= num;
        return *this;
    }

    Numeric& operator*=( Type num )
    {
        if (value != nullptr )
            *value *= num;
        return *this;
    }

    Numeric& operator/=( Type num )
    {
        if ( num == 0.0 )
            std::cout << "warning: floating point division by zero!" << std::endl;
        if ( value != nullptr )
            *value /= num;
        return *this;
    }

    Numeric& pow(const Type& ft)
    {
        return powInternal( ft );
    }

    template<typename Callable>
    Numeric& apply( Callable f )
    {
        f(value);
        return *this;
    }  

    private:
        std::unique_ptr<Type> value;
        Numeric& powInternal(Type ft)
        {
            if (value != nullptr)
                *value = static_cast<Type>(std::pow( *value, ft ));
            return *this;
        }   
};

template<typename NumericType>
void myNumericFreeFunct( std::unique_ptr<NumericType>& value )
{
    *value += 7;
}

void myFloatFreeFunct( float& value )
{
    value += 7.f;
}

void myDoubleFreeFunct( double& value )
{
    value += 6.0;
}

void myIntFreeFunct ( int& value )
{
    value += 5;
}

//////////////////////////////////////////////////
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
/*
3) numify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
     
*/

void part3()
{
    Numeric<float> ft( 5.5f ); 
    Numeric<double> dt( 11.1 );
    Numeric<int> it ( 34 );
    Numeric<double> pi( 3.14 );

    ft *= ft;
    ft *= ft;
    ft /= static_cast<float>(it);
    std::cout << "The result of Numeric<float>^3 divided by Numeric<int> is: " << ft << std::endl;
    
    dt *= 3;
    dt += static_cast<double>(it);
    std::cout << "The result of Numeric<double> times 3 plus Numeric<int> is : " << dt << std::endl;

    it /= static_cast<int>(pi);
    it *= static_cast<int>(dt);
    it -= static_cast<int>(ft);
    std::cout << "The result of Numeric<int> divided by 3.14 multiplied by Numeric<double> minus Numeric<float> is: " << it << std::endl;

    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    it *= it;
    it /= 0;
    it /= (0.f);
    it /= (0.0);
    std::cout << it << std::endl;
    
    it *= static_cast<int>(ft);
    std::cout << "Numeric<float> x Numeric<int>  =  " << it << std::endl;
    
    it += static_cast<int>(dt);
    it += static_cast<int>(ft);
    it *= 24;
    std::cout << "(Numeric<int> + Numeric<double> + Numeric<float>) x 24 = " << it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    Numeric<float> ft1(2);
    Numeric<double> dt1(2);
    Numeric<int> it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    Numeric<int> itExp(2);
    Numeric<float> ftExp(2.0f);
    Numeric<double> dtExp(2.0);
    
    // Power tests with Numeric<float>
    std::cout << "Power tests with Numeric<float> " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(static_cast<float>(dtExp))  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with Numeric<double>
    std::cout << "Power tests with Numeric<double> " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(static_cast<double>(ftExp))  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with Numeric<int>
    std::cout << "Power tests with Numeric<int> " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(static_cast<int>(ftExp))  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(static_cast<int>(dtExp))  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    Numeric<float> ft2(3.0f);
    Numeric<double> dt2(4.0);
    Numeric<int> it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with Numeric<float>
    std::cout << "Point tests with Numeric<float> argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with Numeric<double>
    std::cout << "Point tests with Numeric<double> argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with Numeric<int>
    std::cout << "Point tests with Numeric<int> argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;
}
/*
void part6()
{
    Numeric<float> ft3(3.0f);
    Numeric<double> dt3(4.0);
    Numeric<int> it3(5);
    
    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply( [&ft3]( float& num ) -> Numeric<float>&
    {
        num += 7.f;
        return ft3;
    } );
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling Numeric<float>::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myFloatFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<double>::apply() using a lambda (adds 6.0) and Numeric<double> as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply( [&dt3]( double& num ) -> Numeric<double>&
    {
        num += 6.0;
        return dt3;
    });
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling Numeric<double>::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myDoubleFreeFunct);
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling Numeric<int>::apply() using a lambda (adds 5) and Numeric<int> as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply( [&it3]( int& num ) -> Numeric<int>&
    {
        num += 5;
        return it3;
    });
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling Numeric<int>::apply() using a free function (adds 5) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myIntFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}*/

void part7()
{
    Numeric ft3(3.0f);
    Numeric dt3(4.0);
    Numeric it3(5);
    
    std::cout << "Calling Numeric<float>::apply() using a lambda (adds 7.0f) and Numeric<float> as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;

    {
        using NumericType = decltype(ft3);
        ft3.apply( [&ft3](std::unique_ptr<NumericType::Type>& val)-> NumericType&
        {
            *val += 7.f;
            return ft3;
        } );
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
        using NumericType = decltype(dt3);
        dt3.apply( [&dt3](std::unique_ptr<NumericType::Type>& val)-> NumericType&
        {
            *val += 6.0;
            return dt3;
        } );
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
        using NumericType = decltype(it3);
        it3.apply( [&it3](std::unique_ptr<NumericType::Type>& val)-> NumericType&
        {
            *val += 5;
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

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    Numeric<float> ft ( 2.0f );
    Numeric<double> dt ( 2 );
    Numeric<int> it ( 2 ) ;

    ft += 2.0f;
    std::cout << "Numeric<float> add result=" << ft << std::endl;
    ft -= 2.0f;
    std::cout << "Numeric<float> subtract result=" << ft << std::endl;
    ft *= 2.0f;
    std::cout << "Numeric<float> multiply result=" << ft << std::endl;
    ft /= 16.0f;
    std::cout << "Numeric<float> divide result=" << ft << std::endl << std::endl;

    dt += 2.0;
    std::cout << "Numeric<double> add result=" << dt << std::endl;
    dt -= 2.0;
    std::cout << "Numeric<double> subtract result=" << dt << std::endl;
    dt *= 2.0;
    std::cout << "Numeric<double> multiply result=" << dt << std::endl;
    dt /= static_cast<double>(5.f);
    std::cout << "Numeric<double> divide result=" << dt << std::endl << std::endl;

    it += 2;
    std::cout << "Numeric<int> add result=" << it << std::endl;
    it -= 2;
    std::cout << "Numeric<int> subtract result=" << it << std::endl;
    it *= 2;
    std::cout << "Numeric<int> multiply result=" << it << std::endl;
    it /= 3;
    std::cout << "Numeric<int> divide result=" << it << std::endl << std::endl;
    it *= 1000;
    it /= 2;
    it -= 10;
    it += 100;
    std::cout << "Chain calculation = " << it << std::endl;

    // Numeric<float> object instanciation and method tests
    // --------
    ft += 3.0f;
    ft *= 1.5f;
    ft /= 5.0f;
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // Numeric<double>/Numeric<int> object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    dt *= it;
    dt /= static_cast<double>(5.0f);
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;

    std::cout << "New value of it = it / 0 = ";
    it /= 0;
    std::cout << it << std::endl;
    
    std::cout << "New value of ft = ft / 0 = ";
    ft /= 0.0f;
    std::cout << ft << std::endl;
    
    std::cout << "New value of dt = dt / 0 = ";
    dt /= 0.0;
    std::cout << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();

    part4();

    //part6();

    part7();

    std::cout << "good to go!\n";

    return 0;
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

