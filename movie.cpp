//--------------------------------movie.h------------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for a Movie object. This class is designed
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
#include "movie.h"
using namespace std;

//--------------------------------Movie()------------------------------------
//Description: Empty Constructor - Calls constructor of parent class, Merchandise,
//             and sets default values for variables of Movie.
//---------------------------------------------------------------------------
Movie::Movie()
: Merchandise(), director(""), title(""), releasedYear(0)
{
} //end of Movie()

//--------------------------------Movie(istream)-----------------------------
//Description: Full Constructor - Receives an istream file containing formatted
//             data for movies, and calls its protected helper function, setData
//             to set each data value for the movie.
//---------------------------------------------------------------------------
Movie::Movie(istream &movieFile)
{
  setData(movieFile);
} //end of Movie(istream)

//--------------------------------~Movie-------------------------------------
//Description: Deconstructor.
//---------------------------------------------------------------------------
Movie::~Movie()
{
} //end of ~Movie

//-------------------------------setData-------------------------------------
//Description: Protected function - Receives an istream object (text file), and
//             inserts the director, title and year into the movie's private
//             data variables. Assumption: The text file is formatted properly.
//---------------------------------------------------------------------------
void Movie::setData(istream& movieFile)
{
  movieFile.get();                         //Discards whitespace
  getline(movieFile, this->director, ','); //Grabs and inserts director
  movieFile.get();                         //Discards whitespace
  getline(movieFile, this->title, ',');    //Grabs and inserts title
  movieFile.get();                         //Discards whitespace
  movieFile >> releasedYear;               //Grabs and inserts year
} //end of setData

//-----------------------------getDirector-----------------------------------
//Description: Public function - Returns the name of the director.
//---------------------------------------------------------------------------
string Movie::getDirector() const
{
  return this->director;
} //end of getDirector

//--------------------------------getTitle-----------------------------------
//Description: Public function - Returns the title of the movie.
//---------------------------------------------------------------------------
string Movie::getTitle() const
{
  return this->title;
} //end of getTitle

//---------------------------------getYear-----------------------------------
//Description: Public function - Returns the year the movie released.
//---------------------------------------------------------------------------
int Movie::getYear() const
{
  return this->releasedYear;
} //end of getYear

//-------------------------------display-------------------------------------
//Description: Public function - Helper function for output operator to
//             display formatted information of the merchandise.
//---------------------------------------------------------------------------
ostream& Movie::display(ostream& output) const
{
  output << " " << left << setw(6) << stock << setw(5) << maxStock - stock << setw(4);
  output << setw(34) << title << setw(21) << director << setw(5);
  output << releasedYear << endl;
  return output;
} //end of display

//----------------------------displayHeader----------------------------------
//Description: Public function - Output function to format a header above
//             Movie information. Only for Drama and Comedy at the moment.
//---------------------------------------------------------------------------
void Movie::displayHeader() const
{
  cout << format << "   " << format << "   TITLE                             DIRECTOR";
  cout << "             YEAR" << endl;
} //end of displayHeader

//----------------------------- displayForHistory ----------------------------------------------------------------------
// Description: function displays formatted output for customer's history
//----------------------------------------------------------------------------------------------------------------------
void Movie::displayForHistory() const
{
  Merchandise::displayForHistory();
} // End of displayForHistory
