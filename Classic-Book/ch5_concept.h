#ifndef h_ch5_concept
#define h_ch5_concept

#include "prelude.h"
#include "prelude_boost.h"

inline void test_ch5_iterator_concept()
{
	//  std::vector<int> ivec = { 2,5,7,9,11 };
	using types_seq = mpl::vector<int, long, double, short, char>;  //! ~ void_, unknown, unknown ...
	//  auto ipos = std::find(ivec.begin(),ivec.end(), 7);
	using iter1 = mpl::find<types_seq, long>::type;

	//! <iterator.hpp>--> v_iter
	using t0 = iter1::type; // long (deref)
	using t1 = iter1::pos;
	using t3 = iter1::category;  //todo    ��iterator�������ǣ� ������ʵ�����

	//  vec.end()
	using end1 = mpl::end<types_seq>::type;  //! iter-type ::  v_iter<seq, index>
	//  *iter;
	using elem1 = mpl::deref<iter1>::type;  // long
	// iter++,  iter--
	using iter2 = mpl::next<iter1>::type;
	//using iter2b = iter1::next::type; // iter����û��next��Ա
	using iter3 = mpl::prior<iter1>::type;

	// ��β
	using iter4 = mpl::find<types_seq, char>::type;
	using iter5 = mpl::next<iter4>::type;
	using iter6 = mpl::next<iter5>::type;  // nextֻ�Ǽ򵥵İ� index+1
	using wrong = mpl::deref<iter5>::type;  // end : void_
	using wrong2 = mpl::deref<iter6>::type;  // >end: unknown

	//x ������ʵ�����
	//x  ��ͬ�ĵ�������ǰ��˫������� ֻ����Ϊ�������еĹ�����ʽ��һ������Ҫ�ǹ������ݡ������㷨��
	//x  ������ģ��϶�Ҫ vector + ĳ��element��index
	//x   --------- ǰ��  next ֱ����Ϊ��Ա
	//x   ----------���
	using t2 = mpl::advance<iter1, mpl::int_<3>>::type;  //! advance n = idx + n
	using dis1 = mpl::distance<iter1, iter4>::type;      //! long_<3>  // 


}


inline void test_ch5_sequence_concept()
{
	// ǰ�����У�  begin ,end, front
	// ˫�����У�  begin ,end, front ,back
	// ������У�  at<Seq,n>

}


inline void test_ch5_()
{
	//!   �~�~�~�~���� vector_c ���������Ϊ vector<integral_c<int>...> һ��
	//!    �~�~�~�~Seq<> ������󾭳���ת��Ϊ SeqN<> 
	using vec = mpl::vector<int, double>;
	using vec2 = mpl::pop_back<vec>::type;  //!  vector1<int>,  ��������ͨ��vector!
	auto r  = boost::is_same< vec2, mpl::vector<int>>::value;  // false !
	auto r2 = mpl::equal<vec2, mpl::vector<int> >::value;   // true
}

//x============================================================================================================================
struct none{};

template<typename T0 = none, typename T1 = none,typename T2 = none>
struct tiny
{
	using type = tiny;  //! �~�~�~�~�~�~�~�~������ɺ���Ҫ������һ���ڲ���type��������
	using t0 = T0;
	using t1 = T1;
	using t2 = T2;
};

template<typename Tiny>
struct manipulate_tiny
{
	using t0 = typename Tiny::t0;
	using t1 = typename Tiny::t1;
	using t2 = typename Tiny::t2;

};

//! ��д�������
//todo    ��ͬmpl::v_iter
template<typename Tiny, typename Pos>
struct tiny_iter
{
	using category = mpl::random_access_iterator_tag;
};

//! next, prior support
namespace boost { namespace mpl {

template<typename Tiny,typename Pos>
struct next<tiny_iter<Tiny,Pos>>
{
	using type = tiny_iter<Tiny, typename next<Pos>::type>;
};

template<typename Tiny,typename Pos>
struct prior<tiny_iter<Tiny,Pos>>
{
	using type = tiny_iter<Tiny, typename prior<Pos>::type>;
};

} }
//! at
template<typename Tiny, int n>
struct tiny_at;

template<typename Tiny>
struct tiny_at<Tiny,0>
{
	using type = typename Tiny::t0;
};
template<typename Tiny>
struct tiny_at<Tiny,1>
{
	using type = typename Tiny::t1;
};
template<typename Tiny>
struct tiny_at<Tiny,2>
{
	using type = typename Tiny::t2;
};

struct tiny_tag{};

namespace boost { namespace mpl {
	
//x  ��ʽһ���ṩat���ػ�
/*
template<typename T0,typename T1,typename T2,typename Pos>
struct at<tiny<T0,T1,T2>,Pos>
	: tiny_at<tiny<T0, T1, T2>, Pos::value>    // ע�⣬Ҫ���tiny�ػ�����ҪӰ����������
{ };
*/

//x  ��ʽ�������mpl����at�Ĺ���ģʽ���ӵײ����

} }


#endif

