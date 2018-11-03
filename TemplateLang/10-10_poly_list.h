#ifndef h_polylist
#define h_polylist

#include "10-10_cons_list.h"
//! ��cons�ĵ�һ����������Ϊһ�����ͣ�����int����һ�������ǿ��԰�һ��int��Ա�ģ����һ�������һ��Wrapper���� typenameȡ��int)


/*
���� Java����԰� int/double װ��Ϊ ������һ����
//todo ͨ���� int/bool ֵ��װ�� TypesEnum�͵� һ���������Ϳ���ͳһ�� typename���������� ����ֵ���� T::val ��)

*/
//! 
template<int n>
struct Int
{
	enum { val = n};
};

struct _End      // ��Ϊ���� Type�� ���ݵĽ��
{
	using Head = Int<endValue>;
	using Tail = _End;
};

template<typename _Head, typename _Tail = _End>  //����Ƕ���б��ˡ�������> ��
struct _Cons
{
	using Head = _Head;
	using Tail = _Tail;
};
//x=======================================================================================  ������ (int)
struct BTEnd
{
	enum { val = endValue};
	using Left = BTEnd;
	using Right = BTEnd;
};

template<int _val, typename _Left = BTEnd,typename _Right = BTEnd>
struct BTNode
{
	enum { val = _val };
	using Left = _Left;
	using Right = _Right;
};
//x====================================================================================
#endif
