/*
This is a compilation of everything you would have implemented in 
Project 4 parts 1-6

Your goal is to make main() work without generating any errors 
or warnings.  This main() is from a previous student's approved 
submission.

All of the instructions below are a summation of each project 
part's work, edited to reflect the changes you would have made 
in each project.

===========================
Create a branch named Part6

Purpose:  This project will take you through the process of 
writing a class that wraps a numeric type, beginning with 
writing simple member functions and ending with a fully 
templated class with lots of functionality. 

=============
Project 4 part 1 simplified instructions
=============
1) write 3 UDTs named FloatType, DoubleType, IntType.  
    use struct instead of class so everything is public by 
    default.

2) make each UDT own a heap-allocated primitive type without 
using smart pointers  
    i.e. IntType should own a heap-allocated int.

3) Don't let your heap-allocated owned type leak!

4) give it a single constructor that takes the appropriate 
primitive.
    this argument will initialize the owned primitive's value.
        i.e. if you're owning an int on the heap, your ctor 
        argument will initialize that heap-allocated int's value 
        via the member initializer list.

==============
Project 4 part 3 simplified instructions
==============
1) move all of your implementations out of the class.
    NO IN-CLASS IMPLEMENTATION ALLOWED

2) add user-defined conversion functions that convert to the 
numeric type your object holds.
    i.e. if your type holds an int, you'll need an operator int() 
    function.

3) make your member variable private.
    a) this conversion function should be the ONLY WAY to access 
    the held value.
    b) use the proper casting technique to invoke this conversion 
    function

==============
Project 4 part 4 simplified instructions
==============
1) add pow() functions, and a powInternal() function to each of 
your UDTs
    a) your pow() functions should call powInternal()
    b) add a pow() whose argument type is the primitive your UDT 
    owns.  the argument should be passed by copy.
    c) for each UDT in the file, your class should have pow() 
    overloads that take that UDT as the function argument.
        the argument should be passed as const ref
        i.e. if you had UDTs named IntType, FloatType, DoubleType
            in your IntType class, you'd have:
                pow(const IntType&),
                pow(const FloatType&),
                pow(const DoubleType&),
                and pow(int)
    d) be sure to remember the rules about what member functions 
    can be called on const objects.
        (const objects can only call their const member functions)
    e) the pow() functions should be chainable.
 
2) your powInternal() function should do something like this in 
its body:    *val = std::pow( *val, arg );
    a) where 'arg' is the passed-in type, converted to whatever 
    type your object is holding.
        i.e. if your UDT owns an int, then arg would be an int.
        if your UDT owns a float, then arg would be a float.
    b) std::pow's documentation is found here: 
    https://en.cppreference.com/w/cpp/numeric/math/pow so be sure 
    to include the proper header file listed there.
    c) powInternal() should be chainable.

==============
Project 4 part 5 simplified instructions
==============
1) implement overloaded math operators that modify the internal 
heap-allocated primitive.
    e.g. add() would become operator+=() because it modifies the 
    internal heap-allocated object.
    These math operators should allow for chaining.

2) implement the appropriate action in the member function. 
    i.e. your 'addition assignment' math operator should add the 
    function argument to your heap-allocated member variable.
    a) Be aware that floating point division by 0 is legal, but 
    integer division by 0 will crash your program.  
    b) Handle this possible input when you write your 'divide' 
    functions.
    c) you should warn the user if they're doing floating-point
    division-by-zero but not prevent the division from happening
    d) you should warn AND prevent the division from happening 
    if it is an integer-division-by-zero.

3) Your overloaded operators should only take primitives, passed 
by value.

==============
Project 4 part 6 simplified instructions
==============
1) add two member functions named "apply()" to each of your 
Heap-Allocated Numeric Type wrappers.
    both apply() functions should work with chaining
 
2) One of the apply() functions should takes a std::function<> 
object as the function argument.
    the std::function<> object should return *this;
 
3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
4) Make both of the member functions's Callable Function Parameter 
use your owned object as it's single parameter.  
    i.e. if you managed your owned object via a raw pointer, you'd 
    use this for your std::function argument:
        std::function<OwnedT&(T&)>    
 
5) be sure to practice safe std::function usage (make sure it's 
not a nullptr function being called)
 
6) Make your lambda & free function update the value of your held
object

7) modify the Point class below:
    a) implement the constructor that takes 2 primitives to 
    initialize the member variables.
    b) implement constructors that accept a single instance of 
    your UDTs.
    a) make the Point(UDT) constructor forward its argument to 
    the Point(float,float) constructor.

    b) overload the multiply() function so it can accept each of 
    your UDTs.  These overloaded functions should call and return
    the multiply(float) function.

*/
#include <iostream>
#include <cmath>


