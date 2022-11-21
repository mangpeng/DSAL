#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <deque>
#include "Array.h"
#include "Vector.h"
#include "List.h"
//#include "Deque.h"
#include <algorithm>

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

class Point
{
public:
	Point() : _x(0), _y(0)
	{
		cout << "here" << endl;
	}
	Point(XINT x, XINT y) : _x(x), _y(y) {}

public:
	XVOID Print() const
	{
		cout << _x << ", " << _y << endl;
	}

private:
	XINT _x;
	XINT _y;

};

XVOID TestVector()
{
	{
		cout << "=================== stl vector ===================" << endl;
		vector<XINT> v1;
		v1.push_back(10);
		v1.push_back(20);
		v1.push_back(30);

		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1.pop_back();
		v1.pop_back();
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1[0] = 1000;
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		auto it = v1.begin();
		it += 2;
		*it = 3000;
		v1[0] = 1000;
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;
		
		vector<XINT> v2{ 1,2,3,4 };
		v2.push_back(1023);
		for_each(v2.begin(), v2.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		auto& b = v2.back();
		cout << b << endl;

		vector<Point> v3;
		v3.emplace_back();
		v3.emplace_back(1, 3);
		for_each(v3.begin(), v3.end(), [](const Point& p) { p.Print(); });
		cout << endl;
	}

	cout << endl;

	{
		cout << "=================== XVector ===================" << endl;
		X::XVector<XINT> v1;

		v1.push_back(10);
		v1.push_back(20);
		v1.push_back(30);
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1.pop_back();
		v1.pop_back();
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1[0] = 1000;
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		auto it = v1.begin();
		it += 2;
		*it = 3000;
		v1[0] = 1000;
		for_each(v1.begin(), v1.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		X::XVector<XINT> v2{ 1,2,3,4};
		v2.push_back(1023);
		for_each(v2.begin(), v2.end(), [](XINT a) { cout << a << " "; });
		cout << endl;

		auto& b = v2.back();
		cout << b << endl;

		X::XVector<Point> v3;
		v3.emplace_back();
		v3.emplace_back(1, 3);
		for_each(v3.begin(), v3.end(), [](const Point& p) { p.Print(); });
		cout << endl;
	}

}

XVOID TestList()
{
	{
		cout << "=================== stl list ===================" << endl;
		list<XINT> li1;

		li1.push_back(1);
		li1.push_front(2);
		li1.push_back(3);
		li1.push_front(4);
		for_each(li1.begin(), li1.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;
		cout << li1.size() << endl;

		li1.pop_front();
		li1.pop_back();

		for_each(li1.begin(), li1.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;

		list<XINT> li2;
		li2.push_back(1);
		li2.push_back(2);
		li2.push_back(3);
		li2.push_back(4);
		for (auto it = li2.begin(); it != li2.end();)
		{
			if (*it % 2 == 0)
				it = li2.erase(it);
			else
				++it;
		}
		for_each(li2.begin(), li2.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;
	}

	cout << endl;

	{
		cout << "=================== XList ===================" << endl;
		X::XList<XINT> li1;

		li1.push_back(1);
		li1.push_front(2);
		li1.push_back(3);
		li1.push_front(4);
		for_each(li1.begin(), li1.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;
		cout << li1.size() << endl;

		li1.pop_front();
		li1.pop_back();
		for_each(li1.begin(), li1.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;

		X::XList<XINT> li2;
		li2.push_back(1);
		li2.push_back(2);
		li2.push_back(3);
		li2.push_back(4);
		for (auto it = li2.begin(); it != li2.end();)
		{
			if (*it % 2 == 0)
				it = li2.erase(it);
			else
				++it;
		}
		for_each(li2.begin(), li2.end(), [](XINT& ele) { cout << ele << " "; });
		cout << endl;
	}

}


XVOID TestDeque()
{
	{
		cout << "=================== stl deque ===================" << endl;
		deque<XINT> dq;
		dq.push_back(1);
		dq.push_front(2);
		dq.push_back(3);
		dq.push_front(4);

		for_each(dq.begin(), dq.end(), [](XINT ele) { cout << ele << " "; });
		cout << endl;	

		
		
	}

	cout << endl;

	{
		cout << "=================== XDeque ===================" << endl;
		//X::XDeque<XINT> dq;
		/*dq.push_back(1);
		dq.push_front(2);
		dq.push_back(3);
		dq.push_front(4);

		for_each(dq.begin(), dq.end(), [](XINT ele) { cout << ele << " "; });
		cout << endl;*/

	}

}

int main()
{
	// stl array, XArray
	TestArray();

	// stl vector, XVector
	//TestVector();

	// stl list, XList
	//TestList();

	// stl deque, XDeque
	//TestDeque();



	return 0;
}