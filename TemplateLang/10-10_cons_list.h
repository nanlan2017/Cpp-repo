#ifndef h_10_10_conslist
#define h_10_10_conslist
#include "prelude.h"
#include "10-5_Factorial.h"
//!  �������룺Ԫ��̿��Զ����͡�����ֵ���м��㣬   ��ô���������С�Ԫ��̡��������� lisp��,RubyԪ��̣����ݲ���node,�����﷨��)

//todo  ����һ�����ƣ� �Ը����ֶ���һ�� �������պ����弴��
//x Ruby֧������ʱ��̬�࣬ ����ʱ define function
//x  C#��partial classò��Ҳ���ԣ���
//x    C++��Lisp������ڱ���ʱ��չ�����﷨��
/*
[lisp]
(defmacro create (name)
	`(defun ,name ()
		())
*/

//!  DSL �Ǹ�������ͨ�� һЩö�ٵ�����ֵ������ֵ��+ ���ѡ��ṹ ����������������>  ���õ�һ�����ͣ���ȻҲ�͵õ�������Ա��
/*
//!  �~�~�~�~���������ڿ��Զ����͡�����ֵ�����㣬�������ڲ�������Ƕ�����������ݡ����ļ�����Ҳ������һ������

//!              �~�~�~�~ԭ��������ʵ�����Σ�
//!                �~�~�~�~��TypesEnum������ʵ��һ�ָ������ͣ��������и��ֳ�Ա�� ����/����ֵ
*/

//x==========================================================================================================================
//todo ��Ȼ�������ˣ���Ȼ���Զ������ݽṹ (��ģ��Ԫ��)
//todo   ��������ȫ����Ϊ�����ݣ� ���仰˵�������ڡ����͡� ��������ˡ�

// head [] = nil
// tail [] = []
const int endValue = ~(~0u >> 1);
struct End           //todo end����һ������ֵ��: ���б�  Haskell []   /  lisp '()
{
	enum { head = endValue};
	using Tail = End;   //?   ???
};

// cons :: Int -> TList ->  TList
template<int n, typename _Tail = End>
struct Cons
{
	enum { head = n };
	using Tail = _Tail;
};

//! �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
//! ��Ҫ��ʶ�� church�� �󣬾Ͳ��ᾪ�� �����һ��ͼ���걸�����ԣ� ������������Ԫ�أ�����������������+ �ݹ飩 �����������ָ��ӵ����ݽṹ���㷨�ˡ�
//!    ------>    cons,   if/switch/cond   ,   (atom? /   car | cdr )  eq?  


//todo Haskell�ж������ݽṹ��ͨ�� data MyType = ...
//todo                Cons�Ǻ������������������ͣ� Cons<...> ��������һ��ֵ�����ͣ�
template<typename List>
struct Length
{
	enum { val = 1 + Length<typename List::Tail>::val };
};

//! nil/  '()
template<>
struct Length<End>
{
	enum { val = 0};
};
/*----------------------------------*///todo  car,cdr
template<typename List>
struct Head
{
	enum { val = List::head};
};

// Tail<End>::Ret ---> End
template<typename List>
struct Tail
{
	using Ret = typename List::Tail;   
};

/*----------------------------------*///todo  list
/*
���Ľ��������ʹ��C++11ģ��Ԫ���ʵ��Scheme�е�list����غ���ʽ��̽ӿڣ�
��list��cons��car��cdr��length��is_empty��reverse��append,map��transform��enumerate��lambda��
*/

/*
list x &rest args
= cons x (list args)
*/
template<int n,int...args>
struct List                //! �~�~�~�~��Ȼ��ֻ������һ��Struct���󲻼�<>      (���������ػ���)
{
private:
	//using Tail = List<forward<int>(args...)>;  //x wront

	using Tail = List<args...>;
public: 
	using Ret = Cons<n, typename Tail::Ret>;
};

template<int n>
struct List<n>
{
	using Ret = Cons<n>;
};
/*----------------------------------*///todo  is_empty
template<typename List>
struct Is_Empty
{
	//enum { val = static_cast<bool>(Length<List>::val == 0) };

