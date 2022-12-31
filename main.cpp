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

#include <iostream>

struct A{}; 

struct HeapA 
{
    HeapA():pointerToA(new A){} 
    ~HeapA()
    {
        delete pointerToA;
    }

    A* pointerToA = nullptr;
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

 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

struct FloatType;
struct DoubleType; 
struct IntType;

struct FloatType 
{  
    float* value = nullptr;

    FloatType(float floatTypeValue): value(new float(floatTypeValue)) {} 
    ~FloatType()
    {
        delete value;
    }

    FloatType& add(float lhs);
    FloatType& subtract(float lhs);
    FloatType& multiply(float lhs);
    FloatType& divide(float lhs); 

    FloatType& add(const FloatType& lhs);
    FloatType& subtract(const FloatType& lhs);
    FloatType& multiply(const FloatType& lhs);
    FloatType& divide(const FloatType& lhs);

    FloatType& add(const IntType& lhs);
    FloatType& subtract(const IntType& lhs);
    FloatType& multiply(const IntType& lhs);
    FloatType& divide(const IntType& lhs);

    FloatType& add(const DoubleType& lhs);
    FloatType& subtract(const DoubleType& lhs);
    FloatType& multiply(const DoubleType& lhs);
    FloatType& divide(const DoubleType& lhs);
};    

struct DoubleType 
{  
    double* value = nullptr;

    DoubleType(double doubleTypeValue): value(new double(doubleTypeValue)) {} 
    ~DoubleType()
    {
        delete value;
    }

    DoubleType& add(double lhs);
    DoubleType& subtract(double lhs);
    DoubleType& multiply(double lhs);
    DoubleType& divide(double lhs); 

    DoubleType& add(const IntType& lhs);
    DoubleType& subtract(const IntType& lhs);
    DoubleType& multiply(const IntType& lhs);
    DoubleType& divide(const IntType& lhs);

    DoubleType& add(const FloatType& lhs);
    DoubleType& subtract(const FloatType& lhs);
    DoubleType& multiply(const FloatType& lhs);
    DoubleType& divide(const FloatType& lhs);

    DoubleType& add(const DoubleType& lhs);
    DoubleType& subtract(const DoubleType& lhs);
    DoubleType& multiply(const DoubleType& lhs);
    DoubleType& divide(const DoubleType& lhs);
};   

struct IntType 
{  
    int* value = nullptr;

    IntType(int intTypeValue): value(new int(intTypeValue)) {} 
    ~IntType()
    {
        delete value;
    }

    IntType& add(int lhs);
    IntType& subtract(int lhs);
    IntType& multiply(int lhs);
    IntType& divide(int lhs); 

    IntType& add(const IntType& lhs);
    IntType& subtract(const IntType& lhs);
    IntType& multiply(const IntType& lhs);
    IntType& divide(const IntType& lhs);

    IntType& add(const FloatType& lhs);
    IntType& subtract(const FloatType& lhs);
    IntType& multiply(const FloatType& lhs);
    IntType& divide(const FloatType& lhs);

