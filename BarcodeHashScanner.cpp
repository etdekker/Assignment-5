//============================================================================
// Name        : BarcodBSTScanner.cpp
// Author      : Erik Dekker
// Description : Assignment 5: Barcode Scanner using HashTable
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Item.h"
#include "HashTable.h"
using namespace std;

int main(int argc, const char * argv[]) {
	string fileName = "upc_corpus.txt";
	HashTable<string, Item> table; //Constructs Barcode table
	ifstream inFile;
	inFile.open(fileName);
	string tline;
	string code;
	string desc;
	istringstream tss;

	int count = 0;
	int displayPercent;

	//To be used for Single UPC Look up
	//Comment out for startup efficiency if doing search comparison

	//Populates HashTable with all data
	cout<<"Populating HashTable: "<<endl;
	getline(inFile, tline);
	while(getline(inFile, tline)) {
		tss.clear();
		tss.str(tline);
		getline(tss, code, ',');
		getline(tss, desc);
		Item item(code, desc);
		table.insert(code, item);
		count++;
		displayPercent = count * 100 / 1045913;
		cout<<displayPercent<<"% completed\r";
	}
	cout<<"HashTable Populated\n"<<endl;


	clock_t hashTime;
	clock_t worstTime;
	string UPC;
	int size;
	char input;

	//
	do{
		cout<<"(L) Single UPC Lookup\n(C) Search Comparison\n(Q) Quit\nEnter Command (L/C/Q): ";
		cin>>input;
		if(input == 'L'){//Looks up single UPC and reports time
			cout<<"UPC Code: ";
			cin>>UPC;
			if(isdigit(UPC[0])){
				Item tbf(UPC);
				Item hashOut;
				hashTime = clock();
				hashOut = table.get(UPC, tbf);
				hashTime = clock() - hashTime;
				cout<<hashOut.getDesc()<<endl;
				cout << "HashTable time: " << hashTime << " milliseconds\n" << endl;
			}else{
				cout<<"invalid UPC";
			}
		//Populates and searches a HashTable of a selected size
		}else if(input == 'C'){
			cout<<"Number of Items? (1-1045913): ";
			cin>>size;
			inFile.clear();
			inFile.seekg(0, ios::beg);
			cout<<"Populating HashTable..."<<endl;
			getline(inFile, tline);
			count = 0;
			for(int i = 0; i < size; i++){
				getline(inFile, tline);
				tss.clear();
				tss.str(tline);
				getline(tss, code, ',');
				getline(tss, desc);
				Item it(code, desc);
				table.insert(code, it);
				count++;
				displayPercent = count * 100 / size;
				cout<<displayPercent<<"% populated\r";
			}
			cout<<"Running Search Test...\n"<<endl;

			inFile.clear();
			inFile.seekg(0, ios::beg);
			getline(inFile, tline);
			worstTime = 0;
			Item worstItem;
			count = 0;
			for(int j = 0; j < size; j++){
				getline(inFile, tline);
				tss.clear();
				tss.str(tline);
				getline(tss, code, ',');
				Item tbf(code);
				Item hashOut;
				hashTime = clock();
				hashOut = table.get(code, tbf);
				hashTime = clock() - hashTime;
				if(hashTime > worstTime)
					worstTime = hashTime;
					worstItem = hashOut;
				count++;
				displayPercent = count * 100 / size;
				cout<<displayPercent<<"% searched\r";
			}
			//outputs longest search time for the HashTable
			cout<<"\nWorst Case for BST of size "<<size<<": "<<worstTime<<" milliseconds\n"<<endl;
		}
	}while(input != 'Q');

	return 0;
}
//*/
