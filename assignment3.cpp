// ****************************************************************************
// CS 162 -  Program #3
// Author: Jerry Chen
// Program: App Organizer
// Description: This program will read in the user's entry
//              for the information of an app, and then
//              store that app into a file based on page. When the user
//              asks for a page, they will be shown the information
//              of the apps that are stored on that page.
//
// Program Algorithm
// 1. Ask if the user wants to store apps, retrieve app
//    information, or clear a page of apps.
// Storing information:
// 1. Ask user for the name of the app.
// 2. Ask user for the description of the app.
// 3. Ask user for the folder the app is in.
// 4. Ask user for the page the app is in.
// 5. Repeat the previous steps until the user asks to stop,
//    or when the maximum app limit is reached.
// 6. Store the apps into text files based on the page they
//    are in.
// Retrieving information:
// 1. Ask user what page to check.
// 2. Return to the user the information on the apps on that page.
// Clearing a page:
// 1. Ask user what page to clear.
// 2. Clear the page requested.
// ***************************************************************************

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;
//constants for the length of arrays
const int PAGE = 5;
const int DESC = 50;
const int NAME = 50;
const int FOLDER = 50;
const int LIST = 11;
const int PNUM = 20;

//This is the application struct
struct app
{
  char page[PAGE];
  char description[DESC];
  char name[NAME];
  char folder[FOLDER];
};

//readIn will start the process of asking the user for app info
void readIn(app list[], int count);
//readName reads in the name of the app
void readName(app list[], int count);
//readDescription reads in the description of the app
void readDescription(app list[], int count);
//readPage reads in the page the app is stored in
void readPage(app list[], int count);
//readFolder reads in the name of the folder the app is stored in
void readFolder(app list[], int count);
//writeOut will write the app info to a folder
void writeOut(app list[], int count);
//getInfo will retrieve app data from a file and relay it to the user
bool getInfo(app list[], int & count);
//printCurrent will print out what the user has entered in so far
void printCurrent(app list[], int count);
//flush will clear a file of apps
void flush();

//readIn will call other functions to read in app info from the user
void readIn(app list[], int count)
{
  cout << "Now reading in the app info." << endl;
  //reads name of app
  readName(list, count);
  //reads description
  readDescription(list, count);
  //reads page number
  readPage(list, count);
  //reads folder name
  readFolder(list, count);
}

//reads in name of the app
void readName(app list[], int i)
{
  cout << "Please enter name of the app: ";
  cin.get(list[(i-1)].name, NAME, '\n');
  cin.ignore(100, '\n');
}

//reads in the description of the app
void readDescription(app list[], int i)
{
  cout << "Please enter description of the app: ";
  cin.get(list[(i-1)].description, DESC, '\n');
  cin.ignore(100, '\n');
}

//reads in the folder of the app
void readFolder(app list[], int i)
{
  cout << "Please enter folder of the app: ";
  cin.get(list[(i-1)].folder, FOLDER, '\n');
  cin.ignore(100, '\n');
}

//reads in the page number of the app
void readPage(app list[], int i)
{
  cout << "Please enter page # of the app: ";
  cin.get(list[(i-1)].page, PAGE, '\n');
  cin.ignore(100, '\n');
}

//writeOut writes information to a file
void writeOut(app list[], int i)
{
  cout << "Now writing to file." << endl;
  //output stream variable
  ofstream fileOut;
  //saves the app info to the file
  for(int j = 0; j < i; ++j)
  {
    //pageCurrent stores the name of the page of the currently
    //selected app
    char pageCurrent[PNUM];
    //these following three lines will write the app
    //to a file of (page#)page.txt
    strcpy(pageCurrent, list[j].page);
    strcat(pageCurrent,"page.txt");
    fileOut.open(pageCurrent, ios::app);
    //the parameters are seperated by the newline delimeter
    fileOut << list[j].name << "\n"
            << list[j].description << "\n"
            << list[j].folder << "\n"
            << list[j].page << endl;
    fileOut.close();
    fileOut.clear();
  }
  cout << "Done writing, thank you!" << endl;
}

