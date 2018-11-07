#ifndef h_exer_chap4
#define h_exer_chap4
#include "prelude_boost.h"
#include "prelude.h"


//x========================================================================================================

namespace wjh {
	

template<typename T>
struct is_data_member_pointer
{
	// �ǳ�Աָ��  &  ��Ŀ�������ݳ�Ա �����ǳ�Ա������
	using type = typename mpl::and_<boost::is_member_pointer<T>
		, mpl::not_<boost::is_function<T>>>::type;
};
}
#endif

