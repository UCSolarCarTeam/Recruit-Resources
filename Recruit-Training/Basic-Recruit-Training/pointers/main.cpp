/*
First read through main() and make predictions on what the outpout of each variable will be where indicated.
After doing that add a function prototype at the top for a function called mySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an interger pointer you make that points to the variable y.
In the function mySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void foo(int *a, int b);
void mySwap(int *a, int *b);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: " << "the address of x" << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: " << "the address of x" << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: " << "the value that the pointer points to, in this case 3" << endl;
    cout << "Actual value of *p: " << *p << endl;
    
    foo(p, x);
    
    cout << "Predicted value of *p: " << 42 << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " << "42, because P was pointing to the same thing as x and it also changed to 42" << endl;
    cout << "Actual value of x: " << x << endl;

    foo(p, y);

    cout << "Predicted value of *p: " << 42 << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " << "4, because the local variable b in function foo will not change y" << endl;
    cout << "Actual value of y: " << y << endl;

    //start writing mySwap here
    int *c = &y;
    cout << "Initial value of *p: " << *p << endl;
    cout << "Initial value of *c: " << *c << endl;
    mySwap(p, c);
    cout << "Final value of *p: " << *p << endl;
    cout << "Final value of *c: " << *c << endl;
    
    return 0;
}

 void foo(int *a, int b)
{
   *a = 42;
   b = 78;
}


void mySwap(int *a, int *b)
{
    int t;
    t = *b;
    *b = *a;
    *a = t;
}