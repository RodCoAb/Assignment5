// ASU CSE310 Assignment #5 Spring 2022
// Name of Author: Rodrigo Corrales
// ASU ID: 1216550582
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
// Imports detailed above.
using namespace std;

class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
   
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string firstName, string lastName, int id);
      bool hashInsert(string firstName, string lastName, int id, double gpa);
      bool hashDelete(string firstName, string lastName, int id);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
      //int createHashKey(string firstName, string lastName, int id);
  };

//constructor
Hash::Hash(int size)
{
   m = size;  // Updates int m and makes it of size hash table also.
   hashTable = new LinkedList[m]; // Creates hashtable of "LinkedList size"
}

//Destructor
Hash::~Hash() 
{
   for (int i = 0; i < m; i++) // Iterates through the array.
   {
      hashTable[i].~LinkedList(); // Deletes the linked list at the particular array index.
   }
   delete[] hashTable; // Deletes the whole array.
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashSearch(string firstName, string lastName, int id)
{
  // bool found = false; // Given
   string key = firstName + lastName + to_string(id); // String key is the combination of first and last name as well as id number.
   int index = hashFunction(key); // Returns the index to be hashed at and saves it into variable index.

   if (hashTable[index].searchStudent(id) == true) // Checking if the hashTable at that index finds the student with the given id
   {
      cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8)  << id
            << " is found inside the hash table." << endl;
            return true;
   }
   else // If the student with the given id is not found.
   {
      cout << "\n" << left
           << setw(12) << firstName
           << setw(12) << lastName
           << setw(8)  << id
           << " is NOT found inside the hash table." << endl;
   }
   return false;
}

//hashInsert inserts a Student with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string firstName, string lastName, int id, double gpa)
{
   string key = firstName + lastName + to_string(id); // String key holding first and last name as well as id number.
   int index = hashFunction(key); // Integer Index that holds the index to which we will be hashing.
   
   if (hashTable[index].insertStudent(firstName, lastName, id, gpa) == true) // If statement that checks if the hashTable at that index inserts the student with the given details successfully.
   {
      return true; 
   }
   else // If the student it not inserted properly, return false.
      return false;
}

//hashDelete deletes a Student with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashDelete(string firstName, string lastName, int id)
{
   string key = firstName + lastName + to_string(id); // Creates the key with the parameters needed
   int index = hashFunction(key); // Variable holding the index the hash funciton hashes to.

   if (hashTable[index].searchStudent(id) == true) // If the hash table at that index finds the student we want to delete.
   {
      cout << "\n" << left
            << setw(12) << firstName
            << setw(12) << lastName
            << setw(8)  << id
            << " is found inside the hash table." << endl; 
      hashTable->deleteStudent(id); // Call to delete the particular student.
      cout << "\n";
      cout << setw(12) << firstName
           << setw(12) << lastName
           << setw(8)  << id
           << " is deleted from hash table." << endl;
      return true;
   }
   else // If the student was not found/deleted from the hash table.
   {
      cout << "\n" << left
           << setw(12) << firstName
           << setw(12) << lastName
           << setw(8)  << id
           << " is NOT found inside the hash table." << endl;
      cout << "\n";
      cout << setw(12) << firstName
           << setw(12) << lastName
           << setw(8)  << id
           << " is NOT deleted from hash table." << endl;
      return false;
   }
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
   int largest = 0; // Declared largest to 0. Will hold the biggest linked list.
   for (int i = 0; i < m; i++) // Iterating through each slot.
   {
      if(hashTable[i].getSize() > largest) // If the current slot linked list > largest
      {
         largest = hashTable[i].getSize(); // We update largest to hold this particular linked list size.
      }
   }
   return largest; // Return the largest linked list size.
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
  for (int i = 0; i < m; i++) // Iterates though the array.
  {
     if (hashTable[i].getHead() == NULL) // Checks if the head is null.
     {
        cout << "\nHashTable[" << i << "] is empty, size = 0" << endl;
     }
     else
     {
        cout << "\nHashTable[" << i << "], " << "size = " << hashTable[i].getSize() << endl;
        hashTable[i].displayList(); // We call the display method at that index to print out the corresponding list.
     }
  }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
   int finalVal = 0; // Declaring an int that will hold the sum of the ascii values of the key string.
   for (int i = 0; i < key.length(); i++) // For loop to traverse each char of the string
   {
      finalVal += (int)key[i]; // Adds up every ascii value in the string into a variable.
   }
   return (finalVal % m); // Returns the index that the key is being hashed to.
}

//-------------------------------------------------------------------------------------------------------------------------------------//
