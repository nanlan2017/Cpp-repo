#include <utility>
#include <iostream>


/*
���������� T ת�����������ͣ����� decltype ���ʽ�в��ؾ������캯������ʹ�ó�Ա������

ͨ����ģ����ʹ�� declval ��ģ����ܵ�ģ��ʵ��ͨ�������޹��캯��������ͬһ��Ա�������������������͡�

ע�⣬��Ϊ�����ڶ� declval �Ķ��壬��ֻ�����ڲ���ֵ�ﾳ��
*/

struct Default { int foo() const { return 1; } };
 
struct NonDefault
{
	NonDefault(const NonDefault&) = default;
    int foo() const { return 1; }
};

using T0 = decltype(Default().foo());
//using T1 = decltype(NonDefault().foo());

//! �Ӷ�������ͳһ����ʽȥ��ȡ���г�Ա�����ͣ��ƹ���Ĺ��죨�����޷�Ĭ�Ϲ��죩��ֱ�ӷ������Ա���������ͣ�
using T2 = decltype(std::declval<Default>().foo());
using T3 = decltype(std::declval<NonDefault>().foo());
 