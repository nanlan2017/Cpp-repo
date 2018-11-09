#ifndef h_ch9_dispatching
#define h_ch9_dispatching

#include "prelude.h"
#include "prelude_boost.h"

// dc<T>(x) һ��ȼ��� static_cast, ����T �ǣ��ȼ���dy_cast

// ��һ����������tag��true,false) �ػ�
template<typename TargetType, typename U>
TargetType impl(U& x, mpl::true_)  // true:��Ӧ���ַ�����������
{
	return dynamic_cast<TargetType>(x);
}
template<typename TargetType, typename U>
TargetType impl(U& x, mpl::false_)  // true:��Ӧ���ַ�����������
{
	return static_cast<TargetType>(x);
}

template<typename TargetType, typename U>
TargetType dispatcher(U& x)
{
	return impl<x, typename boost::is_polymorphic<U>::type>();
}


template<typename TargetType, typename U>
TargetType desperate_cast(U& x)
{
	return dispatcher<TargetType>(x);   //x TargetType һֱ��Ϊ������ģ������ڴ��� ����Ȼ�ں����ڲ�ֱ�����һ����������������
}

#endif
