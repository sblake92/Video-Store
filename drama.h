//--------------------------------drama.h------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/20199
//---------------------------------------------------------------------------
//Purpose:
//---------------------------------------------------------------------------
//Notes:
//---------------------------------------------------------------------------
#ifndef DRAMA_H
#define DRAMA_H
#include <iostream>
#include "movie.h"
using namespace std;

class Drama: public Movie
{
public:
  //Constructors
  Drama();
  Drama(istream&);
  Drama(const string&, const string&);
  ~Drama();
  //Getters
  virtual void displayHeader() const;
  virtual void displayForHistory() const;
  //Operator Overloads
  virtual bool operator==(const Merchandise&) const;
  virtual bool operator<(const Merchandise&) const;
};
#endif
