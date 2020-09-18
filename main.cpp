/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) copy the part6() function below and paste it after part4()
 7) call part6() after part4() is called at the end of main().

 8) fill in the missing arguments in part6 such that you produce the expected output.

 9) Make your lambda & free function update the value of your held object
 
 
build/run to make sure you don't have any errors
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */

/*
your program should generate the following output EXACTLY.
This includes the warnings.
The output should have zero warnings.



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
New value of it = it / 0 = error: integer division by zero is an error and will crash the program!
590
New value of ft = ft / 0 = warning: floating point division by zero!
inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

The result of FloatType^3 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
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

Point tests with DoubleType argument:
Point { x: 3, y: 4 }
Multiplication factor: 4
Point { x: 12, y: 16 }
---------------------

Point tests with IntType argument:
Point { x: 3, y: 4 }
Multiplication factor: 5
Point { x: 15, y: 20 }
---------------------

Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:
ft3 before: 3
ft3 after: 10
Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:
ft3 before: 10
ft3 after: 17
---------------------

Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:
dt3 before: 4
dt3 after: 10
Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:
dt3 before: 10
dt3 after: 16
---------------------

Calling IntType::apply() using a lambda (adds 5) and IntType as return type:
it3 before: 5
it3 after: 10
Calling IntType::apply() using a free function (adds 5) and void as return type:
it3 before: 10
it3 after: 15
---------------------

good to go!

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
#include <cmath>// header file for std::pow
#include <functional>

struct FloatType;
struct DoubleType;
struct IntType;

struct Point
{
    ~Point();

    Point(const FloatType& _x, const FloatType& _y);
    Point(const DoubleType& _x, const DoubleType& _y);
    Point(const IntType& _x, const IntType& _y);

    Point& multiply(float m);
    Point& multiply(FloatType& f);
    Point& multiply(DoubleType& d);
    Point& multiply(IntType& i);

    void toString();

private:
    float x{0}, y{0};
};

struct A {};
struct HeapA
{
    A* pointerToA = nullptr;

    HeapA() : pointerToA(new A) {}

    ~HeapA()
    {
        delete pointerToA;
    }

};

struct FloatType;
struct DoubleType;
struct IntType;

struct FloatType
{
    FloatType(float floatPrimitive);
    ~FloatType();

    FloatType& operator+=(float f);
    FloatType& operator-=(float f);
    FloatType& operator*=(float f);
    FloatType& operator/=(float f);

    operator float() const { return *value; }

    FloatType& pow(float f);
    FloatType& pow(const IntType& i);
    FloatType& pow(const FloatType& f);
    FloatType& pow(const DoubleType& d);

    /*
        1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
    */

    //  both apply() functions should work with chaining
    //  2) One of the apply() functions should takes a std::function<> object as the function argument.
    //  the std::function<> object should return *this;
    FloatType& apply(std::function<FloatType&(float&)> func);

    //  3) the other apply() function should take a function pointer. 
    //  the function pointer should return void.
    FloatType& apply(void(*func)(float&));

private:
    float* value = nullptr;
    FloatType& powInternal(const float f);
};

struct DoubleType
{
    DoubleType(double doublePrimitive);
    ~DoubleType();

    DoubleType& operator+=(double d);
    DoubleType& operator-=(double d);
    DoubleType& operator*=(double d);
    DoubleType& operator/=(double d);

    operator double() const { return *value; }

    DoubleType& pow(double d);
    DoubleType& pow(const IntType& i);
    DoubleType& pow(const FloatType& f);
    DoubleType& pow(const DoubleType& d);

    DoubleType& apply(std::function<DoubleType&(double&)> func);
    DoubleType& apply(void(*func)(double&));

private:
    double* value = nullptr;
    DoubleType& powInternal(const double d);
};

struct IntType
{
    IntType(int IntPrimitive);
    ~IntType();

    IntType& operator+=(int i);
    IntType& operator-=(int i);
    IntType& operator*=(int i);
    IntType& operator/=(int i);

    operator int() const { return *value; }
    
    IntType& pow(int i);
    IntType& pow(const IntType& i);
    IntType& pow(const FloatType& f );
    IntType& pow(const DoubleType& d);

    IntType& apply(std::function<IntType&(int&)> func);
    IntType& apply(void(*func)(int&));

private:
    int* value = nullptr;
    IntType& powInternal(const int i);
};

/* FloatType member function definitions */
FloatType::FloatType(float floatPrimitive) : value(new float(floatPrimitive)) { }

FloatType::~FloatType() 
{
    delete value;
    value = nullptr;
}

