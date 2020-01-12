//--------------------------------movie.h------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Header file for a Movie object. This class is designed
//         as a parent class for all movie items in the store. It tracks
//         common attributes of movies: the director, the title and the year
//         it was released. It also contains methods for receiving and
//         displaying those attributes. As per the scope of this project,
//         only Drama and Comedy movies are utilizing those common methods.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <iomanip>
#include "merchandise.h"
using namespace std;

class Movie: public Merchandise
{
public:
  //Constructors
  Movie();
  Movie(istream&);
  virtual ~Movie();
  //Getters
  string getDirector() const;
  string getTitle() const;
  int getYear() const;
  virtual ostream& display(ostream&) const;
  virtual void displayHeader() const;
  virtual void displayForHistory() const;
  //Operator Overloads
  virtual bool operator==(const Merchandise&) const = 0;
  virtual bool operator<(const Merchandise&) const = 0;
protected:
  string director;
  string title;
  int releasedYear;
  virtual void setData(istream&);
};
#endif
