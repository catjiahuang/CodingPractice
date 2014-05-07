// CloudImpTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>

void output() {
	unsigned int t = 1, f = 1;
	for (unsigned int i = 1; i <= 100; ++i) {
		if (t != 3 && f != 5) printf("%d",i);
		if (t == 3) {printf("Apple"); t = 1;}
		else t++;
		if (f == 5) {printf("Juice"); f = 1;}
		else f++;
		printf("\n");
	}
}

// test 1
class A
{
    public:
        int x;
 
        A() : x(0) { }
        virtual void printMe() { std::cout << "Value: " << x <<  std::endl; }
		virtual void printMe2() { std::cout << "Value: " << x <<  std::endl; }
        virtual ~A() { }
};


// test 2
class Base {
	virtual void SomeFunction() {}
};

class Derived: public Base {
	virtual void SomeFunction3() {}
	virtual void SomeFunction2() {}
};

// test 3
class ABase{ 
        int iMem; 
}; 

class BBase : public virtual ABase { 
        int iMem;
};

class Fruit {
	int stuff;
	int stuff2;
};

class Apple: public Fruit {

};

int _tmain(int argc, _TCHAR* argv[])
{
	A a;
	int i = sizeof(a);
	
	Derived d;
	i = sizeof(d);
	
	//Fruit *fruit = new Fruit();
	Apple fruit;
	i = sizeof(fruit);

	output();
	system("pause");
	return 0;
}

