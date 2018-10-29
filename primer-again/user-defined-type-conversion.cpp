#include "prelude.h"

class SmallInt
{
public:
	SmallInt(int i = 0)
	{
		if (i > 255) {
			throw out_of_range("too big!");
		}
		val = i;
	}

	// ������ int ��ת��
	//operator int() const
	//{
	//	return val;
	//}

	//?  C++ 11 �Ľ��� ��ʽ������ת��
	explicit operator int() const
	{
		return val;
	}

private:
	int val;
};

void test_333()
{
	//?  һ��ֻ����һ������ת����  x   --->   �Զ��������ת�����Ը��� ϵͳ�ṩ����ʽ����ת��֮��
	SmallInt si = 3.14;

	static_cast<int>(si) + 3;  //? ת��������ܿ�������
}