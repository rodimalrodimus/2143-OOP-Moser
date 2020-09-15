///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Michael Moser
// Email:            963852741zzz@gmail.com
// Label:            P01
// Title:            Array Based Stack 
// Course:           2143
// Semester:         Fall 2020
//
// Description:
//       Example implementation of an array based stack that holds integers.
//
// Usage:
//       Reads input file and populates stack
//
// Files:            
//       input
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
//#include "input.txt"
using namespace std;

/**
 * Stack
 * 
 * Description:
 *      Integer array based stack implementation
 * 
 * Public Methods:
 *      - Stack()
 *      - Stack(int)
 *      - void Push()
 *      - int Pop()
 *      - bool empty()
 *      - bool full()
 *      - void Print()
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *  Stack S;
 *  S.Push(80);
 *  S.Push(90);
 *  S.Print();
 *  int x = S.Pop();
 *      
 */
class Stack {
private:
    int *S;              //array pointer
    int capacity;        //max stack size
    int top;            //current top (index)
    int size;           //current num items
    int max_cap;        //largest capacity
    int start_capacity;  //starting capacity
public:
    /**
     * Stack:
     *    Constructor.
     * Params:
     *    void
     * 
     * Returns:
     *     Void
     */
    Stack() {
        start_capacity = capacity = 10;          // set array size
        S = new int[capacity];  // allocate new memory
        top = -1;               // initialize top of stack
        size = 0;               // set stack to empty
    }

    /**
     * Stack:
     *    Constructor.
     * Params:
     *    int : capacity
     * 
     * Returns:
     *     Void
     */
    Stack(int cap) {
        start_capacity = capacity = cap;         // set array size      
        S = new int[capacity];  // allocate new memory
        top = -1;               // initialize top of stack
        size = 0;               // set stack to empty
    }
        /**
     * ~Stack:
     *    Destructor.
     * Params:
     *    none
     * 
     * Returns:
     *     Void
     */
    ~Stack(){
      ofstream out;
      out.open("Output.txt");
      out <<"Name: Michael Moser\nProgram: P01\nDate: 15 Sep 2020" << endl 
        << endl << "Start size: " << start_capacity << "\nMax size:"
        << max_cap <<"\nEnding size: " << capacity << endl;

    }
     /**
     * Load:
     *    Loads input file
     * Params:
     *    string (name of input file)
     * 
     * Returns:
     *     void
     */

    void Load(std::string file) {
      ifstream fin;
    string command;
    int value;

    fin.open(file);
    while(!fin.eof()){
        fin>>command;           // read push or pop  
        //cout<<command<<" ";


        if(command == "push"){  // if command is a push we need
            fin>>value;         // to read a value in as well
            Push(value);    
       }
        else{
          Pop();
        }
      

    }
    return;
    }
    /**
     * Push:
     *    Push item onto stack.
     * Params:
     *    int : data
     * 
     * Returns:
     *     Void
     */
    void Push(int data) {
        if (Full())
        {
          cout << "+: " << capacity <<" -> ";
          capacity *= 2;
          max_cap = capacity;
          int *Z = new int[capacity];  // allocate new memory
        for (int i = top; i >= 0; i--) {
          Z[i] = S[i];
          }
        delete [] S;
        S = Z;
        cout << capacity << endl;
        }
        top++;              // move top of stack up
        size++;             // increment size
        S[top] = data;      // add item to array
    }

    /**
     * Pop:
     *    remove item from stack.
     * Params:
     *    void
     * 
     * Returns:
     *     int
     */
    int Pop() {
      if(!Empty())
      {
        int data = S[top];  // pull item from stack
        top--;              // shrink the stack
        size--;             // update our size
        if ((size*2) == capacity)
        {
          cout <<"-: " << capacity <<" -> ";
          capacity /= 2;
          int *Z = new int[capacity];  // allocate new memory
        for (int i = top; i >= 0; i--) {
          Z[i] = S[i];
          }
        delete [] S;
        S = Z;
        cout << capacity << endl;
        }
        return data;        // send item back
      }
      else
      {
        cout << "Stack Empty" << endl;
        return -1;
      }
    
    }

    /**
     * Empty:
     *    is the stack empty?
     * Params:
     *    void
     * 
     * Returns:
     *     bool : true == stack is empty
     */
    bool Empty() {
        //return size == 0;
        return top == -1;
    }

    /**
     * Full:
     *    is the stack full?
     * Params:
     *    void
     * 
     * Returns:
     *     bool : true == stack is full
     */
    bool Full() {
        return top == capacity - 1;
    }

    /**
     * Print:
     *    Used so we can inspect our stack.
     * Params:
     *    void
     * 
     * Returns:
     *     void
     */    
    void Print() {
        for (int i = top; i >= 0; i--) {
            cout << S[i] << endl;
        }
    }

    /**
     * Overloaded ostream <<
     *    Lets us print a stack using cout
     * Params:
     *    ostream &os   : instance of ostream passed in by reference
     *    const Stack   : instance of stack passed in using const so 
     *                    it cannot be changed
     * 
     * Returns:
     *     ostream 
     */
    friend ostream &operator<<(std::ostream &os, const Stack s) {
        os << "Overloaded!!" << endl;
        for (int i = s.top; i >= 0; i--) {
            os << s.S[i] << endl;
        }
        return os;
    }
};

/**
 * Person
 * 
 * Description:
 *      Example struct that represents a person.
 * 
 * Usage: 
 * 
 *  Person P1;
 * 
 *  P1.fname = "firstName";
 *  P1.lname = "lastName";
 *  P1.age = 99
 *  cout<<P1<<endl;
 * 
 *  Person P2("billy","bob",11);
 *  cout<<P2<<endl;
 */
struct Person {
    string fname;
    string lname;
    int age;

    Person();
    Person(string, string, int);

    friend ostream &operator<<(ostream &os, const Person p) {
        os << p.fname << "," << p.lname << " : " << p.age << endl;
        return os;
    }
};

/**
 * Constructor:
 *    Constructs the person structure
 * Params:
 *    void
 * 
 * Returns:
 *     void
 */   
Person::Person() {
    fname = "";
    lname = "";
    age = 0;
}

/**
 * Constructor:
 *    Constructs the person structure
 * Params:
 *    string    : first name
 *    string    : last name
 *    int       : persons age
 * 
 * Returns:
 *     void
 */ 
Person::Person(string f, string l, int a) {
    fname = f;
    lname = l;
    age = a;
}

int main() {

  cout << "Name: Michael Moser\nProgram: P01\nDate: 15 Sep 2020" << endl;
    Stack S1;           // calls default constructor
   S1.Load("input.txt");
}
