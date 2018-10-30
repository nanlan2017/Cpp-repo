#ifndef h_tuple
#define h_tuple
#include "prelude.h"

// tuple<int, string, char> ���Զ�����һ��  �̳���tuple<string,char>���������int����
template<typename T, typename ...Args>
class Tuple : public Tuple<Args...>
{
private:
	T val;
public:
	//!cons
	Tuple(T&& v,Args&&... args)
		:Tuple<Args...>(forward<Args>(args)...)        // �ɱ���� + ����ת��
		,val(forward<T>(v))
	{}

	//!const
	decltype(auto) get(size_t n) const
	{
		static_assert(n <= sizeof(Args));
		if (n == 0)
			return val;
		else
			return Tuple<Args...>::get(n - 1);
	}
};

template<size_t n,
		template<typename...> class Tuple, 
		typename... ArgsWrapper>
struct tuple_element<n, Tuple<ArgsWrapper...>>
{
	//! �����һ��ģ�������ԣ�����Haskell: û�пɱ������л����Ľṹ��
	// û�������ĺ����ˡ� ֻ�в��ɱ�ı���ʱ�������ʽ�������͡�
	//! ��template struct���ɺ������� ����>  �����ݾ��� ���͡����� (template params���ǲ�����
	//!                              ����>  ͨ���ػ�ʵ��ѡ��ṹ������IF)
	//!                              ����>  ͨ���ݹ�ʵ��ѭ��
	/*
	template<typename T,typename...Args>
	struct helper<0,T,Args>
	{
		using type = T;
	};
	template<size_t m, typename T, typename ...Args>
	struct helper : public helper<m-1, Args...,void>
	{};
	*/
	/*------------------------------*/
	using type = helper<n, ArgsWrapper..., void>::type;
};

inline 
void usecase_tuple()
{
	


}
#endif

