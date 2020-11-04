/*
First read through main() and make predictions on what the outpout of each variable will be where indicated.
After doing that add a function prototype at the top for a function called MySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an interger pointer you make that points to the variable y.
In the function MySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void MySwap(int *a, int *b);
void foo(int *a, int b);
void bar(int *a, int b);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: " /* << This will print the address of p/ << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: " /* << This will print the address of int x*/ << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: " /* << The value of *p should be 3 at this point*/ << endl;
    cout << "Actual value of *p: " << *p << endl;

    foo(p, x);

    cout << "Predicted value of *p: " /* << The value of *p should be 42*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " /* << The value of x should be 42*/ << endl;
    cout << "Actual value of x: " << x << endl;
    foo(p, y);

    cout << "Predicted value of *p: " /* << The value of *p should be 42*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " /* << The value of y should remain as 4*/ << endl;
    cout << "Actual value of y: " << y << endl;
    MySwap(p, &y);

    cout << "The value of *p is:" << *p << endl;
    cout << "The value of y is:" << y << endl;

    return 0;
}

void MySwap(int *a, int *b)
{
  int temp = 0;
  temp = *a;
  *a = *b;
  *b = temp;

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
