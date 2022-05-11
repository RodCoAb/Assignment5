// ASU CSE310 Assignment #5 (Spring 2022)
// Name of Author: Rodrigo Corrales
// ASU ID: 1216550582
// Description: A simple linked list that implements a list of Student objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>
// Imports included above.

using namespace std;

struct Student // Student Struct comprised of student details such as name, id and gpa.
{
   string firstName, lastName;
   int id;
   double gpa;
   struct Student* next = NULL;
};

class LinkedList
{
	private:
   struct Student* head;
   int size;      // a variable represents number of Students inside the list
    public:
   LinkedList();
   ~LinkedList();
   Student* getHead();
   int getSize();
   bool searchStudent(int stuID);
   bool insertStudent(string firstName, string lastName, int id, double gpa);
   bool deleteStudent(int stuID);
   void displayList();
};

//Constructor
LinkedList::LinkedList()
{ 
   size = 0; // Initializing the size of the linked list to 0
   head = NULL; // Initializing the head of the linked list to null
}

//Destructor
LinkedList::~LinkedList()
{
    Student* temp = head; // Creating a temporary pointer to help traverse the linked list.
    while(head != NULL) // While the head is not null, iterates through the list.
    {
        temp = head->next; // Pushing the "head" down
        delete temp; // Deletes the node to which the head pointer points to.
        head = temp; // Head pointer now points to temp node (i.e the next item in the linked list.)
    }
}

Student* LinkedList::getHead() // Getter function for the head variable.
{
    return head;
}

//Return number of Students inside the Linked list
int LinkedList::getSize() // Getter method for the size variable.
{
    return size;
}

//This function does a linear search on the Student list with the given student ID
//it returns true if the corresponding student is found, otherwise it returns false.
bool LinkedList::searchStudent(int stuID)
{
    Student* temp = head; // Temporary 
    if (head == NULL) // If the list is empty.
    {
        return false; // Returns false if list is empty.
    }
    while (temp != NULL) // While loop to help iterate through every element in the list.
    {
       if(temp->id == stuID) // Checks if the id at current student matches the search id.
       {
           return true; // Returns true if we have a match.
       }
       temp = temp->next; // Iterates to the next node in the list.
    }
   return false;
}

//Insert the parameter Student at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertStudent(string firstName, string lastName, int id, double gpa)
{
    Student* insertStudent = new Student(); // Allocates memory for the new student being inserted.
    insertStudent->firstName = firstName; // Sets first name.
    insertStudent->lastName = lastName; // Sets last name.
    insertStudent->id = id; // Sets id.
    insertStudent->gpa = gpa; // Sets the gpa.
    
    if (head == NULL) // Checks if the list is empty.
    {
        head = insertStudent; // Our new student is now the head.
        size++; // Incrementing the size of the list.
        return true;
    }
    else // If the list is not empty.
    {
        insertStudent->next = head; // We make new student.next point to head, then head becomes new student.
        head = insertStudent; // Our new students is now the head.
        size++; // Incrementing the size of the list.
        return true;
    }
    return false;
}

//Delete the Student with the given student ID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteStudent(int stuID)
{
    Student* temp = head; // Temp variable equal to head.
    Student* tempDelete = NULL; // Temporary variable to hold the value of the student to be deleted.
    Student* previous = head; // previous pointer to help us keep track of the previous node.
    if (head == NULL) // Checks if list is empty.
    {
        return false; 
    }
    else // If list is not empty.
    {
       if (head->id == stuID) // If head is the one we need to delete.
       {
           head = head->next; // Scoots the head down.
           delete temp; // Deletes the "new" head.
           size--; // Decrements the size of the list after deleting.
           return true;
       }
       temp = temp->next; // Iterates to the next node in the list
       while (temp != NULL) // While the list is not empty.
       {
           
           if (temp->id == stuID) // If the next student is the one we need to delete.
           {
               tempDelete = temp; // We set tempDelete to the student that we need to delete. 
               previous->next = temp->next; // Connects the nodes 
               delete tempDelete; // Deletes the node we needed.
               size--;
               return true;
           }
           previous = temp;
           temp = temp->next; // Iterates to the next student on the list.
       }
       return false;
    }
}
//This function displays the content of the linked list.
void LinkedList::displayList()
{
   Student *temp = head;
   if(head == NULL)
   {
   	  return;  //empty linked list, print nothing here
   }
   else
   {
      while(temp != NULL) // While list is not null, iterates through each student and prints them using the format below.
      {
         cout << left    << setw(12) << temp->firstName
              << left    << setw(12) << temp->lastName
              << right   << setw(8)  << temp->id
              << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
         temp = temp->next;
      }
   }
}