//getInfo reads in information from a file
bool getInfo(app list[], int & count, char pageToRead[])
{
  cout << "Now reading in from the file." << endl;
  //if there is a problem with the file, false is returned
  bool readable = true;
  //count is the number of apps
  count = 0;
  //input stream variable
  ifstream fileIn;
  fileIn.open(pageToRead);
  //if there is a problem with reading, then the user will be asked
  //to enter another number.
  if(!fileIn)
  {
    readable = false;
    cout << "No file present!" << endl << "Please try again." << endl;
    return readable;
  }
  while(!fileIn.eof()) //checks to make sure that the end of file isn't reached
  {
    //reads the appropriate fields into their respective places
    //the delimiter is the '\n' newline
    fileIn.get(list[count].name, NAME, '\n');
    fileIn.ignore(100, '\n');
    fileIn.get(list[count].description, DESC, '\n');
    fileIn.ignore(100, '\n');
    fileIn.get(list[count].folder, FOLDER, '\n');
    fileIn.ignore(100, '\n');
    fileIn >> list[count].page;
    fileIn.ignore(100, '\n');
    ++count;
  }
  //this is to ensure the proper value is passed to the printCurrent function
  count = count - 1;
  fileIn.close();
  //returns true if the read worked
  return readable;
}

//displays the apps read in recently
void printCurrent(app list[], int i)
{
  cout << "Number of apps loaded in: " << i << endl;
  for (int j = 0; j < i; ++j)
  {
    //outputs app info for each app
    cout << "Name of App #" << (j + 1) << ": " << list[j].name << endl;
    cout << "Description of App #" << (j + 1) << ": "
         << list[j].description << endl;
    cout << "Folder name of App # " << (j + 1) << ": " << list[j].folder << endl;
    cout << "On page #" << list[j].page << endl << endl << endl;
  }
}

//flush clears a file of apps
void flush()
{
  //stores user response
  char response[20];
  cout << "Enter in the page number to flush." << endl;
  cin.get(response, 20, '\n');
  cin.ignore(100, '\n');
  strcat(response, "page.txt");
  ofstream writeOut;
  writeOut.open(response);
  cout << response << " has been cleared of apps." << endl;
}

int main()
{
  app list[LIST];
  //count is number of apps
  int count = 1;
  //stores user response
  char response;
  //controls the loop on whether the user enters more apps
  bool repeat = false;
  //stores the response of the user for prompts
  char repeatRes;
  cout << "Do you want to add apps or check apps?" << endl
       << "'A' to add, 'C' to check." << endl
       << "Alternatively, press 'F' to clear a page of apps."
       << endl;

  cin  >> response;
  cin.ignore(100, '\n');
  if (toupper(response) == 'A')
  {
    //this loop will continue to ask user for apps until they reach
    //the maximum or until they answer 'n' to adding more apps
    do
    {
      readIn(list, count);
      cout << "Add another app? (Y/N)" << endl;
      cin  >> repeatRes;
      cin.ignore(100, '\n');
      //keeps the loop true, so it will go to readIn again
      if(toupper(repeatRes) == 'Y')
      {
        repeat = true;
	++count;
      }
      else
        //terminates the loop, causing it to go to printCurrent
        //and writeOut
        if (toupper(repeatRes) == 'N')
	  {
	    printCurrent(list, count);
	    writeOut(list, count);
            //kills the loop
	    repeat = false;
	  }
    //loop maintained if repeat is true, and if there are fewer than
    //11 apps entered.
    }while(repeat == true && count < 11);
  }
  else
    if (toupper(response) == 'C')
    {
      //This will read in the info if user decides not to write out.
      //If getInfo doesn't find the proper file, then it will not
      //print the output.
      //When the user decides to read from a file, they will be asked
      //which page to read from. The corresponding page will be checked
      //and the apps on there will be displayed.
      char pageNum[PNUM];
      do
      {
        cout << "What page would you like to check?" << endl;
        cout << "Page number: ";
        cin.get(pageNum, PNUM, '\n');
        cin.ignore(100, '\n');
        //reads from (page#)page.txt
        strcat(pageNum, "page.txt");
      }
      //if read is invalid, the loop is maintained and
      //user is asked to enter in another value.
      while(!getInfo(list, count, pageNum));
      printCurrent(list, count);
    }
    else
      //flush will clear a file of apps
      if (toupper(response) == 'F')
      {
        //stores user's response to flush
        char fResponse;
        cout << "Are you sure you want to clear a file of apps?"
             << "(Y/N)" << endl;
        cin  >> fResponse;
        cin.ignore(100, '\n');
        if (toupper(fResponse) == 'Y')
          flush();
        else
          cout << "Flush canceled." << endl;
      }
  return 0;
}
