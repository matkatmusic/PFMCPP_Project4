/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A {};
struct HeapA
{
    A* pointerToA = nullptr;

    HeapA( A* aPtr )
    { 
        pointerToA = aPtr;
    }

    ~HeapA()
    {
        delete pointerToA;
    }

};


/*
struct A;
struct HeapA
{
    HeapA( A& a_ ) : a( a_ ) { }

    A& a;
};
struct A
{
    A() : heapA( *this ) { }
    HeapA heapA;
};
*/

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>

struct FloatType;
struct DoubleType;
struct IntType;

struct FloatType
{
    float* floatPointer = nullptr;
    FloatType(float floatPrimitive);
    ~FloatType();

    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );

    int add(const IntType& it);
    float add(const FloatType& ft);
    double add(const DoubleType& dt);

    int subtract(const IntType& it);
    float subtract(const FloatType& ft);
    double subtract(const DoubleType& dt);

    int multiply(const IntType& it);
    float multiply(const FloatType& ft);
    double multiply(const DoubleType& dt);

    int divide(const IntType& it);
    float divide(const FloatType& ft);
    double divide(const DoubleType& dt);
};

struct DoubleType
{
    double* doublePointer = nullptr;
    DoubleType(double doublePrimitive);
    ~DoubleType();

    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );

    int add(const IntType& it);
    float add(const FloatType& ft);
    double add(const DoubleType& dt);

    int subtract(const IntType& it);
    float subtract(const FloatType& ft);
    double subtract(const DoubleType& dt);

    int multiply(const IntType& it);
    float multiply(const FloatType& ft);
    double multiply(const DoubleType& dt);

    int divide(const IntType& it);
    float divide(const FloatType& ft);
    double divide(const DoubleType& dt);    
};

struct IntType
{
    int* intPointer = nullptr;
    IntType(int IntPrimitive);
    ~IntType();

    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );

    int add(const IntType& it);
    float add(const FloatType& ft);
    double add(const DoubleType& dt);

    int subtract(const IntType& it);
    float subtract(const FloatType& ft);
    double subtract(const DoubleType& dt);

    int multiply(const IntType& it);
    float multiply(const FloatType& ft);
    double multiply(const DoubleType& dt);

    int divide(const IntType& it);
    float divide(const FloatType& ft);
    double divide(const DoubleType& dt);
};

FloatType::FloatType(float floatPrimitive) 
{
    floatPointer = new float(floatPrimitive);
}

FloatType::~FloatType() 
{
    delete floatPointer;
}

float FloatType::add( float lhs, float rhs )
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs )
{
    return lhs * rhs;
}

float FloatType::divide( float lhs, float rhs )
{
    if ( rhs <= 0.0f )
    {
        std::cout << "Warning division by zero." << std::endl;
    }
    return lhs / rhs;
}

DoubleType::DoubleType(double doublePrimitive) 
{
    doublePointer = new double(doublePrimitive);
}

DoubleType::~DoubleType() 
{
    delete doublePointer;
}

double DoubleType::add( double lhs, double rhs )
{
    return lhs + rhs;
}

double DoubleType::subtract( double lhs, double rhs )
{
    return lhs - rhs;
}

double DoubleType::multiply( double lhs, double rhs )
{
    return lhs * rhs;
}

double DoubleType::divide( double lhs, double rhs )
{
    if ( rhs <= 0.0 )
    {
        std::cerr << "Warning division by zero." << std::endl;
    }
    return lhs / rhs;
}

IntType::IntType(int intPrimitive) 
{
    intPointer = new int(intPrimitive);
}

IntType::~IntType() 
{
    delete intPointer;
}
int IntType::add( int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract( int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply( int lhs, int rhs )
{
    return lhs * rhs;
}

int IntType::divide( int lhs, int rhs )
{
    if ( rhs <= 0.0 )
    {
        std::cerr << "Warning division by zero." << std::endl;
        return lhs;
    } 
    else 
    {
        return lhs / rhs;
    }
}

int main()
{
    //FloatType ft(5.5f);
    //DoubleType dt(6.6);
    //IntType it(7);

    //auto resultFT = ft.add(3.2f, 23.f );       
    //std::cout << "result of ft.add(): " << resultFT << std::endl;

}
