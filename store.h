//------------------------------------------- store.h ------------------------------------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//----------------------------------------------------------------------------------------------------------------------
// Purpose: Class to represent a store class
//----------------------------------------------------------------------------------------------------------------------
#ifndef STORE_H
#define STORE_H
#include <array>
#include <map>
#include "HASH_MAP.h"
#include <iostream>
#include <fstream>
#include "merchandise.h"
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "bintree.h"
#include "customer.h"
#include "transaction.h"

using namespace std;
const int TABLE_SIZE = 26;

class Store
{
	BinTree* mediaTreeTable[TABLE_SIZE];
	HASH_MAP<int, Customer> customerTable;
	string storename;
	void printCustomerHistory(int&);
	void borrowUtil(int&, char&, char&, istringstream&);
	void returnUtil(int&, char&, char&, istringstream&);
	void formatString(string &);


public:
	Store(string&);
	~Store();
	void setMerchandise(ifstream&);
	void setCustomers(ifstream&);
	void setCommands(ifstream&);
	void allInventory() const noexcept;
	void printCustomers() const;
	inline string getStoreName() const noexcept;
};
#endif
