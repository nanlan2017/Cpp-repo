#include "basics.h"
#include <string>

void test_basics()
{
	using R1 = IF<(2 + 3 < 4), int, std::string>::Ret;

 
	//�޷�ʹ�þֲ��������߶�̬������Ϊģ�����
	pointerT<ca>("Wendy"); //ָ��
 
	referenceT<cr>("Wendy"); //����
 
	fpointerT<global_f>("Caroline Wendy"); //����ָ��


}
