#include <iostream>
#include <array>
#include "Array.h"
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

XVOID TestArray()
{
	{
		cout << "=================== stl array ===================" << endl;
		array<int, 3> a{ 1, 2, 3 };

		/*
		 This code generates an error of compile-level.
		 the error can be controlled by architecturally based array-design.
		 so I make this function in another way for following the function.
		 */
		 /*array<int, 3> a{ 1, 2, 3, 4 }; */

		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		auto& atIt = a.at(1);
		atIt = 10;
		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		a[2] = 20;
		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		cout << a.data();
		cout << endl;

		cout << a.size();
		cout << endl;

		cout << *const_cast<int*>(a.data());
		cout << endl;

		cout << *const_cast<int*>(a.data() + 1);
		cout << endl;
	}

	cout << endl;

	{
		cout << "=================== XArray ===================" << endl;
		X::XArray<int, 3> a{ 1,2, 3 };
		//X::XArray<int, 3> a{ 1,2, 3 ,4 }; // A compile error occur here.

		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		auto& atIt = a.at(1);
		atIt = 10;
		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		a[2] = 20;
		for_each(a.begin(), a.end(), [](int a) { cout << a << " "; });
		cout << endl;

		cout << a.data();
		cout << endl;

		cout << a.size();
		cout << endl;

		cout << *const_cast<int*>(a.data());
		cout << endl;

		cout << *const_cast<int*>(a.data() + 1);
		cout << endl;
	}
}

int main()
{
	// stl array, XArray
	TestArray();
	

	return 0;
}