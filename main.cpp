/*
This is a compilation of everything you would have implemented in 
Project 4 parts 1-6

Your goal is to make main() work without generating any errors 
or warnings.  This main() is from a previous student's approved 
submission.

All of the instructions below are a summation of each project 
part's work, edited to reflect the changes you would have made 
in each project.

===========================
Create a branch named Part6

Purpose:  This project will take you through the process of 
writing a class that wraps a numeric type, beginning with 
writing simple member functions and ending with a fully 
templated class with lots of functionality. 

=============
Project 4 part 1 simplified instructions
=============
1) write 3 UDTs named FloatType, DoubleType, IntType.  
    use struct instead of class so everything is public by 
    default.

2) make each UDT own a heap-allocated primitive type without 
using smart pointers  
    i.e. IntType should own a heap-allocated int.

3) Don't let your heap-allocated owned type leak!

4) give it a single constructor that takes the appropriate 
primitive.
    this argument will initialize the owned primitive's value.
        i.e. if you're owning an int on the heap, your ctor 
        argument will initialize that heap-allocated int's value 
        via the member initializer list.

==============
Project 4 part 3 simplified instructions
==============
1) move all of your implementations out of the class.
    NO IN-CLASS IMPLEMENTATION ALLOWED

2) add user-defined conversion functions that convert to the 
numeric type your object holds.
    i.e. if your type holds an int, you'll need an operator int() 
    function.

3) make your member variable private.
    a) this conversion function should be the ONLY WAY to access 
    the held value.
    b) use the proper casting technique to invoke this conversion 
    function

==============
Project 4 part 4 simplified instructions
==============
1) add pow() functions, and a powInternal() function to each of 
your UDTs
    a) your pow() functions should call powInternal()
    b) add a pow() whose argument type is the primitive your UDT 
    owns.  the argument should be passed by copy.
    c) for each UDT in the file, your class should have pow() 
    overloads that take that UDT as the function argument.
        the argument should be passed as const ref
        i.e. if you had UDTs named IntType, FloatType, DoubleType
            in your IntType class, you'd have:
                pow(const IntType&),
                pow(const FloatType&),
                pow(const DoubleType&),
                and pow(int)
    d) be sure to remember the rules about what member functions 
    can be called on const objects.
        (const objects can only call their const member functions)
    e) the pow() functions should be chainable.
 
2) your powInternal() function should do something like this in 
its body:    *val = std::pow( *val, arg );
    a) where 'arg' is the passed-in type, converted to whatever 
    type your object is holding.
        i.e. if your UDT owns an int, then arg would be an int.
        if your UDT owns a float, then arg would be a float.
    b) std::pow's documentation is found here: 
    https://en.cppreference.com/w/cpp/numeric/math/pow so be sure 
    to include the proper header file listed there.
    c) powInternal() should be chainable.

==============
Project 4 part 5 simplified instructions
==============
1) implement overloaded math operators that modify the internal 
heap-allocated primitive.
    e.g. add() would become operator+=() because it modifies the 
    internal heap-allocated object.
    These math operators should allow for chaining.

2) implement the appropriate action in the member function. 
    i.e. your 'addition assignment' math operator should add the 
    function argument to your heap-allocated member variable.
    a) Be aware that floating point division by 0 is legal, but 
    integer division by 0 will crash your program.  
    b) Handle this possible input when you write your divide() 
    functions.
    c) you should warn the user if they're doing floating-point
    division-by-zero but not prevent the division from happening
    d) you should warn AND prevent the division from happening 
    if it is an integer-division-by-zero.

3) Your overloaded operators should only take primitives, passed 
by value.

==============
Project 4 part 6 simplified instructions
==============
1) add two member functions named "apply()" to each of your 
Heap-Allocated Numeric Type wrappers.
    both apply() functions should work with chaining
 
2) One of the apply() functions should takes a std::function<> 
object as the function argument.
    the std::function<> object should return *this;
 
3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
4) Make both of the member functions's Callable Function Parameter 
use your owned object as it's single parameter.  
    i.e. if you managed your owned object via a raw pointer, you'd 
    use this for your std::function argument:
        std::function<OwnedT&(T&)>    
 
5) be sure to practice safe std::function usage (make sure it's 
not a nullptr function being called)
 
6) Make your lambda & free function update the value of your held
object

7) modify the Point class below:
    a) implement the constructor that takes 2 primitives to 
    initialize the member variables.
    b) implement constructors that accept a single instance of 
    your UDTs.
    a) make the Point(UDT) constructor forward its argument to 
    the Point(float,float) constructor.

    b) overload the multiply() function so it can accept each of 
    your UDTs.  These overloaded functions should call and return
    the multiply(float) function.

*/
#include <iostream>
#include <cmath>


