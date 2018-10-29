#ifndef h_oop
#define h_oop
#include "prelude.h"
class Quote
{
public:
	Quote() = default;
	Quote(const string& book,double sales_price)
		:bookNo(book),price(sales_price){ }

	virtual ~Quote() = default;
	/*-----------------------------------------------*/
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const
	{
		return n*price;
	}
protected:
	double price = 0.0;
private:
	string bookNo;

};

class BulkQuote :public Quote   //? public: ���������� �� �̳ж����ĳ�Ա �Ƿ�� ��������û��ɼ�
{
public:
	BulkQuote() = default;
	BulkQuote(const string& book, double price, size_t qty, double disc)
		:Quote(book, price), min_qty(qty), discount(disc) { }

	/*-------------------------------------------------*/
	double net_price(size_t n) const override
	{
		if (n>= min_qty) {
			return n*(1 - discount)*price;
		}else {
			return n*price;
		}
	}
private:
	size_t min_qty = 0;  // �����Ż����ߵ���͹�����
	double discount = 0.0;  // �ۿ�
};

#endif // h_oop