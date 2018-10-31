#ifndef h_10_5_fac
#define h_10_5_fac
#include "prelude.h"
/*
Fact :: Int -> Int
Fact n = n * Fact (n-1)
Fact 0 = 1

*/

//!  Factorial :: int -> int       ("val")
template<int n>
struct Factorial  //!ԭ�Ͱ棺�˴�û�С���
{
	enum { val = n * Factorial<n-1>::val };
};
template<>     // ��ȫ�ػ���ԭ�����е�type,int���Ѷ�
struct Factorial<0>   // �ػ���Ҫ������д <...>
{
	enum { val = 1 };
};

inline void test_fact()
{
	auto r0 = Factorial<5>::val;
}
//x=====================================================================================================================
//! IF :: int -> Type     -> Type     -> Type
//! IF :: bool-> typename -> typename -> type
//  f  false x y = y   //todo �ػ�ģʽ1
//  f  _     x y = x   //todo ͨ��ģʽ
template<bool cond,typename A,typename B>
struct IF
{
	using Ret = A;
};
template<typename A,typename B>
struct IF<false,A,B>
{
	using Ret = B;
};
//x  F<..>::X  ���X������ָalias,������ָ���� (Ĭ��)����ʱ��Ҫ��typename���߱��������Ǹ�type alias
inline void test_if()
{
	using T0 = IF<(1 + 5 > 4), string, vector<int>>::Ret;  // ����ֵ���ʽ ���� constexpr
}
//x=====================================================================================================================
/*
��������� ָ��ֵ�� ���ã� ���Ǳ����ھ���ȷ���ġ�
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.cbclx01/template_non-type_arguments.htm

A non-type template argument provided within a template argument list is an expression whose value can be determined at compile time. 
Such arguments must be constant expressions, addresses of functions or objects with external linkage, or addresses of static class members. 
Non-type template arguments are normally used to initialize a class or to specify the sizes of class members.

For non-type integral arguments,   //todo ���� �� int/short/long , bool , char   (����ֵ���Ǳ����ڳ���������
the instance argument matches the corresponding template parameter as long as the instance argument has a value and sign appropriate to the parameter type.

For non-type address arguments,    //todo ��ַ��
the type of the instance argument must be of the form identifier or &identifier, 
and the type of the instance argument must match the template parameter exactly, 
except that a function name is changed to a pointer to function type before matching.

The resulting values of non-type template arguments within a template argument list form part of the template class type. 
If two template class names have the same template name and if their arguments have identical values, they are the same class.
*/
enum
{
	val = false,
	v2 = 4,
	v3 = 'c',
	//v4 = 3.2
	//v4 = nullptr
};

template<bool p1, int p2, const char* p3>           //! ֻҪ���ָ��/���õĶ���----��ֵַ���ڱ�����ȷ�����Ϳ�����Ϊģ����������α����ڳ�����
struct Params
{
	
};
//x=====================================================================================================================
inline
int my_max(const int x, const int y)
{
	return x > y ? x : y;
}
//inline
constexpr int my_max_constexpr(const int x, const int y)
{
	return x > y ? x : y;
}

template<int x ,int y>
struct Maxium
{
	enum
	{
		v1 = max(x, y),  
		v3 = my_max(x,y),		// ��constexpr�ĺ��������� ��������ֵ��
		v4 = my_max_constexpr(x,y)  //! constexpr 
	};
};

inline void test_maxium()
{
	using T0 = Maxium<5, 6>;
	auto r1 = T0::v1;  //todo δ���������ڼ��㣬���δĬ�ϵ� enumeratorֵ��0
	auto r3 = T0::v3;  //todo δ���������ڼ��㣬���δĬ�ϵ� ǰһ��enumeratorֵ + 1
	auto r4 = T0::v4;  // 6 ����ȷ
}
//x=====================================================================================================================
//! �ֲ�let��������� ����ֵʹ�� private �� ֻ�ѽ��ֵ��¶Ϊ public ------>  ��ʱ���� Class�� struct�á�

// ��������������ʾ������  Float����
template<int _base, int _exp>
struct Float
{
	enum
	{
		base = _base,
		exp = _exp
	};
	// �� const float ������ת������
	operator const float() const{
		return _base * pow(10, _exp);  // base����base, exp��С�������Ƶ�λ��       2.5 ���� 25 * 10^-1  , ���� F2_5
	}


};

template<typename Float>
struct Sqrt
{
	
};

inline void test_float()
{
	using F1 = Float<25, -1>;
	float f1 = F1();
	//int ay[F1()];
	/*---------------------------*/
	// 2.5
	using F2_5 = Float<25, -1>;
	using F4_0 = Float<4, 0>;


}
//x=====================================================================================================================
//! �߽׺���
/*
Acc :: Int -> (Int->Int) -> Int
Acc n f = f n + Acc (n-1) f
Acc 0 f = f 0
*/
template<int n,
		template<int> class F>    //! F : �Ǿ߱�Int������ģ������       template<, ,> class F
struct Acc
{
	enum {val = F<n>::val + Acc<n-1,F>::val };
};

template<template<int> class F>
struct Acc<0,F>
{
	enum {val = F<0>::val };
};

template<int n>
struct Square
{
	enum { val = n*n };
};


//--------------------------------------------------------------------
// Squrare��һ��ģ�壬 ���Ҵ�����F�� �ڲ��ٵ��� F<...>::val
//! �~�~�~�~�~�~�~�~�����������֧��ģ�����Ϊģ�����ͣ���ֻ֧��ƽ�����ͣ�������԰�����װ��һ����ģ�������У���Ϊ��Աģ�壩
struct SquareWrapper
{
	template<int n>                  //! �~�~�~�~�~�~�~�~
	struct Apply                     //! A::B                // B is value(default)
	{                                //! typename A::B       // B is type
		enum { val = n*n };          //! A::template B       // B is template           
	};
};

template<int n,
		 typename F_Wrapper>
struct Acc2
{
	enum
	{
		val = F_Wrapper::template Apply<n>::val + Acc2<n-1,F_Wrapper>::val
	};
};

template<typename F_Wrapper>
struct Acc2<0,F_Wrapper>
{
	enum {val = F_Wrapper::template Apply<0>::val };
};

inline void test_Acc()
{
	// 3^2 + 2^2 + 1^2 
	int r = Acc<3, Square>::val;

	int r1 = Acc2<3, SquareWrapper>::val;
}
//x=====================================================================================================================
//! ��һ��Ԫ������Ϊ������أ����ص�ֵ���϶���һ��ģ�����ˣ�
//!   
struct ReturnFunction
{
	template <int n>
	using RetF = Square<n>;         //! �~�~�~�~�~�~�~�~ ������һ��ģ���Ա����Ϊ�����һ��ģ��

	//using RetF2 = Square; 
};

inline void test_fback()
{
	auto r = ReturnFunction::RetF<4>::val;  // 16
}
//x=====================================================================================================================





#endif
