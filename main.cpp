/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed...
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */
struct A { };
struct HeapA
{
    A* a = nullptr;

    HeapA() : 
    a( new A() )
    { 
    
    }

    ~HeapA()
    {
        delete a;
    }
};




 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers named 'value'
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
        This technique of having multiple functions with the same name and different function arguments is known as 'function overloading' or 'overloaded functions'.
        This topic will be covered in Chapter 4 Part 7.
     
 5) Don't let your heap-allocated owned type leak!
 
 6) replace your main() with the main() below.
    It has some intentional mistakes that you need to fix to match the expected output
    i.e. don't forget to dereference your pointers to get the value they hold.
    Do not change any values being passed into the functions.

 7) click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
your program should generate the following output EXACTLY.
This includes the warnings.
Use a service like https://www.diffchecker.com/diff to compare your output. 
you'll learn to solve the conversion warnings in the next project part.

18 warnings generated.
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

good to go!

*/
#include<iostream>

struct DoubleType;
struct IntType;

struct FloatType
{
    FloatType(float float_);
    ~FloatType();

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);

    FloatType& add(const FloatType& ft);
    FloatType& subtract(const FloatType& ft);
    FloatType& multiply(const FloatType& ft);
    FloatType& divide(const FloatType& ft);

    FloatType& add(const DoubleType& dt);
    FloatType& subtract(const DoubleType& dt);
    FloatType& multiply(const DoubleType& dt);
    FloatType& divide(const DoubleType& dt);

    FloatType& add(const IntType& it);
    FloatType& subtract(const IntType& it);
    FloatType& multiply(const IntType& it);
    FloatType& divide(const IntType& it);
    float* value = nullptr;
};

FloatType::FloatType(float float_) : value( new float(float_) ) { }

FloatType::~FloatType() { delete value; }

FloatType& FloatType::add(float rhs)
{
    *value += rhs;
    return *this;
}

FloatType& FloatType::subtract(float rhs)
{
    *value -= rhs;
    return *this;
}

FloatType& FloatType::multiply(float rhs)
{
    *value *= rhs;
    return *this;
}

FloatType& FloatType::divide(float rhs)
{
    if(rhs == 0.0f)
    {
        std::cout << "warning: floating point division by zero!\n";
    }
    *value /= rhs;
    return *this;
}

//-----------------------------------------------------------------------
struct DoubleType
{
    DoubleType(double double_);
    ~DoubleType();

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs);

    DoubleType& add(const FloatType& ft);
    DoubleType& subtract(const FloatType& ft);
    DoubleType& multiply(const FloatType& ft);
    DoubleType& divide(const FloatType& ft);

    DoubleType& add(const DoubleType& dt);
    DoubleType& subtract(const DoubleType& dt);
    DoubleType& multiply(const DoubleType& dt);
    DoubleType& divide(const DoubleType& dt);

    DoubleType& add(const IntType& it);
    DoubleType& subtract(const IntType& it);
    DoubleType& multiply(const IntType& it);
    DoubleType& divide(const IntType& it);
    double* value = nullptr;

};

//-----------------------------------------------------------------------
struct IntType
{
    IntType(int int_);
    ~IntType();

    IntType& add(int rhs);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);

    IntType& add(const FloatType& ft);
    IntType& subtract(const FloatType& ft);
    IntType& multiply(const FloatType& ft);
    IntType& divide(const FloatType& ft);

    IntType& add(const DoubleType& dt);
    IntType& subtract(const DoubleType& dt);
    IntType& multiply(const DoubleType& dt);
    IntType& divide(const DoubleType& dt);

    IntType& add(const IntType& it);
    IntType& subtract(const IntType& it);
    IntType& multiply(const IntType& it);
    IntType& divide(const IntType& it);
    int* value = nullptr;
};
//-----------------------DEFINITIONS-------------------------------------

DoubleType::DoubleType(double double_) : value( new double(double_) ) { }
DoubleType::~DoubleType() { delete value; }

