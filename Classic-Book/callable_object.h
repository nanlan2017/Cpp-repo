#ifndef h_callable_object
#define h_callable_object

#include "prelude.h"
#include "prelude_boost.h"

struct add1_obj
{
	template<typename T>
	T operator()(T i)
	{
		return i + 1;
	}
};

template<typename T>
T add1_tempf(T i)
{
	return i + 1;
}

inline int add1_int_tmp(int i)
{
	return i + 1;
}
//x------------------------------------------------------

template<typename F>
void consume_callable(F func)
{
	std::cout << func(1) << std::endl;
}

inline void consume_callable_int(int(*func)(int))
{
	std::cout << func(1) << std::endl;
}
//x------------------------------------------------------
inline void test_callable()
{
	consume_callable(add1_obj());   //!�~�~�~�~�~ ����������ȫ������ڴ���һ���հ���ʵ����Ҳ�� �հ���lambda��ʵ�ʣ�����һ���������󣩡�������ǿ�ڱ�һ��ĺ��� ѡ���Եİ���״̬

	//use_callable(add1);      //todo add1 �Ƿ��͵� ������ ���Խ��շ��޷����� �ƶϳ����Ͳ��� F �����ͣ�

	consume_callable(add1_int_tmp);


	//consume_callable_int(add1_obj());  //todo   ����Ҳ����
	consume_callable_int(add1_tempf);
}
#endif

