#include "pch.h"
#include "CppUnitTest.h"
#include "../DSAL/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(XArrayInitTest1)
		{
			X::XArray<int, 4> a{ 1,2,3,4};
		}

		TEST_METHOD(XArrayInitTest2)
		{
			Assert::ExpectException<std::out_of_range>([]()
				{
					X::XArray<int, 3> a{ 1,2,3, 4 };
				});
		}

		TEST_METHOD(XArrayInitTest3)
		{
			X::XArray<int, 5> a{ 1,2,3,4 };
		}
	};
}
