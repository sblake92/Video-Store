//--------------------------------classic.cpp--------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for a Classic genre Movie object. This class
//         is designed to be the child class of a Movie, however, it does
//         not use many of the inherited functions because of the unique
//         attributes of a Classic movie. This class defines its own comparing
//         and display functions, and overrides the Movie class.
//---------------------------------------------------------------------------
//Notes: The constructor and setData functions assume that the incoming
//       istream file is well-formatted, and that the buffer is at the
//       correct position for reading the next item.
//---------------------------------------------------------------------------
#include "classic.h"
using namespace std;

//------------------------------Classic()------------------------------------
//Description: Empty Constructor - Calls constructor of parent class, Movie,
//             and default values for private variables of Classic.
//---------------------------------------------------------------------------
Classic::Classic()
: Movie(), actorName(""), releasedMonth(0)
{
} //end of Classic()

//------------------------------Classic(istream)-----------------------------
//Description: Full Constructor - Calls private helper function to set the
//             formatted incoming Classic movie data.
//---------------------------------------------------------------------------
Classic::Classic(istream &movieFile)
{
  setData(movieFile);
} //end of Classic(istream)

//---------------------------Classic(int, int, string)-----------------------
//Description: Partial Constructor - Sets the month and year released, also
//             sets the actor's name. Specifically used for the Transaction
//             class when needed to create a Classic with only sorting parameters.
//---------------------------------------------------------------------------
Classic::Classic(const int& releasedMonth, const int& releasedYear, const string& actorName)
: Movie()
{
  this->releasedMonth = releasedMonth;
  this->releasedYear = releasedYear;
  this->actorName = actorName;
} //end of Classic(int, int, string)

//-----------------------------~Classic--------------------------------------
//Description: Deconstructor.
//---------------------------------------------------------------------------
Classic::~Classic()
{
} //end of ~Classic

//------------------------------setData--------------------------------------
//Description: Private function - Receives an istream file and parses the
//             movie data into the Classic and Movie objects. Assumes the
//             data is well-formatted and that the buffer for the istream
//             file is in the proper location.
//---------------------------------------------------------------------------
void Classic::setData(istream& movieFile)
{
  string actorFirstName, actorLastName;
  movieFile.get();                         //Discards whitespace
  getline(movieFile, director, ',');       //Grabs and inserts director
  movieFile.get();                         //Discards whitespace
  getline(movieFile, title, ',');          //Grabs and inserts title
  movieFile.get();                         //Discards whitespace
  movieFile >> actorFirstName >> actorLastName >> releasedMonth >> releasedYear;
  actorName = actorFirstName + " " + actorLastName; //Grabs and inserts actor's
} //end of setData              name, month and year and creates 1 string for name

//----------------------------getActorName-----------------------------------
//Description: Public function - Returns actor's name.
//---------------------------------------------------------------------------
string Classic::getActorName() const
{
  return this->actorName;
} //end of getActorName

//-----------------------------getMonth--------------------------------------
//Description: Public function - Returns month the movie was released.
//---------------------------------------------------------------------------
int Classic::getMonth() const
{
  return this->releasedMonth;
} //end of getMonth

//------------------------------operator==-----------------------------------
//Description: Operator overload - Compares the current Classic with the
//             incoming Classic to determine if they are the same. Returns
//             true if yes, false if no.
//---------------------------------------------------------------------------
bool Classic::operator==(const Merchandise& merch) const
{ //Cast the merchandise object to a Classic in order to compare
  const Classic& classic = static_cast<const Classic&>(merch);
  return (releasedYear == classic.getYear() &&
			releasedMonth == classic.getMonth() &&
			actorName == classic.getActorName());
} //end of operator==

//------------------------------operator<------------------------------------
//Description: Operator overload - Used to compare Classic movies for the
//             purpose of sorting. Conditions for "sorted" are defined by
//             the project requirements: first by release date, then by major
//             actor.
//---------------------------------------------------------------------------
bool Classic::operator<(const Merchandise& merch) const
{
  const Classic& classic = static_cast<const Classic&>(merch); //Cast the Merchandise
  if (releasedYear < classic.getYear())                        //object to a Classic
  {                                                            //in order to compare
    return true;
  }
  else if (releasedYear == classic.getYear())
  {
    if (releasedMonth < classic.getMonth())
    {
      return true;
    }
    else if (releasedMonth == classic.getMonth())
    {
      if (actorName < classic.getActorName())
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
} //end of operator<

//---------------------------------display-----------------------------------
//Description: Public function - Returns ostream back to parent class for
//             printing.
//---------------------------------------------------------------------------
ostream& Classic::display(ostream& output) const
{
  output << " " << left << setw(6) << stock << setw(5) << maxStock - stock << setw(4);
  output << setw(27) << title << setw(19) << director;
  output << setw(20) << actorName << releasedYear << "    " << releasedMonth << endl;
  return output;
} //end of display

//----------------------------displayHeader----------------------------------
//Description: Public function - Output function to format a header above
//             a list of Classic movies.
//---------------------------------------------------------------------------
void Classic::displayHeader() const
{
  cout << "(IN) (OUT)                    CLASSIC" << endl;
  cout << format << "   " << format << "   TITLE                      DIRECTOR";
  cout << "           ACTOR               YEAR  MONTH" << endl;
} //end of displayHeader

//----------------------------- displayForHistory ----------------------------------------------------------------------
// Description: function displays formatted output for customer's history
//----------------------------------------------------------------------------------------------------------------------
void Classic::displayForHistory() const
{
  Movie::displayForHistory();
  cout << "CLASSIC\nTITLE: " << this->title <<" | DIRECTOR: " << this->director;
  cout << " | MAJOR ACTOR: " << this->actorName << " | DATE RELEASED: " << this->releasedMonth;
  cout << " " << this->releasedYear << endl;
} // End of displayForHistory
