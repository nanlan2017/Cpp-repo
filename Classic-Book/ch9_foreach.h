#ifndef h_ch9_foreach
#define h_ch9_foreach

#include "prelude.h"
#include "prelude_boost.h"

template<typename T>
struct wrap {};

struct print_type
{
	template<typename T>
	void operator()(wrap<T>) const
	{
		std::cout << typeid(T).name() << std::endl;
	}
};


//x=================================================================================================================== vistor ģʽ 
//   ÿ�������ṩ�����visit()�� ����ֻ��ͳһ����visit����

//!  ���������������������г�Ա״̬������ʵ�����ͺ��ṩ�Ǹ�������������һ����
struct visit_type
{
	template<typename Visitor>
	void operator()(Visitor) const
	{
		Visitor::visit();
	}
};

//todo   ���������ĺ����� ��һ���İɣ�����
template<typename Visitor>
void f_visit_type(Visitor)
{
	Visitor::visit();
}

template<typename T>
struct print_visitor
{
	static void visit()
	{
		std::cout << typeid(T).name() << std::endl;
	}
};


#endif

