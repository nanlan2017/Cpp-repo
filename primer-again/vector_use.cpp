#include "prelude.h"
#include <cassert>

void use_vector()
{
	vector<string> svec{ "i","love","you" };

	vector<int> ivec(10);  // vector����Ϊ���壺 ��ָ����ʼֵʱ������Ĭ�ϳ�ʼ�����������Ͳ��� Ĭ��<0>, ����Ĭ��<undefined> )
}


void pointer_operator()
{
	int i = 1, j = 3;
	int *p1 = &i, *p2 = &j;
	if(p1 < p2) {  // ����Ŀ�겻��ͬһ�����󣬱ȽϺ�������
		//
	}

	char* p3 = "hello";
	//if (p1 < p3) {}  // �����������Ͳ�ͬ�� �����ڸ�  (<) :: int* -> char*

}


void rvalue_test()
{
	int i = 3;
	int* p = &i;

	// *p �õ��� lvalue :: int  --->  �~�~�~�~�~�~�~decltype(lvalue T)  == T&
	decltype(*p) k = i;  // int& k = i;
	// &p �õ��� rvalue :: int** ---> �~�~�~�~�~�~�~decltype(rvalue T)  == T
	decltype(&p) m = &p;
}


// ��ʵ���ĸ����� ����ģ�塣   ģ������Ͳ���Ϊת����Ŀ������
void type_cast()
{
	// static_cast  (����ȥ�� const���ʣ�
	int i = 2, j = 3;
	double v1 = static_cast<double>(i);

	// const_cast  ��Ψһ������ ����const���ʣ�
	char c = 'L';
	const char c2 = 'I';
	const char* pc = &c;
	const char* pcc = &c2;
	char *p2 = const_cast<char*>(pc);
	char *p22 = const_cast<char*>(pcc);   // �����Ǹ� c2 ������const�� ��ʵ�������ǿ��ڴ� ��c2 ���name����Ϊ const!
	*p2 = 'M';
	//*pc = "N"; //EROOR
	*p22 = 'A';

	// reinterpret_cast
	int* ip = &i;
	char* pc2 = reinterpret_cast<char*>(ip);  //  int* ---> char*  ����һ��char* pc2 ָ��

	// dynamic_cast
	// ? ���� ����ָ��<--> ����ָ�� ��ת����
}

void iterate_seq()
{
	vector<int> ivec = { 1,2,3 };
	for(auto &ele : ivec) {    // ������õ� ivec�д�ŵ� object����
		ele = ele * 2;
	}
	for (auto e :ivec) {    // �������壬�����Ѿ��� object�����˿���
		e = e * 2;     
	}
}

void test_goto()
{
	assert(false);
}

// ������д����һ���ģ� pf ����ָ��
//void has_function_param(bool pf(int));
//void has_function_param2(bool(*pf)(int));


// �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
string global_str = "hi,lily";
string& ret_ref()
{
	return global_str;
}

void call_ret_ref()
{
	string& r1 = ret_ref();  // �ȼ���  string& r1 = global_str;    ����ʱ���ѱ���name r1 �󶨵����ص���������� ����������=== ���ض�����-���Ǹ�����
		// ��ʱ�����õ������ʹ���ĸ�object����
	string r2 = ret_ref();   // �ȼ���  string r2 = global_str;   ��Ȼ���ǿ����ˣ�
	ret_ref() = "hi,jack";   // �ȼ���  global_str = "hi,jack";  
}