struct FloatType;
struct DoubleType;
struct IntType;


struct FloatType // wrote UDT part 1 - 1)
{
    FloatType(float f); //Part 1 - 4) 
    ~FloatType();
    operator float() const { return *ownedVariable; }

    FloatType& operator=(const FloatType&) {return *this;} 
                    // explicit copy assignment opperator to avoid error:
                    //definition of implicit copy assignment operator for 'FloatType' is deprecated
                    //because it has a user-declared destructor [-Wdeprecated] RULE OF 3

    FloatType& operator+=(float f);
    FloatType& operator-=(float f);
    FloatType& operator*=(float f);
    FloatType& operator/=(float f);

    FloatType& pow(float f); 
    FloatType& pow(const IntType& f);
    FloatType& pow(const FloatType& f); 
    FloatType& pow(const DoubleType& f); 

    //void apply(std::function<>)
    //{
      //  return *this;
    //}

    //void apply() ;

    FloatType& powInternal(float f); ///here 
    private: // Part 3 - 3)
    float* ownedVariable = nullptr;
};

//1) implement overloaded math operators that modify the internal 
//heap-allocated primitive.
FloatType& FloatType::operator += (float f)
{//your 'addition assignment' math operator should add the 
    //function argument to your heap-allocated member variable.
    //modify the internal heap-allocated primitive
    *ownedVariable += f;

    //These math operators should allow for chaining.
    return *this; 
        
    //all done!
    //https://en.cppreference.com/w/cpp/language/operators 
}

FloatType& FloatType::operator -= (float f)
{
    *ownedVariable -= f;
    return *this;
    }
    
FloatType& FloatType::operator *= (float f)
{
    *ownedVariable *= f;
    return *this;
}
FloatType& FloatType::operator /= (float f)
{
    if (f == 0.0f)
    {
        std::cout<< "warning: you are about to divide float by zero!\n" << std::endl;
    }
    *ownedVariable /= f;
    return *this;
}
struct DoubleType
{
    DoubleType(double d);
    ~DoubleType();
    operator double() const { return *ownedVariable; }

    DoubleType& operator=(const DoubleType&) {return *this;} 
                    // explicit copy assignment opperator to avoid error

    DoubleType& operator+=(double d);
    DoubleType& operator-=(double d);
    DoubleType& operator*=(double d);
    DoubleType& operator/=(double d);

    DoubleType& pow(const IntType& d);
    DoubleType& pow(const FloatType& d);
    DoubleType& pow(const DoubleType& d);
    DoubleType& pow(double d);
    DoubleType& powInternal(double d);

    private:
    double* ownedVariable;
};

DoubleType& DoubleType::operator += (double d)
{
    *ownedVariable += d;
    return *this;
}
DoubleType& DoubleType::operator -= (double d)
{
    *ownedVariable -= d;
    return *this;
}
DoubleType& DoubleType::operator *= (double d)
{
    *ownedVariable *= d;
    return *this;
}
DoubleType& DoubleType::operator /= (double d)
{
    if (d == 0.0)
    {
        std::cout<< "warning: you are about to divide double by zero! " << std::endl;
    }
    *ownedVariable /= d;
    return *this;
}


struct IntType
{
    IntType(int i);
    ~IntType();
    operator int() const { return *ownedVariable; } 

    IntType& operator=(const IntType&) {return *this;} 
                    // explicit copy assignment opperator to avoid error