	static_constexpr bool val = Length<List>::val == 0;
};
/*----------------------------------*///todo  append
/*
append :: [Int] -> Int -> [Int]
append (x:xs) n = cons x (append xs n)
append [] n = cons n
*/
template<typename List,int n>
struct Append;

template<int headval,typename Tail,int n>
struct Append<Cons<headval,Tail>,n>
{
	using Ret = Cons<headval, typename Append<Tail,n>::Ret>;
};

template<int n>
struct Append<End,n>
{
	using Ret = Cons<n>;
};
/*----------------------------------*///todo  reverse
/*
reverse (x:xs) = reverse xs ++ x
*/
template<typename List>        //! �޷���һ���������List�Ľṹ����ģʽƥ�䣨��⣩
struct Reverse;

template<int headval,typename Tail>        //! �޷���һ���������List�Ľṹ����ģʽƥ�䣨��⣩
struct Reverse<Cons<headval,Tail>>                 //!  �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~ֻҪ�ǵݹ���õ�(�ڲ�������������ȻҪ��ȥ����һ���ػ���� �ݹ���ֹ�߽硪�������������� ����ĳ������ֵ�ﵽ�ٽ�ֵʱ
{
	using Ret = typename Append<typename Reverse<Tail>::Ret, headval>::Ret;
};

template<>
struct Reverse<End>
{
	using Ret = End;
};
/*----------------------------------*///todo  map
// map (x:xs) f = cons (f x) (map xs f)    --- �ڶ���������ﵽ�ٽ�ֵ End (���б�)
// map End f = End
template<typename List,
		template<int> class F>
struct Map;                               //todo  ���ͨ�������Ǳ�Ҫ�ģ� �����򱨴���

template<int headval,typename Tail,     
		template<int> class F>
struct Map<Cons<headval,Tail>,F>          //todo �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~ͨ��ģʽƥ�������һ�� F<a,b,c>���ͣ�   //�˴���  List === Cons<headval,Tail>
{
	using Ret = Cons<F<headval>::val, typename Map<Tail, F>::Ret>;
};
/*
template<typename List,
		template<int> class F>
struct Map   
{
private:
	enum { headVal = Head<List>::val };   //todo  �������ǲ�����ģʽƥ���⣬�����ֶ����ڲ����㣡  ̫2�ˡ�
	using Tail = typename Tail<List>::Ret;
public:
	using Ret = Cons<F<headVal>::val
		, typename Map<Tail, F>::Ret >;
};
*/
template<template<int> class F>
struct Map<End,F>
{
	using Ret = End;
};

//todo ---------------------------------------
template<template<int> class F
		,int ...Args>
struct map_
{
	using Ret = typename List<F<Args>::val...>::Ret;
};
/*----------------------------------*///todo  Last
//!  ע�������ֵ���ݹ���ֹʱ����Ҫ�ٱ��ݹ�һ������

// last [x] = x
// last (x:xs) = last xs

template<typename List>
struct Last;

// last (x:xs) = if (null? xs) then x else last xs
//!  null? xs  �Ͷ�Ӧ��   last (x:End) ����ػ��
template<int headval,typename Tail>
struct Last<Cons<headval,Tail>>
{
	//using Ret = typename Last<Tail>::Ret;
	enum { val = Last<Tail>::val };
};

template<int headval>
struct Last<Cons<headval,End>>
{
	//using Ret = Head;
	enum { val = headval};
};
// ---------------------------------------

inline void test_cons()
{
	//! ���Լ��������е�Int���ͽ��в���������

	//  cons , length
	using list1 = Cons<2>;
	auto len1 = Length<list1>::val;
	// head(car), tail(cdr)
	auto head1 = Head<list1>::val;
	using tail1 = Tail<list1>::Ret;
	// is_empty
	bool r3 = Is_Empty<tail1>::val;
	// list
	using list2 = List<4, 5,7,9,11>::Ret;
	// append, reverse, map
	using added_list1 = Append<list1, 9>::Ret;
	using reversed_list1 = Reverse<added_list1>::Ret;
	using mapped_square = Map<reversed_list1, Square>::Ret;

	// map_, last
	using mapped_new = map_<Square,3,7,10>::Ret;
	auto last = Last<mapped_new>::val;
}
//x==========================================================================================================================

#endif

