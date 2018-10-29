#include "prelude.h"

class Foo
{
public:
	Foo& operator =(const Foo&) &;      // ֻ�ᵱ��౻��ֵ������ l-value object


	Foo  somefun() const &;

	//? ���س�Ա������ ���� �������ӿ�����Ե� object�� ��/��ֵ ���ʲ�ͬ
	//?    reference qualifier
	Foo sorted() &&
	{
		// ����ֱ������ԭ��Ԫ�أ����ؿ���
		sort(data.begin(), data.end());
		return *this;
	}
	Foo sorted() const &
	{
		/*
		// ����  a.sorted() :  ����a �õ�b  -->  ����b  --> ����b�Ŀ���
		Foo ret(*this);
		sort(ret.data.begin(), ret.data.end());
		return ret;
		*/
		return Foo(*this).sorted();  // ����a �õ� tmp-b --> ����b ����������õ� --> �ٴο���
	}
private:
	vector<int> data;
};