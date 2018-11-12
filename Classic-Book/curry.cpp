#include <iostream>
#include <tuple>
using namespace std;

template<template<class...> class F, class...Binded>
struct curry
{
private:
	// Func
	template<class...Args>
	static auto Func(Args...) -> typename  F<Args...>::type;
	// �������ؾ����Ŀ�ģ��䳤���������ȼ���ͣ������ǳ����� SFINAE �е�ȫ��������䡣
	static auto Func(...) -> void;

public:
	template<class arg>
	using apply = typename std::conditional<
		std::is_same<         // ���f����Ĳ�����δ���꣬��������󶨣� ����
			decltype( Func(std::declval<Binded>()..., std::declval<arg>() ) ), // ֻҪ F<Binded..., arg> ���Ա��룬�Ͳ�Ϊvoid
			void
		>::value,
		curry<F, Binded..., arg>,
		decltype(Func(std::declval<Binded>()..., std::declval<arg>()))
	>::type;
};

template<class R, class S, class T>
struct TestFunc
{
	using type = std::tuple<R,S,T>;
};

//test_curry
void test_curry()
{
	using T1 = curry<TestFunc>::apply<char>;   // curry<TestFunc, char>
	using T2 = T1::apply<short>;               // curry<TestFunc, char, short>
	using T3 = T2::apply<long>;                // ---> tuple<char,short,long>
	//using T4 = T3::apply<int>;                 // x 

	cout << typeid(curry<TestFunc>::apply<char>::apply<short>::apply<long>).name() << endl;
}