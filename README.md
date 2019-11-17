# Hashing-Illinois-licence-plates

Implementation of hash table for speciallized IL license plates.
Functions "Search" and  "Insert" are based on linear probing to store accumulate tickets fees for each licence plate. 
It is assumed that collisions are handled using probing.

After tickets and corresponting total of fines were stored program write an output file
with all the record. 

# Tickets format

Original tickets and fine amount information are provided in "tickets#.txt" file where
fine ammount is followed by licence plate number. 
Plate numbers can be repeated in original tickets file.

There are 2 type of speciallize license plates: 

  I) Personalized:
 
      Letters and numbers, with a space between the letters and numbers.  
      Format: 1-5 letters plus 1..99  *OR*  6 letters plus 1..9
      Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3

  II) Vanity:
      
      Format: 1-3 numbers *OR* 1-7 letters
      Examples: 007, 1, 42, X, AAA, ZZZEFGH
      

