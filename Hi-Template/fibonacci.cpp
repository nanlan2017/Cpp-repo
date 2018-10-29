//#pragma comment(lib, "libboost_thread_vc140-mt-gd-1_67.lib")

#include "fibonacci.h"
#include <iostream>

#include <boost/thread/thread.hpp> 

void hello()
{
std::cout << "Hello world, I'm a thread!" << std::endl;
}

void main_fibonacci()
{
	boost::thread thrd(&hello);
	thrd.join();
	system("pause");

}

void test_fib()
{
	/*
	��ģ��ʵ���� Fib<10> 
	--> ���涨����һ��enumֵ�� ��Ҳ�Ǳ�����ȷ���� --> ��ʵ����Fib<9>
	--> ֱ��ȷ�������һ��enumֵ
	*/
	auto fib_10 = Fib<10>::Result;		// �ƶϵã�89
}

