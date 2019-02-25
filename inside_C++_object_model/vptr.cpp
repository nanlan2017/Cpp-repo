#include "prelude.h"
//#include <concepts>
using namespace std;
class Base
{
public:

	Base(int i) :baseI(i) {};

	int getI() const { return baseI; }

	static void countI() {}

	virtual void print(void) { cout << ".......Base::print()"; }

	virtual void setI() { cout << ".......Base::setI()"; }

	virtual ~Base() {}

private:
	int baseI;

	static int baseS;
};

void testBase(Base& p)
{
	//RTTICompleteObjectLocator str = *((RTTICompleteObjectLocator*)*((int*)*(int*)(&p) - 1));

	//x����static�����ĵ�ַ
    p.countI();//�ȵ��ú����Բ���һ��ʵ��
    cout << "static����countI()�ĵ�ַ��" << p.countI << endl;
 
    //x��֤nonstatic���ݳ�Ա
    cout << "�Ʋ�nonstatic���ݳ�ԱbaseI�ĵ�ַ��" << (int *)(&p) + 1 << endl;
    cout << "�����Ʋ���ĵ�ַ������õ�ַ��ֵ��" << *((int *)(&p) + 1) << endl;
    cout << "Base::getI():" << p.getI() << endl;
}


//!  ��ֻ��  non-static�ĳ�Ա���� + virtual �ĳ�Ա����
class Derive : public Base
{
public:
    Derive(int d) :Base(1000),      DeriveI(d){};

    //overwrite�����麯��
    virtual void print(){ cout << "Drive::Drive_print()" ; }

    // Derive�������µ��麯��
    virtual void Drive_print(){ cout << "Drive::Drive_print()" ; }
    virtual ~Derive(){}
private:
    int DeriveI;
};

class Base_2
{
public:
    Base_2(int i) :base2I(i){};

    virtual ~Base_2(){}

    int getI(){ return base2I; }

    static void countI(){};

    virtual void print(void){ cout << "Base_2::print()"; }
 
private:
 
    int base2I;
 
    static int base2S;
};
 
class Drive_multyBase :public Base, public Base_2
{
public:

    Drive_multyBase(int d) :Base(1000), Base_2(2000) ,Drive_multyBaseI(d){};
 
    virtual void print(void){ cout << "Drive_multyBase::print" ; }
 
    virtual void Drive_print(){ cout << "Drive_multyBase::Drive_print" ; }
 
private:
    int Drive_multyBaseI;
};

//test_vptr
void main()
{
	//TODO  ����vptr��ȡ�麯����Ȼ����麯�����л�ȡ��һ���麯�� ���е��á�
	Base b(1000);

	/*
	int* vptr;
	int  baseI;
	*/

	//�麯��ָ��һ�㶼���ڶ����ڴ沼�ֵĵ�һ��λ���ϣ�����Ϊ�˱�֤�ڶ��̳л���ؼ̳е�������������Ч��ȡ���麯����
	//��vprtλ�ڶ����ڴ���ǰ��ʱ������ĵ�ַ��Ϊ�麯��ָ���ַ��
	int * ptr_vptr = (int *)(&b);

	cout << "vptr is : \t" << ptr_vptr << endl;

	typedef void(*Fun)();
	Fun vf1 = (Fun)*((int *)*ptr_vptr);

	cout << "First virtual function at: " << (int *)*(int*)(&b) << endl;
	vf1();

	system("pause");
}