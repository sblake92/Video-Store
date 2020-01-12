//------------------------------------------- transaction.cpp ----------------------------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//----------------------------------------------------------------------------------------------------------------------
// Purpose: Class to represent transaction object. Superclass for Borrow and Return classes.
//----------------------------------------------------------------------------------------------------------------------
// Notes: Contains two virtual functions that must be overwritten in subclass.
//----------------------------------------------------------------------------------------------------------------------
#include "transaction.h"

//----------------------------- Constructor ----------------------------------------------------------------------------
// Description: initializes all values to empty char or nullptr.
//----------------------------------------------------------------------------------------------------------------------
Transaction::Transaction (Merchandise *data, const char &type)
{
	this->type = type;
	this->merchandise = data;
} // End of constructor

//----------------------------- Virtual Destructor ---------------------------------------------------------------------
// Description: virtual destructor.
//----------------------------------------------------------------------------------------------------------------------
Transaction::~Transaction ()
{
	this->merchandise = nullptr;
} // End of destructor

//----------------------------- display --------------------------------------------------------------------------------
// Description: virtual function that will be overwritten in subclass.
//----------------------------------------------------------------------------------------------------------------------
void Transaction::display () const
{
	type == 'B' ? cout << "BORROWED " : cout << "RETURNED ";
	merchandise->displayForHistory();
} // End of display
