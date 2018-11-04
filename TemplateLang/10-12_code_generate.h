#ifndef h_code_Generate
#define h_code_Generate

#include "prelude.h"
#include "10-5_Factorial.h"
#include "haskell_utils.h"

//x==================================================================================================
namespace book {
//todo �������г��ֵ� pow<3>(x) չ��Ϊ x*x*x    -----> �Ż��˺������õĿ���
template<int n>
//inline 
int power(const int& x){ return x * power<n - 1>(x);}
template<>
inline int power<1>(const int& x) { return x; }
template<>
inline int power<0>(const int& x) { return 1; }

inline void test_mypower()
{
	// 2^5
	auto r = power<5>(2);   //----> inline�ģ� �ȼ�����д  auto r = 2*2*2*2*2;
}
//x=========================================== edo ==================================================
/*
int i = 1;
ewhile 	(i<10) 
	statement(i);        // statement ::  print(i);
	i++;

===>
	print(1);
	print(2);
	....
	print(9);
*/


/*   //todo    Common Lisp
(defmacro ewhile (	
*/
//x=========================================== ewhile ===============================================
//todo ÿ�εݹ鶼�� statement(i), ���ж��Խ�����һ�εݹ�
template <int i = 1>
struct Print_Body
{
	enum { i = i };
	static void exec() { cout << i << endl; }       //! body: ��װ��body����
	using Next = Print_Body<i + 1>;
};

template<int n>
struct Print_Cond
{
	template<typename Body>
	struct judge
	{
		static const bool  val = Body::i < n;        //! condition
	};
};
//x======================================================================================================

/*
//todo   data Body = Body Int Statement Body
Ewhile 	:: (Body->bool) -> Body -> ..
Ewhile conder (Body i stats nextbody) = if (conder i) then Ewhile conder nextbody else ..
*/

struct Stop { static void exec() { cout << "stopped..." << endl; } };       //!  �~�~�~�~��� Stop ֵ����� ����Ҫ�� 

template <typename Conder
		,typename Body>
struct Ewhile
{
private:
	static const bool flag = Conder::template judge<Body>::val;
public:
	static void exec()  //! ����������ͨ��inline������������ʵ�ֵģ�
	{
		/*
		if (flag) {
			body::exec();
			Ewhile<cond,nextbody>;
		} else {
			stop::exec();
		}
		*/
		//IF<flag, Body, Stop>::Ret::exec();        // ���ж�ִ�б��εݹ���
		//IF<flag, Ewhile<Conder, typename Body::Next>, Stop>::Ret::exec();  // ������һ�εݹ�
		IF < flag
			, Sequence<Body, Ewhile<Conder, typename Body::Next>>
			, Stop>::Ret::exec();
	}

	template<typename Env>
	static void exec_env(Env&& env)
	{
		IF < flag
			, Sequence<Body, Ewhile<Conder, typename Body::Next>>
			, Stop>::Ret::exec(forward<Env>(env));
	}
};

inline void test_ewhile()
{
	Ewhile< Print_Cond<10>, Print_Body<>>::exec();
}
//x=========================================== efor =================================================

}
#endif
