#include "prelude.h"

// ˵ģ��Ԫ��̲�֧�ֿ��ﻯ��currying�������㺯��ʽ���Ե�Ҳ�ǹ���
// ���ʹ�ñ䳤ģ�������ģ��ģ�������SFINAE����ʵ��

//! ��֧�ָ߽׺�����ģ�������������һ��ģ��
/*
curry f &rest Binded
*/
template<template<class...> class T
		, class...Binded>
struct curry
{
	//! ɶʱ����ģ�庯����ģ�庯���Ľ�ɫӦ����ʲô����
	// TestFunc ts = F ts
	template<class...TestArgs>
	static typename  T<TestArgs...>::type TestFunc(TestArgs...);
	// TestFunc _ = void
	static void TestFunc(...);

	template<class X>
	using type = typename std::conditional<
		std::is_same< 
			decltype( TestFunc( std::declval<Binded>()..., std::declval<X>() ) ), 
			void
		>::value,
		curry<T, Binded..., X>,
		decltype(TestFunc(std::declval<Binded>()..., std::declval<X>()))
	>::type;
};

// TestFunc :: T -> T -> T -> T        
// TestFunc a b c = tuple a b c        (ģ�����Ͳ����Ǳ�����
template<class R, class S, class T>
struct TestFunc
{
	using type = std::tuple<R,S,T>;
};

/*
Schemeʵ��Curry
//todo �������� ����һ���հ���Ҳ�Ǻ�������

(defun curry (f x &rest rest)
	(lambda (&args) (f x args)))

f :: a -> b -> c...


//todo ���ǰ����ṩ�� ����ֵ���� �µõ��ĺ�����

curry:: 
curry :: (T->T->T->T) -> T -> (T->T->T)
// ��T->T) ���ǩ����Ӧ����  template<T> struct F { using RetT = Tr;}

curry< F<a,b,c> , T1>    ===>    F<T1,b,c>
*/



void main_curry()
{
	using R = curry<TestFunc>::type<char>::type<short>::type<long>;
	cout << typeid(R).name() << endl;
}