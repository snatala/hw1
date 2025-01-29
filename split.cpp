/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE

  //check if in is empty
  if(in == nullptr){
    return;
  }

  // store the next node and remove current node from inputted list
  Node* temp = in->next;

  if(in->value%2 == 0){ // even value?
    // add current node to evens list
    in->next = evens; 
    evens = in;
  } else{ // odd value?
    // add current node to evens list
    in->next = odds;
    odds = in;
  }

  // input pointer becomes the rest of the list
  in = temp;

  // process the remaining list recursively
  split(in, odds, evens);
}

/* If you needed a helper function, write it here */


