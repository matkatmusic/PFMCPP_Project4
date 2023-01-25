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
         powInternal() should be a private member function
 
 3) modify the Point class below to have 3 Constructors that accept your UDTs and one that accepts primitives.
     a) make the constructor that takes primitives initialize the two member variables.
     b) for each of your 3 Ctors that accept UDTs: correctly implement a Delegating Constructor that calls the constructor which takes primitives
     c) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     d) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) mark your UDT constructors as 'explicit'.  
    Adding this keyword prevents the compiler from implicitly creating instances of your UDT whenever primitives are passed to functions that take your UDT by const reference.
    This keyword means you can only create an instance of the class by Explicitly writing the type name.
    You can learn more about the explicit keyword here: 
    https://en.cppreference.com/w/cpp/language/explicit
 
 5) insert part4(); at the end of main, before the 'good to go'
 
 6) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 */

struct FloatType;
struct DoubleType;
struct IntType;

struct Point
{ 
    Point (float x1, float y1);
    Point (const FloatType& ft1, const FloatType& ft2);
    Point (const DoubleType& dt1, const DoubleType& dt2);
    Point (const IntType& it1, const IntType& it2);

    Point& multiply(float m);
    Point& multiply (const FloatType& ft);
    Point& multiply (const DoubleType& dt);
    Point& multiply (const IntType& it);

    void toString();
    
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

#include <iostream>
#include <cmath> 

struct A {};
struct HeapA
{ 
    HeapA() : a(new A) {}
    ~HeapA()
    {
        delete a;
    }
    A* a = nullptr;
};

struct FloatType;
struct DoubleType; 
struct IntType;

struct FloatType 
{   

private:
    float* value = nullptr; 
    FloatType& powInternal (const float& arg);
public:
    explicit FloatType(float floatTypeValue): value(new float(floatTypeValue)) {} 
    ~FloatType()
    {
        delete value;
    } 

    FloatType& add(float lhs);
    FloatType& subtract(float lhs);
    FloatType& multiply(float lhs);
    FloatType& divide(float lhs);   

    FloatType& pow (float);
    FloatType& pow (const IntType&);
    FloatType& pow (const DoubleType&);
    FloatType& pow (const FloatType&);

    operator float() const;
    
};    

struct DoubleType 
{  
private:
    double* value = nullptr; 
    DoubleType& powInternal (const double& arg);
public:
    explicit DoubleType(double doubleTypeValue): value(new double(doubleTypeValue)) {} 
    ~DoubleType()
    {
        delete value;
    }

    DoubleType& add(double lhs);
    DoubleType& subtract(double lhs);
    DoubleType& multiply(double lhs);
    DoubleType& divide(double lhs);   

    DoubleType& pow (double);
    DoubleType& pow (const IntType&);
    DoubleType& pow (const DoubleType&);
    DoubleType& pow (const FloatType&);

    operator double() const;
};   

struct IntType 
{   
private:
    int* value = nullptr; 
    IntType& powInternal (const int& arg);
public:
    explicit IntType(int intTypeValue): value(new int(intTypeValue)) {} 
    ~IntType()
    {
        delete value;
    }

    IntType& add(int lhs);
    IntType& subtract(int lhs);
    IntType& multiply(int lhs);
    IntType& divide(int lhs);   

    IntType& pow (int);
    IntType& pow (const IntType&);
    IntType& pow (const DoubleType&);
    IntType& pow (const FloatType&);

