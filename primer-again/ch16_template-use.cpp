#include "ch16_template_compare.h"

void use()
{
	//? compair<int>  ������庯����ʵ��������
	auto r = compare(3, 5);
	auto r2 = compare<double>(2.3, 1);  // ����ָ��`����ģ��`ʵ���������Ͳ�������
}

void type_manipulation()
{
	using Ty1 = remove_reference<int&>::type;  // int

}


void main_t()
{
	use();
}