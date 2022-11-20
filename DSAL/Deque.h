#pragma once
#include <iostream>
#include <unordered_map>

namespace X
{
template<typename _Bucket>
class Iterator_Deque 
{
public:

	_Ty& operator*()
	{
		return *_ptr;
	}

	Iterator_Deque& operator++() 
	{

	}

	Iterator_Deque operator++(int) 
	{

	}

	Iterator_Deque& operator--() 
	{

	}

	Iterator_Deque operator--(int) 
	{

	}

	XBOOL operator==(const Iterator_Deque src) 
	{

	}

	XBOOL operator!=(const Iterator_Deque src)
	{
	}




private:
	_Bucket*	_bucket;
	XINT		_index;

};

template<typename _Ty, typename _Alloc = std::allocator<_Ty>, SIZE_T _BucketSize = 5>
class Bucket
{
	using value_type = _Ty;
	using allocator_type = _Alloc;
	using reference = _Ty&;
	using forward_reference = _Ty&;
	using const_reference = const _Ty&;
	using pointer = _Ty*;
	using const_pointer = const _Ty*;

public:
	Bucket() 
		: _prev(nullptr), _next(nullptr), _data(nullptr), 
	{
		_data = _allocator.allocate(_BucketSize * sizeof(_Ty));
		_start = 0;
		_end = _BucketSize - 1;
	}
	
public:
	XVOID push_front(forward_reference value) 
	{
		_data[_end] = value;
		_end--;
	}

	XVOID push_back(forward_reference value)
	{
		_data[_start] = value;
		_start--;
	}



private:
	allocator_type	_allocator;

	pointer			_data;
	SIZE_T			_start;
	SIZE_T			_end;
};

template<typename _Ty, typename _Alloc = std::allocator<_Ty>, SIZE_T _BucketSize = 5>
class XDeque 
{
	using value_type = _Ty;

public:
	XDeque() :_start(0), _end(start + 1), _size(0), _buckets{} {
		
	}

public:

	// [][][][][] [0][][][][] [][][][][]
	// 11 = 2, 1
	// 시작점 = -12 => -2 , 3
	// 끝점 = 23 = 4, 3
	XVOID push_front(value_type value) {

		SIZE_T id = _start / _BucketSize;
		SIZE_T index = _start % _BucketSize;
		auto fIt = _buckets.find(bId);
		if (fIt == _buckets.end()) {
			Bucket newBk;
			_buckets[id] = newBk;
		}

		auto bk = _buckets[bId];
		bk.push_front(std::move(value))
		_start--;
	}

	XVOID push_back(value_type value) {
		SIZE_T id = _end / _BucketSize;
		SIZE_T index = _end % _BucketSize;
		auto fIt = _buckets.find(bId);
		if (fIt == _buckets.end()) {
			Bucket newBk;
			_buckets[id] = newBk;
		}

		auto bk = _buckets[bId];
		bk.push_back(std::move(value))
		_end++;
	}

public:
	NODISCARD CONSTEXPR SIZE_T size() const 
	{
		return _end - start - 1;
	}

private:
	SIZE_T	_start;
	SIZE_T	_end;
	SIZE_T  _size;

	std::unordered_map<XINT, Bucket<_Ty, _Alloc, _BucketSize>> _buckets;
	

};

}