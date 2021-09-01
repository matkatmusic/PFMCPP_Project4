/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

	Build/Run often with this task to make sure you're not breaking the code
with each step. I recommend committing after you get each step working so you
can revert to a working version easily if needed.

 0) in the blank space below, declare/define an empty struct named 'A' on a
single Line. on the lines below it, write a struct named 'HeapA' that correctly
shows how to own an instance of 'A' on the heap without leaking, without using
smart pointers.
 */

struct A {};

struct HeapA {
	A *ptrToA;
	HeapA() : ptrToA(new A) {
	}

	~HeapA() {
		delete ptrToA;
		ptrToA = nullptr;
	}
};

/*
1) Edit your 3 structs so that they own a heap-allocated primitive type without
using smart pointers named 'value' IntType should own a heap-allocated int, for
example.

2) give it a constructor that takes the appropriate primitive
   this argument will initialize the owned primitive's value.
		i.e. if you're owning an int on the heap, your ctor argument will
initialize that heap-allocated int's value.

3) modify those add/subtract/divide/multiply member functions from chapter 2 on
it a) make them modify the owned numeric type b) set them up so they can be
chained together. i.e. DoubleType dt(3.5);
			dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining

4) write add/subtract/divide/multiply member functions for each type that take
your 3 UDTs These are in addition to your member functions that take primitives
	   for example, IntType::divide(const DoubleType& dt);
	   These functions should return the result of calling the function that
takes the primitive. This technique of having multiple functions with the same
name and different function arguments is known as 'function overloading' or
'overloaded functions'. This topic will be covered in Chapter 4 Part 7.

5) Don't let your heap-allocated owned type leak!

6) replace your main() with the main() below.
   It has some intentional mistakes that you need to fix to match the expected
output i.e. don't forget to dereference your pointers to get the value they
hold.

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
New value of it = it / 0 = error: integer division by zero is an error and will
crash the program! 590 New value of ft = ft / 0 = warning: floating point
division by zero! inf New value of dt = dt / 0 = warning: floating point
division by zero! inf
---------------------

good to go!





*/

#include <iostream>
//need to declare first
struct FloatType;
struct DoubleType;
struct IntType;

struct FloatType {
	float *value;
	FloatType(float floatV) : value(new float(floatV)) {
	}
	~FloatType() {
		delete value;
		value = nullptr;
	}

	FloatType &add(float rhs);
	FloatType &subtract(float rhs);
	FloatType &multiply(float rhs);
	FloatType &divide(float rhs);

	FloatType &add(const DoubleType &dV);
	FloatType &subtract(const DoubleType &dV);
	FloatType &multiply(const DoubleType &dV);
	FloatType &divide(const DoubleType &dV);

	FloatType &add(const IntType &iV);
	FloatType &subtract(const IntType &iV);
	FloatType &multiply(const IntType &iV);
	FloatType &divide(const IntType &iV);
};

struct DoubleType {
	double *value;
	DoubleType(double doubleV) : value(new double(doubleV)) {
	}
	~DoubleType() {
		delete value;
		value = nullptr;
	}

	DoubleType &add(double rhs);
	DoubleType &subtract(double rhs);
	DoubleType &multiply(double rhs);
	DoubleType &divide(double rhs);

	DoubleType &add(const IntType &iV);
	DoubleType &subtract(const IntType &iV);
	DoubleType &multiply(const IntType &iV);
	DoubleType &divide(const IntType &iV);

	DoubleType &add(const FloatType &fV);
	DoubleType &subtract(const FloatType &fV);
	DoubleType &multiply(const FloatType &fV);
	DoubleType &divide(const FloatType &fV);
};

struct IntType {
	int *value;
	IntType(int intV) : value(new int(intV)) {
	}
	~IntType() {
		delete value;
		value = nullptr;
	}
	IntType &add(int rhs);
	IntType &subtract(int rhs);
	IntType &multiply(int rhs);
	IntType &divide(int rhs);
	IntType &add(const FloatType &fV);
	IntType &subtract(const FloatType &fV);
	IntType &multiply(const FloatType &fV);
	IntType &divide(const FloatType &fV);
	IntType &add(const DoubleType &dV);
	IntType &subtract(const DoubleType &dV);
	IntType &multiply(const DoubleType &dV);
	IntType &divide(const DoubleType &dV);
};

