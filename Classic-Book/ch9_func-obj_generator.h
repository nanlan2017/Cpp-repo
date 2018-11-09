#ifndef h_ch9_generator
#define h_ch9_generator

#include "prelude.h"
#include "prelude_boost.h"

//!                    �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~��ʵ����ʵ��Haskell�еĺ�����ϰ���  f.g  (C++TMP���� �����ɵ��ö����compose��

// compose_fg �� ��������ɵ��ö��󣬲���һ���µĿɵ��ö���
//!  ���Ͳ��������ǹ����࣬���ǹ������Ա��������ȫ�����壨��������Ƿ�ֻ�����÷�����
//todo   �������R���ͣ�

template<typename R, typename F,typename G>
struct compose_fg
{
	compose_fg(F const& f, G  const& g)
		:fobj(f),gobj(g)
	{ }

	template<typename T>
	R operator()(const T& x) const        // ��Ȼ��R������Ҫ����ȥָ��
	{
		return fobj(gobj(x));
	}

private:
	F fobj;
	G gobj;
};

template<typename R,typename F, typename G>
auto compose(F const& f, G const& g) -> compose_fg<R,F,G>
{
	return compose_fg<R, F, G>(f, g);
}

// sin2(x)
inline float sin_squared(float x)
{
	return std::sin(std::sin(x));
};

inline void test_composefg()
{
	float in_arr[5] = { 0.1,0.2,0.3,0.4,0.5 };
	float out_arr[5];

	// compose  (-)  sin_squared
	//todo  ��Ȼ��compose_fg ��Ҫʵ����������ʱ�����ֶ�����ģ������ʵ��
	auto composed_func = compose_fg<float
						, std::negate<>
						, float(*)(float)
					   >(std::negate<>(), sin_squared);

	float* ignored = std::transform(in_arr,in_arr+5, out_arr,composed_func);

	//x �Ż��� ����compose
	//!  ������д������̫�࣬�ڸ��˱��ʼ򵥵ļ��㣨����Haskell�Ǹ������ԣ�
	float* ignored2 = std::transform(in_arr, in_arr + 5, out_arr, compose<float>(std::negate<>(), &sin_squared));
}

template<typename F, bool F_empty, typename G, bool G_empty>
struct storage;

//todo   4���ػ���ʽ

template<typename R, typename F,typename G>
struct compose_fg2 
	: storage<F,boost::is_empty<F>::value
			, G,boost::is_empty<G>::value>
{
	using base = storage<F, boost::is_empty<F>::value, G, boost::is_empty<G>::value>;

	compose_fg2(F const& f, G  const& g)
		:base(f,g)
	{ }

	template<typename T>
	R operator()(const T& x) const        // ��Ȼ��R������Ҫ����ȥָ��
	{
		F const& f = this->get_f();
		G const& g = this->get_f();
		return f(g(x));
	}

private:
	//F fobj;
	//G gobj;
};

#endif