    operator int() const;//figure out what to do with this later.
};   

// ========== FLOAT TYPE ========== //

FloatType& FloatType::add(float lhs)
{ 
    *this->value += lhs;
    return *this;
} 

FloatType& FloatType::subtract(float lhs)
{
    *this->value -= lhs;
    return *this;
}

FloatType& FloatType::multiply(float lhs)
{
    *this->value *= lhs;
    return *this;
}

FloatType& FloatType::divide(float lhs)
{ 
    if(lhs == 0.0f) 
        std::cout << "warning: floating point division by zero!" << std::endl;
    *this->value /= lhs;
    return *this;
}   

FloatType::operator float() const 
{
    return *this->value;
}

FloatType& FloatType::pow (float value1)
{
    powInternal (value1);
    return *this;
}

FloatType& FloatType::pow (const IntType& value1)
{
    powInternal (static_cast<float>(value1));
    return *this;
}

FloatType& FloatType::pow (const DoubleType& value1)
{
    powInternal (static_cast<float>(value1));
    return *this;
}

FloatType& FloatType::pow (const FloatType& value1)
{
    powInternal (static_cast<float>(value1));
    return *this;    
} 

FloatType& FloatType::powInternal (const float& arg)
{
    *value = std::pow (*value, arg);
    return *this;
}

// ========== DOUBLE TYPE ========== //

DoubleType& DoubleType::add(double lhs)
{
    *this->value += lhs;
    return *this;
} 

DoubleType& DoubleType::subtract(double lhs)
{
    *this->value -= lhs;
    return *this;
}

DoubleType& DoubleType::multiply(double lhs)
{
    *this->value *= lhs;
    return *this;
}

DoubleType& DoubleType::divide(double lhs)
{ 
    
    if(lhs == 0.0) 
        std::cout << "warning: floating point division by zero!" << std::endl;
    *this->value /= lhs;
    return *this;
} 

DoubleType::operator double() const 
{
    return *this->value;
} 

DoubleType& DoubleType::pow (double value1)
{
    powInternal (value1);
    return *this;    
}

DoubleType& DoubleType::pow (const IntType& value1)
{
    powInternal (static_cast<double>(value1));
    return *this;    
}

DoubleType& DoubleType::pow (const DoubleType& value1)
{
    powInternal (static_cast<double>(value1));
    return *this; 
}
    
DoubleType& DoubleType::pow (const FloatType& value1)
{
    powInternal (static_cast<double>(value1));
    return *this; 
} 

DoubleType& DoubleType::powInternal (const double& arg)
{
    *value = std::pow (*value, arg);
    return *this;    
}

// ========== INT TYPE ========== //

IntType& IntType::add(int lhs)
{
    *this->value += lhs;
    return *this;
} 

IntType& IntType::subtract(int lhs)
{
    *this->value -= lhs;
    return *this;
}

IntType& IntType::multiply(int lhs)
{
    *this->value *= lhs;
    return *this;
}

IntType& IntType::divide(int lhs)
{ 
    if(lhs == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl; 
        return *this; 
    } 
    *this->value /= lhs;
    return *this;
} 

IntType::operator int() const 
{
    return *this->value;
} 

IntType& IntType::pow (int value1)
{
    powInternal (value1);
    return *this;
}

IntType& IntType::pow (const IntType& value1)
{
    powInternal (static_cast<int>(value1));
    return *this;
}

IntType& IntType::pow (const DoubleType& value1)
{
    powInternal (static_cast<int>(value1));
    return *this;
}

IntType& IntType::pow (const FloatType& value1)
{
    powInternal (static_cast<int>(value1));
    return *this;    
} 

IntType& IntType::powInternal (const int& arg)
{
    *value = static_cast<int>(std::pow (*value, arg));
    return *this;
}

// ========== POINT TYPE ========== // 

Point::Point (float x1, float y1) : x(x1), y(y1) 
{
}

Point::Point (const FloatType& ft1, const FloatType& ft2) : Point (static_cast<float>(ft1), static_cast<float>(ft2)) 
{
}

Point::Point (const DoubleType& dt1, const DoubleType& dt2) : Point (static_cast<float>(dt1), static_cast<float>(dt2)) 
{
}

Point::Point (const IntType& it1, const IntType& it2) : Point (static_cast<float>(it1), static_cast<float>(it2)) 
{
}

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply (const FloatType& ft)
{
    x *= ft;
    y *= ft;
    return *this;
}

Point& Point::multiply (const DoubleType& dt)
{
    x *= static_cast<float>(dt);
    y *= static_cast<float>(dt);
    return *this;
}

Point& Point::multiply (const IntType& it)
{
    x *= static_cast<float>(it);
    y *= static_cast<float>(it);
    return *this;
}

void Point::toString()
{
    std::cout << "Point { x: " << x << ", y: " << y << " }" << std::endl;
}


// ========== END OF UDTs ========== //

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide(static_cast<float>( it )) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add(static_cast<double>( it )) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide(static_cast<int>(pi)).multiply(static_cast<int>(dt)).subtract(static_cast<int>(ft)) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << it.multiply(it).divide(0).divide(static_cast<int>(0.0f)).divide(static_cast<int>(0.0)) << std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply(static_cast<int>(ft)) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add(static_cast<int>(dt)).add(static_cast<int>(ft)).multiply( 24 ) << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    float floatExp = 2.0f;
    double doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType" << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType" << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType" << std::endl;
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

// ========== MAIN ========== //

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
    std::cout << "DoubleType divide result=" << dt.divide(static_cast<double>(5.f)) << std::endl << std::endl;

    std::cout << "IntType add result=" << it.add(2) << std::endl;
    std::cout << "IntType subtract result=" << it.subtract(2) << std::endl;
    std::cout << "IntType multiply result=" << it.multiply(2) << std::endl;
    std::cout << "IntType divide result=" << it.divide(3) << std::endl << std::endl;
    std::cout << "Chain calculation = " << (it.multiply(1000).divide(2).subtract(10).add(100)) << std::endl;

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
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << (dt.multiply(static_cast<double>(it)).divide(static_cast<double>(5.0f)).add(static_cast<double>(ft))) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.divide(0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.divide(0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.divide(0) << std::endl;

    std::cout << "---------------------\n" << std::endl;  
    
    part3(); 
    part4();
    std::cout << "good to go!\n";

    return 0;
} 
