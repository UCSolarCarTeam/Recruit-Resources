/*
First read through main() and make predictions on what the outpout of each variable will be where indicated.
After doing that add a function prototype at the top for a function called mySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an interger pointer you make that points to the variable y.
In the function mySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void foo(int *a, int b);
void bar(int *a, int b);
void Myswap(int *a,int*b);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: "<<&x<< endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: "<< &*p << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: " <<3<< endl;
    cout << "Actual value of *p: " << *p << endl;
    
    foo(p, x);
    
    cout << "Predicted value of *p: "  <<42<< endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " <<42<< endl;
    cout << "Actual value of x: " << x << endl;
    foo(p, y);

    cout << "Predicted value of *p: " <<42<< endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " <<4 << endl;
    cout << "Actual value of y: " << y << endl;

<<<<<<< HEAD

    Myswap(&x,&y);

=======
    //start writing mySwap here
>>>>>>> 593c34c5f5eedbf39766e1a637513ba9e09ba233
    
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
void Myswap(int*a, int*b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
