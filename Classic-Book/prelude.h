#ifndef H_PRELUD
#define H_PRELUD

#include <string>
#include <iostream>

#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <memory>

#include <functional>
#include <type_traits>
//x=============================================================================================
#define static_const static const
#define static_constexpr static constexpr

#define PRINT(expression)  std::cout << expression << std::endl;

//?  c++�ĺ� ��lisp �����Ķ���  û��������ֵ����   ,  ,@ 

#define Print_Type(obj)                                           \
{                                                                 \
	PRINT(1)                                                      \
	PRINT(2)                                                      \
	std::cout << typeid(obj).name() << std::endl;                 \
	PRINT(3)                                                      \
}
#endif

