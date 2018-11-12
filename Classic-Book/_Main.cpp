#include "_Exer_chap2.h"
#include "ch3_dimension.h"
#include "_Exer_chap3.h"
#include "ch8_dignostics.h"    //x ����include����/��main�������е��Ż����
#include "ch9_foreach.h"
#include "ch10_expression_template.h"
#include "ch11_dsl_radio.h"

//x---------------------------------------------------------------------------------------
using typevec = mpl::vector<int, long, char*>;
using typevec_ref = mpl::vector<int, long, char*, int&>;  // �����������ͣ��޷�����ֵ��ʼ����

void test_foreach()
{
	
	//  ����ģ�岻���������� ��Խ�����ڡ������ڵ��
	//mpl::for_each<typevec>(print_type());
	//mpl::for_each<typevec_ref>(print_type());  ����

	mpl::for_each<typevec_ref, wrap<mpl::_1>>(print_type());    //x ����һ�������ں�������ȻҪ��ֵ���ã�������ƾ�����ͣ��� ����for_each�Ὣ�����ͽ��С�Ĭ�ϳ�ʼ����

	// visitorģʽ
	mpl::for_each<typevec_ref, print_visitor<_>>(visit_type());
	//mpl::for_each<typevec_ref, print_visitor<_>>(f_visit_type);

}

void main99()
{
	ch10::test_exp_template();

	system("pause");
	
}

