//------------------------------------------- store.cpp ----------------------------------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/20199
//----------------------------------------------------------------------------------------------------------------------
// Purpose: Class to represent a store class
//----------------------------------------------------------------------------------------------------------------------
#include "store.h"
#define valid_month_range(a) (a > 0 && a < 13)
#define valid_year_range(a) (a>1887 && a < 2020)
#define _minus_A(a) a - 'A'
#define DVD "D"
#include <sstream>
#include <iomanip>

//------------------------------(constructor)---------------------------------------------------------------------------
// initialize the store name
//----------------------------------------------------------------------------------------------------------------------
Store::Store(string& s)
{
	storename = s;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		mediaTreeTable[i] = new BinTree();
	}
} // End of constructor

//------------------------------(destructor)----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
Store::~Store()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		mediaTreeTable[i]->makeEmpty();
		delete mediaTreeTable[i];
	}
	for (auto &item : customerTable)
	{
		item.second.deleteUtil();
	}
} // End of destructor

//------------------------------setMerchandise--------------------------------------------------------------------------
// Initialize merchandise objects from rhs ifstream
// Will not insert duplicate objects
//----------------------------------------------------------------------------------------------------------------------
void Store::setMerchandise(ifstream &i)
{
	Merchandise* temp = nullptr;
	string stock = "", type = "";
	while (!i.eof())
	{
		getline(i, type, ',');
		if (!type.empty())
		{
			getline(i, stock, ',');
			istringstream iss(type);
			iss >> type;
			if (type != "\r\n")
			{
				switch (type[0])
				{
					case 'C':
						temp = new Classic(i);
						temp->setMaxStock(stoi(stock));
						temp->setStock(stoi(stock));
						temp->setFormat("DVD");
						mediaTreeTable[_minus_A('C')]->insert(temp);
						break;
					case 'F':
						temp = new Comedy(i);
						temp->setMaxStock(stoi(stock));
						temp->setStock(stoi(stock));
						temp->setFormat("DVD");
						mediaTreeTable[_minus_A('F')]->insert(temp);
						break;
					case 'D':
						temp = new Drama(i);
						temp->setMaxStock(stoi(stock));
						temp->setStock(stoi(stock));
						temp->setFormat("DVD");
						mediaTreeTable[_minus_A('D')]->insert(temp);
						break;
					default:
						cout << "INVALID MEDIA TYPE: EXPECTED 'D', 'C', 'F'. RECEIVED: '" << type << "'. Item not Inserted" << endl;
						string tmp = "";
						getline(i, tmp);
						break;
				}
			}
		}
	}
} // End of setMerchandise

//------------------------------setCustomers----------------------------------------------------------------------------
// Takes in ifstream rhs and initializes a list of Customer objects from
// a properly formatted file
// Will not insert duplicate objects
//----------------------------------------------------------------------------------------------------------------------
void Store::setCustomers(ifstream & i)
{
	string line = "";
	while (!i.eof()) {
		getline(i, line);
		if (!line.empty()) {
			string n = "", f = "", l = "";
			istringstream iss(line);
			iss >> n >> l >> f;
			int id = stoi(n);
			Customer C = Customer(id, f, l);
			if (!customerTable.count(id))
				customerTable.insert(std::pair<int, Customer>(id, C));
		}
	}
} // End of setCustomers

//------------------------------setCommands-----------------------------------------------------------------------------
// Run commands based on properly formatted ifstream rhs
// Will not run ill-formatted commands
//----------------------------------------------------------------------------------------------------------------------
void Store::setCommands(ifstream & in)
{
	while (!in.eof()) {
		char command = ' ';
		string line = " ";
		int id = 0;
		char merchFormat = ' ';
		char mediaType = ' ';

		getline(in,line);
		if (!line.empty())
		{
			istringstream iss(line);
			iss >> command;
			switch(command)
			{
				case 'I':
					cout << "\n::STORE INVENTORY::" << endl;
					allInventory();
					break; // End case 'I'

				case 'H':
					cout << "\n::CUSTOMER TRANSACTION HISTORY::" << endl;
					iss >> id;
					printCustomerHistory(id);
					break; // End case 'H'

				case 'B':
					iss >> id >> merchFormat >> mediaType;
					borrowUtil(id, merchFormat, mediaType, iss);
					break; // End case 'B'

				case 'R':
					iss >> id >> merchFormat >> mediaType;
					returnUtil(id, merchFormat, mediaType, iss);
					break; // End case 'R'

				default:
					cout << "\nINVALID COMMAND: EXPECTED 'I', 'H', 'R', 'B'. RECEIVED: '" << command << "'" << endl;
					break; // End default case
			}
		}
	}
} // End of setCommands

