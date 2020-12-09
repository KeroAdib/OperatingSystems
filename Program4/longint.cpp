#include "longint.h"
#include "deque.h"

//input operator overloading -- reads characters '0' through '9' from the keyboard as well as accept '-' if it is the first character
istream& operator>>(istream& in, LongInt& rhs) {
  rhs.negative = false;
  rhs.digits.clear();
  string str;
  in >> str;
  int input = 0;
  if (str[input] == '-') {
    rhs.negative = true;
    input++;
  }
  for (; input < str.size(); input++) {
    if (isdigit(str[input])) {
      rhs.digits.addBack(str[input]);
    } 
    if (!isdigit(str[input]) && rhs.digits.isEmpty()) {
      rhs.digits.addBack('0');
    }
  }
  rhs.remove0s();
  return in;
}

//output operator overloading -- print out a given LongInt object's digits as an integer. If the LongInt object's digits is empty or 0,it should be printed out as 0 without a negative sign
ostream& operator<<(ostream& out, const LongInt& rhs) {
  LongInt copy(rhs);
  if (copy.digits.isEmpty()) {
    out << "0";
    return out;
  }
  if (copy.negative) {
    out << "-";
  }
  while (!copy.digits.isEmpty()) {
    out << copy.digits.removeFront();
  }
  return out;
}

//constructor -- reads a string to convert to a Deque
LongInt::LongInt(const string str) {
  int input = 0;
  //if the input is a negative number return true, if its not then return false.
  if (str[input] == '-') {
    negative = true;
    input++;
  } else {
    negative = false;
  }
  //insert numbers to the queue
  for (; input < str.size(); input++) {
    if (isdigit(str[input])) digits.addBack(str[input]); 
    if (!isdigit(str[input]) && digits.isEmpty()) digits.addBack('0');
  }
  remove0s();
}

//copy constructor
LongInt::LongInt(const LongInt& rhs) {
  digits = rhs.digits;
  negative = rhs.negative;
}

//default constructor
LongInt::LongInt() {
  negative = false;
}

//destructor
LongInt::~LongInt() {
  negative = false;
  digits.clear();
}

//removes any leading/preceeding zeros
//if given a = 000123, a should be a=123
void LongInt::remove0s() {
  if (!this->digits.isEmpty()) {
    while (this->digits.getFront() == '0' && this->digits.size() > 1) {
      this->digits.removeFront();
    }
  }

  if (this->digits.getFront() == '0') {
    this->negative = false;
  }
}

//-------------------------Arithmetic Operators--------------------
//Overloaded + operator that adds long ints.
//function adds two long ints together. Returns the long int after adding two long ints.
LongInt LongInt::operator+(const LongInt& rhs) const {
  LongInt copyRhs(rhs);
  LongInt copyLhs(*this);
  LongInt returnValue = LongInt();
  if (copyLhs.negative && !copyRhs.negative) {
    copyLhs.negative = !copyLhs.negative;
    returnValue = copyRhs - copyLhs;
  } else if (!copyLhs.negative && copyRhs.negative) {
    copyRhs.negative = !copyRhs.negative;
    returnValue = copyLhs - copyRhs;
  } else {
    Deque<char> lDeque = copyLhs.digits;
    Deque<char> rDeque = copyRhs.digits;
    bool addBool = false;
    returnValue.negative = copyLhs.negative;
    while (!lDeque.isEmpty() || !rDeque.isEmpty()) {
      int l = 0;
      int r = 0;
      int add;
      if (!lDeque.isEmpty()) {
        l = lDeque.removeBack() - '0';
      }
      if (!rDeque.isEmpty()) {
        r = rDeque.removeBack() - '0';
      }
      add = l + r + addBool;
      if (add > 9) {
        addBool = true;
        add -= 10;
      } else{
        addBool = false;
      }
      returnValue.digits.addFront(add + '0');
    }
    if (addBool) {
      returnValue.digits.addFront(1 + '0');
    }
  }
  returnValue.remove0s();
  return returnValue;
}

//Overloaded - operator that subtracts two long ints.
//function subtracts two long ints. Returns the long int after suubtracting two longints.
LongInt LongInt::operator-(const LongInt& rhs) const {
  LongInt copyRhs(rhs);
  LongInt copyLhs(*this);
  LongInt returnValue = LongInt();
  if (!copyLhs.negative && copyRhs.negative) {
    copyRhs.negative = false;
    returnValue = copyLhs + copyRhs;
  } else if (copyLhs.negative && !copyRhs.negative) {
    copyLhs.negative = false;
    returnValue = copyRhs + copyLhs;
    returnValue.negative = true;
  } else if (copyLhs.negative && copyRhs.negative) {
    copyLhs.negative = false;
    copyRhs.negative = false;
    returnValue = copyRhs - copyLhs;
    returnValue.negative = true;
  } else {
    bool lBool = copyLhs.negative;
    bool rBool = copyRhs.negative;
    copyLhs.negative = false;
    copyRhs.negative = false;
    if (copyLhs > copyRhs) {
      bool subBool = false;
      Deque<char> lDeque = copyLhs.digits;
      Deque<char> rDeque = copyRhs.digits;
      while (!lDeque.isEmpty() || !rDeque.isEmpty()) {
        int l = 0;
        int r = 0;
        int sub;
        if (!lDeque.isEmpty()) {
          l = lDeque.removeBack() - '0';
        }
        if (!rDeque.isEmpty()) {
          r = rDeque.removeBack() - '0';
        }        
        sub = l - r - subBool;
        if (sub < 0) {
          sub += 10;
          subBool = true;
        } else {
          subBool = false;
        }
        returnValue.digits.addFront(sub + '0');
      }
      if (subBool) {
        returnValue.digits.addFront(1 + '0');
      }
    } else if (copyLhs < copyRhs) {
      bool subBool = false;
      Deque<char> lDeque = copyRhs.digits;
      Deque<char> rDeque = copyLhs.digits;
      while (!lDeque.isEmpty() || !rDeque.isEmpty()) {
        int l = 0;
        int r = 0;
        int sub;
        if (!lDeque.isEmpty()) {
          l = lDeque.removeBack() - '0';
        }
        if (!rDeque.isEmpty()) {
          r = rDeque.removeBack() - '0';
        }
        sub = l - r - subBool;
        if (sub < 0) {
          sub += 10;
          subBool = true;
        } else {
          subBool = false;
        }
        returnValue.digits.addFront(sub + '0');
      }
      returnValue.negative = true;
    } else {
      returnValue.digits.addFront('0');
    }
  }
  returnValue.remove0s();
  return returnValue;
}

