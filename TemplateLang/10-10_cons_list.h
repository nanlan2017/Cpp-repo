#ifndef h_10_10_conslist
#define h_10_10_conslist
#include <boost/thread/lock_types.hpp>

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

const int endValue = ~(~0u >> 1);

//todo   ��������ȫ����Ϊ�����ݣ� ���仰˵�������ڡ����͡� ��������ˡ�
struct End
{
	enum { head = endValue};
	using Tail = End;   //?   ???
};


template<int n, typename _Tail = End>
struct Cons
{
	enum { head = n };
	using Tail = _Tail;
};



//todo Haskell�ж������ݽṹ��ͨ�� data MyType = ...
//todo                Cons�Ǻ������������������ͣ� Cons<...> ��������һ��ֵ�����ͣ�
template<typename List>
struct Length
{
	enum { val = 1 + Length<typename List::Tail>::val };
};

template<>
struct Length<End>
{
	enum { val = 0};
};

inline void test_cons()
{
	//  2~3~7~'b'~false~End
	using list0 = Cons<2, Cons<3, Cons<7, Cons<'b', Cons<false>>>>>;
	auto len0 = Length<list0>::val;

	//  2~End
	using list1 = Cons<2>;
	auto len1 = Length<list1>::val;
}
//x==========================================================================================================================

#endif

