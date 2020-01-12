//---------------------------------main.cpp----------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Driver implementation file for the Store class. This driver
//         finds text files containing the data for each subclass of the
//         Store and creates the istream files. Then, it sends those files
//         to the Store for creation of each Movie, Customer and Transaction.
//---------------------------------------------------------------------------
//Notes: This driver assumes that the data within the data4movies.txt,
//       data4customers.txt and data4transactions.txt are correctly
//       formatted, per the assignment requirements.
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "store.h"
using namespace std;

int main()
{
  ifstream movieFile("data4movies.txt");
  ifstream customerFile("data4customers.txt");
  ifstream commandFile("data4commands.txt");

  if (!movieFile | !customerFile | !commandFile)
  {
    cout << "Error: Unable to open file." << endl;
    return 1;
  }
  string s = "Out Of Business";
  Store store(s);
  store.setMerchandise(movieFile);
  store.setCustomers(customerFile);
  store.setCommands(commandFile);
  return 0;
}
