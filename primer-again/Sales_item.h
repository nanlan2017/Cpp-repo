#ifndef h_Sales_item
#define h_Sales_item

#include "prelude.h"

/*
�����Ͳ����� ���޲ι�������

*/
struct Dog
{
public:
	Dog() = default;
	Dog(const int& age): myage(age){}

private:
	string name;
	int myage;
	string* ptr_in_dog;
};

							// �~�~�~�~�~  ��ʼ�����ɻ󶼽���ˡ�������ȫ����˳�ʼ�� �����Ϊ��
struct Sales_item  // ��Ȼits_dog�޷�֧��Ĭ�ϳ�ʼ��(�޷��ṩĬ��ֵ) ---> ��ôSales_dataҲ���޷��ṩĬ��ֵ�ˣ�
				   // --->  �������������� ���������� �� undefined ! (ֻ�ᱨ��   ----->  int i; ���ԣ�    Dog dog; ����
                   // --->  T()=default;  ����Ĭ�ϵ��޲ι�������ˣ�  // T() = 0 ��ɾ���������ṩ��Ĭ�������
{
	string bookNo;                // ���������͡�δָ����ʼֵ�� ��Ա��  Ĭ�ϳ�ʼ��ȡ�����Ƿ��С��޲ι������� ����������У�
	unsigned units_sold = 0;      //�~�~�~�~�~ ����ָ�� ��ʼֵ�Ļ��� ��������Ϊ Ĭ�ϳ�ʼ��<�ֲ�> == undefined (�����г�ʼ��)---��Ȼ������ָ�루�����Զ���Ϊnullptr)
	double revenue;

	Dog its_dog;                 // �۲�һ���������޲ι������� ��Ա���� ����Ρ�Ĭ�ϳ�ʼ������ 
};

struct Sales_data
{
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
public:
	Sales_data() = default;
	Sales_data(const string s):bookNo(s) {}
	Sales_data(const string s, const unsigned sold, const double p) : bookNo(s),units_sold(sold),revenue(sold*p){}

	const Sales_data& show() const   // const��Ա��������this������뷵��const &
	{
		return *this;
	}

	friend struct hash<Sales_data>;
};

#endif

