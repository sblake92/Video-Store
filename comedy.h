//--------------------------------comedy.h-----------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Header file for a Comedy genre Movie object. This class is
//         designed to be the child class of a Movie, and uses several of its
//         inherited functions. However, because parameters in which this
//         class is considered to be "sorted," it defines its own comparison
//         for less than.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#ifndef COMEDY_H
#define COMEDY_H
#include <iostream>
#include "movie.h"
using namespace std;

class Comedy: public Movie
{
public:
  //Constructors
  Comedy();
  Comedy(istream&);
  Comedy(const string&, const int&);
  ~Comedy();
  //Getters
  virtual void displayHeader() const;
  virtual void displayForHistory() const;
  //Operator Overloads
  virtual bool operator==(const Merchandise&) const;
  virtual bool operator<(const Merchandise&) const;
};
#endif