    IntType& operator+=(int i);//ok
    IntType& operator-=(int i);
    IntType& operator*=(int i);
    IntType& operator/=(int i);

    IntType& pow(const IntType& i);
    IntType& pow(const FloatType& i);
    IntType& pow(const DoubleType& i);
    IntType& pow(int i);
    IntType& powInternal(int i);

private:
    int* ownedVariable;
};

IntType& IntType::operator += (int i)
{
    *ownedVariable += i;
    return *this;
}
IntType& IntType::operator -= (int i)
{
    *ownedVariable -= i;
    return *this;
}
IntType& IntType::operator *= (int i)
{
    *ownedVariable *= i;
    return *this;
}
IntType& IntType::operator /= (int i)
{
    if (i != 0)
    {
        *ownedVariable /= i;
    }
    else
    {
        
        std::cout<< "error: you are about to divide integer by zero! In order to prevent world from being sucked into itself, we gonna stop you." << std::endl;
    }
        return *this;
}

struct Point
{
Point(float a, float b) : x(a), y(b) {} //Part 6 - 7)
Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    void toString()
    {
        std::cout << "The x coordinate is: " << x << "\nThe y coordinate is: " << y << std::endl;
    }
private:
    float x{0}, y{0};
};
//===================================================================================



//FUNCTION IMPLEMENTAIONS++++++++++++++++++++++++++++++++++++++++++
FloatType::FloatType(float f) : ownedVariable(new float(f)) { } // made heap-allocated primitive type. Part 1 -2) 
FloatType::~FloatType() 
{
    delete ownedVariable; 
    
}

DoubleType::DoubleType(double d) : ownedVariable(new double(d)) { }
DoubleType::~DoubleType() {delete ownedVariable; ownedVariable = nullptr; }

IntType::IntType(int i) : ownedVariable(new int (i)){ }
IntType::~IntType() { delete ownedVariable; ownedVariable = nullptr;}


//POW IMPLEMENTAIONS++++++++++++++++++++++++++++++++++++++++++

FloatType& FloatType::powInternal(const float f)
{
    *ownedVariable = std::pow(*ownedVariable, f);
    return *this;
}

FloatType& FloatType::pow(float f) 
{
    return powInternal(f);
}

FloatType& FloatType::pow(const IntType& f) 
{
    return powInternal(static_cast<float>(f));
}

FloatType& FloatType::pow(const FloatType& f) 
{
    return powInternal(f);
}

FloatType& FloatType::pow(const DoubleType& f) 
{
    return powInternal(static_cast<float>(f));
}
//=========================================

DoubleType& DoubleType::powInternal(double d)
{
    *ownedVariable = std::pow(*ownedVariable, d);
    return *this;
}

DoubleType& DoubleType::pow(double d) 
{
    return powInternal(d);
}

DoubleType& DoubleType::pow(const IntType& d) 
{
    return powInternal(static_cast<double>(d));
}

DoubleType& DoubleType::pow(const FloatType& d) 
{
    return powInternal(static_cast<double>(d));
}

DoubleType& DoubleType::pow(const DoubleType& d) 
{
    return powInternal(d);
}
//=========================================
IntType& IntType::powInternal(int i)
{
    *ownedVariable = static_cast<int>(std::pow(*ownedVariable, i));
    return *this;
}

IntType& IntType::pow(int i)
{
    return powInternal(i);
}

IntType& IntType::pow(const IntType& i)
{
    powInternal(i);
    return *this;
}

IntType& IntType::pow(const DoubleType& i )
{
    return powInternal(static_cast<int>(i));
}

IntType& IntType::pow(const FloatType& i )
{
    return powInternal(static_cast<int>(i));
}

//+++++++++++++++++++++++++
//         Free Functions               

void updateValue( float& value)
{
    value += value;
}

void updateValue( double& value)
{
    value += value;
}

void updateValue( int& value)
{
    value += value;
}

void divider()
{
    std::cout << "\n\n===============================\n\n";
}

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    ft = ft.pow(4);
    ft /= it;
    std::cout << "The result of FloatType^4 divided by IntType is: " << ft << std::endl;

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
    // */
}


