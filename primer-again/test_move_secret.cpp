#include "prelude.h"

/*
		//  �ƶ�����
		auto dest = newdata;    //?  ��Ȼ�����ڴ治�� ��һ��� ����  ����ôͨ�� move ���⿽�������ܡ���һ�顱���أ�
									//? <Primer>-P469 : �ͺ������objʵ�岢�����κ�vec�У���vec��ֻ�� ��ֵ���塱��obj��ָ����ѡ�---> ����ֻҪ��ָ�뿽����ȥ�����ˣ���ͬswap)
		auto old_ele = elements;
		for( size_t i = 0; i < size(); ++i) {
			alloc.construct(dest++, std::move(*old_ele++));        //  string(string&&  r_obj)
		}
*/

void test_move()
{
	/*
	û�з�����������ô s2 �ĵ�ַ�����𣿣�
	*/
	// ͨ����move��obj�ĵ�ַ���й۲�
	string s1 = string("i'm lily");
	cout << &s1 << endl;

	string s2;
	cout << &s2 << endl;

	s2 = std::move(s1);      //? s1 ��Ϊ"" ,  s2�߱���s1��ֵ��
	//cout << &s1 << endl;  // error !
	cout << &s2 << endl; //? ��ַû�䣡

}

void main_move()
{
	test_move();
}