//------------------------------allInventory----------------------------------------------------------------------------
// prints all inventory to the console
//----------------------------------------------------------------------------------------------------------------------
void Store::allInventory() const noexcept
{
	for (int i = 25; i >= 0; i--)
	{
		if (!mediaTreeTable[i]->isEmpty())
		{
			cout << *mediaTreeTable[i];
		}
	}
} // End of allInventory

//----------------------------- printCustomers -------------------------------------------------------------------------
// Description: prints formatted output for all customers
//----------------------------------------------------------------------------------------------------------------------
void Store::printCustomers () const
{
	for (auto &item : customerTable)
	{
		if (item.first != 0)
		{
			cout << item.second;
		}

	}
} // End of printCustomers

//------------------------------getStoreName----------------------------------------------------------------------------
// Returns the store name
//----------------------------------------------------------------------------------------------------------------------
inline string Store::getStoreName() const noexcept
{
	return storename;
} // End of getStoreName

//----------------------------- printCustomerHistory -------------------------------------------------------------------
// Description: helper function that takes customer id and searches hash map for that customer;
//              in the case of finding a customer with a given id, prints formatted output for that customer;
//              int the case of not finding a customer with a given id, prints error message.
//----------------------------------------------------------------------------------------------------------------------
void Store::printCustomerHistory (int &id)
{
	if (!customerTable.count(id))
	{
		cout << "INVALID CUSTOMER ID:" << id << endl;
	}
	else
	{
		cout << " " << left << setw(6) << "ID" << setw(14) << "FIRST NAME" << "LAST NAME" << endl;
		cout << customerTable[id];
	}
}// End of printCustomerHistory

