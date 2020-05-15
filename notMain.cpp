
#include <iostream>

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

