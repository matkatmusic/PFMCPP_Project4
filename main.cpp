/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 do not remove anything from main().  you'll be revising your main() to work with these new code changes.
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
        REMEMBER: if a member function doesn't modify any member variables of the class it exists in, what qualifier can we add to that function's signature?
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) make sure it compiles & runs without errors.
 
 7) use your knowledge of casting to remove any conversion warnings. 

 8) insert 'part3();' before the 'good to go' at the end of your main(); 
        move this part3 function to before main()

 9) click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
your program should generate the following output EXACTLY.
This includes the warnings.
The output should have zero warnings.
Use a service like https://www.diffchecker.com/diff to compare your output. 

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
good to go!
*/

#include <iostream>

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

public:
    FloatType(float floatTypeValue): value(new float(floatTypeValue)) {} 
    ~FloatType()
    {
        delete value;
    } 

    FloatType& add(float lhs);
    FloatType& subtract(float lhs);
    FloatType& multiply(float lhs);
    FloatType& divide(float lhs);  

    operator float() const;
    
};    
/*
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
*/ 
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

// ========== DOUBLE TYPE ========== //
/*
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
        std::cout << "error: integer division by zero is an error and will crash the program!" << std::endl; 
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
*/

/*
void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( ft ).multiply( ft ).divide( it ) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( 3 ).add( it ) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( pi ).multiply( dt ).subtract( ft ) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << it.multiply(it).divide(0).divide(0.0f).divide(0.0) << std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply( ft ) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( dt ).add( ft ).multiply( 24 ) << std::endl;
}
*/

// ========== MAIN ========== //

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );/*
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;*/

    std::cout << "FloatType add result=" << *ft.add( 2.0f ).value << std::endl;
    std::cout << "FloatType subtract result=" << *ft.subtract( 2.0f ).value << std::endl;
    std::cout << "FloatType multiply result=" << *ft.multiply( 2.0f ).value << std::endl;
    std::cout << "FloatType divide result=" << *ft.divide( 16.0f).value << std::endl << std::endl;
/*
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
*/
    std::cout << "good to go!\n";

    return 0;
}