//----------------------------- borrowUtil -----------------------------------------------------------------------------
// Description: util function that takes id, merchandise format, media type, and string stream as parameters;
//              retrieves customer with a given id, retrieves media with a given parameters,
//              creates new borrow object and adds to the customer with a given id, and returns true;
//              in the case of invalid parameters, prints error message and returns false;
//              in the case of not finding a customer for a given id, prints error message and returns false;
//              in the case of not finding a merchandise with a given parameters, prints error message and returns false
//----------------------------------------------------------------------------------------------------------------------
void Store::borrowUtil (int &id, char &merchFormat, char &mediaType, istringstream &iss)
{
	if ((merchFormat == 'D') && (mediaType == 'F' || mediaType == 'C' || mediaType == 'D'))
	{
		if (customerTable.count(id))
		{
			Comedy* targetComedy = nullptr;
			Classic* targetClassics = nullptr;
			Drama* targetDrama = nullptr;
			Merchandise* toRetrieve = nullptr;
			string mediaTitle = " ";
			int month = 0;
			int year = 0;
			string mediaDirector = " ";
			string mediaActor = " ";
			string tmp = " ";

			switch(mediaType)
			{
				case 'F': // Comedy
					getline(iss, mediaTitle, ',');
					iss >> year;
					formatString (mediaTitle);
					if (!valid_year_range(year))
					{
						cout << "\nBORROW TRANSACTION FAILED\tINVALID YEAR INDICATED: YEAR = " << year << endl;
						return;
					}
					targetComedy = new Comedy(mediaTitle, year);
					if (mediaTreeTable[_minus_A('F')]->retrieve(*targetComedy, toRetrieve))
					{
						if (toRetrieve->getStock() > 0)
						{
								toRetrieve->decreaseStock();
								customerTable[id].addTransaction(new Transaction(toRetrieve, 'B'));
								delete targetComedy;
								toRetrieve = nullptr;
						}
						else
						{
							delete targetComedy;
							toRetrieve = nullptr;
							cout << "\nBORROW TRANSACTION FAILED\tCOMEDY TITLE = " << mediaTitle << " YEAR = " << year << " IS OUT OF STOCK!" << endl;
							return;
						}
					}
					else
					{
						delete targetComedy;
						cout << "\nBORROW TRANSACTION FAILED\tCOMEDY TITLE = " << mediaTitle << " YEAR = " << year << " NOT IN DATABASE!" <<endl;
						return;
					}
				break; // End 'F' case

				case 'D': // Drama
					getline(iss, mediaDirector, ',');
					getline(iss, mediaTitle, ',');
					formatString (mediaTitle);
					formatString (mediaDirector);
					targetDrama = new Drama(mediaDirector, mediaTitle);
					if (mediaTreeTable[_minus_A('D')]->retrieve(*targetDrama, toRetrieve))
					{
						if (toRetrieve->getStock() > 0)
						{
							toRetrieve->decreaseStock();
							customerTable[id].addTransaction(new Transaction(toRetrieve, 'B'));
							delete targetDrama;
							toRetrieve = nullptr;
						}
						else
						{
							delete targetDrama;
							toRetrieve = nullptr;
							cout << "\nBORROW TRANSACTION FAILED\tDRAMA TITLE = " << mediaTitle << " DIRECTOR = " << mediaDirector << " IS OUT OF STOCK!" << endl;
							return;
						}
					}
					else
					{
						delete targetDrama;
						cout << "\nBORROW TRANSACTION FAILED\tDRAMA TITLE = " << mediaTitle << " DIRECTOR = " << mediaDirector << " NOT IN DATABASE!" << endl;
						return;
					}
				break; // End 'D' case

				case 'C': // Classics
					iss >> month >> year;
					getline(iss, tmp);
					size_t pos = tmp.find('\r');
					mediaActor = tmp.substr (0,pos);
					formatString (mediaActor);
					targetClassics = new Classic(month, year, mediaActor);
					if (!valid_month_range(month) || !valid_year_range(year))
					{
						cout << "\nBORROW TRANSACTION FAILED\tINVALID MONTH OR YEAR INDICATED: MONTH = " << month << " YEAR = " << year << endl;
						return;
					}
					if (mediaTreeTable[_minus_A('C')]->retrieve(*targetClassics, toRetrieve))
					{
						if (toRetrieve->getStock() > 0)
						{
							toRetrieve->decreaseStock();
							customerTable[id].addTransaction(new Transaction(toRetrieve, 'B'));
							delete targetClassics;
							toRetrieve = nullptr;
						}
						else
						{
							delete targetClassics;
							toRetrieve = nullptr;
							cout << "\nBORROW TRANSACTION FAILED\tCLASSICS ACTOR = " << mediaActor << " MONTH = " << month << " YEAR = " << year <<  " IS OUT OF STOCK!" << endl;
							return;
						}
					}
					else
					{
						delete targetClassics;
						cout << "\nBORROW TRANSACTION FAILED\tCLASSICS ACTOR = " << mediaActor << " MONTH = " << month << " YEAR = " << year << " NOT IN DATABASE!" << endl;
						return;
					}
				break; // End 'C' case
			}
		}
		else
		{
			cout << "\nBORROW TRANSACTION FAILED\tINVALID CUSTOMER ID: ID = " << id << endl;
			return;
		}
	}
	else
	{
		cout << "\nBORROW TRANSACTION FAILED\tINVALID PARAMETERS INDICATED: MERCHANDISE FORMAT = " << merchFormat << " MEDIA TYPE = " << mediaType << endl;
	}
} // End of borrowUtil

