//--------------------------------comedy.cpp---------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for a Comedy genre Movie object. This class is
//         designed to be the child class of a Movie, and uses several of its
//         inherited functions. However, because parameters in which this
//         class is considered to be "sorted," it defines its own comparison
//         for less than.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#include "comedy.h"
using namespace std;

//-------------------------------Comedy()------------------------------------
//Description: Empty Constructor - Calls constructor of parent class, Movie,
//             and default values for private variables of Classic.
//---------------------------------------------------------------------------
Comedy::Comedy()
: Movie()
{
} //end of Comedy()

//-------------------------------Comedy(istream)-----------------------------
//Description: Full Constructor - Calls constructor of parent class, Movie,
//             and passes in the istream file to it for creation.
//---------------------------------------------------------------------------
Comedy::Comedy(istream &movieFile)
: Movie(movieFile)
{
} //end of Comedy(istream)

//------------------------------Comedy(string, int)--------------------------
//Description: Partial Constructor - Sets the title and year released.
//             Specifically used for the Transaction class when needed
//             to create a Comedy with only sorting parameters.
//---------------------------------------------------------------------------
Comedy::Comedy(const string& title, const int& releasedYear)
: Movie()
{
  this->title = title;
  this->releasedYear = releasedYear;
} //end of Comedy(string, int)

//------------------------------~Comedy--------------------------------------
//Description: Deconstructor.
//---------------------------------------------------------------------------
Comedy::~Comedy()
{
} //end of ~Comedy

//----------------------------displayHeader----------------------------------
//Description: Public function - Output function to format a header above
//             a list of Comedy movies. Calls the parent class, Movie, to
//             display the common attributes underneath.
//---------------------------------------------------------------------------
void Comedy::displayHeader() const
{
  cout << "(IN) (OUT)                    COMEDY" << endl;
  Movie::displayHeader();
} //end of displayHeader

//-------------------------------operator<-----------------------------------
//Description: Operator overload - Used to compare Comedy movies for the
//             purpose of sorting. Conditions for "sorted" are defined by
//             the project requirements: first by title, then by year released.
//---------------------------------------------------------------------------
bool Comedy::operator<(const Merchandise &comedy) const
{
  const Comedy& aComedy = static_cast<const Comedy&>(comedy); //Cast the Merchandise
  if (title < aComedy.getTitle())                             //object to a Comedy
  {                                                           //in order to compare
    return true;
  }
  else if (title == aComedy.getTitle())
  {
    return (releasedYear < aComedy.getYear());
  }
  else
  {
    return false;
  }
} //end of operator<

//------------------------------operator==-----------------------------------
//Description: Operator overload - Used to compare two Comedy movies based
//             on the parameters used to sort; title and year released.
//---------------------------------------------------------------------------
bool Comedy::operator==(const Merchandise &merch) const
{
  const Comedy& comedy = static_cast<const Comedy&>(merch);
  return (title == comedy.getTitle() && releasedYear == comedy.getYear());
} //end of operator==

//----------------------------- displayForHistory ----------------------------------------------------------------------
// Description: Public function - Displays formatted output for customer's history
//----------------------------------------------------------------------------------------------------------------------
void Comedy::displayForHistory() const
{
  Movie::displayForHistory();
  cout << "COMEDY\nTITLE: " << this->title << " | DIRECTOR: " << this->director;
  cout << " | YEAR RELEASED: " << this->releasedYear << endl;
} // End of displayForHistory
