/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// <<Aleksandra Dmtrieva  >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#include "ILplates.h"

using namespace std;


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//

bool isUpper(string letters)
{
    bool allcaps = true;
    for (int i = 0; i < letters.size(); ++i)
    {
		if(!isupper(letters[i]) || !isalpha(letters[i]))
		{
			allcaps = false;
			break;
		} 
    }
    return allcaps;
}

bool allDigits(string digits)
{
    bool alldigits = true;

    for (int i = 0; i < digits.size(); i++)
    {
        if(!isdigit(digits[i]))
        {
            alldigits = false;
            break;
        }
    }
    return alldigits;
}

bool valid (string plate)
{
    int space = plate.find(" "); // find space position 
    int strLen = plate.length(); // get string len
    string letters, digits; 
	
    if (space == -1 ) // if there is no spaces
    {
		
		if (strLen > 7) 
		{
			return false;
		}	
        if (strLen < 4 && allDigits(plate)) //if string is 1-3 char and all digits
        {
            return true;
        }
        else if (strLen < 8  && isUpper(plate)) // if string is all caps and 1 -6 letters
        {
            return true;
        }

    }
	else if(strLen > 8)// Check string length no longer then 8
	{
		return false;
	}
    else if(strLen -1 - space > 2) // if more then 2 chars after space
    {
        return false;
    }
    else if (space == 6) // if 1-6 letters an 1 digit
    {
        letters = plate.substr(0,6);
        if (isUpper(letters) && isdigit(plate[7]) )
        {
            return true;
        }
    }
    else  // 1-5 caps letters and 1..99 number
    {
        letters = plate.substr(0, space);
        digits = plate.substr(space+1);

        if (isUpper(letters) && allDigits(digits)) 
        {
            return true;
        }
    }
	return false;
}



int ILplates::Hash(string plate)
{
    int index = -1;
    int stringSize = plate.size();
	unsigned long long int total = 0;

	if (valid(plate))
	{
		if (allDigits(plate))
		{
			total = stoi(plate);
		}
		else 
		{
			for (int i =0; i < stringSize; i ++)
			{
				total += plate[i]*pow(36,i);
			}
		}
		
		index = total % HT.Size();
	}
    return index ;
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
    int index = Hash(plate);
    int indexProbed = 0;

    bool empty;
    string key;
    int value = -1;


    HT.Get(index, empty, key, value);  // find the hashtable values at the index position

    while (!empty && indexProbed < HT.Size())
    {
		if (!empty && key == plate)
		{
			return value;
		}

		if (index < HT.Size())
			index++;
		else
			index = 0;  // reset

		HT.Get(index, empty, key, value);
		indexProbed++;
    }

    return value;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  int index = Hash(plate);
  int indexProbed = 0; // keep track of probed indexes

  // Values at index:
  bool empty;
  string key;
  int value;


  while (indexProbed < HT.Size()) //go through the hashtable till the end
  {

      HT.Get(index, empty, key, value); // find the hashtable values at the index position
      
      if (empty) // if position is empty insert key value pair end the loop
      {
          HT.Set(index, plate, newValue);
          break;

      }else if (plate == key) // if position is not empty check the plate # if the same change increase fine value.
      {
          HT.Set(index, plate, newValue); // overwrite hashtable value
          break;         // end the loop
      }

      // go to the next index
      if (index < HT.Size())
          index++;
      // if index reaches the end of hash table start over.
      else
          index = 0;

      indexProbed++; // increment local # of probes

  }


}
