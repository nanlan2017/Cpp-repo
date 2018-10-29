#ifndef h_hasptr
#define h_hasptr

#include "prelude.h"

// value-like : ����ָ�����������Դ
/*
���ö���ָ������⣺ �ڲ���ָ����ȫ�ǲ��ɼ��ġ�
*/
class HasPtrV
{
private:
	int i;
	string* ps;
public:
	// Ĭ�Ϲ���
	HasPtrV(const string& s = string()):i(0),ps(new string(s)){}


	// ��ֵ������ ��������ֵ
	HasPtrV(const HasPtrV& rhs): i(rhs.i),ps(new string(*rhs.ps)){}
	/*-----------------------------------------
	      // ��������Ҹ�ֵ   a = a;
	HasPtrV& operator =(const HasPtrV& rhs)
	{
		i = rhs.i;
		// ��ʱ��Ҫ�ͷű���ֵ�����ԭ����Դ����(���������ȿ����Ҳ��  --->  ��ֵ= ���ͷ���� + �����Ҳ�
		auto newp = new string(*rhs.ps);
		delete ps;
		ps = newp;
		return *this;
	}
	*/
	HasPtrV& operator =(HasPtrV rhs)  // ��ֵ = ���� + �ͷ�ԭ
	{
		swap(*this, rhs);
		return *this;
	}
	//----------------------------------------
	// ����
	~HasPtrV() { delete ps; }

	//?  һ�� value-like �ġ�ͨ��ָ�������Դ���࣬ �����Ż��������� swap  
	//?    (����ϵͳ��swap�� 1�ο���+ 2�θ�ֵ��������value-like Holder�ᵼ����ԴҲ���п�����
	//? ��������> ��ĳ�������ṩ���Ż��汾��swapʱ���ϼ����swapҪȷ�����ô˳�Ա���Ż���swap��������ϵͳĬ�ϰ�dumb-swap
	friend void swap(HasPtrV&, HasPtrV&) noexcept;

};

inline
void swap(HasPtrV& l, HasPtrV& r) noexcept //? noexcept? (�쳣��ȫ��= �����쳣/ִ����;�ϵ� ���ܱ�֤ ״̬����
{
	std::swap(l.ps, r.ps);
	std::swap(l.i, r.i);
}
/*****************************************************************************************************************
******************************************************************************************************************
******************************************************************************************************************
******************************************************************************************************************/
// ���������ﲻ���ͷ���Դ�������һ��user�����ͷ��Ǹ�ָ�����Դ��
//�~�~�~�~�~�~�~�~�~�~ �����ṩһ���ӿ��� ��ִ�� delete ps ;  �����޷������� �����һ��user ��զ�ͷ� �Ǹ���Դ����
// ����������������>  �~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~�~ shared_ptr ��Ӧ�ó������� ���������Դ����  Ҳ���� pointer-like���������Դ��Ա ʹ�� shared_ptr ����õģ�
class HasPtrP
{
private:
	int i;
	string* ps;
public:
	// Ĭ�Ϲ���
	HasPtrP(const string& s = string()) :i(0), ps(new string(s)) {}

	/*
	// ��ֵ������ ��������ֵ
	HasPtrP(const HasPtrP& rhs) = default;
	HasPtrP& operator =(const HasPtrP& rhs) = default;
	// ����
	~HasPtrP() = default;
	*/

	//?  �ṩ�����һ�������� ���ͷŽӿ�
	void free_resoure() const { delete ps; }
};

/******************************************************************************************************************/
class RefCounter
{
public:
	unsigned cnt = 0;

	explicit RefCounter(const int i):cnt(i){}
	RefCounter& operator ++() { ++cnt;  return *this; }
};

class HasPtrCt
{
	// �Զ�����һ�� ����������¼��object����Դ���� �Ĺ�����
private:
	int i;
	string* ps;
	RefCounter* pcounter;   // �� ps ��Դ�� �����߸��� ��Ӧ
public:
	// Ĭ�Ϲ���
	HasPtrCt(const string& s = string())
		:i(0)
		,ps(new string(s))
		,pcounter(new RefCounter(1)){}
	// 
	HasPtrCt(const HasPtrCt& rhs)
		:i(rhs.i)
		,ps(rhs.ps)
		,pcounter(rhs.pcounter)
	{ ++(*pcounter); }

	HasPtrCt& operator =(const HasPtrCt& rhs)
	{
		i = rhs.i;

		// �ּ��ұ���Դ�������� �� �ټ������Դ�������� + update �����Դ
		++(*rhs.pcounter);
		pcounter->cnt -= 1;
		if (pcounter->cnt == 0) {
			delete pcounter;
			delete ps;
		}

		ps = rhs.ps;
		pcounter = rhs.pcounter;
		return *this;
	}

	~HasPtrCt()
	{
		// ֻ���Լ������һ��Userʱ���ͷ�
		if (pcounter->cnt == 1) {
			delete pcounter;
			delete ps;
		}		
	}
};

#endif

