/*
First read through main() and make predictions on what the outpout of each variable will be where indicated.
After doing that add a function prototype at the top for a function called MySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an interger pointer you make that points to the variable y.
In the function MySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void foo(int *a, int b);
void bar(int *a, int b);
void Myswap(int *a, int *b);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;
    int *q = &y;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: " /* << address of x*/ << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: " /* << address of x*/ << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: " /* << 3*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    
    foo(p, x);
    
    cout << "Predicted value of *p: " /* << 42*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " /* << PLACE YOUR PREDICTION HERE: 42*/ << endl;
    cout << "Actual value of x: " << x << endl;
    foo(p, y);

    cout << "Predicted value of *p: " /* << PLACE YOUR PREDICTION HERE:42*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " /* << PLACE YOUR PREDICTION HERE:4*/ << endl;
    cout << "Actual value of y: " << y << endl;

cout<< " value of x before swap: " << x << endl;
cout<< " value of y before swap: " << y << endl;
cout << " value of *p before swap: " << *p << endl;
   cout << " value of *q before swap: " << *q << endl;
    
    //start writing MySwap here
   Myswap(p, q);
   cout<< " value of x after swap: " << x << endl;
cout<< " value of y after swap: " << y << endl;
   cout << "Actual value of *p after swap: " << *p << endl;
   cout << "Actual value of *q after swap: " << *q << endl;
    
    return 0;
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
 void Myswap (int *a, int *b)
 {
int temp1;
int temp2;
temp1= *b;
temp2= *a;
*b=temp2;
*a=temp1;
 }