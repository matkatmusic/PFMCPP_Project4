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
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 

 9) insert 'part3();' before the 'good to go' at the end of your main(); 
        move this part3 function to before main()

 10) click the [run] button.  Clear up any errors or warnings as best you can.

your program should generate the following output.   The output should have zero warnings.
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

struct DoubleType;
struct IntType;
struct FloatType
{
    FloatType(float v) : value( new float(v) ) {}
    ~FloatType() { delete value; }

    FloatType& add(float f);
    FloatType& subtract(float f);
    FloatType& multiply(float f);
    FloatType& divide(float f);

    operator float() { return *value; }

private:
    float* value = nullptr;
};

struct DoubleType
{
    DoubleType(double v) : value( new double(v) ) {}
    ~DoubleType() { delete value; }


    DoubleType& add(double d);
    DoubleType& subtract(double d);
    DoubleType& multiply(double d);
    DoubleType& divide(double d);

    operator double() { return *value; }

private:
    double* value = nullptr;
};

struct IntType
{
    IntType(int v) : value( new int(v) ) {}
    ~IntType() { delete value; }


    IntType& add(int i);
    IntType& subtract(int i);
    IntType& multiply(int i);
    IntType& divide(int i); 

    operator int() { return *value; }

private:
    int* value = nullptr;
};

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
    if(f == 0.f) 
    { 
        std::cout << "WARNING: FloatType division by zero\n"; 
    }
    *value /= f;
    return *this;
}


// DoubleType Functions
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
    if(d == 0.0) 
    { 
        std::cout << "WARNING: DoubleType division by zero\n"; 
    }
    *value /= d;
    return *this;
}

// IntType Functions
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
    if(i == 0) 
    { 
        std::cout << "WARNING: IntType division by zero\n Returning unaltered IntType\n"; 
        return *this; 
    }
    *value /= i;
    return *this;
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

void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    std::cout << "The result of FloatType^4 divided by IntType is: " << static_cast<float>(ft.multiply( static_cast<float>(ft) ).multiply( static_cast<float>(ft) ).divide( static_cast<int>(it) ) ) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << static_cast<double>(dt.multiply( static_cast<double>(3) ).add( static_cast<int>(it) ) ) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << static_cast<int>(it.divide( static_cast<double>(pi) ).multiply( static_cast<double>(dt) ).subtract( static_cast<float>(ft) ) ) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << static_cast<int>(it.multiply( static_cast<int>(it) ).divide(0).divide( static_cast<int>(0.0f) ).divide( static_cast<int>(0.0) )<<std::endl;
    
    std::cout << "FloatType x IntType  =  " << static_cast<int>(it.multiply( static_cast<float>(ft) )<< std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << static_cast<int>(it.add( static_cast<double>(dt) ).add( static_cast<float>(ft) ).multiply( 24 ) ) << std::endl;
}

int main()
{   
    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << ( static_cast<float>( ft.add( 2.0f )) ) << std::endl;
    std::cout << "FloatType subtract result=" << ( static_cast<float>( ft.subtract( 2.0f )) ) << std::endl;
    std::cout << "FloatType multiply result=" << ( static_cast<float>( ft.multiply( 2.0f )) ) << std::endl;
    std::cout << "FloatType divide result=" << ( static_cast<float>(ft.divide( 16.0f)) ) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << ( static_cast<double>(dt.add(2.0)) ) << std::endl;
    std::cout << "DoubleType subtract result=" << ( static_cast<double>(dt.subtract(2.0)) ) << std::endl;
    std::cout << "DoubleType multiply result=" << ( static_cast<double>(dt.multiply(2.0)) ) << std::endl;
    std::cout << "DoubleType divide result=" << ( static_cast<double>(dt.divide( static_cast<double>(5.f)) ) ) << std::endl << std::endl;

    std::cout << "IntType add result=" << ( static_cast<int>(it.add(2)) ) << std::endl;
    std::cout << "IntType subtract result=" << ( static_cast<int>(it.subtract(2)) ) << std::endl;
    std::cout << "IntType multiply result=" << ( static_cast<int>(it.multiply(2)) ) << std::endl;
    std::cout << "IntType divide result=" << ( static_cast<int>(it.divide(3)) ) << std::endl << std::endl;
    std::cout << "Chain calculation = " << ( static_cast<int>(it.multiply(1000).divide(2).subtract(10).add(100)) ) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ( static_cast<float>(ft.add(3.0f).multiply(1.5f).divide(5.0f)) ) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << static_cast<double>(dt) << std::endl;
    std::cout << "Initial value of it: " << static_cast<int>(it) << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << ( static_cast<double>( dt.multiply( static_cast<int>(it) ).divide( static_cast<double>(5.0f) ).add( static_cast<double>(ft)) ) ) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << ( static_cast<int>(it.divide(0)) ) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ( static_cast<float>(ft.divide(0)) ) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << ( static_cast<double>(dt.divide(0)) ) << std::endl;

    std::cout << "---------------------\n" << std::endl; 

    part3();

    std::cout << "good to go!\n";

    return 0;
}


