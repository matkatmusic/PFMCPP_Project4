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
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

#include <iostream>

struct FloatType
{
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

struct DoubleType
{
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

struct IntType
{
    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

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
    FloatType ft;

    auto resultFT = ft.add(3.2f, 23.f );       
    std::cout << "result of ft.add(): " << resultFT << std::endl;

    resultFT = ft.subtract(3.2f, 23.f );
    std::cout << "result of ft.subtract(): " << resultFT << std::endl;

    resultFT = ft.multiply(3.2f, 23.f );        
    std::cout << "result of ft.multiply(): " << resultFT << std::endl;

    resultFT = ft.divide(3.2f, 23.f );     
    std::cout << "result of ft.divide(): " << resultFT << std::endl;

    DoubleType dt;

    auto resultDT = dt.add(3.2, 23. );       
    std::cout << "result of dt.add(): " << resultDT << std::endl;

    resultDT = dt.subtract(3.2, 23. );
    std::cout << "result of dt.subtract(): " << resultDT << std::endl;

    resultDT = dt.multiply(3.2, 23. );        
    std::cout << "result of dt.multiply(): " << resultDT << std::endl;

    resultDT = dt.divide(3.2, 23. );     
    std::cout << "result of dt.divide(): " << resultDT << std::endl;

    IntType it;

    auto resultIT = it.add(3, 23 );       
    std::cout << "result of it.add(): " << resultIT << std::endl;

    resultIT = it.subtract(3, 23 );
    std::cout << "result of it.subtract(): " << resultIT << std::endl;

    resultIT = it.multiply(3, 23 );        
    std::cout << "result of it.multiply(): " << resultIT << std::endl;

    resultIT = it.divide(3, 23 );     
    std::cout << "result of it.divide(): " << resultIT << std::endl;

    std::cout << "good to go!" << std::endl;
}
