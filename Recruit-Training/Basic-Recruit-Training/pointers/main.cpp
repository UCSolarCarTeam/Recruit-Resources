/*
First read through main() and make predictions on what the output of each variable will be where indicated.
After doing that add a function prototype at the top for a function called mySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an integer pointer you make that points to the variable y.
In the function mySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void foo(int *a, int b);
void bar(int *a, int b);
void mySwap(int *a, int *y);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: The Address to the variable x" /* Correct! << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: 3" /* No &x means the address of the variable x << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: 3" /* Correct! << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value of *p: " << *p << endl;

    foo(p, x);
    
    cout << "Predicted value of *p: 42" /* Correct! << PLACE YOUR PREDICTION HERE*/ << endl; 
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: 3" /* x is linked to *p because *p changed to 42 x will too << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value of x: " << x << endl;

    foo(p, y);

    cout << "Predicted value of *p: 42" /* Correct! << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: 4" /* Correct! << PLACE YOUR PREDICTION HERE*/ << endl;
    cout << "Actual value of y: " << y << endl; 

    int *q = &y;
    //start writing mySwap here
    // NEED TO FIGURE OUT HOW TO WRITE MYSWAP
    cout << "Value of p before swap: " << *p << endl;
    cout << "Value of q before swap: " << *q << endl;

    mySwap(p, q);
    
    cout << "Value of p after swap: " << *p << endl;
    cout << "Value of q after swap: " << *q << endl;
    
    return 0;
}

void mySwap(int *a, int *y)
{
    int t;
    t = *a;
    *a = *y;
    *y = t;
}

void foo(int *a, int b)
{
   *a = 42;
   b = 78;
}

void var(int *a, int b)
{
    *a = 365;
    b = 912;
}
