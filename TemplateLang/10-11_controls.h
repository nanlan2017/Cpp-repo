#ifndef h_controls
#define h_controls

#include "prelude.h"
#include "10-5_Factorial.h"
#include "10-10_cons_list.h"

//!  һ�����Ϳ��Կ��������ݵķ�װ����Ϊ�����滹���Զ����Ա�������ݡ���Ա���ͣ�
//!  һ�����ͱ���ȻҲ��һ�����ݡ�
//��           ��Haskell��data ���������� һ�������

/*

data Tree a = Empty | Node a (Tree a) (Tree a)
data Shape = Circle Float Float Float | Rectangle Float Float Float Float
*/
// 
//  if<bool, T1, T2> ģ���ǻ���ƫ�ػ��� (�൱��boolֵ�ϵ�if)
//    Ҫ��������ƫ�ػ�����Ҫ�� ������� ��ʽд���ڲ� ���޳����Զ������� ��������ѡ��
//! ��ʵ����������ֵģ��ǿ��Խ� ֵ��ģʽƥ��/ƫ�ػ��������Զ���ifѡ��,  ��ʽͨ����ͬһ�� ģʽ�ڲ��ļ��㣨ͨ������ֵ��������������ƫ�ػ���

namespace wjh
{

//struct SelectThen
//{
//	template <typename _Then, typename _Else>
//	struct Result
//	{
//		using RET = _Then;
//	};
//};
//
//struct SelectElse
//{
//	template <typename _Then, typename _Else>
//	struct Result
//	{
//		using RET = _Else;
//	};
//};

template<bool cond>
struct ChooseSelector
{
	//using RET = SelectElse;

	template <typename _Then, typename _Else>
	struct F
	{
		using RET = _Else;
	};
};

template<>
struct ChooseSelector<true>
{
	//using RET = SelectThen;

	template <typename _Then, typename _Else>
	struct F
	{
		using RET = _Then;
	};
};

//X ��һ������ȫ�ػ���  ���� cond ѡ��һ�� ���� �� �ú��������� 
//X �ڶ�������ʣ�����������������������
	//!  ���� curry ��!  / �հ� �� 
template<bool cond, typename _Then, typename _Else>
class if_
{

	//using Selector = typename ChooseSelector<cond>::RET;
public:

	//using Ret = typename Selector::template Result<_Then, _Else>::RET;

	using RET = typename ChooseSelector<cond>::template F<_Then, _Else>::RET;
};

inline void test_new_if()
{
	//using t0 = if_<(1 + 1 > 3), int, double>::Ret;
	using t1 = if_<(1 + 1 > 3), int, double>::RET;
}
}
//x====================================================================================================================
/*
Switch< 1,
	Case<1,A,
	Case<2,B,
	Case<Default,C>>  ---> 1
*/

constexpr int Default = endValue;
struct NoMatch;

template<int _val, typename _T>
struct Case;

/*
data Case = Case { val = Int, T = Type }

switch :: Int -> [Case] -> Type
switch c [(Case Default T): _]    =    T
switch c [(Case val T):cases]     =    if c==val then T else switch c cases
*/

template<int cond, typename... Cases>
struct Switch;

template<int cond, int _val, typename _T, typename...Cases>
struct Switch<cond, Case<_val, _T>, Cases...>
{
	using Ret = typename IF<(cond == _val), _T, typename Switch<cond, Cases...>::Ret>::Ret;

	//using Tt = (1 == 1) ? int : double;
	//using Ret = (cond == _val) ? _T : Switch<cond, Cases...>::Ret;  // ?: ����ĸ��������ֵ�����������ͣ�
};

template<int cond, typename _T, typename...Cases>
struct Switch<cond, Case<Default, _T>, Cases...>
{
	using Ret = _T;
};

template<int cond>
struct Switch<cond>
{
	using Ret = NoMatch;
};

inline void test_switch()
{
	using T0 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<3, long>
		, Case<Default, float>>::Ret;

	using T1 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>
		, Case<Default, float>
		, Case<3, long>>::Ret;

	// ��ƥ��,��default
	using T2 = Switch<(1 + 2)
		, Case<1, int>
		, Case<2, double>>::Ret;
}
//x====================================================================================================================
/*
template <typename T>
struct Fuck
{
	������
	foo(){...}
}

... Fuck<int> ...                // ģ����С�ʵ������ �� Fuck<int> ������ͱ�����       //todo  ����ʵ����  ����ʵֻ�൱��һ�����͵�����  struct Dog;)


... Fuck<int>::foo(x)...          //todo ��ȫʵ����     ��ʵ����������͵ĳ�Աֻ�ڱ�����ʱ���Ž���ʵ������<--- "����"
                                        //todo ---------------->  ������ֻ��������Ӧ����������� ��Ret/val ��Ա��--------->  ����� ����struct�����������Ա


*/

//=========>  �ֶ�Ҫ�󳹵�ʵ������  template class Fuck<int>;   //ע����"template"
//x====================================================================================================================




#endif

