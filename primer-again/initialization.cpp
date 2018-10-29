#include "iostream"
using namespace std;

void e_list_initialization()
{
	// ���ֻ���д��
	int i1 = 3;
	int i2(3);

	// List Initilization
	int i3 = { 3 };
	int i4{ 3 };
}


int f_target(double* p_d)
{
	return 1;
}

/*
�~�~�~�~�~�~�~ �������ʱδָ����ʼֵ�� ���������Ĭ�ϳ�ʼ����   ---> ��Ĭ��ֵ"

	�������ͣ�������ָ�룡��
		1. ȫ��������  --->  0  ( int global_x; �൱��--->  int global_x = 0; )
		2. �ֲ�����    --->  ������ʼ������undefined)  --->  ���� ֻ�оֲ����������Ϳ��ܳ���undefined !������ָ�룩 --->  rawֵ���ڴ�ԭʼ0101)
    Class���ͣ�
		 Dog dog;  ---> �������޲ι��캯�������޲ι�����г�ʼ�� 
                         ���������޲ι������Ļ�������д�� �������ᱨ����)
*/
void e_default_initialization()
{
	//int i = { 3.14 }; // ERROR!
	//double x1 = x2 = 9999.99;
	int i2 = 3.14;

	int x = 3;
	int* px = &x;
	int& rx = x;
	int*& rpx = px;  // ����������һ��ָ�����

	int(*pf)(double*) = &f_target;  // ����һ��  FUNCTION :: double* -> int ���͵�ָ����� pf
	int(*pf2)(double*) = f_target;  // ָ����ʱ������ʡ�� & ȡ��ַ
	double y = 3.14;
	(*pf)(&y);
}


// ��������=������definition = creation)  vs   ��������


void const_compound()
{
	const int x = 3;
	int y = 9;

	//int& rx = x;   //ERROR !                  ����һ������ʱ������ʹ�� const T ������
	const int &crx = x;

	const int &cry = y;  // ���� ������ const int�� & ������һ�� ��const ����
	//cry = 7;   //ERROR !                     �� ��ô����cryʱ �ö������Ϊֻ���� ����ԭ����yʱ ���Ƿ�const;
	y = 7;

	//int* px = &x;   //ERROR !                ָ��һ������ʱ������ʹ�� const T ��ָ��
	const int *cpx = &x;  // cpx :: const int <- *
	cpx = &y;             // ���� ��Ȼ���Ի�ָ��  int <- *    (��ʵ���� int* ��ֵ���� const int* ����
	//*cpx = 4;  // ERROR !                      cpx����ָ��Ķ������һ��const���Σ�

	/////////////////////////////////////////////////////////
	/*
	�ܽ᣺ ����һ�� const ����ֻ��ʹ�� const & �� const * ������
	      ������һ�� mutable ���� �Կ���ʹ�� const & cr �� const * cp������ ���� cr , *cp ���ʸö���ʱ����Ϊ const ) 

	==>  ͸�� & �� * ������һ������ʱ�����ܶ������һ�� const ��
	*/


	//////////////////////////////////////////////////////////
	// ===>   ˵���ˣ�pointer�е����⣬ ��������һ�����һ�� �������������ֵ Ϊ const /mutable ����
	// ===>                            �����Զ� ���������Ķ��� ����һ�㱣�� ����ʹ�ô�ָ�����ʱ��
	// int y = 9;  const int* pt = &y ;   ������ڴ��y��˵��mutable�ģ��� *pt��˵�� const�ġ�
	//////////////////////////////////////////////////////////

	int m = 1;
	// �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~
	// ������д����һ���� ��const д�� * ǰ�棩  ---��  ��� const ���ֳ�Ϊ  low-level const  (ֻ�� ָ��/���� �ſ��ܳ��� low-level const) 
	// const int& r = m ;    "�����������õ�const ���� �ײ�const"(���ñ����Ƕ��󣬲����ڶ���const)
	int const * p1 = &m;
	const int * p2 = &m;
	// ������ָ�뱾���ǳ��� (const д�� * ���棩 ---��  ��� const ���ֳ�Ϊ  top-level const
	int * const p3 = &m;
}


void auto_infer()
{
	int i = 0, &r = i;
	auto a = r;   // a :: int

	const int ci = 1, &cr = ci;   // cr �ǵײ�const (���õ�const���ǵײ�const)
	auto b = ci; // b :: int  === auto����Զ���� const���ԣ� ���ᱣ�� �ײ��const����

	
	auto d = &ci;
	auto e = &cr;
}


