// Float - Float
FloatType &FloatType::add(float rhs) {
	*value += rhs;
	return *this;
}
FloatType &FloatType::subtract(float rhs) {
	*value -= rhs;
	return *this;
}
FloatType &FloatType::multiply(float rhs) {
	*value *= rhs;
	return *this;
}
FloatType &FloatType::divide(float rhs) {
	if (*value != 0.f) {
		*value /= rhs;
		return *this;
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Double-Double
DoubleType &DoubleType::add(double rhs) {
	*value += rhs;
	return *this;
}
DoubleType &DoubleType::subtract(double rhs) {
	*value -= rhs;
	return *this;
}
DoubleType &DoubleType::multiply(double rhs) {
	*value *= rhs;
	return *this;
}
DoubleType &DoubleType::divide(double rhs) {
	if (*value != 0.0) {
		*value /= rhs;
		return *this;
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Int-Int
IntType &IntType::add(int rhs) {
	*value += rhs;
	return *this;
}

IntType &IntType::subtract(int rhs) {
	*value -= rhs;
	return *this;
}
IntType &IntType::multiply(int rhs) {
	*value *= rhs;
	return *this;
}
IntType &IntType::divide(int rhs) {
	if (*value != 0) {
		*value /= rhs;
		return *this;
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

/*
 UDT-accepting member function implementations
*/

// Float - Double
FloatType &FloatType::add(const DoubleType &dV) {
	return add(*dV.value);
}
FloatType &FloatType::subtract(const DoubleType &dV) {
	return subtract(*dV.value);
}
FloatType &FloatType::multiply(const DoubleType &dV) {
	return multiply(*dV.value);
}
FloatType &FloatType::divide(const DoubleType &dV) {
	if (*dV.value != 0.0) {
		return divide(*dV.value);
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Float - Int
FloatType &FloatType::add(const IntType &iV) {
	return add(*iV.value);
}
FloatType &FloatType::subtract(const IntType &iV) {
	return subtract(*iV.value);
}
FloatType &FloatType::multiply(const IntType &iV) {
	return multiply(*iV.value);
}
FloatType &FloatType::divide(const IntType &iV) {
	if (*iV.value != 0) {
		return divide(*iV.value);
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Double-Int
DoubleType &DoubleType::add(const IntType &iV) {
	return add(*iV.value);
}
DoubleType &DoubleType::subtract(const IntType &iV) {
	return subtract(*iV.value);
}
DoubleType &DoubleType::multiply(const IntType &iV) {
	return multiply(*iV.value);
}
DoubleType &DoubleType::divide(const IntType &iV) {
	if (*iV.value != 0) {
		return divide(*iV.value);
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}
// Double-Float
DoubleType &DoubleType::add(const FloatType &fV) {
	return add(*fV.value);
}
DoubleType &DoubleType::subtract(const FloatType &fV) {
	return subtract(*fV.value);
}
DoubleType &DoubleType::multiply(const FloatType &fV) {
	return multiply(*fV.value);
}
DoubleType &DoubleType::divide(const FloatType &fV) {
	if (*fV.value != 0.f) {
		return divide(*fV.value);
	}
	std::cout << "error, integer division by zero will crash the program!"
			  << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Int-Float
IntType &IntType::add(const FloatType &fV) {
	return add(*fV.value);
}
IntType &IntType::subtract(const FloatType &fV) {
	return subtract(*fV.value);
}
IntType &IntType::multiply(const FloatType &fV) {
	return multiply(*fV.value);
}
IntType &IntType::divide(const FloatType &fV) {
	if (*fV.value != 0.f) {
		return divide(*fV.value);
	}
	std::cout << "error, integer division by zero will crash the program!" << std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

// Int-Double
IntType &IntType::add(const DoubleType &dV) {
	return add(*dV.value);
}
IntType &IntType::subtract(const DoubleType &dV) {
	return subtract(*dV.value);
}
IntType &IntType::multiply(const DoubleType &dV) {
	return multiply(*dV.value);
}
IntType &IntType::divide(const DoubleType &dV) {
	if (*dV.value != 0.0) {
		return divide(*dV.value);
	}
	std::cout << "error, integer division by zero will crash the program!"<< std::endl;
	std::cout << "returning lhs" << std::endl;
	return *this;
}

int main() {
	// testing instruction 0
	HeapA heapA;

	// assign heap primitives
	FloatType ft(2.0f);
	DoubleType dt(2);
	IntType it(2);

	std::cout << "FloatType add result=" << ft.add(2.0f).value << std::endl;
	std::cout << "FloatType subtract result=" << ft.subtract(2.0f).value << std::endl;
	std::cout << "FloatType multiply result=" << ft.multiply(2.0f).value << std::endl;
	std::cout << "FloatType divide result=" << ft.divide(16.0f).value << std::endl << std::endl;

	std::cout << "DoubleType add result=" << dt.add(2.0).value << std::endl;
	std::cout << "DoubleType subtract result=" << dt.subtract(2.0).value << std::endl;
	std::cout << "DoubleType multiply result=" << dt.multiply(2.0).value << std::endl;
	std::cout << "DoubleType divide result=" << dt.divide(5.f).value << std::endl << std::endl;

	std::cout << "IntType add result=" << it.add(2).value << std::endl;
	std::cout << "IntType subtract result=" << it.subtract(2).value << std::endl;
	std::cout << "IntType multiply result=" << it.multiply(2).valuev << std::endl;
	std::cout << "IntType divide result=" << it.divide(3).value << std::endl << std::endl;
	std::cout << "Chain calculation = " << (it.multiply(1000).divide(2).subtract(10).add(100)).value << std::endl;

	// FloatType object instanciation and method tests
	// --------
	std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft.add(3.0f).multiply(1.5f).divide(5.0f).value << std::endl;

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