//----------------------------- returnUtil -----------------------------------------------------------------------------
// Description: util function that takes id, merchandise format, media type, and string stream as parameters;
//              retrieves customer with a given id, retrieves media with a given parameters,
//              creates new return object and adds to the customer with a given id, and returns true;
//              in the case of invalid parameters, prints error message and returns false;
//              in the case of not finding a customer for a given id, prints error message and returns false;
//              in the case of not finding a merchandise with a given parameters, prints error message and returns false
//----------------------------------------------------------------------------------------------------------------------
void Store::returnUtil (int &id, char &merchFormat, char &mediaType, istringstream &iss)
{
	if ((merchFormat == 'D') && (mediaType == 'F' || mediaType == 'C' || mediaType == 'D'))
	{
		if (customerTable.count(id))
		{
			Comedy* targetComedy = nullptr;
			Classic* targetClassics = nullptr;
			Drama* targetDrama = nullptr;
			Merchandise* toRetrieve = nullptr;
			string mediaTitle = " ";
			int month = 0;
			int year = 0;
			string mediaDirector = " ";
			string mediaActor = " ";
			string tmp = " ";

			switch(mediaType)
			{
				case 'F': // Comedy
					getline(iss, mediaTitle, ',');
					iss >> year;
					formatString(mediaTitle);
					if (!valid_year_range(year))
					{
						cout << "\nRETURN TRANSACTION FAILED\tINVALID YEAR INDICATED: YEAR = " << year << endl;
						return;
					}
					targetComedy = new Comedy(mediaTitle,year);
					if (mediaTreeTable[_minus_A('F')]->retrieve(*targetComedy, toRetrieve))
					{
						if (toRetrieve->getStock() < toRetrieve->getMaxStock())
						{
							toRetrieve->increaseStock();
							customerTable[id].addTransaction(new Transaction(toRetrieve, 'R'));
							delete targetComedy;
							toRetrieve = nullptr;
						}
						else
						{
							delete targetComedy;
							targetComedy = nullptr;
							cout << "\nRETURN TRANSACTION FAILED\tCOMEDY TITLE = " << mediaTitle << " YEAR = " << year << " IS AT MAXIMUM INVENTORY!" << endl;
							return;
						}
					}
					else
					{
						delete targetComedy;
						toRetrieve = nullptr;
						cout << "\nRETURN TRANSACTION FAILED\tCOMEDY TITLE = " << mediaTitle << " YEAR = " << year << " NOT IN DATABASE!" << endl;
						return;
					}
					break; // End 'F' case

				case 'D': // Drama
					getline(iss, mediaDirector, ',');
					getline(iss, mediaTitle, ',');
					formatString(mediaTitle);
					formatString(mediaDirector);
					targetDrama = new Drama(mediaDirector, mediaTitle);
					if (mediaTreeTable[_minus_A('D')]->retrieve(*targetDrama, toRetrieve))
					{
						if (toRetrieve->getStock() < toRetrieve->getMaxStock())
						{
							toRetrieve->increaseStock();
							customerTable[id].addTransaction(new Transaction(toRetrieve, 'R'));
							delete targetDrama;
							toRetrieve = nullptr;
						}
						else
						{
							delete targetDrama;
							targetDrama = nullptr;
							cout << "\nRETURN TRANSACTION FAILED\tDRAMA TITLE = " << mediaTitle << " DIRECTOR = " << mediaDirector << " IS AT MAXIMUM INVENTORY!" << endl;
							return;
						}
					}
					else
					{
						delete targetDrama;
						toRetrieve = nullptr;
						cout << "\nRETURN TRANSACTION FAILED\tDRAMA TITLE = " << mediaTitle << " DIRECTOR = " << mediaDirector << " NOT IN DATABASE!" << endl;
						return;
					}
					break; // End 'D' case

				case 'C': // Classics
					iss >> month >> year;
					getline(iss, tmp);
					size_t pos = tmp.find('\r');
					mediaActor = tmp.substr (0,pos);
					formatString (mediaActor);
					targetClassics = new Classic(month, year, mediaActor);
					if (!valid_month_range(month) || !valid_year_range(year))
					{
						cout << "\nRETURN TRANSACTION FAILED\tINVALID MONTH OR YEAR INDICATED: MONTH = " << month << " YEAR = " << year << endl;
						return;
					}
					if (mediaTreeTable[_minus_A('C')]->retrieve(*targetClassics, toRetrieve))
					{
						if (toRetrieve->getStock() < toRetrieve->getMaxStock())
						{
							toRetrieve->increaseStock();
							customerTable[id].addTransaction(new Transaction(toRetrieve, 'R'));
							delete targetClassics;
							toRetrieve = nullptr;
						}
						else
						{
							delete targetClassics;
							targetClassics = nullptr;
							cout << "\nRETURN TRANSACTION FAILED\tCLASSICS ACTOR = " << mediaActor << " MONTH = " << month << " YEAR = " << year << " IS AT MAXIMUM INVENTORY!" << endl;
							return;
						}
					}
					else
					{
						delete targetClassics;
						toRetrieve = nullptr;
						cout << "\nRETURN TRANSACTION FAILED\tCLASSICS ACTOR = " << mediaActor << " MONTH = " << month << " YEAR = " << year << " NOT IN DATABASE!" << endl;
						return;
					}
					break; // End 'C' case
			}
		}
		else
		{
			cout << "\nRETURN TRANSACTION FAILED\tINVALID CUSTOMER ID: ID =" << id << endl;
			return;
		}
	}
	else
	{
		cout << "\nRETURN TRANSACTION FAILED\tINVALID PARAMETERS INDICATED: MERCHANDISE FORMAT = " << merchFormat << " MEDIA TYPE = " << mediaType << endl;
	}
} // End of returnUtil

//----------------------------- formatString ---------------------------------------------------------------------------
// Description: removes white space at the beginning of a given string
//----------------------------------------------------------------------------------------------------------------------
void Store::formatString (string &str)
{
	size_t pos = str.find(' ');
	str = str.substr (pos+1, str.size());
} // End of formatString
