#pragma once

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

	Iterator& operator+=(SIZE_T off) 
	{
		_ptr += off;
		return *this;
	}

	Iterator& operator-=(SIZE_T off)
	{
		_ptr -= off;
		return *this;
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
	_Ty* _ptr;

};


template<typename _Ty, typename _Alloc = std::allocator<_Ty>>
class XVector
{
	using value_type = _Ty;
	using allocator_type = _Alloc;
	using reference = _Ty&;
	using const_reference = const _Ty&;
	using pointer = _Ty*;
	using const_pointer = const _Ty*;
	using iterator = Iterator<_Ty>;

public:
	XVector() : _data(nullptr), _size(0), _capacity(0)
	{
		_Alloc alloc;
	}
	XVector(std::initializer_list<value_type> l) : _data(nullptr), _size(0), _capacity(0)
	{
		reserve(l.size());
		for(auto& ele : l)
		{
			push_back(ele);
		}
	}

	~XVector()
	{
		if(_data != nullptr)
		{
			_allocator.deallocate(_data, _capacity);
		}
	}

public:

	XVOID push_back(value_type value)
	{
		if(_size >= _capacity)
		{
			SIZE_T newCap = static_cast<SIZE_T>(_capacity * 1.5f);
			if(newCap <= _capacity)
			{
				newCap++;
			}

			reserve(newCap);
		}

		_data[_size] = value_type(value);
		_size++;
	}

	template<typename... Args>
	XVOID emplace_back(Args&&... _args)
	{
		if (_size >= _capacity)
		{
			SIZE_T newCap = static_cast<SIZE_T>(_capacity * 1.5f);
			if (newCap <= _capacity)
			{
				newCap++;
			}

			reserve(newCap);
		}

		_data[_size] = value_type(std::forward<Args>(_args)...);
		_size++;
	}

	XVOID pop_back()
	{
		if (_size == 0)
			return;
		
		_size--;
	}

	XVOID reserve(SIZE_T capacity)
	{
		if (capacity <= _capacity)
			return;


		pointer temp = _allocator.allocate(capacity);

		for(SIZE_T i =0; i < _capacity; i++)
		{
			temp[i] = _data[i];
		}

		_allocator.deallocate(_data, _capacity);
		_data = temp;

		_capacity = capacity;
	}

public:
	reference operator[](SIZE_T pos)
	{
		_STL_VERIFY(pos < static_cast<SIZE_T>(_size), "vector subscript out of range");

		return _data[pos];
	}

public:

	NODISCARD CONSTEXPR SIZE_T size() const
	{
		return _size;
	}

	NODISCARD CONSTEXPR reference back() const
	{
		return _data[_size - 1];
	}

	NODISCARD CONSTEXPR iterator begin() const
	{
		return iterator(_data, 0);
	}

	NODISCARD CONSTEXPR iterator end() const
	{
		return iterator(_data, _size);
	}

		
private:
	pointer		_data;
	SIZE_T		_size;
	SIZE_T		_capacity;

	_Alloc		_allocator;

};

}
