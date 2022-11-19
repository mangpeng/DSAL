#pragma once
#include "Types.h"
#include "xutility"

namespace X
{

template<typename _Ty>
class Iterator
{
public:
	Iterator(_Ty* ptr, SIZE_T pos) : _ptr(ptr + pos) {}

public:
	_Ty& operator*()
	{
		return *_ptr;
	}

	Iterator& operator++() // prefix increment operator
	{
		_ptr += 1;
		return *this;
	}

	Iterator operator++(int) // suffix increment operator
	{
		_Ty* p = _ptr + 1;
		return Iterator(p, 0);
	}

	Iterator& operator--() // prefix increment operator
	{
		_ptr -= 1;
		return *this;
	}

	Iterator operator--(int) // suffix increment operator
	{
		_Ty* p = _ptr - 1;
		return Iterator(p, 0);
	}

	XBOOL operator==(const Iterator& src) 
	{
		return _ptr == src._ptr;
	}

	XBOOL operator!=(const Iterator& src)
	{
		return !(*this == src);
	}

private:
	_Ty*   _ptr;

};

template<typename _Ty, SIZE_T _Size>
class XArray
{

	using value_type = _Ty;
	using reference = _Ty&;
	using const_reference = const _Ty&;
	using pointer = _Ty*;
	using const_pointer = const _Ty*;
	
	using iterator = Iterator<_Ty>;

public:
	XArray() = delete;
	XArray(std::initializer_list<value_type> l) :_data(nullptr), _len(0)
	{
		if (l.size() > _Size)
		{
			_Xran();
		}

		_data = new value_type[_Size];
		for (auto it = l.begin(); it != l.end(); ++it)
		{
			_data[_len] = *it;
			_len++;
		}

	}

	~XArray()
	{
		delete[] _data;
	}

public:
	NODISCARD CONSTEXPR reference at(value_type pos)
	{
		if (_Size <= pos) {
			_Xran();
		}

		return _data[pos];
	}

public:
	NODISCARD CONSTEXPR reference operator[](value_type pos)
	{
		return _data[pos];
	}

public:

	NODISCARD iterator begin()
	{
		return iterator(_data, 0);
	}

	NODISCARD iterator end()
	{
		return iterator(_data, _Size);
	}

	NODISCARD CONSTEXPR const_pointer data() const
	{
		return const_cast<const_pointer>(_data);
	}

	NODISCARD CONSTEXPR SIZE_T size() const
	{
		return _len;
	}

private:

	NORETURN void _Xran() const {
		std::_Xout_of_range("invalid XArray<T, N> subscript");
	}

private:
	value_type*			_data;
	SIZE_T				_len;

};

}