DoubleType& DoubleType::add(double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::subtract(double rhs)
{
    *value -= rhs;
    return *this;
}

DoubleType& DoubleType::multiply(double rhs)
{
    *value *= rhs;
    return *this;
}

DoubleType& DoubleType::divide(double rhs)
{
    if(rhs == 0.0)
    {
        std::cout << "warning: floating point division by zero!\n";
    }
    *value /= rhs;
    return *this;
}

IntType::IntType(int int_) : value(new int(int_) ) { }
IntType::~IntType() { delete value; }

IntType& IntType::add(int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::subtract(int rhs)
{
    *value -= rhs;
    return *this;
}

IntType& IntType::multiply(int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::divide(int rhs)
{
    if(rhs == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!\n";
    }
    else
    {
        *value /= rhs;
    }
    return *this;
}
//-----------------------------------------------------------------------
FloatType& FloatType::add(const FloatType& ft)
{
    return add(*ft.value);
}

FloatType& FloatType::subtract(const FloatType& ft)
{
    return subtract(*ft.value);
}

FloatType& FloatType::multiply(const FloatType& ft)
{
    return multiply(*ft.value);
}

FloatType& FloatType::divide(const FloatType& ft)
{
    return divide(*ft.value);
}

FloatType& FloatType::add(const DoubleType& dt)
{
    return add(*dt.value);
}

FloatType& FloatType::subtract(const DoubleType& dt)
{
    return subtract(*dt.value);
}

FloatType& FloatType::multiply(const DoubleType& dt)
{
    return multiply(*dt.value);
}

FloatType& FloatType::divide(const DoubleType& dt)
{
    return divide(*dt.value);
}

FloatType& FloatType::add(const IntType& it)
{
    return add(*it.value);
}

FloatType& FloatType::subtract(const IntType& it)
{
    return subtract(*it.value);
}

FloatType& FloatType::multiply(const IntType& it)
{
    return multiply(*it.value);
}

FloatType& FloatType::divide(const IntType& it)
{
    return divide(*it.value);
}

//-----------------------------------------------------------------------
DoubleType& DoubleType::add(const FloatType& ft)
{
    return add(*ft.value);
}

DoubleType& DoubleType::subtract(const FloatType& ft)
{
    return subtract(*ft.value);
}

DoubleType& DoubleType::multiply(const FloatType& ft)
{
    return multiply(*ft.value);
}

DoubleType& DoubleType::divide(const FloatType& ft)
{
    return divide(*ft.value);
}

DoubleType& DoubleType::add(const DoubleType& dt)
{
    return add(*dt.value);
}

DoubleType& DoubleType::subtract(const DoubleType& dt)
{
    return subtract(*dt.value);
}

DoubleType& DoubleType::multiply(const DoubleType& dt)
{
    return multiply(*dt.value);
}

DoubleType& DoubleType::divide(const DoubleType& dt)
{
    return divide(*dt.value);
}

DoubleType& DoubleType::add(const IntType& it)
{
    return add(*it.value);
}

DoubleType& DoubleType::subtract(const IntType& it)
{
    return subtract(*it.value);
}

DoubleType& DoubleType::multiply(const IntType& it)
{
    return multiply(*it.value);
}

DoubleType& DoubleType::divide(const IntType& it)
{
    return divide(*it.value);
}

//-----------------------------------------------------------------------
IntType& IntType::add(const FloatType& ft)
{
    return add(*ft.value);
}

IntType& IntType::subtract(const FloatType& ft)
{
    return subtract(*ft.value);
}

IntType& IntType::multiply(const FloatType& ft)
{
    return multiply(*ft.value);
}

IntType& IntType::divide(const FloatType& ft)
{
    return divide(*ft.value);
}

IntType& IntType::add(const DoubleType& dt)
{
    return add(*dt.value);
}

IntType& IntType::subtract(const DoubleType& dt)
{
    return subtract(*dt.value);
}

IntType& IntType::multiply(const DoubleType& dt)
{
    return multiply(*dt.value);
}

IntType& IntType::divide(const DoubleType& dt)
{
    return divide(*dt.value);
}

IntType& IntType::add(const IntType& it)
{
    return add(*it.value);
}

IntType& IntType::subtract(const IntType& it)
{
    return subtract(*it.value);
}

IntType& IntType::multiply(const IntType& it)
{
    return multiply(*it.value);
}

IntType& IntType::divide(const IntType& it)
{
    return divide(*it.value);
}

//--------------------------------------------------------------------------------
int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 );

    std::cout << "FloatType add result=" << *ft.add( 2.0f ).value << std::endl;
    std::cout << "FloatType subtract result=" << *ft.subtract( 2.0f ).value << std::endl;
    std::cout << "FloatType multiply result=" << *ft.multiply( 2.0f ).value << std::endl;
    std::cout << "FloatType divide result=" << *ft.divide( 16.0f).value << std::endl << std::endl;

    std::cout << "DoubleType add result=" << *dt.add(2.0).value << std::endl;
    std::cout << "DoubleType subtract result=" << *dt.subtract(2.0).value << std::endl;
    std::cout << "DoubleType multiply result=" << *dt.multiply(2.0).value << std::endl;
    std::cout << "DoubleType divide result=" << *dt.divide(5.0f).value << std::endl << std::endl;

    std::cout << "IntType add result=" << *it.add(2).value << std::endl;
    std::cout << "IntType subtract result=" << *it.subtract(2).value << std::endl;
    std::cout << "IntType multiply result=" << *it.multiply(2).value << std::endl;
    std::cout << "IntType divide result=" << *it.divide(3).value << std::endl << std::endl;
    std::cout << "Chain calculation = " << *(it.multiply(1000).divide(2).subtract(10).add(100)).value << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << *ft.add( 3.0f ).multiply(1.5f).divide(5.0f).value << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << *dt.value << std::endl;
    std::cout << "Initial value of it: " << *it.value << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << *(dt.multiply(it).divide(5.0f).add(ft).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << *it.divide(0).value << std::endl;
    std::cout << "New value of ft = ft / 0 = " << *ft.divide(0).value << std::endl;
    std::cout << "New value of dt = dt / 0 = " << *dt.divide(0).value << std::endl;

    std::cout << "---------------------\n" << std::endl; 

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
