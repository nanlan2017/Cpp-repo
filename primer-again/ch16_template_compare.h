#ifndef h_ch16_1
#define h_ch16_1

#include "prelude.h"

template<typename T>
int compare(const T& v1, const T& v2)  
{
	/*
	if (v1 > v2) return 1;     //? T��֧��> �����
	else return -1;
	
	//?  �������İ汾�� ʹ�ñ�׼���ṩ�ĺ�������less<T>  :: ����T�����ͣ��Զ�ѡ����ʵıȽ������
	if (less<T>(v1, v2)) return 1;
	else return -1;
	*/
	return 0;
}


template<typename Ty, typename F = less<Ty>>   // ����Ҳ�Ǳ����� F������ͱ�����Ĭ��ֵ���� less<Ty>
int comp(const Ty& v1, const Ty& v2, F f = F()) // ������Ĭ��ֵ�� ��ѡ�ĵ�3����������������
{
	if (f(v1, v2)) return 1;
	else return -1;
}


template<unsigned M, unsigned N>
int compare(const char(&s1)[M], const char(&s2)[N])
{
	return strcmp(s1, s2);
}


//? �౾����ģ�壬���и���Ա������ģ��  ����>�~�~�~�~  ����ģ��  ʹ��ʱû���κ��ر������Ͳ�������ʵ���Զ��ƶ���
//?                                   ����>�~�~�~�~  ��ʱ����ģ������ͱ��������������� �����б��ϣ� ��ʱ��Ҫ ��Class һ����ʽָ��
class DebugDelete
{
public:
	DebugDelete(ostream& os = cerr):os(os){}

	template<typename T>
	void operator ()(T* ptr) const
	{
		os << "deleting unique_ptr" << endl;
		delete ptr;
	}

private:
	ostream& os;
};

inline void use_case()
{
	unique_ptr<int, DebugDelete> uptr(new int(), DebugDelete());
	uptr.release();  // ����� DebugDelete::operater()<int>(int*)
}

/*
template<typename T>
T fobj(T, T);       // ������õ�ʵ���� const�ģ���T ��Ȼ����const

template<typename T>
T fref(const T&, const T&);

inline void use_f()
{
	int a[10], b[20], c[10];
	fobj(a, b);   // T = int*  (������ת��Ϊָ�룩
	//fref(a, b);   // �޷��Ƶ���T 
	//fref(a, c);   // ��ʹά����ͬҲ����  
}
*/
//? ���ʹ�� decltype,  remove_ref ::  ���ص�������ָ���Ԫ�صĿ�����
template<typename It>
auto fcn(It beg, It end) -> typename remove_reference<decltype(*beg)>::type
{
	return *beg;
}
/****************************************************************************/
/*
//?        �~�~�~�~�~�~�~�~�Ϳ���������û�а취 �� ���õ�ʵ�� ����
template<typename T>
void g1(T);      //?  object����������const ���У�(��������const,���ײ�const)  ����>  const int * const pt;   ���βλ��ʼ���õ�  const int*  p; 
template<typename T>
void g2(const T&);   //?  ��ֵ��   const ��ֵ
template<typename T>
void g3(T&&)    //?  ��ֵ�� ��const��ֵ
{
	vector<T> vec;
}
	
template<typename T>
void g2(T&);     //?  ֻ�ܽ�����ֵ�����ұ�Ȼ�ƶ�Ϊ ��ֵ����

inline void test_fold()
{
	int i = 0;                // int  l-value + non-const
	const int ci = 0;         // int  l-value + const

	g1(i);
	g1(ci);
	g1(3);

	g2(i);
	g2(ci);
	g2(3);

	g3(i);
	g3(ci);
	g3(3);
}
*/
// �����������r
template<typename T>
auto _move(T&& obj) -> typename remove_reference<T>::type&&
{
	return static_cast<typename remove_reference<T>::type&&>(obj);
}

inline void use_move()
{
	int i = 3;
	static_cast<int&&>(i);    // move(i)  ----> ������һ�� rvalue object , Ȼ�����÷���

	/*  ��ֵ
	int&&  move(int&& i) {
		return static_cast<int&&>(i);  ==  return i;
	}

	    ��ֵ        ------------- ֻҪ����ֵ��������& ���ţ��Ͳ���� return �� obj ���п��� 
				   -------------  return �ı�Ȼ��һ��obj����--��������"����"�� ֻ���� rvalue/ lvalue�� object
								------------- ����ʹ��һ�� "���á� ʱ�� ��ȫ�൱��  ��ʹ���Ǹ������õ�object
	int&&  move(int& i) {
		return static_cast<int&&>(i);
	}
	*/
}
#endif