//---------------------Assignment Operators-----------

//Sets this long int the same as the parameter(another long int) 
//copies the digits and the sign
//Return value is reference to this long int.
const LongInt& LongInt::operator=(const LongInt& rhs) {
  digits = rhs.digits;
  negative = rhs.negative;
  return *this;
}

//------------------Logical Binary Operators ---------------------
//compares the left hand operand to the right hand operand
//compares their negative signs. if one operand has a negative sign infront of it, then this one is smaller
//compares the deque size. if their signs are both positive, but their size is different, then the deque with the smaller size is the smaller int. If their signs are both negative, then the deque with the larger size is the smaller one.
//compare their deque elements from the front as removing them. The operand with a larger deque element is a larger integer in a positive sign but a smaller integer in a negative sign.


//return 1 if the left hand integer is smaller
//return 0 if the left hand integer is larger
bool LongInt::operator<(const LongInt& rhs) const {
  if (this->negative && !rhs.negative) return true;
  else if (!this->negative && rhs.negative) return false;
  else if (!this->negative && !rhs.negative) {
    if (this->digits.size() > rhs.digits.size()) {
        return false;
    } else if (this->digits.size() < rhs.digits.size()) {
      return true;
    } else {
      if (this->digits.getFront() < rhs.digits.getFront()) {
        return true;
      } else if (this->digits.getFront() > rhs.digits.getFront()) {
        return false;
      } else {
        LongInt copyLhs(*this);
        LongInt copyRhs(rhs);
        while (!copyLhs.digits.isEmpty()) {
          if (copyLhs.digits.getFront() < copyRhs.digits.getFront()) {
            return true;
          } else if(copyLhs.digits.getFront() > copyRhs.digits.getFront()) {
            return false;
          }
          copyLhs.digits.removeFront();
          copyRhs.digits.removeFront();
        }
        return false;
      }
    }
  } else {
    if (this->digits.size() < rhs.digits.size()) {
      return false;
    } else if (this->digits.size() > rhs.digits.size()) {
      return true;
    } else {
      if (this->digits.getFront() > rhs.digits.getFront()) {
        return true;
      } else if (this->digits.getFront() < rhs.digits.getFront()) {
        return false;
      } else {
        LongInt copyLhs(*this);
        LongInt copyRhs(rhs);
        while (!copyLhs.digits.isEmpty()) {
          if (copyLhs.digits.getFront() > copyRhs.digits.getFront()) {
            return true;
          } else {
            return false;
          }
          copyLhs.digits.removeFront();
          copyRhs.digits.removeFront();
        }
        return false;
      }
    }
  }
}

//return 1 if the left hand integer is equal to or smaller than the right hand integer
//return 0 if the left hand integer is equal to or larger than the right hand integer
bool LongInt::operator<=(const LongInt& rhs) const {
  return !(*this > rhs);
}

//return 1 if the left hand integer is larger
//return 0 if the left hand integer is smaller
bool LongInt::operator>(const LongInt& rhs) const {
  return !(*this < rhs) && !(*this == rhs);
}

//return 1 if the left hand integer is equal to or larger than the right hand integer
//return 0 if the left hand integer is equal to or smaller than the right hand integer
bool LongInt::operator>=(const LongInt& rhs) const {
  return !(*this < rhs ) || *this == rhs;
}

//---------------Boolean Comparison Operators----------------

//overloaded == operator that checks whether two long ints are the same or not
//return 1 if the long ints are the same. Returns 0 if the long ints are different.
bool LongInt::operator==(const LongInt& rhs) const {
  LongInt copyLhs(*this);
  LongInt copyRhs(rhs);
  if (copyLhs.digits.size() != copyRhs.digits.size()) {
    return false;
  }
  while (!copyLhs.digits.isEmpty()) {
    if (copyLhs.digits.getFront() != copyRhs.digits.getFront()) {
      return false;
    }
    copyLhs.digits.removeFront();
    copyRhs.digits.removeFront();
  }
  return true;
}

//overloaded != operator that checks whether two long ints are the not the same or if they are the same
//return 1 if the long ints are not the same(different). Returns 0 if the long ints are the same.
bool LongInt::operator!=(const LongInt& rhs) const {
  return !(*this== rhs);
}