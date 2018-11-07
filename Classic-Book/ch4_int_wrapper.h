#ifndef h_ch4_wrapper
#define h_ch4_wrapper
#include "prelude.h"
#include "prelude_boost.h"

//x=========================================  bool ==============================================================
//  paramtype ������ ���Ǳ���ʱ�� ʹ��ֵ������ �����ʹ������
template<typename T>
struct param_type
	//!  identity,     eval_if
	//!  ����ת�����൱��ֱ�ӵ�������һ��Ԫ����
	: mpl::eval_if<mpl::or_<boost::is_scalar<T>,boost::is_reference<T>>    //x bool_ �ϵ����㣺 or_, and_ , not_
				, mpl::identity<T>
				, boost::add_reference<T const>>
{
	using t0 = typename mpl::if_<typename boost::is_scalar<T>::type
		//! �ӻ��������͵ĳ�Ա����ȷ�������ͣ���ȥ�����Ա
		, mpl::identity<T>
		, boost::add_reference<T const>>::type;   // �Ⱦ������ͣ���������type��Ա�������������Ͷ�����ȫʵ������
};

template<typename T>
struct holder
{
public:
	holder(typename param_type<T>::type x);     // ���T�Ǳ������ͣ��� (T x) , ����Ϊ (const T& x)
};

inline void test_boolen_wrapper()
{
	using t0 = param_type<int>::type;
	using t1 = param_type<std::vector<int>>::type;
	using t2 = param_type<std::vector<int>&>::type;

	int i = 3;
	holder<int> h1(i);
	std::vector<int> iv;
	holder<std::vector<int>> h2(iv);

	if (boost::is_scalar<int>()) {
		
	}

	using t5 = mpl::if_<boost::is_scalar<int>, long, double>::type;
}
//x=========================================  integral ==============================================================
//!  int_
//!  long_
//!  -----> integral_c

// ֵ�ȼ��ԣ�
//!  equal_to
//!  equal (for Sequence)

inline void test_integral_wrapper()
{
	using Int3 = mpl::int_<3>;

	using Int4 = mpl::next<Int3>::type;

	using Intc5 = mpl::next<mpl::integral_c<int, 4>>::type;
}
#endif

