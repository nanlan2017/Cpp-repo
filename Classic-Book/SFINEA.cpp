#include "prelude.h"
#include "prelude_boost.h"

//x===============================================================================================================
//! SFINEA ʹ�����ǿ��Զ�ģ����ػ�ƥ���ṩ��ʽ������ƥ��
template<int i>
struct A
{};

char g(int);
char g(float);

template <class T>
auto f(T) -> A<sizeof( g((T)0) )>
{
	return A<4>();
}

inline void test_SFINEA()
{
	//f(1);
}
//x===============================================================================================================
//todo    �ж����Ƿ����foo()�����Ա����
template<typename T>
struct has_member_foo
{
private:
	/*
	//TODO    �����һ��ʽ���ǿ�ͨ���ģ�������true_type
	//TODO    auto Check(int)  ->  true_type       // ���foo���ڣ���˶��屻���� ����> �Ӷ� Check(int) �ܵõ�true_type.  ������� false_type
	//TODO    auto Check(...)  ->  false_type
	*/

	//! decltype(exp1, exp2, ...expN)  :  ֻ�е�exp1,exp2����valid (compilable)ʱ���Ż����expN �������
	//! enable_if(test-T, T)           :  ֻ�е�T��������ʱ���Ż��ڴ˴�����һ��T���͡�
    template<typename U>
        static auto Check(int) -> decltype( std::declval<U>().foo(), std::true_type() );  

    template<typename U>
        static std::false_type Check(...);   // ����ƥ��� �� ��������� ���� �ܹ��õ�ƥ�䣨�������ڱ�������
public:
	static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
};
 
struct myStruct
{
    void foo() { std::cout << "hello" << std::endl;  }
};
 
struct another
{
    void test() { std::cout << "test" << std::endl;  }
};
 
void test_sfinea()
{
	auto r1 = has_member_foo<myStruct>::value;
	auto r2 = has_member_foo<another>::value;
}
//x===============================================================================================================
//!  �Ƶ�������
//!      T has foo()  --->   T* p->foo()  [Compilable]   -> decltype(~, UNT) will pass , become a specialization  ->  decltype(Ret) will differ

// Non-templated helper struct:
struct _test_has_foo {
    template<class T>
    static auto test(T* p) -> decltype(p->foo(), std::true_type());

    template<class>
    static auto test(...) -> std::false_type;
};

// Templated actual struct:
template<class T>
struct has_foo : decltype(_test_has_foo::test<T>(nullptr))
{};

void test_sfinea_2()
{
	auto r1 = has_foo<myStruct>::value;
	auto r2 = has_foo<another>::value;
}

//x===============================================================================================================
template <typename... Ts> 
using void_t = void;

template <typename T, typename = void>
struct has_typedef_foobar : std::false_type {};

template <typename T>
struct has_typedef_foobar<T, void_t<typename T::foobar>> : std::true_type {};

//template<typename T>
//struct has_typedef_foobar<T> : std::true_type
//{
//private:
//	using T = typename T::foobar;
//};

struct foo {
  using foobar = float;
};

void test_sfinea_3() {
  std::cout << std::boolalpha;
  std::cout << has_typedef_foobar<int>::value << std::endl;
  std::cout << has_typedef_foobar<foo>::value << std::endl;
}