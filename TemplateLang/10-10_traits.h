#ifndef h_10_10_traits
#define h_10_10_traits
#include "10-5_Factorial.h"
#define statcon static const


//! 1. member traits  
//! 2. traits class
//! 3. traits template

struct FooBase
{
	enum  {fooBase = 100, foo1, foo2};
	enum {id = fooBase};
};

struct Foo1 : FooBase
{
	enum { id = foo1 };          //! �����ڲ��������Լ�������ص���Ϣ
};

struct Foo2 : FooBase
{
	enum { id = foo2 };
};


template<typename SomeFoo>
struct TestFoo
{
	enum { val = SomeFoo::id };  //! ������Ϣ��Ա
};
inline void test_foobase()
{
	auto r = TestFoo<Foo1>::val;
}
//x============================================================================================================
//! 2. traits class
//!    �Ѷ����Ϣ���޷������͡�����ֵ����һ��ͳһ����һ����Ա������





//x============================================================================================================
//! 3. traits template
//!    �൱��һ������ F<type> ���ú��������Ϣֵͬʱȷ�������������� һ�������ڲ����԰����ܶ����Ա��Ϣ


//todo  numeric_traits  :: Type -> [Info...]
template<typename T>
struct nume_traits
{
	//x ͨ������
	static T max() noexcept;
};

//! ���û���ͼ̳�
struct IntBase
{
	
};

template<>
struct nume_traits<long> : public IntBase
{
	using Type = long;
};

template<>
struct nume_traits<int>
{
	// bool, int ,char
	statcon bool has_infinity = false;
	statcon bool is_bounded = false;
	static int max() noexcept { return 1000000; }   // ������ֵ�޷��ڱ�����ʹ��
};

inline void test_traits()
{
	bool r = nume_traits<int>::is_bounded;
}
//x============================================================================================================
//! ��������
//  Promotion<A,B>::Type  �������������� ���Ƚϸߵ��Ǹ�����   �� T::precision ������Ǹ�)
template<typename A, typename B>
struct Promotion
{
private:
	enum
	{
		a_max_exp = nume_traits<A>::has_infinity,
		b_max_exp = nume_traits<B>::has_infinity
	};
public:
	using Type = typename IF< (a_max_exp < b_max_exp), A, B>::Ret;
};
//x============================================================================================================


#endif

