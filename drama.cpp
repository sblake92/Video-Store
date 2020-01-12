//-------------------------------drama.cpp------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019/2019
//Modified: 03/06/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for a Drama genre Movie object. This class is
//         designed to be the child class of a Movie, and uses several of its
//         inherited functions. However, because parameters in which this
//         class is considered to be "sorted," it defines its own comparison
//         for less than.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#include "drama.h"
using namespace std;

//-------------------------------Drama()-------------------------------------
//Description: Empty Constructor - Calls constructor of parent class, Movie,
//             and default values for private variables of Classic.
//---------------------------------------------------------------------------
Drama::Drama()
: Movie()
{
} //end of Drama()

//-------------------------------Drama(istream)------------------------------
//Description: Full Constructor - Calls constructor of parent class, Movie,
//             and passes in the istream file to it for creation.
//---------------------------------------------------------------------------
Drama::Drama(istream &movieFile)
: Movie(movieFile)
{
} //end of Drama(istream)

//------------------------------Drama(string, string)------------------------
//Description: Partial Constructor - Sets the title and director's name.
//             Specifically used for the Transaction class when needed
//             to create a Drama with only sorting parameters.
//---------------------------------------------------------------------------
Drama::Drama(const string& director, const string& title)
: Movie()
{
  this->director = director;
  this->title = title;
} //end of Drama(string, string)

//------------------------------~Drama---------------------------------------
//Description: Deconstructor.
//---------------------------------------------------------------------------
Drama::~Drama()
{
} //end of ~Drama

//----------------------------displayHeader----------------------------------
//Description: Public function - Output function to format a header above
//             a list of Drama movies. Calls the parent class, Movie, to
//             display the common attributes underneath.
//---------------------------------------------------------------------------
void Drama::displayHeader() const
{
  cout << "(IN) (OUT)                    DRAMA" << endl;
  Movie::displayHeader();
} //end of displayHeader

//-------------------------------operator<-----------------------------------
//Description: Operator overload - Used to compare Drama movies for the
//             purpose of sorting. Conditions for "sorted" are defined by
//             the project requirements: first by director, then by title.
//---------------------------------------------------------------------------
bool Drama::operator<(const Merchandise &drama) const
{
  const Drama& aDrama = static_cast<const Drama&>(drama); //Casts the Merchandise
  if (director < aDrama.getDirector())                    //object to a Drama
  {                                                       //in order to compare
    return true;
  }
  else if (director == aDrama.getDirector())
  {
    return (title < aDrama.getTitle());
  }
  else
  {
    return false;
  }
} //end of operator<

//------------------------------operator==-----------------------------------
//Description: Operator overload - Used to compare two Drama movies based
//             on the parameters used to sort; title and director.
//---------------------------------------------------------------------------
bool Drama::operator==(const Merchandise &merch) const
{
  const Drama& drama = static_cast<const Drama&>(merch);
  return (title == drama.getTitle() && director == drama.getDirector());
} //end of operator==

//----------------------------- displayForHistory ----------------------------------------------------------------------
// Description: function displays formatted output for customer's history
//----------------------------------------------------------------------------------------------------------------------
void Drama::displayForHistory () const
{
  Movie::displayForHistory();
  cout << "DRAMA\nTITLE: " << this->title << " | DIRECTOR: " << this->director;
  cout << " | YEAR RELEASED: " << this->releasedYear << endl;
} // End of displayForHistory
