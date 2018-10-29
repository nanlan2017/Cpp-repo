#ifndef h_strvec
#define h_strvec
#include "prelude.h"

/*
�Լ�ʵ��һ��vector �� ������ֻ��װstring����
���� ���ö�̬�������������洢��strings
*/
class StrVec        // ֵ����  ��������>  ��ʵ��ָ�� һ�鶯̬����� ָ��
{
public:
	// ��ʵ����Ĭ�ϳ�ʼ������ִ�й��캯����
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
	// ���巨��
	StrVec(const StrVec& rhs)
	{
		/*
		// �Ȼ���ͬ������ڴ棬Ȼ����Ҳ�����Ԫ�ؿ�������
		auto head = alloc.allocate(rhs.capacity());
		elements = head;
		first_free = uninitialized_copy(rhs.begin(), rhs.end(), head);
		cap = elements + rhs.capacity();
		*/
		auto newdata = this->alloc_and_copy(rhs.begin(), rhs.end());
		elements = newdata.first;
		cap = first_free = newdata.second;
	}
	StrVec& operator =(const StrVec& rhs)
	{
		/*
		// �ȿ����Ҳ�ģ����ͷ����ġ��ٹ���
		//? newvec ���٣����ᱻ���ͷţ�  ���Եð� newvec ������ ���ϣ�
		StrVec* newvec = new StrVec(rhs); // �� StrVec newvec(rhs); ��һ���ģ����ǿ�������
		free();
		elements = newvec->begin();
		first_free = newvec->end();
		cap = elements + newvec->capacity();
		return *this;
		*/
		auto data = alloc_and_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		cap = first_free = data.second;
		return *this;
	}

	StrVec(StrVec&& tmp_obj) noexcept
	: elements(tmp_obj.elements), first_free(tmp_obj.first_free), cap(tmp_obj.cap)
	{
		tmp_obj.elements = tmp_obj.first_free = tmp_obj.cap = nullptr;   // ��ʱ����Ҫ�������ģ��˴����ⱻ����
	}

	StrVec& operator =(StrVec&& robj) noexcept
	{
		if (this == &robj) return *this;  //? dying ��obj �����Ը�ֵ�𣿿��� ��   s = move(s);   // s �� ��ֵ����

		free();
		elements = robj.elements;
		first_free = robj.first_free;
		cap = robj.cap;
		robj.elements = robj.first_free = robj.cap = nullptr;
		return *this;
	}

	~StrVec() { free(); }
	/*--------------------------------------------*/
	// ���Ԫ�أ� ��ȷ��������������first_free construct һ��
	void push_back(const string& s)
	{
		check_alloc();
		alloc.construct(first_free++, s);
	}


	// Reader
	size_t capacity() const { return cap - elements; }
	size_t size() const { return first_free - elements; }
	// getter
	string* begin() const { return elements; }
	string* end() const { return first_free; }

private:
	string* elements;
	string* first_free;
	string* cap;
	static allocator<string> alloc;  // ���ʵ��ѹ��������/�����κ�object�� ���Կ���һ��ȫ�ֵģ����� cout һ���� ����ʵ�塣


	// ��������ĸı䣬 �Ϳ���4������
	// ����>  pushԪ��ʱ�� check  --> ������������� ���·��䡢copy�� ��push
	void check_alloc() { if (first_free == cap) re_allocate(); }

	void re_allocate()       // ����������ʱ���������»����ڴ棬����ԭ����Ԫ�ؿ�����ȥ
	{
		//?  ������� ԭ�е��Ǹ���û��Ҫ���������ͷţ� Ӧ�� move "�ӹ�"
		//?     move : ��һ�� lvalue-object ���һ�� rvalue-object ���Ӷ�����ƥ�� T&& /const T& �����ԡ����ӹܡ�
		auto new_capacity = size() ? 2 * size() : 1;
		auto newdata = alloc.allocate(new_capacity);

		/*
		//  �ƶ�����
		auto dest = newdata;    //?  ��Ȼ�����ڴ治�� ��һ��� ����  ����ôͨ�� move ���⿽�������ܡ���һ�顱���أ�
									//? <Primer>-P469 : �ͺ������objʵ�岢�����κ�vec�У���vec��ֻ�� ��ֵ���塱��obj��ָ����ѡ�---> ����ֻҪ��ָ�뿽����ȥ�����ˣ���ͬswap)
		auto old_ele = elements;
		for( size_t i = 0; i < size(); ++i) {
			alloc.construct(dest++, std::move(*old_ele++));        //  string(string&&  r_obj)
		}  //x ʲô�����Ҫ����move�ӹ��أ�  ֵ�����obj
		*/
		//? "move iterator"
		auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);

		free();
		elements = newdata;
		first_free = last;
		cap = elements + new_capacity;
	};

	/*----------------------------------------------*/
	// ���ߺ����������õã�
	pair<string*,string*> alloc_and_copy(string* b,string* e)
	{
		string* new_head = alloc.allocate(e-b);
		auto new_end = uninitialized_copy(b, e, new_head);
		return { new_head, new_end };
	}

	// ���objects�� �����ڴ�ռ�
	void free()
	{
		if (!elements) return;

		for (auto pt = elements; pt != first_free; /**/ ) {
			alloc.destroy(pt++);
		}
		alloc.deallocate(elements, first_free - elements);
	}
};

#endif

