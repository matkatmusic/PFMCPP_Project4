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

#include <iostream>

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << ft.add( 2.0f ).value << std::endl;
    std::cout << "FloatType subtract result=" << ft.subtract( 2.0f ).value << std::endl;
    std::cout << "FloatType multiply result=" << ft.multiply( 2.0f ).value << std::endl;
    std::cout << "FloatType divide result=" << ft.divide( 16.0f).value << std::endl << std::endl;

    std::cout << "DoubleType add result=" << dt.add(2.0).value << std::endl;
    std::cout << "DoubleType subtract result=" << dt.subtract(2.0).value << std::endl;
    std::cout << "DoubleType multiply result=" << dt.multiply(2.0).value << std::endl;
    std::cout << "DoubleType divide result=" << dt.divide(5.f).value << std::endl << std::endl;

    std::cout << "IntType add result=" << it.add(2).value << std::endl;
    std::cout << "IntType subtract result=" << it.subtract(2).value << std::endl;
    std::cout << "IntType multiply result=" << it.multiply(2).value << std::endl;
    std::cout << "IntType divide result=" << it.divide(3).value << std::endl << std::endl;
    std::cout << "Chain calculation = " << (it.multiply(1000).divide(2).subtract(10).add(100)).value << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft.add( 3.0f ).multiply(1.5f).divide(5.0f).value << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt.value << std::endl;
    std::cout << "Initial value of it: " << it.value << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << (dt.multiply(it).divide(5.0f).add(ft).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.divide(0).value << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.divide(0).value << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.divide(0).value << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    std::cout << "good to go!\n";

    return 0;
}



struct FloatType
{
    float add(float lhs, float rhs );
    float subtract(float  lhs, float rhs );
    float multiply(float  lhs, float rhs );
    float divide(float  lhs, float rhs );
};

float FloatType::add(float lhs, float rhs )
{
    return lhs + rhs;
}

float FloatType::subtract(float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply(float lhs, float rhs )
{
    return lhs * rhs;
}

float FloatType::divide(float lhs, float rhs )
{
    if (rhs == 0.0f)
    {
        std::cout << "\nwarning, floating point division by zero returns 'inf' !" << std::endl;
    }
    return lhs / rhs;
}
struct DoubleType
{
    double add(double lhs, double rhs );
    double subtract(double lhs, double rhs );
    double multiply(double lhs, double rhs );
    double divide(double lhs, double rhs );
};

double DoubleType::add(double lhs, double rhs )
{
    return lhs + rhs;
}

double DoubleType::subtract(double lhs, double rhs )
{
    return lhs - rhs;
}

double DoubleType::multiply(double lhs, double rhs )
{
    return lhs * rhs;
}

double DoubleType::divide(double lhs, double rhs )
{
    if (rhs == 0.00)
    {
        std::cout << "\nwarning, floating point division by zero returns 'inf' !" << std::endl;
    }
    return lhs / rhs;
}

struct IntType
{
    int add(int lhs, int rhs );
    int subtract(int lhs, int rhs );
    int multiply(int lhs, int rhs );
    double divide(int lhs, int rhs );
};

int IntType::add(int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract(int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply(int lhs, int rhs )
{
    return lhs * rhs;
}

double IntType::divide(int lhs, int rhs )
{
    if (rhs != 0)
    {
        return lhs / rhs;
    }
    std::cout << "error, integer division by zero will crash the program!"<< std::endl;
    std::cout<<"returning lhs" << std::endl;
    return lhs;    
}

int main() 
{
    FloatType ft;
    std::cout << "result of ft.add(): " << ft.add( 123.456f, 432.1f) << std::endl;
    std::cout << "result of ft.subtract(): " << ft.subtract( 123.456f, 432.1f) << std::endl;
    std::cout << "result of ft.multiply(): " << ft.multiply( 123.456f, 432.1f) << std::endl;
    std::cout << "result of ft.divide(): " << ft.divide( 123.456f, 432.1f) << std::endl;

    std::cout << "result of ft.add(): " << ft.add( 4444.56f, 0.0f)  << std::endl;
    std::cout << "result of ft.subtract(): " << ft.subtract( 4444.56f, 0.0f) << std::endl;
    std::cout << "result of ft.multiply(): " << ft.multiply( 4444.56f, 0.0f) << std::endl;
    std::cout << "result of ft.divide(): " << ft.divide( 4444.56f, 0.0f) << std::endl;

    DoubleType db;
    std::cout << "result of db.add(): " << db.add( 123.456, 432.1) << std::endl;
    std::cout << "result of db.subtract(): " << db.subtract( 123.456, 432.1) << std::endl;
    std::cout << "result of db.multiply(): " << db.multiply( 123.456, 432.1) << std::endl;
    std::cout << "result of db.divide(): " << db.divide( 123.456, 432.1) << std::endl;

    std::cout << "result of db.add(): " << db.add( 123.456, 0.0) << std::endl;
    std::cout << "result of db.subtract(): " << db.subtract( 123.456, 0.0) << std::endl;
    std::cout << "result of db.multiply(): " << db.multiply( 123.456, 0.0) << std::endl;
    std::cout << "result of db.divide(): " << db.divide( 123.456, 0.0) << std::endl;

    IntType i;
    std::cout << "result of i.add(): " << i.add( 10, 20) << std::endl;
    std::cout << "result of i.subtract(): " << i.subtract( 10, 20) << std::endl;
    std::cout << "result of i.multiply(): " << i.multiply( 10, 20) << std::endl;
    std::cout << "result of i.divide(): " << i.divide( 10, 20) << std::endl;

    std::cout << "result of i.add(): " << i.add( 10, 0) << std::endl;
    std::cout << "result of i.subtract(): " << i.subtract( 10, 0) << std::endl;
    std::cout << "result of i.multiply(): " << i.multiply( 10, 0) << std::endl;
    std::cout << "result of i.divide(): " << i.divide( 10, 0) << std::endl;

    std::cout << "good to go!" << std::endl;
}


