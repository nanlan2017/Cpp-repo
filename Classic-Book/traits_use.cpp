#include <type_traits>
using namespace std;

//x=========================================================================================
//! type categorization

template<typename T>
void use_traits_category()
{
	// void?  pointer?  reference?  array?  enum?  union?
	// integral?  float?  class?
	auto r1 = is_void<T>::value;

	//! R(C::*)(args...)  cv   ,   D C::*
	// ָ���Ա��ָ�� ��ʵ�ϲ�����pointer, ����һ�� offset(ƫ����)
	auto r2 = is_member_pointer<T>::value;


	//! R(args...)
	auto r3 = is_function<T>::value;

	/*---------------------------------------------*/
	// fundamental?  ��������
	// compound?     ��������
	// scalar?        
	// object?
}