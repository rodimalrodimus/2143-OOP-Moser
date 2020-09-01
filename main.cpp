///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Michael Moser
// Email:            963852741zzz@gmail.com
// Label:            02-H01
// Course:           COMP 2143
// Semester:         Fall 2020
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

int A[100];

/**
 * Class Name: Node
 * 
 * Description:
 *      nodes of a linked list
 * 
 * Public Methods:
 *      - Node  
 * 
 * Usage: 
 * 
 *      - Node *next
 *      - Node(5) *next
 *      
 */

struct Node
{
    int x;	 // data
    Node *next;  // adress of next node 
  /**
     * Public: Node
     * 
     * Description:
     *     default constructor for Node.
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - none
     */
    Node()
    {
        x = -1;
        next = NULL;
    }
  /**
     * Public: Node
     * 
     * Description:
     *     constructor for Node ands sets x
     * 
     * Params:
     *      - int n
     * 
     * Returns:
     *      - none
     */
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};
/**
 * Class Name: List
 * 
 * Description:
 *      Makes list with head and tail.
 * 
 * Public Methods:
 *      - List
 *      - void Push
 *      - void Insert
 *	- void PrintTail
 *	- string Print
 *	- int Pop()  // does nothing just like the "//" in this line
 *	- List operator+
 * 
 * Usage: 
 * 
 *      - List L1
 *      - L1.Insert(5)
 *      
 */
class List
{
  private:
    Node *Head; // head of list
    Node *Tail; // tail of list
    int Size;   // size of list

  public:
  /**
     * Public:List
     * 
     * Description:
     *      default constructor of list
     * 
     * Params:
     *      - none
     * Returns:
     *      - none
     */
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }
  /**
     * Public: Push
     * 
     * Description:
     *      makes new node at end of list
     * 
     * Params:
     *      - int val
     * 
     * Returns:
     *      - void
     */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
  /**
     * Public:Insert
     * 
     * Description:
     *       makes new node at front of list
     * 
     * Params:
     *      - int val
     * 
     * Returns:
     *      - void
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }
     /**
     * Public: PrintTail
     * 
     * Description:
     *      prints tail
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - none
     */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }
    /**
     * Public: Print
     * 
     * Description:
     *      returns a list of the varibles of the list
     * 
     * Params:
     *      - none
     * 
     * Returns:
     *      - string (list of the varibles of the list)
     */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};
    /**
     * Public:main
     * 
     * Description:
     *      main
     * 
     * Params:
     *      - int argc
     *      - char **argv
     * 
     * Returns:
     *      - int 0
     */
int main(int argc, char **argv)
{
    List L1; // first list
    List L2; // secod list

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}