#include "prelude_boost.h"

//!  macro function :   fmacro
//!  macro varible :   VARIBLE

#ifndef TINY_MAX_SIZE
#	define TINY_MAX_SIZE 3
#endif

struct none;

/*
template<typename T0, typename T1, typename T2>
struct tiny_size
	: mpl::int_<3>
{};
*/
template<BOOST_PP_ENUM_PARAMS(TINY_MAX_SIZE,typename T)>
struct tiny_size
	: mpl::int_<TINY_MAX_SIZE>
{ };

/*
template<class T0, class T1>
struct tiny_size<T0,T1,none>
	: mpl::int_<2> { };

template<class T0>
struct tiny_size<T0,none,none>
	: mpl::int_<1> { };

template<>
struct tiny_size<none,none,none>
	: mpl::int_<0> { };
*/

#define TINY_print(z,n,data) data

//TODO    lisp
/*
defmacro tiny-size (n)
	template< ypename T0~ typename Tn >
	struct tiny_size< T0~ Tn, ��� max_size-n ��none >
		: int_<n> {};
*/
//TODO   TINY_size�꣺  ���� n (sizeֵ), ����  tiny_size�� n �汾
#define TINY_size(z,n,unused)                                                \
	template <BOOST_PP_ENUM_PARAMS(n,class T)>                               \
	struct tiny_size<	                                                     \
		BOOST_PP_ENUM_PARAMS(n, T)                                           \
		BOOST_PP_COMMA_IF(n)                                                 \
		BOOST_PP_ENUM(BOOST_PP_SUB(TINY_MAX_SIZE, n), TINY_print, none)      \
	>                                                                        \
	: mpl::int_<n>{};

//TODO   ����TINY_size�� max_size �� ���������е�tiny_size�ػ���
BOOST_PP_REPEAT(TINY_MAX_SIZE, TINY_size, ~)

#undef TINY_size
#undef TINY_print


#define Tiny
