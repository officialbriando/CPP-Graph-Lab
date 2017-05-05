//Author: Brian Do

#include <iostream>
using namespace std;

template<class E> //Creating a template class of data type E.

class GenStack
{
	private:
		E *myArray; 	//Standard array of type E
		E *tempArray;	//Temporary array for reallocating array size.

		int max;		//Used to set max array size
		int top;		//Used to keep track of logical top of array
	public:
		GenStack(int maxSize);
		~GenStack();

		void push(E data);
		E pop();
		E peek();

		int getSize();
		int isEmpty();
		int isFull();

		void expand();
};

template<class E>
GenStack<E>::GenStack(int maxSize)
{
	myArray = new E[maxSize];
	max = maxSize;
	top = -1;

	tempArray = new E[max]; 	//Necessary to create tempArray so that deletion of it later does not abort core.
}

template<class E>
GenStack<E>::~GenStack()
{
	delete []myArray;
	delete []tempArray;
	cout << "Objects destroyed." << endl;
}

template<class E>
void GenStack<E>::push(E data)
{
	if(isFull() == 1)
	{
		expand();
		push(data);
	}
	else
	{
		myArray[++top] = data; 	//Simultaneously assigns data to and increments the index of top.
	}
}

template<class E>
E GenStack<E>::pop()
{
	if(isEmpty() == 1)
	{
		cout << "The stack is empty; you cannot pop any more elements out." << endl;
	}
	else
	{
		return myArray[top--]; 	//Simultaneously returns and post decrements the index of rtop to simulate removal.
	}
}

template<class E>
E GenStack<E>::peek()			//Essentially same as pop() function but without changing the value of top.
{
	if(top == -1) {}
	else
	{
		return myArray[top];
	}
}

template<class E>
int GenStack<E>::getSize()
{
	return (top + 1);
}

template<class E>
int GenStack<E>::isEmpty()
{
	return(top == -1); 			//Returns binary values of true/false for the equation.
}

template<class E>
int GenStack<E>::isFull()
{
	return(top == (max - 1));
}

template<class E>
void GenStack<E>::expand()		//Expands the size of *myArray by 10 whenever called.
{
	tempArray = new E[max];

	for(int i = top; i > -1; --i)	//Copies all values starting from top over to a temporary array.
	{
		tempArray[i] = myArray[i];
	}

	max += 10;						//Adds 10 more spaces to max size.
	myArray = new E[max];

	for(int i = top; i > -1; --i)	//Copies over all the elements back into bigger myArray.
	{
		myArray[i] = tempArray[i];
	}
}