#ifndef _FIBONACCI_H_
#define _FIBONACCI_H_

/*
Haskell:

fib :: Int -> Int    // Ϊ��ͬ�Ĳ���ƥ�䣬ֱ���ṩһ������ֵ
fib 0 = 1
fib 1 = 1
fib N = (fib (n-1)) + (fib (n-2))

*/


// Ϊÿ��ʵ����һ������ֵ
template<int N>
struct Fib
{
	enum
	{
		Result = Fib<N-1>::Result + Fib<N-2>::Result
	};
};

template<>
struct Fib<1>
{
	enum { Result = 1};
};

template<>
struct Fib<0>
{
	enum { Result = 1};
};


#endif

