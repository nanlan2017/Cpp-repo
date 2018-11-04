#include "prelude.h"
#include <cstdarg>

//! �ɱ����ģ��   ...(ʡ�Ժ�)
// �϶�Ҳ�ǰ�ʣ�µĲ��������һ������: &rest args�� �����ڲ�ʹ���������ʱ������ args,����  args...
// ...Args       ----->   Args...
template<typename T,typename ...Args>
void vfoo(const T& t, const Args&... args)
{
	//!   ...args           <----- [a,b,c]
	//!   Patter(args)...   -----> [Patter(a),Patter(b),Patter(c)]
	cout << sizeof...(Args) << endl;  //ģ������� ��0������
	cout << sizeof...(args) << endl;  //����������
}

/*     ͨ���ݹ鷽ʽ������һ���������ȵ��б�ģʽƥ�䵽headԪ�أ�
f :: os -> [T] -> a
f os [x]    = os << x
f os (x:xs) = os << x  ; f os xs ;
*/

//todo ģ��struct�ҿ�����⣨ģ��������������� ��ôģ�庯����ô��⣿
template<typename T>
ostream& print(ostream& os,const T& t)  //! ��Haskellһ���������ȶ���ݹ���ֹ���������
{
	return os << t;
}
template<typename T, typename...Args>
ostream& print(ostream& os, const T& t, const Args&... rest)
{
	//! ���ԶԴ�'rest'���б��������
	os << t << " ,";
	return print(os, rest...);
}


template<typename T>
void patf(const T& t){}

template<typename ...Args>
void vf(ostream& os,const Args&... rest)
{
	print(os, patf(rest)...);
	//-->     patf(a),patf(b),,,,
}

//! ���ת��
template<typename ...Args>
void fun(Args&&... rest)
{
	// ����Щ����ת����works����
	works(forward<Args>(rest)...);
}

//x---------------------------------------------------------------------------------------------------------------
//! �ɱ������
int sum(int count, ...)
{
	//! va = varadic arguments
	//! list, start, arg,end
	va_list ap;
	va_start(ap, count);

	int sum = 0;
	for (int i = 0; i < count; i++) {
		sum += va_arg(ap, int);   //�ڶ���������ʾ�β�����
	}
	
	va_end(ap);  //��������
 
	return sum;
}

//! initializer-list
int sum2(initializer_list<int> ilist)
{
	int sum = 0;
 
	for (int i : ilist) //�����������Ĳ���
	{
		sum += i;
	}
 
	return sum;
}

//! ...?
/*
int sum3(int i, int ... args)
{
	int sum = i;
	for (auto it : args) {
		sum += it;
	}
	return sum;
}
*/
//x---------------------------------------------------------------------
//! ���������ģ�壺�Ǹ���ϰ�ߣ�����
template<typename ...Elements>
struct _tuple;
/*
tuple :: [T] -> To (��������)
tuple (t:ts) = <t,>~(tuple ts)    // ~: add field to (tuple ts) by Inherit
tuple []     = <>
*/

//!  ����һ����������_tuple<###> �϶�Ҫд�ģ���
template<typename Head,typename ...Tail>                  //x ͨ���ݹ飬�ܹ���Argsչ��?
struct _tuple<Head,Tail...> :private _tuple<Tail...>             //�����  tuple<TLast> : tuple<>
{
	Head headval;
};

template<>
struct _tuple<>
{};

/*
tuple :: [Ts] -> T

tuple [T]    = T
tuple (T:Ts) = T : tuple Ts  //x �˴� Ts���Ϳ���Ϊ�գ����Ա߽����� ������ [] �� [x]
*/
//x----------------------------------------------------------------------
//!  ������Ϊ����ģ��Ԫ���ԡ���֧�� List �ṹ ����֧��ģʽƥ��ȥ�ݹ鴦��List) ��������>  ��Haskell�͸����ˡ�

//!        ��ģ��Ԫ���ԡ� �еı���ֻ���������ͣ�  
//!                         ����/�ڲ�ֵ�� Type(typename) ���� Integer  
//!          f(x,y,z)--> res  �Ķ�Ӧд��   template<Type a,Type y,Type c> struct F { res = ...}
template<int...nums>
struct Multiply;
//todo		Multiply :: [Int] -> Int
//todo		Multiply [] = 1
//todo		Multiply (x:xs) = x * (Multiply xs)
template<int n,int...restnums>
struct Multiply<n,restnums...>
{
	static const int val = n * Multiply<restnums...>::val;
};

template<>
struct Multiply<>
{
	static const int val = 1;
};
//x----------------------------------------------------------------------


void main_varadic()
{
	cout << sum(3, 1, 2, 3) <<endl;
	cout << sum(4, 1, 2, 3)<<endl;//x --����

	cout << sum2({ 1,2,3 })<<endl;
	cout << sum2({ 1,2,3,4,5 })<<endl;

	vfoo(3, "abc", 2,2);  //2��ģ��Σ�3��������
	vfoo(6.67, 'b', 5.4,7); //3��ģ��Σ�3��������

	_tuple<int, double, string> tup;

	auto r = Multiply<3, 4, 5>::val;

	system("pause");
}