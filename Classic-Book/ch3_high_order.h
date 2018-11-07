#ifndef h_ch3_highorder
#define h_ch3_highorder
#include "prelude_boost.h"
#include <boost/type_traits/add_pointer.hpp>
//using namespace mpl;

template<typename NumT>
struct square
	: mpl::int_<99999999>
{ };

template<int n>
struct square<mpl::int_<n>>
	: mpl::int_<n*n>
{};

struct square_f
{
	//todo  what's different?
	//template<typename T>
	//struct apply<T> : square<T> {};

	template<typename T>
	struct apply
	{
		using type = typename square<T>::type;
	};
};
//x-----------------------------------------------------------------------------
//!  apply call tool
// F_wrapper ���ڲ����� apply ���Ԫ������Wrapper Struct
template<typename F_Wrapper, typename...Args>
struct apply    // �Ѿ���mpl�����һ���ˡ�
	: mpl::lambda<F_Wrapper>::type::template apply<Args...>     //todo    ��lambdaһ�£��Ӷ��������Խ���Ԫ�����ࡢ�����Խ���ռλ�����ʽ��
{};

//!  Ԫ����ת���棨����Haskell)
//!   twice f x = f (f x)
template<typename F,typename T>
struct twice 
	: ::apply<F, typename ::apply<F,T>::type>
{};

inline void test_apply_lambda()
{
	using T0 = twice<boost::add_pointer<mpl::_1>, int>::type;

	using T1 = ::apply<boost::add_pointer<mpl::_1>, int>::type;

}

//x===============================================================================================
struct add_pointer_f
{
	template<typename T>
	struct apply : boost::add_pointer<T>{};
};
inline void test_ch3_high()
{
	using Int3 = mpl::int_<3>;
	auto r0 = Int3::value;
	using T00 = Int3::value_type;
	using T01 = Int3::type;
	using T02 = Int3::tag;
	using T03 = Int3::next;


	//using T1 = twice<square_f, T>::type;
	using T1 = square_f::apply<Int3>::type;
	//using T2 = apply<square_f, Int3, Int3>::type;
	using T3 = twice<square_f, Int3>::type;

}
//x===============================================================================================
// two_pointers x = twice (\ ==> add_pointer _1) x
template<typename X>
struct two_pointers
	: twice<typename mpl::lambda<boost::add_pointer<mpl::_1>>::type, X> { };

//!  �~�~�~�~�~�~�~�~�~�~�~�~��ǰ��û��template���������Դ���һ����������Wrap��һ�������ʱ������Ϊ"Ԫ������"
//!        plus,minus��������Ȼ��һ��Ԫ������ģ�����ͣ�������ֱ����Ϊtypename���д��ݡ�
//!                ���� plus<_1,_2> ��������һ���������ͣ����Դ��ݣ�����Ҫlambda�����ܽ����ڲ�apply)
//!           �����ܺ��������ĺ����ڲ�����ֱ����apply���ô˺����� lambda<param_f>::template apply<...>::type )

//!  �~�~�~�~�~�~�~�~�~�~�~�~���к������õ����壬������Ҫд ::type  ȡ������  (��д��lambda���ռλ�����ʽ����ȡ::type)

//todo ȡ��lambda���ɵ�Ԫ�������е�applyԪ����
template<typename M, typename N> 
using apply_plus = mpl::lambda<mpl::plus<mpl::_1, mpl::_2>>::type::template apply<M, N>;

inline void test_ch3_lambda()
{
	//  \x -> x       ---->   lambda(_1)
	//  \x -> x * 2   ---->   lambda(_1 * 2)       // ����clojure���д��
	BOOST_STATIC_ASSERT((
		std::is_same<int**
		, two_pointers<int>::type>()
		));

	//! mpl::apply
	auto r4 = mpl::apply<mpl::plus<mpl::_1, mpl::_2>, mpl::int_<3>, mpl::int_<4>>::type::value;

	//using T0 = apply<mpl::lambda<square<mpl::_1>>, mpl::int_<3>>::type;
	//!  lambda
	// �ڲ�����  apply ģ�� ��һ����ģ��struct
	//! lambda<square>  ====  
	using T00 = boost::add_pointer<mpl::_1>;
	using T01 = mpl::lambda <T00>::type;          //!  lambda����һ��ռλ�����ʽ ת��Ϊ Ԫ�����ࣨ����applyԪ����)
	using T02 = T01::template apply<int>::type;

	auto r1 = std::is_same <add_pointer_f, T01>::type::value;

	//todo    ԭ������Ԫ�����ģ���lambda������Ӱ��
	auto r2 = std::is_same<add_pointer_f
		, boost::mpl::lambda<add_pointer_f>::type>::value;

	//todo     plus<_1,_2>  ����lambda�� ------>  �õ��ڲ��� applyԪ������ Ԫ������   ------>  ��ʽ���ø�applyԪ����
	using T1 = mpl::lambda<mpl::plus<mpl::_1, mpl::_2>>::type::template apply<mpl::int_<3>, mpl::int_<4>>::type;

	using T3 = apply_plus<mpl::int_<3>, mpl::int_<4>>::type;
}

//x================================================================================================================
inline void test_compose()
{
	using Int7 = mpl::int_<7>;
	using Int3 = mpl::int_<3>;
	//  f = \x y -> (x+y) * (x-y)
	//  f = \_1 _2 -> (_1 + _2) * (_1 - _2)
	using Fexp = mpl::multiplies<mpl::plus<mpl::_1, mpl::_2>, mpl::minus<mpl::_1, mpl::_2>>;
	using Fcla = mpl::lambda<Fexp>::type;
	using T0 = Fcla::apply<Int7, Int3>::type;
	//auto r0 = mpl::equal<T0, mpl::int_<4>>::value;

	//! true!!!
	auto r1 = mpl::equal<mpl::int_<3>, mpl::int_<4>>::type::value;

}
//x================================================================================================================

#endif

