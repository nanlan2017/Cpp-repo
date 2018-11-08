#ifndef h_ch6_inserter
#define h_ch6_inserter

#include "prelude.h"
#include "prelude_boost.h"

inline void test_ch6_inserter()
{
	using namespace mpl;

	using seq = vector<bool, char, short, int, long, float, double>;
	auto size_of_int = sizeof_<int>::value;
	using seq2 = replace<seq, char, long>::type;
	using iter_max = max_element<seq2, less<sizeof_<_1>, sizeof_<_2>>>::type;

	//x--------------------------------------------------------------------
	//todo      inserter : �е���yield�� 
	//todo              inserter ������ "continuation����"��  ����Ϊ�������ݣ������ĳ�������Ľ���Ĵ���

	//! foldl      f    acc    [Seq]
	//! inserter   op   state  [Seq]
	// inserter ��state������ ��ʵ��һ��Sequence��yeild
	// inserter ��operation������ ���� f ��
	using result_vec = copy<seq, back_inserter<vector<>>>::type;



	typedef vector<int, float, float, char, int, int, int, double> types;
	typedef vector<int, float, char, int, double> expected;
	typedef unique< types, boost::is_same<_1, _2> >::type result;

	BOOST_MPL_ASSERT((equal< result, expected >));
}

#endif

