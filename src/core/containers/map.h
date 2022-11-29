#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::pair;


namespace Containers {
    template<class K, class V>
    class Map;

    template<class K, class V>
    ostream& operator<<(ostream&, const Map<K, V>&);

    template<class K, class V>
    class Map {
    private:
	class Node {

	private:
	    enum Color {
		RED,
		BLACK,
	    };

	    K key;
	    V value;
	    Color color;
	    Node* parent;
	    Node* left;
	    Node* right;

	    friend class Map;

	public:
	    Node(K key, V value, Color color = BLACK, Node* parent = nullptr, Node* left = nullptr,
		 Node* right = nullptr) :
		    key(key),
		    value(value),
		    color(color),
		    parent(parent),
		    left(left),
		    right(right) {};
	};

	Node* root;
	unsigned int size;
	static Node* const TNULL;

	void inOrderHelper(Node* node) const;

	Node* searchTreeHelper(Node* node, K key) const;

	void fixErase(Node* x);

	void transplant(Node* u, Node* v);

	void eraseNodeHelper(Node* node, K key);

	void fixPut(Node* k);

	void printHelper(ostream& os, Node* root, string indent = "", bool visitRight = true) const;

	static Node* predecessor(Node* x);

	void leftRotate(Node* x);

	void rightRotate(Node* x);

	static Node* minimum(Node* node);

	static Node* maximum(Node* node);

	static Node* successor(Node* x);

    public:
	Map() : root(TNULL), size(0) {};

	Map(const Map<K, V>& map) : root(inOrderCopy(map.root)), size(map.size) {};

	~Map();

	bool empty() const;

	Map& operator=(const Map&);

	static void destroy(Node*);

	static Node* inOrderCopy(Node*);

	void inOrderTraversal() const;

	void put(K key, V value);

	void erase(K key);

	int get(K key) const;

	unsigned int getSize() const;

	friend ostream& operator
	<<<K, V>(ostream&, const Map<K, V>&);

	class MapIterator {
	private:
	    Map::Node* node;
	    bool isPastTheEnd;
	    bool isBeforeTheStart;
	public:
	    MapIterator(Map::Node* n) : node(n), isPastTheEnd(false), isBeforeTheStart(false) {};

	    bool operator==(const MapIterator& i) const;

	    bool operator!=(const MapIterator& i) const;

	    MapIterator operator++(int);  // postfix
	    MapIterator& operator++();    // prefix

	    MapIterator operator--(int);  // postfix
	    MapIterator& operator--();    // prefix

	    pair<K, V> operator*() const;

	    friend class Map<K, V>;
	};

	MapIterator begin();

	MapIterator end();

	friend ostream& operator
	<<<K, V>(ostream&, const Map<K, V>&);
    };
}

#endif // MAP_H
