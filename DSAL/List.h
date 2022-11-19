#pragma once

namespace X
{

template<typename _Ty>
class Node;

template<typename _Ty, typename _Alloc>
class Iterator_List;

template<typename _Ty, typename _Alloc>
class XList;



template<typename _Ty >
class Node
{
	using value_type = _Ty;
	using const_reference = const _Ty&;
	
public:
	Node() : _data{}, _prev(nullptr), _next(nullptr) {}
	Node(const_reference ele) : _data(ele), _prev(nullptr), _next(nullptr) {}

public:
	_Ty		_data;
	Node*	_prev;
	Node*	_next;
};


template<typename _Ty, typename _Alloc = std::allocator<Node<_Ty>> >
class Iterator_List
{
	using node_type = Node<_Ty>;
	using node_pointer_type = Node<_Ty>*;

public:
	Iterator_List(node_pointer_type node) : _node(node) {}

public:
	_Ty& operator*()
	{
		return _node->_data;
	}

	Iterator_List& operator++() // prefix increment operator
	{
		_node = _node->_next;
		return *this;
	}

	Iterator_List operator++(int) // suffix increment operator
	{
		node_pointer_type p = _node->_next;
		return Iterator_List(p);
	}

	Iterator_List& operator--() // prefix increment operator
	{
		_node = _node->_prev;
		return *this;
	}

	Iterator_List operator--(int) // suffix increment operator
	{
		node_pointer_type p = _node->_prev;
		return Iterator_List(p);
	}


	XBOOL operator==(const Iterator_List& src)
	{
		return _node->_data == src._node->_data;
	}

	XBOOL operator!=(const Iterator_List& src)
	{
		return !(*this == src);
	}

private:
	friend class XList<_Ty, _Alloc>;
	node_pointer_type	_node;

};



template<typename _Ty, typename _Alloc = std::allocator<Node<_Ty>> >
class XList
{
	using value_type = _Ty;
	using allocator_type = _Alloc;
	using node_type = Node<value_type>;
	using node_pointer_type = node_type*;
	using iterator = Iterator_List<_Ty>;

public:
	XList() : _allocator{}
	{
		_head = _allocator.allocate(sizeof(node_type));
		new(_head)node_type();
		
		_tail = _allocator.allocate(sizeof(node_type));
		new(_tail)node_type();

		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~XList()
	{
		_head->~node_type();
		_allocator.deallocate(_head, sizeof(node_type));

		_tail->~node_type();
		_allocator.deallocate(_tail, sizeof(node_type));

		// delete elements left
	}

public:

	XVOID push_front(value_type value)
	{
		node_pointer_type next = _head->_next;

		node_pointer_type newNodePtr = _allocator.allocate(sizeof(node_type));
		new(newNodePtr)node_type(value);

		newNodePtr->_prev = _head;
		newNodePtr->_next = next;

		_head->_next = newNodePtr;
		next->_prev = newNodePtr;

		_size++;
	}

	XVOID push_back(value_type value)
	{
		node_pointer_type prev = _tail->_prev;

		node_pointer_type newNodePtr = _allocator.allocate(sizeof(node_type));
		new(newNodePtr)node_type(value);

		newNodePtr->_prev = prev;
		newNodePtr->_next = _tail;

		_tail->_prev = newNodePtr;
		prev->_next = newNodePtr;
		
		_size++;
	}

	XVOID pop_front()
	{
		_STL_VERIFY(_size > 0, "pop_front called on empty list");
		erase(iterator(_head->_next));
	}

	XVOID pop_back()
	{
		_STL_VERIFY(_size > 0, "pop_back called on empty list");
		erase(iterator(_tail->_prev));
	}

	iterator erase(iterator eraseIt)
	{
		node_pointer_type prev = eraseIt._node->_prev;
		node_pointer_type next = eraseIt._node->_next;

		eraseIt._node->~node_type();
		_allocator.deallocate(eraseIt._node, sizeof(node_type));

		prev->_next = next;
		next->_prev = prev;

		_size--;

		return iterator(next);
	}

public:

	NODISCARD CONSTEXPR SIZE_T size() const
	{
		return _size;
	}

	NODISCARD CONSTEXPR iterator begin() const
	{
		return iterator(_head->_next);
	}

	NODISCARD CONSTEXPR iterator end() const
	{
		return iterator(_tail);
	}


private:
	allocator_type				_allocator;
	node_pointer_type			_head;
	node_pointer_type			_tail;
	SIZE_T						_size;

};

}


