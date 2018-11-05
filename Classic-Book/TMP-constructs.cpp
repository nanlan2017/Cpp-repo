#include "prelude.h"

//! 0.  "type" has members, which can be type/int.    so , type 

//!  1. data struct 
// data Dog = Dog String Int
//todo       1.   ...F< People<age,Dog> ...   ��ģʽƥ�������ֵ
//todo       2.   people::age,  typename people::Dog  ����ȡ���ڲ���Աֵ
template<int _age,typename _Dog>
struct People
{
	enum { age =  _age };
	using Dog = _Dog;
};


//!  2. function
template<int x, typename Dog>
struct Calc
{
	enum { val = x + Dog::age };             //todo   ���õĶ��� <ģ�����>,   1. �����ֱ����Ϊ ��Ա���ݣ� ���� data struct   (Ҳ���ò���ģʽƥ�� ��������Աֵ)
											 //todo                          2. ������������Ǽ����һ��ֵ�� ���� function
											 //todo                          3. ����ֱ�ӷ�װ�ģ��ִ��м��㣬 ���� closure/ ��������
};

//!  3. closure  ,  function object
template<int _limit>
struct Judger
{
	enum { limit = _limit };

	template<int x>
	struct code
	{
		static const bool val = x < limit;
	};
};