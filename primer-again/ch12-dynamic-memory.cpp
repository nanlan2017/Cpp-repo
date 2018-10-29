#include "prelude.h"

#include <memory>

void test_shared()
{
	shared_ptr<int> sp1 = make_shared<int>();

	int* sp1_raw = sp1.get();
	bool is_sp1_unique = sp1.unique();
	long sp1_count = sp1.use_count();

	cout << *sp1;

	//-------------------------------
	string s1 = "make it";
	auto ps2 = new auto(s1);

	//------------------------------- placement new (����λnew����
	int* p2 = new (nothrow) int; // ����ʧ�ܣ��᷵��һ����ָ�루����bad_alloc�쳣��

	//------------------------------- ����д��
	if (!sp1.unique()) {
		sp1.reset(new int(100));
	}
	++(*sp1);
}


void test_delete()
{
	int local_i = 3;
	int *p1 = &local_i;
	int *p2 = nullptr;

	//delete local_i;
	//delete p1;  // �~�~�~�~�~�~��Ϊδ���壡�����ͷ� ջ�ϵĶ��� (ֱ�ӳ����쳣��������
	delete p2;  // �ͷ�nullptr ����û��ģ�����ûɶ�ã�

	double *heap_d = new double(3.3);
	auto pd1 = heap_d;
	delete heap_d;  //�~�~�~�~�~�~ delete��ָ��ֵ�����𣿣���--->  heap_d ��ָ��ֵ�����ˣ���
	heap_d = nullptr; // ������ᱣ�������������Ϊnullptr�Ǹ���ϰ�ߣ�
	delete pd1; // �~�~�~�~�~�~δ���壡 �ö����ڴ��Ѿ��ͷš����գ�

}

void test_share_ptr()
{
	shared_ptr<string> sp1;  // ��empty"
	sp1 = make_shared<string>("fuck");
	sp1 = nullptr;  // �յ�shared_ptr
}

void test_unique()
{
	unique_ptr<string> p1(new string("sterotype"));
	unique_ptr<string> p2(p1.release());  // releaseֻ���ͷš�unique����Ȩ����ͬʱ����up��Ϊnullptr)�� �������ͷ�Ŀ�����
	unique_ptr<string> p3(new string("Tex"));
	p3.reset(p2.release());  // ��Tex�����ͷţ� 'sterotype'��p3�ӹܡ�  p2Ϊnull-unique-pointer
	//p3 = move(p2);
}

void main_ch12()
{
	//test_shared();
	//test_delete();
	//test_unique();
	test_share_ptr();


	system("pause");
}