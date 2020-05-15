#include "notMain.cpp"
// here goes forward declaration

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


