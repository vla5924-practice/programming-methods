#ifndef _FORWARDLIST_H_
#define _FORWARDLIST_H_

namespace ForwardList
{
	template<typename KeyType, typename ValueType>
	struct Node
	{
		KeyType key;
		ValueType data;
		Node<KeyType, ValueType>* next;
	};

	template<typename KeyType, typename ValueType>
	Node<KeyType, ValueType>* find(Node<KeyType, ValueType>* first, KeyType key)
	{
		if (!first)
			return nullptr;
		while (first)
		{
			if (first->key == key)
				return first;
			first = first->next;
		}
		return nullptr;
	}

	template<typename KeyType, typename ValueType>
	void insertToBegin(Node<KeyType, ValueType>*& first, KeyType key)
	{
		Node<KeyType, ValueType>* node = new Node<KeyType, ValueType>;
		node->key = key;
		node->next = first;
		first = node;
	}

	template<typename KeyType, typename ValueType>
	void insertToEnd(Node<KeyType, ValueType>*& first, KeyType key)
	{
		if (!first)
		{
			first = new Node<KeyType, ValueType>;
			first->key = key;
			first->next = nullptr;
			return;
		}
		Node<KeyType, ValueType>* temp = first;
		while (temp->next)
		{
			temp = temp->next;
			temp->next = new Node<KeyType, ValueType>;
			temp->next->key = key;
			temp->next->next = nullptr;
		}
	}

	template<typename KeyType, typename ValueType>
	void insertAfter(Node<KeyType, ValueType>* first, KeyType key, KeyType newKey)
	{
		Node<KeyType, ValueType>* prev = find(first, key);
		if (!prev)
			return;
		Node<KeyType, ValueType>* node = new Node<KeyType, ValueType>;
		node->key = newKey;
		node->next = prev->next;
		prev->next = node;
	}

	template<typename KeyType, typename ValueType>
	void insertBefore(Node<KeyType, ValueType>*& first, KeyType key, KeyType newKey)
	{
		if (!first)
			return;
		if (first->key == key)
		{
			Node<KeyType, ValueType>* node = new Node<KeyType, ValueType>;
			node->key = newKey;
			node->next = first;
			first = node;
			return;
		}
		Node<KeyType, ValueType>* temp = first;
		while (temp->next && (temp->next->key != key))
			temp = temp->next;
		if (!temp->next)
			return;
		Node<KeyType, ValueType>* node = new Node<KeyType, ValueType>;
		node->key = newKey;
		node->next = temp->next;
		temp->next = node;
	}

	template<typename KeyType, typename ValueType>
	void remove(Node<KeyType, ValueType>*& first, KeyType key)
	{
		if (!first)
			return;
		if (first->key == key)
		{
			Node<KeyType, ValueType>* node = first;
			first = first->next;
			delete node;
			return;
		}
		Node<KeyType, ValueType>* temp = first;
		while (temp->next && (temp->next->key != key))
			temp = temp->next;
		if (!temp->next)
			return;
		Node<KeyType, ValueType>* node = temp->next;
		temp->next = node->next;
		delete node;
	}

	template<typename KeyType, typename ValueType>
	void removeAll(Node<KeyType, ValueType>*& first)
	{
		if (!first)
			return;
		while (first)
		{
			Node<KeyType, ValueType>* node = first;
			first = first->next;
			delete node;
		}
		first = nullptr;
	}
}

#endif // !_FORWARDLIST_H_
