#include "libs/mpl/book/chapter1/binary.hpp"
#include "prelude.h"

//template<typename T>
//void showtype(T&&);

//! �㷨�Ķ�̬�汾
namespace dynamic {
	

}

namespace wjh {
template<int n>
struct to_binary
{
	enum { val = to_binary<n/10>::val*2 + n % 10 };
};

template<>
struct to_binary<0>
{
	enum { val = 0 };
};
}
//x----------------------------------------------------------------------------------------------------------------------------
//!  
template<typename T, typename UnaryOp1, typename UnaryOp2>
T apply_fg(T x, UnaryOp1 f , UnaryOp2 g)
{
	return f(g(x));
}

float square(float x)
{
	return x*x;
};

void test_applyfg()
{
	auto r1 = apply_fg(5.0f, square, negate<>());
	auto r2 = apply_fg(5.0f, negate<float>(), square);
}
//  �����������������װ��ͬһ��������Ļ��� ���á�

//x=============================================================================================================================
// what for ?
//template<typename T1,typename T2>
//void swap(T1& a, T2& b)
//{
//	T1 tmp = a;
//	a = b;
//	b = tmp;
//}

//? �ܷ�ʹ�����Ͳ���ƥ��Ϊ�����е�ĳ����Ա������ͬʱ
//?         ��������������ͽ���Լ����

template<bool use_swap>
struct iter_swap_impl;

template<>
struct iter_swap_impl<true>
{
	template <typename Iter>
	static void do_it(Iter it1, Iter it2)
	{
		std::swap(*it1, *it2);
	}
};

template<>
struct iter_swap_impl<false>
{
	template <typename Iter1, typename Iter2>
	static void do_it(Iter1 it1, Iter2 it2)
	{
		typename iterator_traits<Iter1>::value_type tmp = *it1;
		*it1 = *it2;
		*it2 = tmp;
	}	
};


template <typename Iter1, typename Iter2>
void iter_swap(Iter1 it1, Iter2 it2)
{
	//todo  Iter1, Iter2 ������ͬ��value_type ���������õ����������������ö��Ǵ���  ---->  �� use_swap
	using v1 = typename iterator_traits<Iter1>::value_type;
	using r1 = typename iterator_traits<Iter1>::reference;

	using v2 = typename iterator_traits<Iter2>::value_type;
	using r2 = typename iterator_traits<Iter2>::reference;

	const bool use_swap = is_same<v1, v2>::value && is_reference<r1>::value && is_reference<r2>::value;

	//todo  ������������㷨�ɷ���dispatching)
	iter_swap_impl<use_swap>::do_it(it1, it2);
}
//x=============================================================================================================================


void main_ex()
{
	auto r1 = binary<101>::value;
	auto r2 = wjh::to_binary<20>::val;
	system("pause");
}
