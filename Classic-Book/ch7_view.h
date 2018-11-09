#ifndef h_ch7_view
#define h_ch7_view

#include "prelude.h"
#include "prelude_boost.h"

using namespace mpl;
// Seq�ǰ�sizeof �ź��������
// ����Seq�е�һ��size >= min_size ��Ԫ�ص�size
template<typename Seq, typename min_size>
struct padded_size
										//   \x y -> (sizeof x) < y           (y == min_size)
	: sizeof_<typename deref<typename lower_bound<Seq,min_size,  less<sizeof_<_1>, _2>>::type>::type >     //! ȱ�㣺˼·���ᣬ�������ˣ�����ʵ��ֻ��size���У�
{};

template<typename Seq, typename min_size>
struct _padded_size
	: deref<typename lower_bound<typename transform<Seq, sizeof_<_>>::type     //! ȱ�㣺 Ԥ�ȶ�����Ԫ�ض�Ӧ���� sizeof ���㣬 ���ǲ���Ҫ��
								 , min_size>::type>::type
{ };

template<typename Seq, typename min_size>
struct ___padded_size
	: deref<typename lower_bound<typename transform_view<Seq, sizeof_<_>>::type     //! OK! (sequence view�Ƕ�����ֵ��)
								 , min_size>::type>::type
{ };

inline void test_ch7_view()
{
	using vec = vector<bool, char, short, int, long, float, double>;
	using padded_vec = padded_size<vec, mpl::size_t<5>>::type;
	using padded_vec2 = _padded_size<vec, mpl::size_t<5>>::type;
	using padded_vec3 = ___padded_size<vec, mpl::size_t<5>>::type;


	using vec1 = vector_c<int, 1, 2>;
	using vec2 = vector_c<int, 9, 10>;
	using vec3 = vector_c<int, 50, 51>;
	// ��3��vec��Ԫ�����
	// map (\x y z -> x + y + z) (zip vec1 vec2 vec3)
	using res = transform_view < zip_view<vector<vec1, vec2, vec3>>
		, plus<at<_, int_<0>>
		, at<_, int_<1>>
		, at<_, int_<2>> >>;
	using res2 = transform_view < zip_view<vector<vec1, vec2, vec3>>
		, unpack_args<plus<_,_,_>> >;
}

#endif

