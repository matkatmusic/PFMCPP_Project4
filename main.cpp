/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1

 Purpose:  This project will take you through the process of writing a class that wraps a numeric type, beginning with writing simple member functions and ending with a fully templated class with lots of functionality. 
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.

 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );

       lhs is the left-hand-side of the operation, rhs is the right-hand-side
       e.g. x = 2 + 3
              '2' is the lhs
              '3' is the rhs
              '+' is the operation

 3) implement the appropriate action in the member function. 
         a) Be aware that floating point division by 0 is legal, but integer division by 0 will crash your program.  
         b) Handle this possible input when you write your divide() functions.
         c) you should warn the user if they're doing floating-point-division-by-zero but not prevent the division from happening
         d) you should warn AND prevent the division from happening if it is an integer-division-by-zero.
 
 4) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 5) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 6) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 7) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>

struct FloatType
{
    float add(float lhs, float rhs);
    float subtract(float lhs, float rhs);
    float multiply(float lhs, float rhs);
    float divide(float lhs, float rhs);
};

float FloatType::add(float lhs, float rhs)
{
    return lhs + rhs;
}

float FloatType::subtract(float lhs, float rhs)
{
    return lhs - rhs;
}

float FloatType::multiply(float lhs, float rhs)
{
    return lhs * rhs;
}

float FloatType::divide(float lhs, float rhs)
{
    if(rhs == 0.f) { std::cout << "WARNING: FloatType division by zero\n"; }
    return lhs / rhs;
}

struct DoubleType
{
    double add(double lhs, double rhs);
    double subtract(double lhs, double rhs);
    double multiply(double lhs, double rhs);
    double divide(double lhs, double rhs);
};

double DoubleType::add(double lhs, double rhs)
{
    return lhs + rhs;
}

double DoubleType::subtract(double lhs, double rhs)
{
    return lhs - rhs;
}

double DoubleType::multiply(double lhs, double rhs)
{
    return lhs * rhs;
}

double DoubleType::divide(double lhs, double rhs)
{
    if(rhs == 0.0) { std::cout << "WARNING: DoubleType division by zero\n"; }
    return lhs / rhs;
}

struct IntType
{
    int add(int lhs, int rhs );
    int subtract(int lhs, int rhs );
    int multiply(int lhs, int rhs );
    int divide(int lhs, int rhs ); 
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

int IntType::divide(int lhs, int rhs)
{
    if(rhs == 0) 
    { 
        std::cout << "WARNING: IntType division by zero\nReturning 0\n"; 
        return 0; 
    }
    return lhs / rhs;
}



int main()
{
    IntType it;
    FloatType ft;
    DoubleType dt;

    auto result1 = it.add(3,4);
    std::cout << "result of it.add(): " << result1 << std::endl;
    auto result2 = it.subtract(3,3);
    std::cout << "result of it.subtract(): " << result2 << std::endl;
    auto result3 = it.divide(2,0);
    std::cout << "result of it.divide(): " << result3 << std::endl;

    auto result4 = ft.multiply(3.1f,4.3f);
    std::cout << "result of ft.multiply(): " << result4 << std::endl;
    auto result5 = ft.subtract(3.3f,-3.1f);
    std::cout << "result of ft.subtract(): " << result5 << std::endl;
    auto result6 = ft.divide(2.1231f,0.0f);
    std::cout << "result of ft.divide(): " << result6 << std::endl;

    auto result7 = dt.multiply(-3.1,4.32);
    std::cout << "result of dt.multiply(): " << result7 << std::endl;
    auto result8 = dt.subtract(3.3,3.13);
    std::cout << "result of dt.subtract(): " << result8 << std::endl;
    auto result9 = dt.divide(-321.1, 0.0);
    std::cout << "result of dt.divide(): " << result9 << std::endl;

    std::cout << "good to go!" << std::endl;
}
