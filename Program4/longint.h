#ifndef LONGINT_H
#define LONGINT_H
#include <iostream>
#include "deque.h"

using namespace std;

class LongInt {
	friend istream& operator>>(istream& in, LongInt& rhs); //checks how you input things
	friend ostream& operator<<(ostream& out, const LongInt& rhs); //checks how things display/print out
public:
	// Constructors
	LongInt(const string str); //constructor
	LongInt(const LongInt& rhs); //copy constructor
	LongInt(); // default constructor

	// Destructor
	~LongInt();

	// Arithmetic binary operators
	LongInt operator+(const LongInt& rhs) const; //add lhs and rhs
	LongInt operator-(const LongInt& rhs) const; //subtracts lhs and rhs

	// assignment operators
	const LongInt& operator=(const LongInt& rhs); //assignes lhs to the value of rhs

	// Logical binary operators
	bool operator< (const LongInt& rhs) const; //checks if lhs is less than rhs
	bool operator<=(const LongInt& rhs) const; //checks if lhs is less than or equal to rhs
	bool operator> (const LongInt& rhs) const; //checks if lhs is greater than rhs
	bool operator>=(const LongInt& rhs) const; //checks if lhs is greater than or less than rhs
	bool operator==(const LongInt& rhs) const; //checks if lhs is equal to rhs
	bool operator!=(const LongInt& rhs) const; //checks if lhs is not equal to rhs

private:
	Deque<char> digits;
	bool negative;
	void remove0s(); //function removes leading zeros
};

#endif