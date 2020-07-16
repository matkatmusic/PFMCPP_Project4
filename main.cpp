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
    float* value = nullptr;
    FloatType(float floatPrimitive);
    ~FloatType();

    FloatType& add(float f);
    FloatType& subtract(float f);
    FloatType& multiply(float f);
    FloatType& divide(float f);

    FloatType& add(const IntType& it);
    FloatType& add(const FloatType& ft);
    FloatType& add(const DoubleType& dt);

    FloatType& subtract(const IntType& it);
    FloatType& subtract(const FloatType& ft);
    FloatType& subtract(const DoubleType& dt);

    FloatType& multiply(const IntType& it);
    FloatType& multiply(const FloatType& ft);
    FloatType& multiply(const DoubleType& dt);

    FloatType& divide(const IntType& it);
    FloatType& divide(const FloatType& ft);
    FloatType& divide(const DoubleType& dt);
};

struct DoubleType
{
    double* value = nullptr;
    DoubleType(double doublePrimitive);
    ~DoubleType();

    DoubleType& add(double d);
    DoubleType& subtract(double d);
    DoubleType& multiply(double d);
    DoubleType& divide(double d);

    DoubleType& add(const IntType& it);
    DoubleType& add(const FloatType& ft);
    DoubleType& add(const DoubleType& dt);

    DoubleType& subtract(const IntType& it);
    DoubleType& subtract(const FloatType& ft);
    DoubleType& subtract(const DoubleType& dt);

    DoubleType& multiply(const IntType& it);
    DoubleType& multiply(const FloatType& ft);
    DoubleType& multiply(const DoubleType& dt);

    DoubleType& divide(const IntType& it);
    DoubleType& divide(const FloatType& ft);
    DoubleType& divide(const DoubleType& dt);    
};

struct IntType
{
    int* value = nullptr;
    IntType(int IntPrimitive);
    ~IntType();

    IntType& add(int i);
    IntType& subtract(int i);
    IntType& multiply(int i);
    IntType& divide(int i);

    IntType& add(const IntType& it);
    IntType& add(const FloatType& ft);
    IntType& add(const DoubleType& dt);

    IntType& subtract(const IntType& it);
    IntType& subtract(const FloatType& ft);
    IntType& subtract(const DoubleType& dt);

    IntType& multiply(const IntType& it);
    IntType& multiply(const FloatType& ft);
    IntType& multiply(const DoubleType& dt);

    IntType& divide(const IntType& it);
    IntType& divide(const FloatType& ft);
    IntType& divide(const DoubleType& dt);
};

/* FloatType member function definitions */
FloatType::FloatType(float floatPrimitive) 
{
    value = new float(floatPrimitive);
}

FloatType::~FloatType() 
{
    delete value;
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
    if (f <= 0.0f)
    {
        std::cout << "Warning division by zero." << std::endl;
        return *this;
    }
    else
    {
        *value /= f;
        return *this;
    }
}

FloatType& FloatType::add(const IntType& it)
{
    return add( (float) *it.value );
}

FloatType& FloatType::add(const FloatType& ft)
{
    return add( *ft.value );
}

FloatType& FloatType::add(const DoubleType& dt)
{
    return add( (float) *dt.value );
}

FloatType& FloatType::subtract(const IntType& it)
{
    return subtract( (float) *it.value );
}

FloatType& FloatType::subtract(const FloatType& ft)
{
    return subtract( *ft.value );
}

FloatType& FloatType::subtract(const DoubleType& dt)
{
    return subtract( (float) *dt.value );
}

FloatType& FloatType::multiply(const IntType& it)
{
    return multiply( (float) *it.value );
}

FloatType& FloatType::multiply(const FloatType& ft)
{
    return multiply( *ft.value );
}

FloatType& FloatType::multiply(const DoubleType& dt)
{
    return multiply( (float) *dt.value );
}

FloatType& FloatType::divide(const IntType& it)
{
    return divide( (float) *it.value );
}

FloatType& FloatType::divide(const FloatType& ft)
{
    return divide( (float) *ft.value );
}

