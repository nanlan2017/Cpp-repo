#include "prelude.h"

void by_new()
{
	string* pstr_arr = new string[10]{ "first","second" };
	// pstr_arr ��Ȼ��ָ��һ��string�� �϶��� ��ͨ�ĵ��� pointer ��Щ��ͬ ����֪���Լ�����һ����̬���飩

	delete[] pstr_arr;

	//------------------------ new + unique_ptr
	unique_ptr<string[]> uptr(new string[10]{ "first","second" });
	cout << uptr[1];
	uptr.release();

	//------------------------ new + shared_ptr
	shared_ptr<string> sptr(new string[10]{ "first","second" },
		                      [](string* ptr) {delete[] ptr; });   // �����ṩ ������deletor ������ delete[]
///*
	// ����
	for (size_t i = 0; i < 10; i++) {
		cout << *(sptr.get() + i);
	}
	auto v0 = *sptr; // "first" // ���ֵú͵���Ԫ��һ��
	sptr.reset(); // �ͷŸö�̬����
//*/

}

void by_lib_allocator()
{
	//?          ����׼���ṩ�ġ���̬���顰 API��
	// allocate  ->  construct  -> destory() ->  de-allocate() 
	//  ����             ����         ����             ����

	// allocator<T>  a;
	// a.allocate(����);
	// a.construct( T* ptr_position, &args)
	// a.destory(T* ptr_position)
	// a.de-allocate(T* ptr_position, ����)  // ������allocate�� λ�á����� �Ǻϣ�


	//-------------------------------  ��䶯̬���� ������һ����construct)
	// un-initialized -~~
	//                copy (Դbegin,Դend, T* ptr_postion)
	//				 copy_n (Դbegin,����, T* ptr_postion)

	//				 fill (Ŀ��_begin, Ŀ��_end,  object)  // ��Ϊobject����
	//				 fill_n ��Ŀ��_begin, ����,  object)  // ��Ϊobject����

}

void main_dynamic()
{
	by_new();
	by_lib_allocator();

	string s = "love";
	addressof(s);
}