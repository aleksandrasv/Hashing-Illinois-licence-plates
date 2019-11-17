/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by: << Aleksandra Dmtrieva >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;




// Swap helper functions for bubble sorting
void swapNumbers(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 
void swapPlates(string *xp, string *yp)  
{  
    string temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 

// Bubble sort function 
void sort(vector<string>& plates1, vector<int>& amounts1,  int n)  
{  
    int i, j;  
	bool swapped;
    for (i = 0; i < n-1; i++)
	{
		swapped = false;
		for (j = 0; j < n-i-1; j++)  
		{			
			if (plates1[j].compare(plates1[j+1]) > 0)  
			{
				swapPlates(&plates1[j], &plates1[j+1]);
				swapNumbers(&amounts1[j], &amounts1[j+1]);
				swapped = true;
			}
		}
		if (swapped == false) 
			break;
	}     
} 


		
//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;
   
    // 
    // is plate valid?  Only process valid plates:
    //

	if (hashplates.Hash(plate) >= 0)  // yes:
	{
		int amount = hashplates.Search(plate);

		if (amount < 0)  // not found:
		{
			hashplates.Insert(plate, stoi(fine));
		}
		else  // we found it, so update total in hash table:
		{
			amount += stoi(fine);
			hashplates.Insert(plate, amount);
		}

	}

    getline(infile, fine);
  }
}



int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";


  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;
  string outfilename = basename + "-output.txt";
  ofstream outfile(outfilename);
  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();

	// Sort plates values
	sort(plates,amounts, plates.size());
	
  for (size_t i = 0; i < plates.size(); ++i)
  {
	outfile << "\"" << plates[i] << "\"" << " $" <<amounts[i] << endl;
	  
	//Debugging
   //cout << plates[i] << ", " << amounts[i] << endl;
  }
	
	cout << endl;
	
	
  //
  // done:
  //
  return 0;
}