FloatType& FloatType::divide(const DoubleType& dt)
{
    return divide( (float) *dt.value );
}

/* DoubleType member function definitions */

DoubleType::DoubleType(double doublePrimitive) 
{
    value = new double(doublePrimitive);
}

DoubleType::~DoubleType() 
{
    delete value;
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
    if (d <= 0.0)
    {
        std::cerr << "Warning division by zero." << std::endl;
        return *this;
    }
    else
    {
        *value /= d;
        return *this;
    }
}

DoubleType& DoubleType::add(const IntType& it)
{
    return add( (double) *it.value );
}

DoubleType& DoubleType::add(const FloatType& ft)
{
    return add( (double) *ft.value );
}

DoubleType& DoubleType::add(const DoubleType& dt)
{
    return add( (double) *dt.value );
}

DoubleType& DoubleType::subtract(const IntType& it)
{
    return subtract( (double) *it.value );
}

DoubleType& DoubleType::subtract(const FloatType& ft)
{
    return subtract( (double) *ft.value );
}

DoubleType& DoubleType::subtract(const DoubleType& dt)
{
    return subtract( (double) *dt.value );
}

DoubleType& DoubleType::multiply(const IntType& it)
{
    return multiply( (double) *it.value );
}

DoubleType& DoubleType::multiply(const FloatType& ft)
{
    return multiply( (double) *ft.value );
}

DoubleType& DoubleType::multiply(const DoubleType& dt)
{
    return multiply( (double) *dt.value );
}

DoubleType& DoubleType::divide(const IntType& it)
{
    return divide( (double) *it.value );
}

DoubleType& DoubleType::divide(const FloatType& ft)
{
    return divide( (double) *ft.value );
}

DoubleType& DoubleType::divide(const DoubleType& dt)
{
    return divide( (double) *dt.value );
}

/* IntType member function definitions */

IntType::IntType(int intPrimitive) 
{
    value = new int(intPrimitive);
}

IntType::~IntType() 
{
    delete value;
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
    if (i <= 0.0)
    {
        std::cerr << "Warning division by zero." << std::endl;
        return *this;
    } 
    else 
    {
        *value /= i;
        return *this;
    }
}

IntType& IntType::add(const IntType& it)
{
    return add( (int) *it.value );
}

IntType& IntType::add(const FloatType& ft)
{
    return add( (int) *ft.value );
}

IntType& IntType::add(const DoubleType& dt)
{
    return add( (int) *dt.value );
}

IntType& IntType::subtract(const IntType& it)
{
    return subtract( (int) *it.value );
}

IntType& IntType::subtract(const FloatType& ft)
{
    return subtract( (int) *ft.value );
}

IntType& IntType::subtract(const DoubleType& dt)
{
    return subtract( (int) *dt.value );
}

IntType& IntType::multiply(const IntType& it)
{
    return multiply( (int) *it.value );
}

IntType& IntType::multiply(const FloatType& ft)
{
    return multiply( (int) *ft.value );
}

IntType& IntType::multiply(const DoubleType& dt)
{
    return multiply( (int) *dt.value );
}

IntType& IntType::divide(const IntType& it)
{
    return divide( (int) *it.value );
}

IntType& IntType::divide(const FloatType& ft)
{
    return divide( (int) *ft.value );
}

IntType& IntType::divide(const DoubleType& dt)
{
    return divide( (int) *dt.value );
}

int main()
{
    FloatType ft(4.44f);
    DoubleType dt(5.555);
    IntType it(3);

    ft.add(10.0f).subtract(10.0f).multiply(10.0f).divide(10.0f);
    ft.add(it).subtract(it).multiply(it).divide(it);

    dt.add(10.0).subtract(10.0).multiply(10.0).divide(10.0);

    it.add(10.0).subtract(10.0).multiply(10.0).divide(10.0);

    std::cout << "FloatType chained operations result is: " << *ft.value << std::endl;
    std::cout << "DoubleType chained operations result is: " << *dt.value << std::endl;
    std::cout << "IntType chained operations result is: " << *it.value << std::endl;
}
