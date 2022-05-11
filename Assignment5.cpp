// ASU CSE310 Assignment #5 Spring 2022
// Name of Author: Rodrigo Corrales
// ASU ID: 1216550582
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Student
//   object's hash value.
1. My hash function is the sum of every ascii value in the key string mod hash table size. By doing the 
mod operation, we return an integer that acts as the index of the hash table to which we can hash to.
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.

Test Case 1: The performance ratio was 1.67 and the longest linked list size was 5.
Test Case 2: The performance ratio was 1.83 and the longest linked list size was 6.
Test Case 3: The performance ratio was 1.54 and the longest linked list size was 7.
Test Case 4: The performance ration was 1.85 and the longest linked list size was 12.

I think my hash function was serviceable, but perhaps less collisions could have been achieved.

//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?

I would change the hash function by making it a bit less predictable. People with different last names that contain the same letters and similar ids would 
be causing collisions, since I dealt with ASCII values. Perhaps a different approach (i.e multiplying by some number, then mod size) could prove to be a more
optimized solution.
********************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include "Hash.h"

// imports happen right above^

using namespace std;

//This function used to get a Student key which is the combination of firstName, lastName and id
void getKey(string oneLine, string& command, string& firstName, string& lastName, int& id);
void parser(string oneLine, string& firstName, string& lastName, int& id, double& gpa); // Modified getKey function to pass in students.

int main()
{
   int size = 0;
   int numOfCommand = 0;
   string firstName, lastName;
   int id;
   double gpa;
   //Given.
   //declare any other necessary variables here
   
   int insertionCounter = 0; // Keeps track of students being inserted.
   string firstToken; // To be used for commands such as hashDisplay and hashLoadFactor
   string command, input; // Strings to pass in student details/hold commands with multiple commas.

   cout << "Enter the size of the hash table: ";   
   cin >> size;
   cin.ignore(20, '\n');

   //Instantiate the hash table with the relevant number of slots
   Hash* someHashTable = new Hash(size);
   do 
   {
         //use this do..while loop to repreatly get one line Student info. and extract tokens
         //create one Student object and insert it inside the hashTable until seeing the message
         //"InsertionEnd" to terminate
         getline(cin, input); // Gets details.
         if (input.compare("InsertionEnd") == 0) // Checking if InsertionEnd is entered.
         { 
            break; // Exits the loop if conditions are met.
         } 
         else
         {
            parser(input, firstName, lastName, id, gpa); // Utilizing modified getkey function to save student details.
            someHashTable->hashInsert(firstName, lastName, id, gpa); // Inserting students to the hash table.
            insertionCounter++; // Increments variable that tracks number of students input.
         }
   } 
   while(true);

	cout << "\nEnter number of commands: ";   //***need to comment out in submitting
   cin >> numOfCommand;
   cin.ignore(20, '\n');

   for(int i = 0; i < numOfCommand; i++)
   {
       cin >> firstToken; // Retrieves command.
   	//get one line command, extract the first token, if only one token
      if(firstToken.compare("hashDisplay") == 0) // If the command is hashDisplay.
      {
         someHashTable->hashDisplay(); // Calls hashDisplay.
      }   
      else if(firstToken.compare("hashLoadFactor") == 0) // If the command is hashLoadFactor.
      {
        double idealLoadFactor = (double)insertionCounter/(double)size; // Calculating the ideal load factor.
        double actualLoadFactor = someHashTable->hashLoadFactor(); // We got the real load factor by calling the function on our hashtable.
        double performance_ratio = actualLoadFactor/idealLoadFactor; // Performance ratio calculated.
      
        // Print out statements below, formatted to two decimal places.
        cout << "\nThe ideal load factor is: " << fixed << setprecision(2) << idealLoadFactor << endl;
        cout << "My hash table real load factor is: " << fixed << setprecision(2) << actualLoadFactor << endl;
        cout << "My hash table performance ratio is: " << fixed << setprecision(2) << performance_ratio << endl;
      }
      else  //more than one tokens, check the command name, extract the remaining tokens
      {
         getKey(firstToken, command, firstName, lastName, id); // Calls getKey if there are commas present in input string.
         if(command.compare("hashSearch") == 0) 
         {
            someHashTable->hashSearch(firstName, lastName, id); // Calls hashSearch.
         }
         else if(command.compare("hashDelete") == 0)
         {
            if(someHashTable->hashDelete(firstName, lastName, id)) // If we delete successfully.
            {
               insertionCounter--; // Updates the student input size if we delete successfully.
            };
         }
         else
            cout << "Invalid command"<<endl;
      }
   } //end for loop
   return 0;
}

//****************************************************************************************
//Given one line, this function extracts the firstName, lastName, id info. of a Student
//This function is completed and given here as a study guide for extracting tokens
void getKey(string oneLine, string& command, string& firstName, string& lastName, int& id)
{
   string delimiter = ",";
   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
}

void parser(string oneLine, string& firstName, string& lastName, int& id, double& gpa) // Modified getKey method to take in the gpa parameter for students.
{
   string delimiter = ",";
   
   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   pos = oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   gpa = stod(token);
   oneLine.erase(0, pos+delimiter.length());
}