FloatType& FloatType::operator+=(float f)
{
    *value += f;
    return *this;
}

FloatType& FloatType::operator-=(float f)
{
    *value -= f;
    return *this;
}

FloatType& FloatType::operator*=(float f)
{
    *value *= f;
    return *this;
}

FloatType& FloatType::operator/=(float f)
{
    if (f == 0.f)
    {
        std::cout << "warning: floating point division by zero!" << std::endl;
    }
    *value /= f;
    return *this;
}

// 1) add pow() functions, and a powInternal() function to each of your UDTs
FloatType& FloatType::pow(float f)
{
    return powInternal(f);
}

/*
 2) your powInternal() function should do something like this in its body:    
    *val = std::pow( *val, arg );
    where 'arg' is the passed-in type, converted to whatever type your object is holding.
*/
FloatType& FloatType::powInternal(float f)
{
    *value = std::pow(*value, f);
    return *this;   //powInternal() should be chainable.
}

// c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
FloatType& FloatType::pow(const IntType& i)
{
    return powInternal(static_cast<float>(i));
}

FloatType& FloatType::pow(const FloatType& f)
{
    return powInternal(static_cast<float>(f));
}

FloatType& FloatType::pow(const DoubleType& d)
{
    return powInternal(static_cast<float>(d));    
}

//  2) One of the apply() functions should takes a std::function<> object as the function argument.
// the std::function<> object should return *this;
FloatType& FloatType::apply(std::function<FloatType&(float&)> func)
{
    if(func)
    {
        return func(*value);
    }

    return *this; 
}

//  3) the other apply() function should take a function pointer. 
// the function pointer should return void.
FloatType& FloatType::apply( void(*func)(float&) )
{
    if(func)
    {
        func(*value);
    }

    return *this; 
}

void myFloatFreeFunct( float& value)
{
    value += 7.0f;
}

/* DoubleType member function definitions */

DoubleType::DoubleType(double doublePrimitive) : value(new double(doublePrimitive)) {}

DoubleType::~DoubleType() 
{
    delete value;
    value = nullptr;
}

DoubleType& DoubleType::operator+=(double d)
{
    *value += d;
    return *this;
}

DoubleType& DoubleType::operator-=(double d)
{
    *value -= d;
    return *this;
}

DoubleType& DoubleType::operator*=(double d)
{
    *value *= d;
    return *this;
}

DoubleType& DoubleType::operator/=(double d)
{
    if (d == 0.0)
    {
        std::cerr << "warning: floating point division by zero!" << std::endl;
    }
    *value /= d;
    return *this;
}

/* 
    1) add pow() functions, and a powInternal() function to each of your UDTs
    b) add a pow() whose argument type is the primitive your UDT owns.  
    the argument should be passed by copy.
*/
DoubleType& DoubleType::pow(double d)
{
    return powInternal(d);
}

DoubleType& DoubleType::powInternal(double d)
{
    *value = std::pow(*value, d);
    return *this;   //powInternal() should be chainable.
}

/*
    1c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
*/
DoubleType& DoubleType::pow(const IntType& i)
{
    return powInternal(static_cast<double>(i));
}

DoubleType& DoubleType::pow(const FloatType& f)
{
    return powInternal(static_cast<double>(f));
}

DoubleType& DoubleType::pow(const DoubleType& d)
{
    return powInternal(static_cast<double>(d));
}

DoubleType& DoubleType::apply(std::function<DoubleType&(double&)> func)
{
    if(func)
    {
        return func(*value);
    }

    return *this; 
}

DoubleType& DoubleType::apply( void(*func)(double&) )
{
    if(func)
    {
        func(*value);
    }

    return *this; 
}

void myDoubleFreeFunct( double& value)
{
    value += 6.0;
}

/* IntType member function definitions */

IntType::IntType(int intPrimitive) : value(new int(intPrimitive)) {}

IntType::~IntType() 
{
    delete value;
    value = nullptr;
}

IntType& IntType::operator+=(int i)
{
    *value += i;
    return *this;
}

IntType& IntType::operator-=(int i)
{
    *value -= i;
    return *this;
}

IntType& IntType::operator*=(int i)
{
    *value *= i;
    return *this;
}

IntType& IntType::operator/=(int i)
{
    if (i == 0)
    {
        std::cerr << "error: integer division by zero is an error and will crash the program!" << std::endl;
    } 
    else
    {
        *value /= i;
    }
    return *this;
}

