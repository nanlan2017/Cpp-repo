#ifndef h_ch9_enableif
#define h_ch9_enableif

#include "prelude.h"
#include "prelude_boost.h"

namespace wjh
{

template<bool b,typename T>
struct enable_if_c
{
	using type = T;
};

template<typename T>
struct enable_if_c<false, T>
{
};

using t0 = typename enable_if_c<boost::is_arithmetic<int>::value, double>::type;
//using t1 = typename enable_if_c<boost::is_arithmetic<void>::value, double>::type;
//x-----------------------------------------------
template<typename Cond,typename T>
struct enable_if : enable_if_c<Cond::value,T>
{ };

using t0 = typename enable_if<boost::is_arithmetic<int>, double>::type;
//using t1 = typename enable_if<boost::is_arithmetic<void>, double>::type;
}


using namespace boost;
//todo  �ú���ģ��ֻ��Ӧ�����������͵ĵ�������
//! enable_if
template<typename Iter>
typename enable_if<is_arithmetic<typename iterator_value<Iter>::type>
					,typename iterator_value<Iter>::type>::type
sum(Iter start,Iter end)          //! ֻ�е�T��������ʱ���Ż����һ��T������Ļ��޷�ʵ������������������Ȼ�ͱ���ֹ�ˣ�=======> �~�~�~�~�~�~�~�~�൱��concept mapping
{
	typename iterator_value<Iter>::type x(0);
	for(; start!= end; ++start) {
		x += *start;
	}
	return x;
}

//todo  ���һ�����ذ汾����Ӧ���� vector<vector<int>>
template<typename ContainerIter>
struct inner_value
	: iterator_value<typename iterator_value<ContainerIter>::type>::iterator
{};

//! disable_if                           lazy_disable_if
template<typename Iter>
typename lazy_disable_if<is_arithmetic<typename iterator_value<Iter>::type>      //x ��������ʱ���ã�
						, inner_value<Iter>>::type                      //x  lazy : ֻ�е���һ������ͨ��ʱ�� �Ž��еڶ��������ļ��㡣������Ļ�����������
sum(Iter start,Iter end)
{
	typename inner_value<Iter>::type x(0);
	for (; start!= end; ++start) {
		x += sum(start->begin(), start->end());   // ����������Ǹ�
	}
	return x;
}
#endif

