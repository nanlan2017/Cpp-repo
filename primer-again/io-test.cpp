#include "prelude.h"
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>

// 9.2.4 
// ���õ�array  vs  ��׼��array����
void use_array()
{
	// ���õ�array  --- ����C�ģ��������Ͷ��󡣡�

	// ��׼��array<ElemType,SIZE> --- ���ͻ��ˣ���api
}

void use_lambda();
void main_io()
{
	// ��List<int> ��ʼ��һ�� Vector<Double>
	list<int> ilst(10, 99);
	vector<double> dvec(ilst.begin(), ilst.end());

	use_lambda();	
}

bool check_size(const string& str, const string::size_type size)
{
	return str.size() >= size;
}

// ��Primer�� - 10.3 ��
void use_lambda()
{
	//  () -> {return 3;}
	auto f1 = []() ->int {return 3;  };
	cout << f1();

	int ilocal = 9;
	string slocal = "like";
	auto f2 = [ilocal, slocal](const int x) -> int {return ilocal + x; };


	// 
	vector<string> words = { "i","like","it" };
	// for_each
	for_each(words.begin(), words.end(), [](string& wd)-> auto { cout << wd; });



	// find_if
	string::size_type limit_size = 4;
	auto r1 = find_if(words.begin(), words.end(),
		             [&limit_size](const string& wd)-> bool {return wd.size() >= limit_size; });
	// ʹ����ͨ���� + bind  // �~�~�~�~�~�~�~�~�~�~ �ⲻ������� ���ﻯ������  ��������Ĳ��ֵ��ã���
	auto check_size_bounded = bind(check_size, placeholders::_1 , limit_size);  // ռλ����1��ʼ�ƣ�
	auto check_size_bounded_ref = bind(check_size, placeholders::_1 , ref(limit_size)); 
	// test
	bool res1 = check_size_bounded("love"); // true
	limit_size = 5;   //�~�~�~�~�~�~�~  ��ref���� ������bind�ˣ��Ӷ��ﵽlambda�������
	bool res2 = check_size_bounded("love"); // true (check_size_bounded��Ȼ�󶨵ڶ�������ֵΪ4����
	bool res3 = check_size_bounded_ref("love"); // false 

	auto r3 = find_if(words.begin(), words.end(),
		              bind(check_size, placeholders::_1, 4));


	//
	int dat = 10;
	auto xf1 = [dat]()mutable {return ++dat; };
	auto xf2 = [&dat]()-> auto {return ++dat; };
	auto xf3 = [=]() mutable {return ++dat; };
	auto xf4 = [&]() {return ++dat; };
}

// inserter iterator
// stream iterator
//
void other_iterators()
{
	list<int> lst = { 1,2,3,4 };
	list<int> lst2, lst3;

	// ͷ�ļ��� <iterator>
	auto front_inserter = std::front_inserter(lst2);

}