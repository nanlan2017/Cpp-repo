#include "prelude.h"


/* --------------------------------------------------------------------------------------------------
���ڲ���(Policy)��������ǽ�templates�Ͷ��ؼ̳�����������������Բ���������еġ����Ԫ�ء���
Policies��templates�Ͷ��ؼ̳���ɡ�
һ��class���ʹ����policies,�ͳ���Ϊhost class,����һ��ӵ�ж��template������class template,ÿһ����������һ��policy.
host class���еĻ��ܶ�����policies,��������������һ���ۺ�������policies��������
----------------------------------------------------------------------------------------------------*/
template <
	class RunPolicy,
	class FlyPolicy
>
class Bird : public RunPolicy, public FlyPolicy       
{
};

/*
class BirdOO : public IRunnable, public IFlyable
{
};
*/

struct Dog
{
	int age = 0;
	std::string name;
};

//!   һ��Policy�������һ���ӿڣ�utilҵ������),  ����ӿڵ�ʵ�ֶ���policy class
/*
����һ��ploicy ������������,
Creator policy��һ�������ͱ�ΪT��class template,�������ṩһ����ΪCreate()�ĺ��������ʹ�ã�
�˺��������ܲ���������һ��ָ��T��ָ�롣
���������ֲ�������ķ�����policy
*/
//TODO     Ϊ Creator Policy ����3�� Policy Class
//Policy 1:  new T
template<class T>
struct OpNewCreator
{
	static T * Create()
	{
		return new T;
	}
};

//Policy 2:  malloc -> placement new
template<class T>
struct MallocCreator
{
	static T * Create()
	{
		void* buf = std::malloc(sizeof(T));
		if (!buf)  return 0;
		return new(buf) T;
	}
};

//Policy 3:  
template<class T>
struct PrototypeCreator
{
	PrototypeCreator(T* pObj = nullptr)
		:pPrototype_(pObj){}

	T * Create(){return pPrototype_ ? pPrototype_->Clone() : 0;}

	T *GetPrototype() { return pPrototype_; }
	void setPrototype(T* pObj) { pPrototype_ = pObj; }

private:
	T * pPrototype_;
};

//test_creator
void main()
{
	Dog* dog1 = OpNewCreator<Dog>::Create();
	Dog* dog2 = MallocCreator<Dog>::Create();
	Dog* dog3 = PrototypeCreator<Dog>(dog2).Create();
}


//TODO    ͨ���̳�/���, ������� ����A ӵ������B ��ҵ������������CreateT����  �����������ĸ�����һ���Ե�
//TODO    ��� CreateT�������� ���ṩʵ���ɶ��֣� B1, B2, B3,    
//TODO                     �~�~�~�~�~�~�~�~�~�~�~�~[���������һ������Creator Component �������滻�� Creator���࣬ ����ô��]
//TODO                     ��ô�� ������Ҫ  �ֱ��� A1, A2, A3  ���̳����ǣ����ܸ��ϳ���Ҫ�����͡�
//TODO        �~�~�~�~�~�~�~�~��������Ҫ�̳У������������� ������ (��Ϊģ������Ͳ���) (��������ģ�廯)��  ---------> ����ʹ��������װ����Ķ࣬ �� A<B1>, A<B2>, A<B3> ���ɣ�
//TODO        һ�仰�� ͨ�����͵Ĳ������������͵Ĺ��������
/*
���һ���������һ������policy class,�ͳ���Ϊhost��host classes.���涨���WidgetManager������һ��policy,����Ϊhost class.Hosts��Ҫ��������涨���policies�Ľṹ����Ϊ���һ���縴�ӵĽṹ����Ϊ��
*/
struct Widget
{ };

struct Gadget
{};

template<class CreationPolicy>
class WidgetManager:public CreationPolicy
{
public:
	using CreationPolicy = CreationPolicy;
};


template<template<class> class CreationPolicy>
class WidgetMan:public CreationPolicy<Widget>   // ������֪WidgetMan���Ǵ���Widgetʵ��
{
public:
	using CreationPolicy = CreationPolicy<Widget>;
};



void test_host()
{
	// ���1 �� ������ �߱� Widget���͵� new create ����
	using MyWidgetPtr = WidgetManager<OpNewCreator<Widget>> ;
	auto* w = MyWidgetPtr::CreationPolicy::Create();

	// ���2 �� 
	using MyWidgetPtr2 = WidgetManager<MallocCreator<Widget>> ;
	auto* w2 = MyWidgetPtr2::CreationPolicy::Create();


	using MyWigetMan = WidgetMan<OpNewCreator>;
	auto* w3 = MyWigetMan::CreationPolicy::Create();
}

//x===========================================================================================================

//!  ��policy class������ģ�壬 ��host������Ϊtypename����
//!  ��policy class�������ģ�����ͣ� ��host��Ҫ������Ϊ template template
template<template<class> class CreationPolicy = OpNewCreator>
class WidgetManager :public CreationPolicy<Widget>
{
	void DoSomething()
	{
		Gadget *pW = CreationPolicy<Gadget>::Create();
	}

	void SwitchPrototype(Widget *pNewPrototype)
	{
		CreationPolicy<Widget> &myPolicy = *this;
		delete myPolicy.GetPrototype();
		myPolicy.SetPrototype(pNewPrototype);
	}

};