#ifndef h_recursion
#define h_recursion
#include "10-10_cons_list.h"

//! �ѵݹ鶼���β�ݹ�
//!    �~�~�~�~�~�~�~�~��ʽ����ѭ�����µ�״̬ջҲ���ڵݹ������


//! �~�~��̬���벻���ڶ�ͬһ���ݵĶ����ֵ��     Fib<3>::Ret ���۳��ֶ��ٴΣ�ֻ����ֵһ��  ����ͬ�ڶ�̬�����е� fib(3) ���ã�
//x==========================================================================================================
inline int fib(int n)
{
	//  0  1  ...
	int i = 1;
	int x = 1, y = 0;

	while (i < n) {
		++i;
		x += y;      // x + y 
		y = x - y;   // ��һ����x 
	}
	return x;
}

namespace wjhtest {
	
template<bool cond, int n ,int i, int x ,int y>
struct Fib_
{
	enum { val = Fib_<(i+1<n), n, i+1, x+y, x>::val };
};

template<int n ,int i, int x ,int y>
struct Fib_<false,n,i,x,y>
{
	enum {val = x};
};

template<int n>
struct FibMain
{
	enum { val = Fib_<(n>1),n,1, 1,0>::val };
};

inline void test_fibmain()
{
	// 0 1 2 3 4 5 6 7  8  9  10 11
	// 0 1 1 2 3 5 8 13 21 34 55 89
	auto r1 = FibMain<5>::val;
	auto r2 = FibMain<10>::val;
}
}
//x==========================================================================================================
template<int n, int i ,int x ,int y>
struct Fib_Env
{
	enum { result = x };
};

template<typename Fib_Env>
struct Fib_Predict; //! ԭ������
template<int n, int i ,int x ,int y>
struct Fib_Predict<Fib_Env<n,i,x,y>>
{
	static const bool val = i < n;            //x bool ֵ �� int ֵ���ܻ���ת���� �һ��� bool ��ʾ�������Ͱɣ�
};

template<typename Fib_Env>
struct Fib_Update;  //! ԭ������
template<int n, int i ,int x ,int y>
struct Fib_Update<Fib_Env<n,i,x,y>>
{
	using Ret = Fib_Env<n, i + 1, x + y, x>;
};


template<template<int,int,int,int> class Predict        // ģ��� template ��������� �������Ͷ� �����
	, template<int,int,int,int> class Update
	, template<int,int,int,int> class InitEnv>
struct Fib_While
{
	using InitEnv = Fib_Env<5, 1, 1, 0>;
	using Result = typename IF<Fib_Predict<InitEnv>::val, InitEnv, typename Fib_Update<InitEnv>::Ret>::Ret;


	//using Ret = typename IF<Predict<InitEnv>::val, typename Update<InitEnv>::Ret, InitEnv>::Ret;
};

inline void test_Fib_00()
{
	//auto r = 
}

//x ==========================================================================================================
//!  Haskell�е�typeclass�����C++TMP�б���
//!     struct �ȿ��Ա�����ݡ��ֿ��Ա�ﺯ�� ����ʵ�ϣ���ģ��Ԫ��Ψһconstruct)
//��γ����أ���
/*
����� lisp ��ʵ��while:
//todo  ���жϵ�ǰ״̬�Ƿ�Ҫiterate�� �����Ҫ����iterate ----> �����ؿ�ͷ

while  f_cond_judge   f_update  state  
=  if (f_cond_judge state)  then  state  
                            else  while f_cond_judge f_update (f_update state)

data Env a = Env a

while :: (Env a -> bool)  -> (Env a -> Env a) -> Env a -> Env a
while fpred fupdate state = if (fpred state) then state else while fpred fupdate (fupdate state)

*/
template<typename T>
struct Env
{
	using data = T;
};

template<typename T
	,template<Env<T>> class F_predict
	,template<Env<T>> class F_update
	,typename  State>      //! ������ Env<T> State ����ģ����� -------->   Ҫ������ typename / template / int 
struct While<F_predict,F_update,State>
{
	using Ret = typename IF<F_predict<State>::val
					, State
					, typename F_update<State>::Ret>::Ret;
};
//x ==========================================================================================================

template<typename Env
	, template<Env> class Predict
	, template<Env> class Update>  //! ��������
struct Whilexx;

//template<typename Env
//	, template<Env> class Predict
//	, template<Env> class Update>  //! ��������
//struct While<Predict,Update,Env>   //! ����˳�򡪡�������������������˳��һ�£�
//{
//	using Ret = typename IF<Predict<Env>::val, typename Update<Env>::Ret, Env>::Ret;
//};
template<typename Env
	, template<Env> class Predict
	, template<Env> class Update>
struct Whilexx<Env,Predict,Update>
{
	using Ret = typename IF<Predict<Env>::val, typename Update<Env>::Ret, Env>::Ret;
};

template<int n>
struct Fibs
{
	using InitEnv = Fib_Env<5, 1, 1, 0>;

	using Ret = typename Whilexx<InitEnv, Fib_Predict, Fib_Update>::Ret;
	//using Ret = typename While<Fib_Predict, Fib_Update, InitEnv>::Ret;       //Env = Fib_Env
};

#endif