// void part4()
// {
//     // ------------------------------------------------------------
//     //                          Power tests
//     // ------------------------------------------------------------
//     FloatType ft1(2);
//     DoubleType dt1(2);
//     IntType it1(2);    
//     int floatExp = 2.0f;
//     int doubleExp = 2.0;
//     int intExp = 2;
//     IntType itExp(2);
//     FloatType ftExp(2.0f);
//     DoubleType dtExp(2.0);
    
//     // Power tests with FloatType
//     std::cout << "Power tests with FloatType " << std::endl;
//     std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
//     std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
//     std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
//     std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
//     std::cout << "---------------------\n" << std::endl;  

//     // Power tests with DoubleType
//     std::cout << "Power tests with DoubleType " << std::endl;
//     std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
//     std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
//     std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
//     std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
//     std::cout << "---------------------\n" << std::endl;    

//     // Power tests with IntType
//     std::cout << "Power tests with IntType " << std::endl;
//     std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
//     std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
//     std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;    
//     std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;    
//     std::cout << "===============================\n" << std::endl; 

//     // ------------------------------------------------------------
//     //                          Point tests
//     // ------------------------------------------------------------
//     FloatType ft2(3.0f);
//     DoubleType dt2(4.0);
//     IntType it2(5);
//     float floatMul = 6.0f;

//     // Point tests with float
//     std::cout << "Point tests with float argument:" << std::endl;
//     Point p0(ft2, floatMul);
//     p0.toString();   
//     std::cout << "Multiplication factor: " << floatMul << std::endl;
//     p0.multiply(floatMul); 
//     p0.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with FloatType
//     std::cout << "Point tests with FloatType argument:" << std::endl;
//     Point p1(ft2, ft2);
//     p1.toString();   
//     std::cout << "Multiplication factor: " << ft2 << std::endl;
//     p1.multiply(ft2); 
//     p1.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with DoubleType
//     std::cout << "Point tests with FloatType argument:" << std::endl;
//     Point p2(ft2, static_cast<float>(dt2));
//     p2.toString();   
//     std::cout << "Multiplication factor: " << dt2 << std::endl;
//     p2.multiply(dt2); 
//     p2.toString();   
//     std::cout << "---------------------\n" << std::endl;

//     // Point tests with IntType
//     std::cout << "Point tests with IntType argument:" << std::endl;
//     Point p3(ft2, static_cast<float>(dt2));
//     p3.toString();   
//     std::cout << "Multiplication factor: " << it2 << std::endl;
//     p3.multiply(it2); 
//     p3.toString();   
//     std::cout << "---------------------\n" << std::endl;
// }

// void part6()
// {
//     FloatType ft3(3.0f);
//     DoubleType dt3(4.0);
//     IntType it3(5);
    
//     std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply( [](){} );
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
//     std::cout << "ft3 before: " << ft3 << std::endl;
//     ft3.apply(myFloatFreeFunct);
//     std::cout << "ft3 after: " << ft3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply( [](){} );
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
//     std::cout << "dt3 before: " << dt3 << std::endl;
//     dt3.apply(myDoubleFreeFunct);
//     std::cout << "dt3 after: " << dt3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;

//     std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;
//     it3.apply( [](){} );
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
//     std::cout << "it3 before: " << it3 << std::endl;//what's up
//     it3.apply(myIntFreeFunct);
//     std::cout << "it3 after: " << it3 << std::endl;
//     std::cout << "---------------------\n" << std::endl;    
// }

int main()
{   
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
    dt /= 5.0;
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
 
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;

    it /= 0;
    std::cout << "New value of it = it / 0 = " << it << std::endl;
    /*
    gotta figure out why it outputs:
   "New value of it = it / 0 = 590 warning: ..."
    insted of: 
    "New value of it = it / 0 = error: ... 590"
    */
    ft /= 0;
    std::cout << "New value of ft = ft / 0 = " << ft << std::endl;

    dt /= 0;
    std::cout << "New value of dt = dt / 0 = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    part3();
    // part4();
    // part6();
    std::cout << "good to go!\n";

    return 0;
}
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