/* 
    1) add pow() functions, and a powInternal() function to each of your UDTs
    b) add a pow() whose argument type is the primitive your UDT owns.  
    the argument should be passed by copy.
*/
IntType& IntType::pow(int i)
{
    return powInternal(i);
}

IntType& IntType::powInternal(int i)
{
    // use the float pow ( float base, float exp );
    *value = static_cast<int>( std::pow(static_cast<float>(*value), static_cast<float>(i)) );
    return *this;   //powInternal() should be chainable.
}

/*
    1c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
*/
IntType& IntType::pow(const IntType& i)
{
    return powInternal(static_cast<int>(i));
}

IntType& IntType::pow(const FloatType& f)
{
    return powInternal(static_cast<int>(f));
}

IntType& IntType::pow(const DoubleType& d)
{
    return powInternal(static_cast<int>(d));
}

IntType& IntType::apply(std::function<IntType&(int&)> func)
{
    if(func)
    {
        return func(*value);
    }

    return *this; 
}

IntType& IntType::apply( void(*func)(int&) )
{
    if(func)
    {
        func(*value);
    }

    return *this; 
}

void myIntFreeFunct( int& value)
{
    value += 5;
}

/* Point member function definitions */

Point::~Point() {}

Point::Point(const FloatType& _x, const FloatType& _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)) { }

Point::Point(const DoubleType& _x, const DoubleType& _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)) { }

Point::Point(const IntType& _x, const IntType& _y) : x(static_cast<float>(_x)), y(static_cast<float>(_y)) { }

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}

/*
    3 b) overload the multiply() function so it can accept each of your UDTs.
*/
Point& Point::multiply(FloatType& f)
{
    return multiply(static_cast<float>(f));
}

Point& Point::multiply(DoubleType& d)
{
    return multiply(static_cast<float>(d));
}

Point& Point::multiply(IntType& i)
{
    return multiply(static_cast<float>(i));
}

/*
    3 c) add a toString() function to the Point class that prints out the x and y members via std::cout.
*/
void Point::toString()
{
    std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
}

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    ft *= ft;
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
    it /= 0;
    it /= 0.0f;
    it /= 0.0;
    std::cout << it << std::endl;
    
    it *= static_cast<int>(ft);
    std::cout << "FloatType x IntType  =  " << it << std::endl;

    it += static_cast<int>(dt);
    it += static_cast<int>(ft);
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
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
    std::cout << "Point tests with DoubleType argument:" << std::endl;
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

void part6()
{
    FloatType ft3(3.0f);
    DoubleType dt3(4.0);
    IntType it3(5);
    
    std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply( [&ft3](float& f) -> FloatType&
    {
        f += 7.0f;
        return ft3;
    });
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myFloatFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply( [&dt3](double& d) -> DoubleType&
    {
        d += 6.0;
        return dt3;
    });
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myDoubleFreeFunct);
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply( [&it3](int& i) -> IntType&
    {
        i += 5;
        return it3;
    });
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myIntFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    ft += 2.0f;
    std::cout << "FloatType add result=" << ft << std::endl;
    ft -= 2.0f;
    std::cout << "FloatType subtract result=" << ft << std::endl;
    ft *= 2.0f;
    std::cout << "FloatType multiply result=" << ft << std::endl;
    ft /= 16.0f;
    std::cout << "FloatType divide result=" << ft << std::endl << std::endl;

    dt += 2.0;
    std::cout << "DoubleType add result=" << dt << std::endl;
    dt -= 2.0;
    std::cout << "DoubleType subtract result=" << dt << std::endl;
    dt *= 2.0;
    std::cout << "DoubleType multiply result=" << dt << std::endl;
    dt /= static_cast<double>(5.f);
    std::cout << "DoubleType divide result=" << dt << std::endl << std::endl;

    it += 2;
    std::cout << "IntType add result=" << it << std::endl;
    it -= 2;
    std::cout << "IntType subtract result=" << it << std::endl;
    it *= 2;
    std::cout << "IntType multiply result=" << it << std::endl;
    it /= 3;
    std::cout << "IntType divide result=" << it << std::endl << std::endl;
    it *= 1000;
    it /= 2;
    it -= 10;
    it += 100;
    std::cout << "Chain calculation = " << it << std::endl;

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
    dt /= static_cast<double>(5.0f);
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << (it /= 0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << (ft /= 0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << (dt /= 0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();

    part4();    // 4) insert part4(); at the end of main, before the 'good to go'

    part6();    // 7) call part6() after part4() is called at the end of main().

    std::cout << "good to go!\n";

    return 0;
}
