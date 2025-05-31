#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/phone_subscription.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
	phone_subscription* build_subscription(int hours, int minutes, int seconds, double pay)
	{
		phone_subscription* subscription = new phone_subscription;
		subscription->tm.hours = hours;
		subscription->tm.minutes = minutes;
		subscription->tm.seconds = seconds;
		subscription->pay = pay;
		return subscription;
	}

	//       
	void delete_subscription(phone_subscription* array[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			delete array[i];
		}
	}

	TEST_CLASS(unittestproject)
	{
	public:
		
		
		TEST_METHOD(TestMethod1) //         
		{
			phone_subscription* subscriptions[3];
			subscriptions[0] = build_subscription(0, 1, 3, 0.10);
			subscriptions[1] = build_subscription(0, 2, 57, 0.20);
			subscriptions[2] = build_subscription(0, 2, 40, 0.10);
			Assert::AreEqual(7, process(subscriptions, 3));
			delete_subscription(subscriptions, 3);
		}

		TEST_METHOD(TestMethod2) //         
		{
			phone_subscription* subscriptions[3];
			subscriptions[0] = build_subscription(0, 4, 58, 0.20);
			subscriptions[1] = build_subscription(0, 5, 2, 0.20);
			subscriptions[2] = build_subscription(0, 6, 40, 0.10);
			Assert::AreEqual(12, process(subscriptions, 3));
			delete_subscription(subscriptions, 3);
		}

	};
}
