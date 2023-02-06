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



#include <iostream>

// forward declarations
struct DoubleType;
struct IntType;

struct FloatType
{
    FloatType (float initValue) : value(new float (initValue)) {}
    ~FloatType() 
    {
        delete value;
    }

    float* value; // no need to set to nullptr due to initialization in explicit constructor

    FloatType& add (float rhs)
    {
        *value += rhs; 
        return *this;
    }
    FloatType& add (const FloatType& ft);
    FloatType& add (const DoubleType& dt);
    FloatType& add (const IntType& it);
    
    FloatType& subtract (float rhs)
    {
        *value -= rhs;
        return *this;
    }
    FloatType& subtract (const FloatType& ft);
    FloatType& subtract (const DoubleType& dt);
    FloatType& subtract (const IntType& it);

    FloatType& multiply (float rhs)
    {
        *value *= rhs;
        return *this;
    }
    FloatType& multiply (const FloatType& ft);
    FloatType& multiply (const DoubleType& dt);
    FloatType& multiply (const IntType& it);


    FloatType& divide (float rhs)
    {
        if (rhs == 0.0f)
        {
            std::cout << "warning: floating point division by zero!"
                      << std::endl;
        }
        *value /= rhs;
        return *this;
    }
    FloatType& divide (const FloatType& ft);
    FloatType& divide (const DoubleType& dt);
    FloatType& divide (const IntType& it);

};

struct DoubleType
{
    DoubleType (double initValue) : value (new double(initValue)) {}
    ~DoubleType ()
    {
        delete value;
    }
    double* value;

    DoubleType& add (double rhs)
    {
        *value += rhs;
        return *this;
    }
    DoubleType& add (const DoubleType& dt);
    DoubleType& add (const FloatType& ft);
    DoubleType& add (const IntType& it);
    
    DoubleType& subtract (double rhs)
    {
        *value -= rhs;
        return *this;
    }
    DoubleType& subtract (const DoubleType& dt);
    DoubleType& subtract (const FloatType& ft);
    DoubleType& subtract (const IntType& it);
    
    DoubleType& multiply (double rhs)
    {
        *value *= rhs;
        return *this;
    }

    DoubleType& multiply (const DoubleType& dt);
    DoubleType& multiply (const FloatType& ft);
    DoubleType& multiply (const IntType& it);

    DoubleType& divide (double rhs)
    {
        if (rhs == 0.)
        {
            std::cout << "warning: floating point division by zero!"
                      << std::endl;
        }
        *value /= rhs;
        return *this;
    }

    DoubleType& divide (const DoubleType& dt);
    DoubleType& divide (const FloatType& ft);
    DoubleType& divide (const IntType& it);
};

struct IntType
{
    IntType(int initValue) : value(new int(initValue)) {}
    ~IntType() 
    {
        delete value;
    }

    int* value;

    IntType& add (int rhs)
    {
        *value += rhs;
        return *this;
    }

    IntType& add (const IntType& it);
    IntType& add (const FloatType& ft);
    IntType& add (const DoubleType& dt);

    IntType& subtract (int rhs)
    {
        *value -= rhs;
        return *this;
    }

    IntType& subtract (const IntType& it);
    IntType& subtract (const FloatType& ft);
    IntType& subtract (const DoubleType& dt);

    IntType& multiply (int rhs)
    {
        *value *= rhs;
        return *this;
    }

    IntType& multiply (const IntType& it);
    IntType& multiply (const FloatType& ft);
    IntType& multiply (const DoubleType& dt);
    
    IntType& divide (int rhs)
    {
        if (rhs == 0)
        {
            std::cout << "error: integer division by zero is "
                         "an error and will crash the program!"
                      << std::endl;
        }
        else
        {
            *value /= rhs;
        }
        return *this;
    }

    IntType& divide (const IntType& it);
    IntType& divide (const FloatType& ft);
    IntType& divide (const DoubleType& dt);
};


FloatType& FloatType::add (const FloatType& ft)
{
    return add (*ft.value);
}
FloatType& FloatType::add (const DoubleType& dt)
{
    return add (*dt.value);
}
FloatType& FloatType::add (const IntType& it)
{
    return add (*it.value);
}

FloatType& FloatType::subtract (const FloatType& ft)
{
    return subtract (*ft.value);
}
FloatType& FloatType::subtract (const DoubleType& dt)
{
    return subtract (*dt.value);
}
FloatType& FloatType::subtract (const IntType& it)
{
    return subtract (*it.value);
}

FloatType& FloatType::multiply (const FloatType& ft)
{
    return multiply (*ft.value);
}
FloatType& FloatType::multiply (const DoubleType& dt)
{
    return multiply (*dt.value);
}
FloatType& FloatType::multiply (const IntType& it)
{
    return multiply (*it.value);
}

FloatType& FloatType::divide (const FloatType& ft)
{
    return divide (*ft.value);
}
FloatType& FloatType::divide (const DoubleType& dt)
{
    return divide (*dt.value);
}
FloatType& FloatType::divide (const IntType& it)
{
    return divide (*it.value);
}

DoubleType& DoubleType::add (const DoubleType& dt)
{
    return add (*dt.value);
}
DoubleType& DoubleType::add (const FloatType& ft)
{
    return add (*ft.value);
}
DoubleType& DoubleType::add (const IntType& it)
{
    return add (*it.value);
}

DoubleType& DoubleType::subtract (const DoubleType& dt)
{
    return subtract (*dt.value);
}
DoubleType& DoubleType::subtract (const FloatType& ft)
{
    return subtract (*ft.value);
}
DoubleType& DoubleType::subtract (const IntType& it)
{
    return subtract (*it.value);
}

DoubleType& DoubleType::multiply (const DoubleType& dt)
{
    return multiply (*dt.value);
}
DoubleType& DoubleType::multiply (const FloatType& ft)
{
    return multiply (*ft.value);
}
DoubleType& DoubleType::multiply (const IntType& it)
{
    return multiply (*it.value);
}

DoubleType& DoubleType::divide (const DoubleType& dt)
{
    return divide (*dt.value);
}
DoubleType& DoubleType::divide (const FloatType& ft)
{
    return divide (*ft.value);
}
DoubleType& DoubleType::divide (const IntType& it)
{
    return divide (*it.value);
}

IntType& IntType::add (const IntType& it)
{
    return add (*it.value);
}
IntType& IntType::add (const FloatType& ft)
{
    return add (*ft.value);
}
IntType& IntType::add (const DoubleType& dt)
{
    return add (*dt.value);
}

IntType& IntType::subtract (const IntType& it)
{
    return subtract (*it.value);
}
IntType& IntType::subtract (const FloatType& ft)
{
    return subtract (*ft.value);
}
IntType& IntType::subtract (const DoubleType& dt)
{
    return subtract (*dt.value);
}

IntType& IntType::multiply (const IntType& it)
{
    return multiply (*it.value);
}
IntType& IntType::multiply (const FloatType& ft)
{
    return multiply (*ft.value);
}
IntType& IntType::multiply (const DoubleType& dt)
{
    return multiply (*dt.value);
}

IntType& IntType::divide (const IntType& it)
{
    return divide (*it.value);
}
IntType& IntType::divide (const FloatType& ft)
{
    return divide (*ft.value);
}
IntType& IntType::divide (const DoubleType& dt)
{
    return divide (*dt.value);
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


