#include "prelude.h"
#include <regex>

void test_reg()
{
	// i ������c֮�󣬷��������c֮ǰ
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex reg(pattern);  //? ����һ��regex����

	string test_str = "receipt friend theif receive";

	smatch results; //? ���ڱ���match�Ľ��

	if (regex_search(test_str, results, reg))
		cout << results.str() << endl;



}