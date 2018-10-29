#ifndef h_spec
#define h_spec

#include "prelude.h"
#include "Sales_item.h"
namespace std {
	template<>   //?  template<> ˵������ĳ��ģ�����ȫ�ػ��汾�� T === Sales_data
	struct hash<Sales_data>
	{
		using result_type = size_t;
		using argument_type = Sales_data;

		// ����Sale_data��ÿһ������ ���ô˺�������  �����һ��Ψһ��hashֵ
		size_t operator()(const Sales_data& s) const
		{
			return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
		}
	};
}

inline void use_hash()
{
	
}
//?  ֻ����ģ����� �������������� ��ƫ�ػ�����    ����ģ��ֻ����ȫ�ػ�����

#endif

