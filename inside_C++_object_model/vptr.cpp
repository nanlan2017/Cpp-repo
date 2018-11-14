#include "prelude.h"
using namespace std;
class Base
{
public:

	Base(int i) :baseI(i) {};

	virtual void print(void) { cout << ".......Base::print()"; }

	virtual void setI() { cout << ".......Base::setI()"; }

	virtual ~Base() {}

private:
	int baseI;
};

//test_vptr
void main()
{
	//TODO  ����vptr��ȡ�麯����Ȼ����麯�����л�ȡ��һ���麯�� ���е��á�
	Base b(1000);

	//�麯��ָ��һ�㶼���ڶ����ڴ沼�ֵĵ�һ��λ���ϣ�����Ϊ�˱�֤�ڶ��̳л���ؼ̳е�������������Ч��ȡ���麯����
	//��vprtλ�ڶ����ڴ���ǰ��ʱ������ĵ�ַ��Ϊ�麯��ָ���ַ��
	int * vptr = (int *)(&b);

	cout << "vptr is : \t" << vptr << endl;

	typedef void(*Fun)();
	Fun vf1 = (Fun)*((int *)*vptr);

	cout << "First virtual function at: " << (int *)*(int*)(&b) << endl;
	vf1();

	system("pause");
}