//--------------------------------classic.h----------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Header file for a Classic genre Movie object. This class
//         is designed to be the child class of a Movie, however, it does
//         not use many of the inherited functions because of the unique
//         attributes of a Classic movie. This class defines its own comparing
//         and display functions, and overrides the Movie class.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#ifndef CLASSIC_H
#define CLASSIC_H
#include <iostream>
#include <iomanip>
#include "movie.h"
using namespace std;

class Classic: public Movie
{
public:
  //Constructors
  Classic();
  Classic(const int&, const int&, const string&);
  Classic(istream&);
  ~Classic();
  //Getters
  string getActorName() const;
  int getMonth() const;
  virtual ostream& display(ostream&) const;
  virtual void displayHeader() const;
  virtual void displayForHistory() const;
  //Operator Overloads
  virtual bool operator==(const Merchandise&) const;
  virtual bool operator<(const Merchandise&) const;
private:
  string actorName;
  int releasedMonth;
  virtual void setData(istream&);
};
#endif
