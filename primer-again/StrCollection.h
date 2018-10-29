#ifndef h_strcollection
#define h_strcollection

#include "prelude.h"
#include <memory>

class StrBlobPtr;
class StrBlob
{
public:
	friend class StrBlobPtr;

	using size_type = vector<string>::size_type;

	StrBlob() { data = make_shared<vector<string>>(); }
	StrBlob(initializer_list<string> il) { data = make_shared<vector<string>>(il); }

	// const 
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// 
	void push_back(const string& str) { data->push_back(str); }
	void pop_back() { data->pop_back(); }
	// 
	//string& front() { return data->front(); }
	//? todo  �������ʹ����忼�ǣ��ò��ü�const�أ�
	string& front() const { return data->front(); }  // ���ﲢ���Ƿ��� *this���� ���Է������ò�Ҫ�� const T&
	//string& back() { return data->back(); }
	string& back() const { return data->back(); }

	StrBlobPtr begin();
	StrBlobPtr end();
private:
	shared_ptr<vector<string>> data;
	void check(size_type index, const string& msg) const;
};

inline void StrBlob::check(const size_type index, const string& msg) const
{
	if (index >= data->size() ) {
		throw out_of_range(msg);
	}
}

class StrBlobPtr
{
public:
	StrBlobPtr(): curr(0){}
	StrBlobPtr(/*const*/ StrBlob& blob, size_t sz=0): wptr(blob.data), curr(sz) {}

	string& operator *() const  // vector�����const �Ժ� ���е�item��const�� �Ƿ������
	{
		// ͨ�� weak_ptrȥ���ʹ����Ķ����޷�ʹ�� *�����ã�
		// ��checkһ���Ƿ�expired�� ��ͨ��lock()��� shared_ptr ȥ����
		auto sp = check(curr);
		return (*sp)[curr];
	}

	// ����һ���µ� x 
	StrBlobPtr& operator ++()
	{
		curr++;
		return *this;
	}


private:
	// ��û�й���StrBlob�������ǹ��� vector<string>
	weak_ptr<vector<string>> wptr;
	std::size_t curr;  // string/vector��size_type , ���������� size_t

	shared_ptr<vector<string>> check(size_t index) const
	{
		auto ret = wptr.lock();  // ��δexpired���򷵻�һ��shared_ptr�� ���򷵻� empty��shared_ptr (��ת��Ϊfalse)
		if(!ret) throw runtime_error("already expired");
		if (index >= ret->size()) throw out_of_range("not that many!");
		return ret;
	}
};

inline StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}




#endif