    IntType& add(const DoubleType& lhs);
    IntType& subtract(const DoubleType& lhs);
    IntType& multiply(const DoubleType& lhs);
    IntType& divide(const DoubleType& lhs);
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
        std::cout << std::endl << "warning, floating point division by zero returns 'inf' !" << std::endl;
    *this->value /= lhs;
    return *this;
} 

FloatType& FloatType::add(const IntType& lhs)
{
    return add(*lhs.value);
}

FloatType& FloatType::subtract(const IntType& lhs)
{
    return subtract(*lhs.value);
}

FloatType& FloatType::multiply(const IntType& lhs)
{
    return multiply(*lhs.value);
}

FloatType& FloatType::divide(const IntType& lhs)
{
    return divide(*lhs.value);
}

FloatType& FloatType::add(const FloatType& lhs)
{
    return add(*lhs.value);
}

FloatType& FloatType::subtract(const FloatType& lhs)
{
    return subtract(*lhs.value);
}

FloatType& FloatType::multiply(const FloatType& lhs)
{
    return multiply(*lhs.value);
}

FloatType& FloatType::divide(const FloatType& lhs)
{
    return divide(*lhs.value);
}

FloatType& FloatType::add(const DoubleType& lhs)
{
    return add(*lhs.value);
}

FloatType& FloatType::subtract(const DoubleType& lhs)
{
    return subtract(*lhs.value);
}

FloatType& FloatType::multiply(const DoubleType& lhs)
{
    return multiply(*lhs.value);
}

FloatType& FloatType::divide(const DoubleType& lhs)
{
    return divide(*lhs.value);
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
        std::cout << std::endl << "warning, floating point division by zero returns 'inf' !" << std::endl;
    *this->value /= lhs;
    return *this;
}

DoubleType& DoubleType::add(const IntType& lhs)
{
    return add(*lhs.value);
}

DoubleType& DoubleType::subtract(const IntType& lhs)
{
    return subtract(*lhs.value);
}

DoubleType& DoubleType::multiply(const IntType& lhs)
{
    return multiply(*lhs.value);
}

DoubleType& DoubleType::divide(const IntType& lhs)
{
    return divide(*lhs.value);
}

DoubleType& DoubleType::add(const FloatType& lhs)
{
    return add(*lhs.value);
}

DoubleType& DoubleType::subtract(const FloatType& lhs)
{
    return subtract(*lhs.value);
}

DoubleType& DoubleType::multiply(const FloatType& lhs)
{
    return multiply(*lhs.value);
}

DoubleType& DoubleType::divide(const FloatType& lhs)
{
    return divide(*lhs.value);
}

DoubleType& DoubleType::add(const DoubleType& lhs)
{
    return add(*lhs.value);
}

DoubleType& DoubleType::subtract(const DoubleType& lhs)
{
    return subtract(*lhs.value);
}

DoubleType& DoubleType::multiply(const DoubleType& lhs)
{
    return multiply(*lhs.value);
}

DoubleType& DoubleType::divide(const DoubleType& lhs)
{
    return divide(*lhs.value);
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
        std::cout << "error, integer division by zero will crash the program!" << std::endl << "returning lhs" << std::endl; 
        return *this; 
    } 
    *this->value /= lhs;
    return *this;
} 

IntType& IntType::add(const IntType& lhs)
{
    return add(*lhs.value);
}

IntType& IntType::subtract(const IntType& lhs)
{
    return subtract(*lhs.value);
}

IntType& IntType::multiply(const IntType& lhs)
{
    return multiply(*lhs.value);
}

IntType& IntType::divide(const IntType& lhs)
{
    return divide(*lhs.value);
}

IntType& IntType::add(const FloatType& lhs)
{
    return add(*lhs.value);
}

IntType& IntType::subtract(const FloatType& lhs)
{
    return subtract(*lhs.value);
}

IntType& IntType::multiply(const FloatType& lhs)
{
    return multiply(*lhs.value);
}

IntType& IntType::divide(const FloatType& lhs)
{
    return divide(*lhs.value);
}

IntType& IntType::add(const DoubleType& lhs)
{
    return add(*lhs.value);
}

IntType& IntType::subtract(const DoubleType& lhs)
{
    return subtract(*lhs.value);
}

IntType& IntType::multiply(const DoubleType& lhs)
{
    return multiply(*lhs.value);
}

IntType& IntType::divide(const DoubleType& lhs)
{
    return divide(*lhs.value);
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

    std::cout << "FloatType add result=" << *ft.add( 2.0f ).value << std::endl;
    std::cout << "FloatType subtract result=" << *ft.subtract( 2.0f ).value << std::endl;
    std::cout << "FloatType multiply result=" << *ft.multiply( 2.0f ).value << std::endl;
    std::cout << "FloatType divide result=" << *ft.divide( 16.0f).value << std::endl << std::endl;

    std::cout << "DoubleType add result=" << *dt.add(2.0).value << std::endl;
    std::cout << "DoubleType subtract result=" << *dt.subtract(2.0).value << std::endl;
    std::cout << "DoubleType multiply result=" << *dt.multiply(2.0).value << std::endl;
    std::cout << "DoubleType divide result=" << *dt.divide(5.f).value << std::endl << std::endl;

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


