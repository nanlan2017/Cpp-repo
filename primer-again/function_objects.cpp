#include "prelude.h"
#include <functional>

//? ��������һ�� ����
int add(int x, int y) { return x + y; }

//? ����������� ������()������Ķ���
struct divide
{
	int operator ()(int x, int y) { return x / y; }
};

void test_ittt()
{
	//? ������������ lambda
	// lambda ��������� ��ɶ��
	auto mod = [](int x, int y) {return x % y; };
	cout << typeid(mod).name() << endl;



	map<string, int(*)(int, int)>  binops;          //x ---->   ���Ƕ��ɳ�Ϊͬһ�����ͣ�  function<int (int,int)>
	binops.insert({ "+", add });  // ���Դ���
	 
	//?     ָ���Ա������ָ��  ��ĳ��object�� ?)
	//int (*pt)(int, int);



	map<string, function<int(int, int)>> ops = {
		{"+", add},
		{"-", std::minus<int>()},
		{"/", divide()},
		{"*", [](int i,int j) {return i*j; }},
		{"%", mod}
	};

	cout << ops["+"](3, 4) << endl;
	PRINT(ops["*"](3, 4));
}

void main_fun()
{
	test_ittt();
}


//int& ret()
//{
//	return 3;
//}