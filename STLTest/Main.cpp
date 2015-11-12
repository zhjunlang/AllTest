
#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include "glog/logging.h" 

using namespace std;

//adacent_find
//寻找第一个重复的元素
void test_adacent_find_1()
{
	int A[] = {1, 2, 3, 3, 5, 6, 7, 8};
	const int N = sizeof(A) / sizeof(int);

	const int* p = adjacent_find(A, A + N);

	if (p != A + N)
		cout<<"Duplicate element: "<<*p<<"\n";
	else
		cout<<"None same element\n";
}

//寻找第一个大于其后继者的元素
void test_adacent_find_2()
{
	int A[] = {1, 2, 3, 40, 5, 6, 7, 8};
	const int N = sizeof(A) / sizeof(int);

	const int* p = adjacent_find(A, A + N, greater<int>());

	if (p == A + N)
		cout<<"The range is sorted in ascending order.\n";
	else
		cout<<"Element "<<p - A<<" is out of order: "
		    <<*p<<" > "<<*(p + 1)<<".\n";
}

bool binary_search_function (int i,int j) 
{ 
	return (i<j);
}

void test_binary_search_1()
{
	int myints[] = {1,2,3,4,5,4,3,2,1};
	std::vector<int> v(myints, myints + 9);                         // 1 2 3 4 5 4 3 2 1

	// using default comparison:
	std::sort (v.begin(), v.end());

	std::cout << "looking for a 3... ";
	if (std::binary_search (v.begin(), v.end(), 3))
		std::cout << "found!\n"; else std::cout << "not found.\n";
}

void test_binary_search_2()
{
	int myints[] = {1,2,3,4,5,4,3,2,1};
	std::vector<int> v(myints,myints+9);                         // 1 2 3 4 5 4 3 2 1

	// using myfunction as comp:
	std::sort (v.begin(), v.end(), binary_search_function);

	std::cout << "looking for a 6... ";
	if (std::binary_search (v.begin(), v.end(), 6, binary_search_function))
		std::cout << "found!\n"; else std::cout << "not found.\n";
}

void test_lower_bound_1()
{
	int myints[] = {10,20,30,30,20,10,10,20};
	std::vector<int> v(myints, myints + 8);         // 10 20 30 30 20 10 10 20

	std::sort (v.begin(), v.end());					// 10 10 10 20 20 20 30 30

	std::vector<int>::iterator low, up;
	low=std::lower_bound (v.begin(), v.end(), 20);	//          ^
	up= std::upper_bound (v.begin(), v.end(), 20);  //                   ^

	std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
	std::cout << "upper_bound at position " << (up - v.begin()) << '\n';
}

void test_lower_bound_2()
{
	int A[] = {1, 2, 3, 3, 3, 5, 8};
	const int N = sizeof(A) / sizeof(int);

	for(int i= 1; i <= 10; ++i)
	{
		int* p = lower_bound(A, A + N, i);
		cout<<"Searching for "<<i<<". ";
		cout<<"Result: index = "<< p - A<<". ";
		if (p != A + N)
			cout<<"A[" << p - A<<"] == "<< *p <<"\n";
		else
			cout<<"which is off-the-end.\n";
	}
}

void test_upper_bound_1()
{
	int A[] = {1, 2, 3, 3, 3,  5, 8};
	const int N = sizeof(A) / sizeof(int);

	for (int i = 1; i <= 10; ++i)
	{
		int* p = upper_bound(A, A + N, i);
		cout<<"Serarching for "<<i<<". ";
		cout<<"Result: index = "<<p - A<<". ";
		if (p != A + N)
			cout<<"A["<<p - A <<"] == "<<*p<<"\n";
		else
			cout<<"which is off-the-end.\n";
	}
}

void test_upper_bound_2()
{
	int myints[] = {10,20,30,30,20,10,10,20};
	std::vector<int> v(myints, myints + 8);           // 10 20 30 30 20 10 10 20

	std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

	std::vector<int>::iterator low,up;
	low=std::lower_bound (v.begin(), v.end(), 20); //          ^
	up= std::upper_bound (v.begin(), v.end(), 20); //                   ^

	std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
	std::cout << "upper_bound at position " << (up - v.begin()) << '\n';
}

bool mygreater (int i,int j) 
{ 
	return (i>j); 
}

void test_equal_range_1()
{
	int myints[] = {10,20,30,30,20,10,10,20};
	std::vector<int> v(myints, myints + 8);                         // 10 20 30 30 20 10 10 20
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> bounds;

	// using default comparison:
	std::sort (v.begin(), v.end());                              // 10 10 10 20 20 20 30 30
	bounds = std::equal_range (v.begin(), v.end(), 20);            //          ^        ^

	// using "mygreater" as comp:
	std::sort (v.begin(), v.end(), mygreater);                   // 30 30 20 20 20 10 10 10
	bounds = std::equal_range (v.begin(), v.end(), 20, mygreater); //       ^        ^

	std::cout << "bounds at positions " << (bounds.first - v.begin());
	std::cout << " and " << (bounds.second - v.begin()) << '\n';
}

void test_equal_range_2()
{
	int A[] = {1, 2, 3, 3, 3, 5, 8};
	const int N = sizeof(A) / sizeof(int);

	for (int i = 2; i <= 5; ++i)
	{
		pair<int*, int*> result = equal_range(A, A + N, i);

		cout<<"\n";
		cout<<"Searching for "<<i<<"\n";

		cout<<"  First position where "<< i << " could be inserted: "<< result.first - A << "\n";
		cout<<"  Last position where "<<i << " could be inserted: "<<result.second - A <<"\n";

		if (result.first < A + N)
			cout<<" *result.first = "<<*result.first<<"\n";
		if (result.second < A + N)
			cout<<" *result.second = "<<*result.second<<"\n";
	}
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging("STLTest");
	google::SetLogDestination(google::INFO,"./../Debug/");

	LOG(INFO) << "Test STL Begin";

	LOG(INFO) << "adacent_find";
	test_adacent_find_1();
	test_adacent_find_2();
	cout<<"\n";
	LOG(INFO) << "binary_search";
	test_binary_search_1();
	test_binary_search_2();
	cout<<"\n";
	LOG(INFO) << "lower_bound";
	test_lower_bound_1();
	test_lower_bound_2();
	cout<<"\n";
	LOG(INFO) << "upper_bound";
	test_upper_bound_1();
	test_upper_bound_2();
	cout<<"\n";
	LOG(INFO) << "equal_range";
	test_equal_range_1();
	test_equal_range_2();
	cout<<"\n";

	LOG(INFO) << "Test STL End";

	return 0;
}