/*
 * HashTable.h
 *
 *  Created on: Dec 3, 2018
 *      Author: Erik Dekker
 *      Assignment 5: BarcodeHashScanner
 *      HashTable implementation with Chaining/Closed Addressing
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

using namespace std;

template <typename K, typename V>
class HashTable {
private:
	HashNode<K,V> **table;
	int capacity = 1000; //table size = 1000
public:
	HashTable(){ //constructor
		table = new HashNode<K,V> *[capacity];
	}
	int hashCode(K key) //provides hashcodes when given UPC string
	{
		if(key.length() >= 3)
			key = key.substr(key.length()-3);
		return stoi(key) % capacity;
	}
	//inserts a HashNode into the table
	//parameters: string UPC key, Item object value
	void insert(K key, V value){
        int index = hashCode(key);
	    HashNode<K, V> *temp = table[index];
		HashNode<K, V> *prev = NULL;
		//checks if buckets are empty or duplicates
		while(temp != NULL && temp->getKey() != key){
			prev = temp;
			temp = temp->getNext();
		}
		//adds new node to chain
		if (temp == NULL) {
			temp = new HashNode<K, V>(key, value);
			if (prev == NULL) { //adds as first link in chain
				table[index] = temp;
			} else { //adds to end of chain
				prev->setNext(temp);
			}
		} else { //sets previous key to new value
			temp->setValue(value);
		}
	}
	//returns a value from HashTable
	//parameters: UPC string key, Item value with null description
	V get(K key, V value){
		int index = hashCode(key);
        HashNode<K, V> *entry = table[index];

        while (entry != NULL) {
            if (entry->getKey() == key) {
                return entry->getValue();
            }
            entry = entry->getNext();
        }
        return value; //empty description
	}
};



#endif /* HASHTABLE_H_ */