struct FloatType;
struct DoubleType;
struct IntType;


struct FloatType // wrote UDT part 1 - 1)
{
    FloatType(float _float); //Part 1 - 4) 
    ~FloatType();
    operator float() { return *ownedVariable; }
    FloatType& pow(const IntType&); 
    FloatType& pow(const FloatType&); 
    FloatType& pow(const DoubleType&); 
    FloatType& pow(float); 
    FloatType& powInternal(); 
private: // Part 3 - 3)
    float* ownedVariable;
};

struct DoubleType
{
    DoubleType(double _double);
    ~DoubleType();
    operator double() { return *ownedVariable; }
    DoubleType& pow(const IntType&);
    DoubleType& pow(const FloatType&);
    DoubleType& pow(const DoubleType&);
    DoubleType& pow(double);
    DoubleType& powInternal();
private:
    double* ownedVariable;
};

struct IntType
{
    IntType(int _int);
    ~IntType();
    operator int() { return *ownedVariable; }
    IntType& pow(const IntType&);
    IntType& pow(const FloatType&);
    IntType& pow(const DoubleType&);
    IntType& pow(int);
    IntType& powInternal();
private:
    int* ownedVariable;
};


struct Point
{
Point(float, float) : x{0}, y {0}; //Part 6 - 7)
Point(FloatType);
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    void toString()
    {
        std::cout << "The x coordinate is: " << x << "\nThe y coordinate is: " << y << std::endl;
    }
private:
    float x{0}, y{0};
};



//moved implemetations out of class. part 3 - 1)
FloatType::FloatType(float _float) : ownedVariable(new float(_float)) { } // made heap-allocated primitive type. Part 1 -2) 
FloatType::~FloatType() { delete ownedVariable; ownedVariable = nullptr; }// prevents heap allocating type from leaking Part1 - 3)
//void FloatType::float() {return *ownedVariable} // - tried to move this function out of class, not sure why I can't


DoubleType::DoubleType(double _double) : ownedVariable(new double(_double)) { }
DoubleType::~DoubleType() {delete ownedVariable; ownedVariable = nullptr; }
//void DoubleType::double() {return *ownedVariable}


IntType::IntType(int _int) : ownedVariable(new int (_int)){ }
IntType::~IntType() { delete ownedVariable; ownedVariable = nullptr;}
//void IntType::int() {return *ownedVariable}

Point::Point();

//Point::Point(FloatType) {}
//Point::Point(DoubleType) {}
//Point::Point(IntType) {}
//         Free Functions               

void updateValue( float& value)
{
    value += value;
}

void updateValue( double& value)
{
    value += value;
}

void updateValue( int& value)
{
    value += value;
}

void divider()
{
    std::cout << "\n\n===============================\n\n";
}










