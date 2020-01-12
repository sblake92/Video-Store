//------------------------------merchandise.h--------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Header file for a Merchandise object. This class is
//         designed as a parent class for any sellable or rentable item
//         in the store. It tracks the stock of each item and for Movies,
//         it keeps track of the format.
//---------------------------------------------------------------------------
//Notes: This class assumes that there are subclasses that contain the
//       information of the merchandise that is being carried in the store.
//---------------------------------------------------------------------------
#ifndef MERCHANDISE_H
#define MERCHANDISE_H
#include <iostream>
using namespace std;

class Merchandise
{
public:
  //Constructors
  Merchandise();
  virtual ~Merchandise();
  //Getters
  int getStock() const;
  virtual ostream& display(ostream&) const;
  virtual void displayHeader() const = 0;
  virtual void displayForHistory() const;
  string getFormat() const;
  inline int getMaxStock() { return maxStock; };
  //Setters
  bool increaseStock();
  bool decreaseStock();
  bool setStock(const int&);
  void setMaxStock(const int&);
  void setFormat(const string&);
  //Operator Overloads
  virtual bool operator==(const Merchandise&) const = 0;
  virtual bool operator<(const Merchandise&) const = 0;
  friend ostream& operator<<(ostream&, const Merchandise&);

protected:
  int stock;
  int maxStock;
  string format;
  virtual void setData(istream&) = 0;
};
#endif
