#ifndef h_ch1_3
#define h_ch1_3
#include "prelude.h"

template<typename T>
const T& max_elem(const T* lis, unsigned const size)
{
	const T* max_val(lis);
	for (unsigned i = 1; i < size; ++i) {
		if (lis[i] > *max_val) { max_val = &(lis[i]);  };
	}
	return *max_val;
}


//?  Ctrl+H  :  �滻T �� �ػ�������   <�������� �߼�δ�䣬�����ػ��� �����ʵ����������ӡ�
/*
template<> inline
const int& max_elem(const int* lis, unsigned const size)
{
	const int* max_val(lis);
	for (unsigned i = 1; i < size; ++i) {
		if (lis[i] > *max_val) { max_val = &(lis[i]);  };
	}
	return *max_val; 
}
*/

//? Haskell
/*
max :: (Ord a) => [a] -> a
max [x] = x
max (x:xs) = let omax = max xs in if x > omax then x else omax
*/

//x===========================================================================================================*/
template<typename T0,
         typename T1,
         typename T2,
         typename T3,
         typename T4>
T2 func(T1 v1, T3 v3, T4 v4)  //? ���T1�� T3��T4 һ���Ļ����Ǿ���ͬһ�������� ������static��������ͬһ����
{
    T0 static sv0 = T0(0);
    T2 static sv2 = T2(0);

    std::cout << "\tv1: " << v1
              << "\tv3: " << v3
              << "\tv4: " << v4
              << "\t|| sv0: " << sv0;
    T2 v2 = sv2;

    sv0 -= 1;
    sv2 -= 1;

    return v2;
}

inline void use_Fuc() {

    double sv2 = func<double, int, int>(1, 2, 3);  // d i i i i
    cout << "\tsv2: " << sv2 << endl;              

    sv2 = func<double, int, int>(1, 2, 3);         // d i i i i 
    cout << "\tsv2: " << sv2 << endl;                        // ��ʵ������   int      f  (int, int ,int)

	sv2 = func<double, int, double>(1, 2, 3);      //?* i * i i   
    cout << "\tsv2: " << sv2 << endl;                        //todo ��ʵ������   double   f  (int, int, int)  .. �����������������ء����ֲ���ͬһ��������
	                                                         //todo  �Ṳ�������ڵ�static�����𣿣�
	                                                         //?  ģ��ʵ���������ľͲ��������ˣ�ֻҪģ���������һ�������ǲ�ͬ�ĺ�����

    sv2 = func<double, int, int>(1, 0.1, 0.1);     // d i i d d
    cout << "\tsv2: " << sv2 << endl;

    sv2 = func<int, double, double>(0.1, 0.1, 0.1);// i d d d d 
    cout << "\tsv2: " << sv2 << endl;
}


#endif

