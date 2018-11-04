#ifndef h_haskellutils
#define h_haskellutils
#include "prelude.h"

//todo   �������ڲ����� exec() ��Ա���������ݣ�������һ������
template<typename T1,typename ...Args>
struct Sequence
{
	static void exec()
	{
		T1::exec();
		Sequence<Args...>::exec();
		// E1::exec();    E2::exec();   ....      ���չ�������� ������
		//Args::exec();
	}

	//? env
	template <typename Env>
	static void exec_env(Env&& env)
	{
		T1::exec_env(forward<Env>(env));
		Sequence<Args...>::exec_env(forward<Env>(env));
	}
};

template<typename T>
struct Sequence<T>
{
	static void exec()
	{
		T::exec();
	}

	//? env
	template <typename Env>
	static void exec_env(Env&& env)
	{
		T::exec_env(forward<Env>(env));
	}
};
//x------------------------------------------------------------------------------------

#endif
