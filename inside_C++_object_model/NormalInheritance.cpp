/**
	��ͨ�̳У�û��ʹ������ࣩ
*/

//! VSS2015 Command Prompt :     cl NormalInheritance.cpp /d1reportSingleClassLayoutD
//!                              cl NormalInheritance.cpp /d1reportSingleClassLayoutB

// ����A
class A
{
public:
	int dataA;
};
 
class B : public A
{
public:
	int dataB;
};
 
class C : public A
{
public:
	int dataC;
};
 
class D : public B, public C
{
public:
	int dataD;
};
