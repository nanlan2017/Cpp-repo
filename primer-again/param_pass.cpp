#include "prelude.h"

void f_1(int* pint){}

void call()
{
	int i = 3;
	const int j = 4;

	f_1(&i);
	//f_1(&j);  //  int* pint = &j ;   // ERROR! ������const T* ȥ����const����
	// const ���ÿ��԰� const��������ֵ��...
	// ���ԣ� ����õ� ���� const�����ˣ� 

}



/*
 initilizer_list<T>  ��ʵ���� List<T> ���� �͸� ���Դ�����һ��������
��������>  ò��û�� lisp�е� &rest ���Ͼ��˼��Ƕ�̬���͵ģ�
*/
// const T& ���԰� ����ֵ�����ȿ�����Ϊ lvalue���á�Ҳ������Ϊ��ֵ���ã�
void error_handler(const int& count, const initializer_list<string>& il)
{
	cout << count;
	for(auto &str : il) {
		cout << str;
	}
}

vector<string> get_strs()
{
	return { "fuck","it" };  // {} �б�����ֵ�����Զ����� vector����ֵ  
}

void call_error_handler()
{
	error_handler(5, { "it","is","wrong" });

	vector<string> backed_strs = get_strs();
}

// ���к������ɸ�дΪ�� ��β�÷�������-��� trailing return type  ��ʽ // ���������ͽϸ���ʱ
auto f_2(int i) -> int
{
	return 1;
}

auto f_3(int i) -> int (*)[10]
{
	return nullptr;
}

//int(*foo(int))[10];  // ����е��ԣ��ܲ�ֵ�ۣ�

void call_f()
{
	using Type_int10Arr = int[10];
	Type_int10Arr* (*pt)(int) = nullptr;   // ����һ��ָ��
	pt = f_3;

	decltype(f_3) *p2 = f_3;

}

/////////////////////// Ϊconst �ṩconst���   /////////////////////////////////////////////////
const string& shorter(const string& s1, const string& s2)  // const �汾
{
	return (s1 < s2) ? s1 : s2;
}

// �����ض��������ʱ����һ�䣺�ö������ٺ������ڴ����İɣ���
string& shorter(string& s1, string& s2)                // ����const�汾 ʵ�ַ�const�汾
{
	auto &r = shorter(const_cast<const string&>(s1), const_cast<const string&>(s2));
	// r :: const string&
	return const_cast<string&>(r);
}

void f_callit()
{
	const string cstr1 = "love";
	const string cstr2 = "like";

	string str3 = "fuck";
	string str4 = "fun";

	shorter(cstr1, cstr2);     // ƥ�� shorter:: const string& -> const string& ===> const string&
	shorter(str3, str4);       // ƥ�� shorter:: string& -> string& ===> string&

	//void ppp(int);   // ������һ��ppp����
	//ppp(3);      // ����ʱ�ŷ���û��ʵ�֣�����
}
