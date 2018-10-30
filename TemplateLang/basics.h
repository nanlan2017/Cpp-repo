#ifndef h_basics
#define h_basics
#include "prelude.h"
//! �����һ��ģ�������ԣ�����Haskell: û�пɱ������л����Ľṹ��
	// û�������ĺ����ˡ� ֻ�в��ɱ�ı���ʱ�������ʽ�������͡�
	//! ��template struct���ɺ������� ����>  �����ݾ��� ���͡����� (template params���ǲ�����
	//!                              ����>  ͨ���ػ�ʵ��ѡ��ṹ������IF)
	//!                              ����>  ͨ���ݹ�ʵ��ѭ��

/*
data TypesEnum = Int | Bool | ....
*/

/*
if :: bool -> TYE -> TYE -> TYE
if true x y = x
if _    x y = y

*/
template<bool cond, typename A, typename B>
struct IF
{
	using Ret = B;
};

template<typename A,typename B>
struct IF<true,A,B>
{
	using Ret = A;
};

//x -----------------------------------------------------------------

//ָ��
template<const char* C>
void pointerT(const char* str){
	std::cout << C << " " << str << std::endl;
}
 
//����
template<char (&ra)[9]>
void referenceT(const char* str){
	std::cout << ra << " " << str << std::endl;
}
 
char ca[] = "Caroline"; //��ʼ��ָ��
char cr[9] = "Caroline"; //��ʼ������, ����һ����β����
 
inline void global_f(const char* c) {std::cout << c << std::endl; }
 
//����ָ��
template<void (*F)(const char*)>
void fpointerT(const char* c) {
	F(c);
}

#endif

