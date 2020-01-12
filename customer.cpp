//------------------------------------------- Customer.h -------------------------------------------------------------
// Team GNUgat: Johnathan Hewit, Adam Sirkis, Jenny Troyan
// Author: Jenny Troyan CSS 343 C
// Creation: 03-07-2019
// Modified: 03-07-2019
//----------------------------------------------------------------------------------------------------------------------
// Purpose: Class to represent customer object.
//----------------------------------------------------------------------------------------------------------------------
// Notes: Stores all transaction in a vector.
//----------------------------------------------------------------------------------------------------------------------
#include "customer.h"

//----------------------------- operator<< -----------------------------------------------------------------------------
// Description: overloaded ostream operator, prints formatted output.
//----------------------------------------------------------------------------------------------------------------------
ostream &operator<< (ostream &output, const Customer &customer)
{
	output << left << setw(7) << customer.id << setw(14) << customer.firstName << customer.lastName << endl;
	customer.displayHistory();
	return output;
} // End of operator<<

//----------------------------- Constructor ----------------------------------------------------------------------------
// Description: takes unique id, first name, and last name as parameters.
//----------------------------------------------------------------------------------------------------------------------
Customer::Customer (int id, string firstName, string lastName)
{
	this->id = id;
	this->firstName = firstName;
	this->lastName = lastName;
} // End of constructor

Customer::Customer()
{
	this->id = -1;
	this->firstName = " ";
	this->lastName = " ";
}

//----------------------------- Destructor -----------------------------------------------------------------------------
// Description: deletes object.
//----------------------------------------------------------------------------------------------------------------------
Customer::~Customer ()
{
	deleteUtil();
	transactionHistory.clear();
} // End of destructor

//----------------------------- getName --------------------------------------------------------------------------------
// Description: returns full name for a customer.
//----------------------------------------------------------------------------------------------------------------------
string Customer::getName () const
{
	return (this->firstName + " " + this->lastName);
} // End of getName

//----------------------------- getID ----------------------------------------------------------------------------------
// Description: returns customer's ID.
//----------------------------------------------------------------------------------------------------------------------
int Customer::getID () const
{
	return this->id;
} // End of getID

//----------------------------- getHistory -----------------------------------------------------------------------------
// Description: displays all transactions.
//----------------------------------------------------------------------------------------------------------------------
void Customer::displayHistory () const
{
	for (auto &item : transactionHistory)
	{
		item->display();
	}
} // End of getHistory

//----------------------------- addTransaction -------------------------------------------------------------------------
// Description: adds transaction to all transaction history.
//----------------------------------------------------------------------------------------------------------------------
void Customer::addTransaction (Transaction *transaction)
{
	this->transactionHistory.push_back(transaction);
} // End of addTransaction

//----------------------------- deleteUtil -----------------------------------------------------------------------------
// Description: iterates through vector and deletes each transaction object
//----------------------------------------------------------------------------------------------------------------------
void Customer::deleteUtil ()
{
	vector<Transaction *>::iterator it;
	for (it = transactionHistory.begin(); it != transactionHistory.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
} // End of deleteUtil

