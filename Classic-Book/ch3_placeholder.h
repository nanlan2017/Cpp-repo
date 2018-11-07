#ifndef h_ch3_placeholder
#define h_ch3_placeholder

#include "prelude_boost.h"
#include "prelude.h"
namespace wjh {
using namespace std;
	
struct void_;

template<int n> 
struct arg;

template<>
struct arg<1>
{
	template<typename A1,typename A2 = void_, typename A3 = void_, typename A4 = void_>
	struct apply
	{
		using type = A1;
	};
};

template<>
struct arg<2>
{
	template<typename A1,typename A2 = void_, typename A3 = void_, typename A4 = void_>
	struct apply
	{
		using type = A2;
	};
};

template<>
struct arg<3>
{
	template<typename A1,typename A2 = void_, typename A3 = void_, typename A4 = void_>
	struct apply
	{
		using type = A3;
	};
};

template<>
struct arg<4>
{
	template<typename A1,typename A2 = void_, typename A3 = void_, typename A4 = void_>
	struct apply
	{
		using type = A4;
	};
};

using _1 = arg<1>;
using _2 = arg<2>;
using _3 = arg<3>;
using _4 = arg<4>;

inline void test_my_placeholder()
{
	using Int7 = mpl::int_<7>;
	using Int3 = mpl::int_<3>;
	//  f = \x y -> (x+y) * (x-y)
	//  f = \_1 _2 -> (_1 + _2) * (_1 - _2)
	using Fexp = mpl::multiplies<mpl::plus<_1, _2>, mpl::minus<_1, _2>>;    //todo  �滻Ϊ�Ҷ���� placeholders
	using Fcla = mpl::lambda<Fexp>::type;
	//using T0 = Fcla::template apply<Int7, Int3>::type;	//todo   x 


	//x-------------------------------------------------------------------------------------
	//x  lambda( f(_1, _2)  )::type   ���ǵõ����Ǹ� Ԫ����Wrapper��
	//x     Ĭ�ϵĻ��� f��һ��Ԫ������lambda��ȡ��type��Ϊtype)
	//x      ���f ֻ��һ��ģ�塢������Ԫ�����Ļ�������type��Ա���� �����ػ���ģ��ʵ��������� type����lambda�ķ���type)
	using t0 = mpl::apply<vector<mpl::_1>, int>::type;
	//using t1 = vector<int>::type; // ����type��Ա
	static_assert(is_same<t0, vector<int>>::value, "");

	//!  nullary ->  unary -> binary -> ternary
	//!   �޲�        ����      ��Ԫ      ��Ԫ   
	using t3 = add_pointer<int>;
	using t4 = add_pointer<int>::type;

}
}

#endif
