#ifndef h_lisplist
#define h_lisplist

#include "prelude.h"
//! ��Щ���ݽṹ�ǳ��򵥣������¶��������������
/*
  //todo   �����л������͵�ֵ����ʾΪһ�����ͣ�  
  //todo            ���� ��  Fuck��ֵ it�� ��ʾΪ Fuck<it>
  //todo                  type       : Fuck<it>
  //todo                  value_type : Fuck
  //todo                  value      : it
*/



// type_
//
template <typename T, T N>
struct type_ {
    using type = type_<T, N>;
    using value_type = T;
    static constexpr T value = N;
};

// int_
//
template <int N>
struct int_ {
    using type = int_<N>;
    using value_type = int;
    static constexpr int value = N;
};

// uint_
//
template <unsigned int N>
struct uint_ {
    using type = uint_<N>;
    using value_type = unsigned int;
    static constexpr unsigned int value = N;
};

template <>
struct uint_<0> {
    using type = uint_<0>;
    using value_type = unsigned int;
    static constexpr unsigned int value = 0;
};

// bool_
template <bool N>
struct bool_ {
    using type = bool_<N>;
    using value_type = bool;
    static constexpr bool value = N;
};

// empty
//
struct empty {
    using type = empty;
    using value = empty;
};
//x=================================================================================================================================
template <unsigned int N>
struct binary :            uint_< binary<N/10>::type::value * 2 + (N % 10) > 
{};

template <>
struct binary<0> : uint_<0> 
{};


inline void test_binary()
{
	using i3 = type_<int, 3>;

	// 3
	using int_3 = int_<3>;

	// �����Ƶ� 10101 ��Ӧ ʮ���Ƶ� 21
	auto r = binary<10101>::value; // 21
}

#endif

