/*
 * HashNode.h
 *
 *  Created on: Dec 3, 2018
 *      Author: Erik Dekker
 *      Assignment 5: BarcodeHashScanner
 *      HashNode template class
 */

#ifndef HASHNODE_H_
#define HASHNODE_H_

#include <iostream>
using namespace std;

template <typename K, typename V>
class HashNode {
private:
	K key;
	V value;
	HashNode* next;
public:
	HashNode(const K &_key, const V &_value){
		this->key = _key;
		this->value = _value;
		this->next = NULL;
	}
	K getKey(){
		return key;
	}
	V getValue(){
		return value;
	}
	void setValue(V _value){
		this->value = _value;
	}
	HashNode *getNext(){
		return next;
	}
	void setNext(HashNode* _next){
		this->next = _next;
	}

};



#endif /* HASHNODE_H_ */
