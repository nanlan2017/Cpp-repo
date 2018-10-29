#ifndef h_mystack
#define h_mystack
#include <stdexcept>
#include "prelude.h"
//? ��������ʵ�ֵ�ջ�ṹ
template<typename T>
struct MyStack;

template<typename T = int>
struct Node   //? ����ÿһ������ʱ����Ҫ��ϸ��������ʵ�֣�ֵ���壿�������壿�Ƿ��ṩ�ƶ�������Щ���췽ʽ��������������
{
private:
	T val;
	Node* next = nullptr;
public:
	//! constructors
	/*
	Node(4); Node("li");
	Node(4,nod);
	*/
	//explicit Node(const T& val):val(val){}
private:
	//! �~�~�~�~�~�����ֵ���ݣ���ζ���㷽�������������ʱ�������Ѿ������õ��ģ�
	//!     �����ô��ݣ�����Խ��������������ں����ڲ������Ƿ񿽱�
	//! �~�~�~�~�~�~�~�~�~�~�~�~ ����������Ϊ, ȡ����������� �������ϵ����費��Ҫ ����/ֱ�Ӳ��� ��Ϊ�������������
	Node(const T& val, Node* next_node):val(val),next(next_node){}   // ��ָ�룬�Ϳ��Դ�nullptr�ˣ�  
																	 //! shared_ptr ֻ������Դ���ʵĶ�������������Ϊ��Ա����������Ϊ�������ݣ�
	//! self-base
	//������һ��object������������һ��object��ֵ
	//todo   [C#|Java ����C++�����ʵ��]
	//todo  ��Java�У�һ��object instance ֻ�ᱻ�����������ô��ݡ�         
	//todo   ����>  1. obj1 = obj2��           ������obj1Ҳ����obj2�Ķ���   
	//todo   ����>  2. T obj1 = new T(obj2);   ��һ��û�����ֹ��캯����
	//todo   ����>  3. intance�Ŀ�������ʽ����clone();
	//todo   ����>  4. ����object�������ڶ��ϣ������Զ�GC����������ʱ��������ָ������⡣
	Node(const Node& node) = default;  //! �������� ����Ȼ�ǿ�������Ȼ���ں��ṩ��ԭ����rvalue/ lvalue�ˡ� ������const T&��
	//! const

	//! modifiers

	//! others
	friend MyStack<T>;  //todo private����+friend : �൱���ڲ����ˣ�ֻ��friend class����ʹ����)
};

template<typename T = int>
struct MyStack
{
public:
	using NodeType = Node<T>;

	//! constructors
	MyStack() = default;                   //? Ĭ�Ϲ��� MyStack() ʱ,stack��Ӧ��û���κ�node!  (��ôhead��Ȼ�Ͳ�����T��ʽ����
	MyStack(const T& val):head(new NodeType(val)){}
	MyStack(const NodeType& node):head(new NodeType(node)){}
	//! semantics
	// �ö��󲻿��Ը��ơ�Ҳ�����Ը�ֵ
	MyStack(const MyStack& obj) = delete;
	MyStack operator=(const MyStack& obj) = delete;
	~MyStack()
	{
		while (!empty()) {
			pop();
		}
	}
	//! const
	bool empty() const { return head == nullptr; }
	const T& top() const noexcept(false)
	{
		if (empty()) throw std::runtime_error("no node to get top");
		else return head->val;
	}
	//! modifier
	void push(const T& v)  //! push���Ǳ�Ȼ��Ҫ�����ģ���ֻҪ����һ�Σ����Ͼ���stack��ֵ����ġ�
	{
		head = new NodeType(v, head);
	}

	void pop();
	//! other

private:
	NodeType* head = nullptr;
};
template <typename T>
void MyStack<T>::pop()
{
	if (head) {
		NodeType* tmp = head;
		head = head->next;
		delete tmp;
	} else {
		throw new std::runtime_error("no elements to pop");
	}
}

template<typename T>
class CountStack:MyStack<T>
{
	using Base = MyStack<T>;
private:
	unsigned size;
public:
	//!cons
	CountStack():Base(),size(0){}
	//!const
	unsigned get_size() const
	{
		return size;
	}
	//!modifiers
	void push(const T& val)
	{
		Base::push(val);
		++size;
	}
	void pop()
	{
		if (size >0) {
			Base::pop();
			--size;
		}
	}
};

template<typename TV, typename TN>
struct SNode
{
	TV val;
	TN* next;
	//!cons
	SNode(const TV& v,TN* next):val(v),next(next){}
};

inline
void test_snode()
{
	// ����  3 -> 'c' -> "love"
	//      no3   no2      no1
	auto no1 = SNode<string, void>("love", nullptr);
	auto no2 = SNode<char, decltype(no1)>('c', &no1);
	auto no3 = SNode<int, decltype(no2)>(3, &no2);
}



#endif



