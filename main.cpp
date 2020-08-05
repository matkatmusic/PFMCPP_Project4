/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4
 
 Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
     e) the pow() functions should be chainable.
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
         powInternal() should be chainable.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) insert part4(); at the end of main, before the 'good to go'
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 */
#include <iostream>

struct FloatType;
struct DoubleType;
struct IntType;

struct Point
{

/*
    3) modify the Point class below to have Constructors that accept your UDTs.
    a) make the Constructor's UDT arguments initialize the Point class's two member variables.
*/

    Point(float _x, float _y) : x(_x), y(_y) {}

    Point(const FloatType& _x, const FloatType& _y) : Point(static_cast<float>(_x),static_cast<float>(_y)) { }

    Point(const DoubleType& _x, const DoubleType& _y) : Point(static_cast<float>(_x),static_cast<float>(_y)) { }

    Point(const IntType& _x, const IntType& _y) : Point(static_cast<float>(_x),static_cast<float>(_y)) { }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

/*
    3 b) overload the multiply() function so it can accept each of your UDTs.
*/
    Point& multiply(FloatType& f)
    {
        return multiply(static_cast<float>(f));
    }

    Point& multiply(DoubleType& d)
    {
        return multiply(static_cast<float>(d));
    }

    Point& multiply(IntType& i)
    {
        return multiply(static_cast<float>(i));
    }

/*
    3 c) add a toString() function to the Point class that prints out the x and y members via std::cout.
*/

    void toString()
    {
        std::cout << "x: " << x << " y: " << y << std::endl;
    }

private:
    float x{0}, y{0};
};

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

The result of FloatType^4 divided by IntType is: 26.9136
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

good to go!

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

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

#include <iostream>
#include <cmath>    // header file for std::pow

struct FloatType;
struct DoubleType;
struct IntType;

struct FloatType
{
    FloatType(float floatPrimitive);
    ~FloatType();

    FloatType& add(float f);
    FloatType& subtract(float f);
    FloatType& multiply(float f);
    FloatType& divide(float f);

    operator float() { return *value; }

/* 
    1) add pow() functions, and a powInternal() function to each of your UDTs
    b) add a pow() whose argument type is the primitive your UDT owns.  
    the argument should be passed by copy.
*/
    FloatType& pow(float f);

/*
    1c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
*/
    FloatType& pow(const IntType&);
    FloatType& pow(const FloatType&);
    FloatType& pow(const DoubleType&);

private:
    float* value = nullptr;
    FloatType& powInternal(const float f);
};

struct DoubleType
{
    DoubleType(double doublePrimitive);
    ~DoubleType();

    DoubleType& add(double d);
    DoubleType& subtract(double d);
    DoubleType& multiply(double d);
    DoubleType& divide(double d);

    operator double() { return *value; }

/* 
    1) add pow() functions, and a powInternal() function to each of your UDTs
    b) add a pow() whose argument type is the primitive your UDT owns.  
    the argument should be passed by copy.
*/
    DoubleType& pow(double d);

/*
    1c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
*/
    DoubleType& pow(const IntType&);
    DoubleType& pow(const FloatType&);
    DoubleType& pow(const DoubleType&);

private:
    double* value = nullptr;
    DoubleType& powInternal(const double d);
};

struct IntType
{
    IntType(int IntPrimitive);
    ~IntType();

    IntType& add(int i);
    IntType& subtract(int i);
    IntType& multiply(int i);
    IntType& divide(int i);

    operator int() { return *value; }

/* 
    1) add pow() functions, and a powInternal() function to each of your UDTs
    b) add a pow() whose argument type is the primitive your UDT owns.  
    the argument should be passed by copy.
*/
    IntType& pow(int i);

/*
    1c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
*/
    IntType& pow(const IntType&);
    IntType& pow(const FloatType&);
    IntType& pow(const DoubleType&);

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

FloatType& FloatType::add(float f)
{
    *value += f;
    return *this;
}

FloatType& FloatType::subtract(float f)
{
    *value -= f;
    return *this;
}

FloatType& FloatType::multiply(float f)
{
    *value *= f;
    return *this;
}

FloatType& FloatType::divide(float f)
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
FloatType& FloatType::powInternal(const float f)
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

/* DoubleType member function definitions */

DoubleType::DoubleType(double doublePrimitive) : value(new double(doublePrimitive)) {}

DoubleType::~DoubleType() 
{
    delete value;
    value = nullptr;
}

DoubleType& DoubleType::add(double d)
{
    *value += d;
    return *this;
}

DoubleType& DoubleType::subtract(double d)
{
    *value -= d;
    return *this;
}

DoubleType& DoubleType::multiply(double d)
{
    *value *= d;
    return *this;
}

DoubleType& DoubleType::divide(double d)
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

DoubleType& DoubleType::powInternal(const double d)
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

/* IntType member function definitions */

IntType::IntType(int intPrimitive) : value(new int(intPrimitive)) {}

IntType::~IntType() 
{
    delete value;
    value = nullptr;
}

IntType& IntType::add(int i)
{
    *value += i;
    return *this;
}

IntType& IntType::subtract(int i)
{
    *value -= i;
    return *this;
}

IntType& IntType::multiply(int i)
{
    *value *= i;
    return *this;
}

IntType& IntType::divide(int i)
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
    return powInternal(static_cast<int>(i));
}

IntType& IntType::powInternal(const int i)
{
    *value = std::pow(*value, i);
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

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;

    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;

    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( int(pi) ).multiply( int(dt) ).subtract( int(ft) ) << std::endl;

    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;

    std::cout << it.multiply(it).divide(0).divide(0.0f).divide(0.0) << std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply( int(ft) ) << std::endl;

    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( int(dt) ).add( int(ft) ).multiply( 24 ) << std::endl;
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

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << ft.add( 2.0f ) << std::endl;
    std::cout << "FloatType subtract result=" << ft.subtract( 2.0f ) << std::endl;
    std::cout << "FloatType multiply result=" << ft.multiply( 2.0f ) << std::endl;
    std::cout << "FloatType divide result=" << ft.divide( 16.0f) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << dt.add(2.0) << std::endl;
    std::cout << "DoubleType subtract result=" << dt.subtract(2.0) << std::endl;
    std::cout << "DoubleType multiply result=" << dt.multiply(2.0) << std::endl;
    std::cout << "DoubleType divide result=" << dt.divide(double(5.f)) << std::endl << std::endl;

    std::cout << "IntType add result=" << it.add(2) << std::endl;
    std::cout << "IntType subtract result=" << it.subtract(2) << std::endl;
    std::cout << "IntType multiply result=" << it.multiply(2) << std::endl;
    std::cout << "IntType divide result=" << it.divide(3) << std::endl << std::endl;
    std::cout << "Chain calculation = " << it.multiply(1000).divide(2).subtract(10).add(100) << std::endl;

    // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft.add( 3.0f ).multiply(1.5f).divide(5.0f) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt.multiply(it).divide(double(5.0f)).add(double(ft)) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.divide(0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.divide(0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.divide(0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();

    //part4();    // 4) insert part4(); at the end of main, before the 'good to go'

    std::cout << "good to go!\n";

    return 0;
}