int main()
{ 
    /*
    divider();

    FloatType ft(3.2f);
    DoubleType dt(8.473276);
    IntType it(19);

    std::cout << "The starting value of FloatType 'ft' is: " << static_cast<float>(ft) << std::endl;
    std::cout << "The starting value of DoubleType 'dt' is: " << static_cast<double>(dt) << std::endl;
    std::cout << "The starting value of IntType 'it' is: " << static_cast<int>(it) << std::endl;

    divider();

    ft += 5.4f;
    ft *= 6;

    std::cout << "We can add (5.4) to 'ft' and multiply 'it' by (6) which equals: " << static_cast<float>(ft) << std::endl;
 
    dt /= 2.2;
    dt += 0.86;

    std::cout << "We can divde 'dt' by (2.2) and add (0.86) which equals: " << static_cast<double>(dt) << std::endl;

    it -= 10;
    it *= 12;
    it /= static_cast<int>(ft);

    std::cout << "We can subtract (10) from 'it' and multiply by (12) and divide by ft(" << static_cast<float>(ft) << ") which equals: " << static_cast<int>(it) << std::endl;
 
    divider();

    std::cout << "We will find that we cannot divide 'it' by a number less than 1:\n"; 
    std::cout << "it(" << static_cast<int>(it) << ") divided by 0.2 throws an error:\n";
    std::cout << ( it /= static_cast<int>(0.2) ) << std::endl;

    divider();

    dt *= static_cast<double>(it);
    dt += static_cast<double>(ft);

    std::cout << "But we can use all types together.  The result of 'dt' times 'it' plus 'ft' is: " << static_cast<double>(dt) <<std::endl;

    divider();

    std::cout << "Ft is currently: " << static_cast<float>(ft) << std::endl;
    std::cout << "ft pow of 3: " << ft.pow( 3 ) << std::endl;
    std::cout << "it is currently: " << static_cast<int>(it) << std::endl;
    std::cout << "it pow of 2: " << it.pow( 2 ) << std::endl;
    std::cout << "dt is currently: " << static_cast<double>(dt) << std::endl;
    std::cout << "dt pow of 1.2: " << dt.pow( 1.2 ) << std::endl;

    std::cout << "Chaining makes ridiculous numbers: " << ft.pow(it).pow(3) << std::endl;

    divider();

    Point pt( 2.f, 3.f );

    std::cout << "pt's initial points are:\n";
    pt.toString();

    pt *= static_cast<float>(ft);

    std::cout << "pt multiplied by ft is:\n";
    // pt.multiply(ft);
    pt.toString();

    pt *= static_cast<float>(it);


    std::cout << "then pt multiplied by it is:\n";
    // pt.multiply(it);
    pt.toString();

    DoubleType dtp( 5.67893 );
    Point pdt( dtp );

    divider();

    std::cout << "pdt initialized with a DoubleType has these points:\n";
    pdt.toString();
    std::cout << "And then multiplied by the initializing DoubleType moves the point:\n";
    // pdt.multiply(dtp);

    pdt *= static_cast<float>(dtp);

    pdt.toString();

    divider();

    std::cout << "The apply() function applies the current value of the current object to itself.\n\n";

    FloatType ftA(4.5f);

    std::cout << "FtA is currently: " << static_cast<float>(ftA) << std::endl;
    
    ftA.apply( [&ftA]( float &a ) -> FloatType&
    {
        a += a;
        return ftA;    
    } );
    
    std::cout << "FtA applied to itself by lambda is: " << static_cast<float>(ftA) << std::endl;

    ftA.apply( updateValue );

    std::cout << "FtA applied to itself via function pointer is: " << static_cast<float>(ftA) << std::endl;

    divider();

    DoubleType dtA(7.894561);

    std::cout << "dtA is currently: " << static_cast<double>(dtA) << std::endl;
    
    dtA.apply( [&dtA]( double &a ) -> DoubleType&
    {
        a += a;
        return dtA;    
    } );
    
    std::cout << "dtA applied to itself by lambda is: " << static_cast<double>(dtA) << std::endl;

    dtA.apply( updateValue );

    std::cout << "dtA applied to itself via function pointer is: " << static_cast<double>(dtA) << std::endl;

    divider();

    IntType itA(495);

    std::cout << "itA is currently: " << static_cast<int>(itA) << std::endl;
    
    itA.apply( [&itA]( int &a ) -> IntType&
    {
        a += a;
        return itA;    
    } );
    
    std::cout << "itA applied to itself by lambda is: " << static_cast<int>(itA) << std::endl;

    itA.apply( updateValue );

    std::cout << "itA applied to itself via function pointer is: " << static_cast<int>(itA) << std::endl;

    divider();

    std::cout << "good to go!" << std::endl;
    */
}


