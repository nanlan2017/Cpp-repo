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
template<typename Iter>
typename enable_if<is_arithmetic<typename iterator_value<Iter>::type>
					,typename iterator_value<Iter>::type>::type
sum(Iter start,Iter end)          //! ֻ�е�T��������ʱ���Ż����һ��T������Ļ��޷�ʵ��������Ȼ�ͱ���ֹ�ˣ�=======> �~�~�~�~�~�~�~�~�൱��concept mapping
{
	typename iterator_value<Iter>::type x(0);
	for(; start!= end; ++start) {
		x += *start;
	}
	return x;
}

#endif

