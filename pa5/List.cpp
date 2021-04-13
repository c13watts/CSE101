/****************************************************************************************
*  Cole Watts
*  comwatts
*  PA5
*  List.cpp
*  Implementation file for List ADT
*****************************************************************************************/

#include<iostream>
#include<string>

#include"List.h"

using namespace std;

List::Node::Node(int x)
{
   data = x;
   next = nullptr;
   prev = nullptr;
}

List::List()
{
   backDummy = new Node(0);
   frontDummy = new Node(0);

   backDummy->prev = frontDummy;
   frontDummy->next = backDummy;
   
   afterCursor = backDummy;
   beforeCursor = frontDummy;
   
   num_elements = 0;
   pos_cursor = 0;
}


List::List(const List& L)
{
   backDummy = new Node(0);
   frontDummy = new Node(0);

   backDummy->prev = frontDummy;
   frontDummy->next = backDummy;

   afterCursor = backDummy;
   beforeCursor = frontDummy;

   num_elements = 0;
   pos_cursor = 0;

   Node* newNode1 = L.frontDummy->next;
   Node* newNode2 = L.backDummy;

   if( newNode1 == newNode2)
   {
      cerr << "Test" << endl;
   }

   while( newNode1 != newNode2 )
   {
      insertBefore(newNode1->data);
      newNode1 = newNode1->next;
   }

   moveFront();
}

List::~List()
{ 
   clear();
   delete frontDummy;
   delete backDummy;
}

bool List::isEmpty()
{
   if( num_elements == 0 )
   {
      cerr << "Returned true: List is empty" << endl;
      return true;
   }

   else
   {
      cerr << "Returned false: List is not empty" << endl;
      return false;
   }
}

int List::position()
{
   cerr << "The position of the cursor in the List is " << pos_cursor << endl;
   return(pos_cursor);
}

int List::size()
{
   cerr << "The size of the List is " << num_elements << endl;
   return(num_elements);
}

int List::peekPrev()
{
   int returnNext = beforeCursor->data;
   return returnNext;
}

int List::peekNext()
{
   int returnAfter = afterCursor->data;
   return returnAfter;
}

void List::moveBack()
{
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   
   pos_cursor = size();
}

void List::moveFront()
{
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;

   pos_cursor = 0;
}

void List::insertAfter(int x)
{
   Node* N = new Node(x);

   if (position() < 0)
   {
      cerr << "Error: Could not insert x after cursor" << endl;
      exit(EXIT_FAILURE);
   }

   if (afterCursor < 0)
   {
      cerr << "Error: Could not insert x after cursor" << endl;
      exit(EXIT_FAILURE);
   }

   if (beforeCursor < 0)
   {
      cerr << "Error: Could not insert x after cursor" << endl;
      exit(EXIT_FAILURE);
   }

   N->prev = beforeCursor;
   beforeCursor->next = N;

   N->next = afterCursor;
   afterCursor->prev = N;
   afterCursor = N;

   num_elements++;
}

void List::insertBefore(int x)
{
   Node* N = new Node(x);

   if (position() < 0)
   {
      cerr << "Error: Could not insert x before cursor" << endl;
      exit(EXIT_FAILURE);
   }

   if (afterCursor < 0)
   {
      cerr << "Error: Could not insert x before cursor" << endl;
      exit(EXIT_FAILURE);
   }

   if (beforeCursor < 0)
   {
      cerr << "Error: Could not insert x before cursor" << endl;
      exit(EXIT_FAILURE);
   }

   N->prev = beforeCursor;
   beforeCursor->next = N;

   N->next = afterCursor;
   afterCursor->prev = N;
   beforeCursor = N;

   pos_cursor++;
   num_elements++;
}

void List::eraseAfter()
{
   Node* remove = afterCursor;

   afterCursor = afterCursor->next;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;
   
   delete remove;
   num_elements--;
}

void List::eraseBefore()
{
   Node* remove = beforeCursor;

   beforeCursor = beforeCursor->prev;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;

   delete remove;
   num_elements--;
   pos_cursor--;
   
}

int List::movePrev()
{
   pos_cursor--;

   beforeCursor = beforeCursor->prev;
   afterCursor = afterCursor->prev;

   int advLower = afterCursor->data;
   return advLower;
}

int List::moveNext()
{
   pos_cursor++;
   
   beforeCursor = beforeCursor->next;
   afterCursor = afterCursor->next;

   int advHigher = beforeCursor->data;
   return advHigher;
}

int List::findNext(int x)
{
   if (afterCursor < 0)
   {
      cerr << "Error: Could not find first occurance of element x" << endl;
      exit(EXIT_FAILURE);
   }

   if (backDummy < 0)
   {
      cerr << "Error: Could not find first occurance of element x" << endl;
      exit(EXIT_FAILURE);
   }

   while(afterCursor != backDummy)
   {
      if(afterCursor->data == x)
      {
         moveNext();
         return pos_cursor;
      }

      moveNext();
   }

   return -1;
}

int List::findPrev(int x)
{
   if (beforeCursor < 0)
   {
      cerr << "Error: Could not find first occurance of element x" << endl;
      exit(EXIT_FAILURE);
   }

   if (frontDummy < 0)
   {
      cerr << "Error: Could not find first occurance of element x" << endl;
      exit(EXIT_FAILURE);
   }

   while(beforeCursor != frontDummy)
   {
      if(beforeCursor->data == x)
      {
         movePrev();
         return pos_cursor;
      }

      movePrev();
   }

   return -1;
}

void List::clear()
{
   moveFront();

   if( num_elements < 0)
   {
      cerr << "Error: Cannot delete elements in the List" << endl;
      exit(EXIT_FAILURE);
   }

   while(num_elements > 0)
   {
      eraseAfter();
   }
}

void List::cleanup()
{
   Node* newNode = frontDummy->next;
   int variable = 0;
   int cursorPos = pos_cursor;

   while (newNode != backDummy)
   {
      moveFront();

      findNext(newNode->data);

      while (true) 
      {
         if (findNext(newNode->data) == -1) 
         {
            break;
         }
         
         if (pos_cursor <= cursorPos)
         {
            cursorPos--;
         }

         eraseBefore();
      }

      newNode = frontDummy->next;
      variable++;

      for (int var = 0; var < variable; var++)
      {
         newNode = newNode->next;
      }
   }

	moveFront();

	for (int var = 0; var < cursorPos; var++) 
   {
		moveNext();
	}
}

List List::concat(const List& L)
{
   List newList;
   Node* newNode1 = frontDummy->next;
   Node* newNode2 = L.frontDummy->next;

   if(newNode1 == backDummy)
   {
      cerr << "Error: Cannot return cursor to front of new List" << endl;
      exit(EXIT_FAILURE);
   }

   while(newNode1 != backDummy)
   {
      newList.insertBefore(newNode1->data);
      newNode1 = newNode1->next;
   }

   if(newNode2 == L.backDummy)
   {
      cerr << "Error: Cannot return cursor to front of new List" << endl;
      exit(EXIT_FAILURE);
   }

   while(newNode2 != L.backDummy)
   {
      newList.insertBefore(newNode2->data);
      newNode2 = newNode2->next;
   }

   moveFront();

   return newList;   
}

string List::to_string()
{
   Node* newNode;

   string stringRep = "(";

   for(newNode = frontDummy->next; newNode != backDummy->prev; newNode = newNode->next)
   {
      stringRep += std::to_string(newNode->data) + ", ";
   }

   stringRep += std::to_string(newNode->data);
   stringRep += ")";

   return stringRep;
}

bool List::equals(const List& L)
{   
   bool sameSequence = false;
 
   if(sameSequence == true)
   {
      cerr << "Error: List is not the same integer sequence as R" << endl;
      exit(EXIT_FAILURE);
   }

   Node* newNode1;
   Node* newNode2;

   sameSequence = (size() == L.num_elements);

   newNode1 = frontDummy->next;
   newNode2 = L.frontDummy->next;

   if(sameSequence && newNode1 == backDummy)
   {
      cerr << "Error: List is not the same integer sequence as R" << endl;
      exit(EXIT_FAILURE);
   }

   while( sameSequence && newNode1 != backDummy )   
   {
      sameSequence = (newNode1->data == newNode2->data);
      newNode1 = newNode1->next;
      newNode2 = newNode2->next;
   }

   return sameSequence;
}

ostream& operator<< (ostream& stream,  List& L)
{
   return stream << L.List::to_string();
}

bool operator== (List& A, const List& B)
{
   return A.List::equals(B);
}

List& List::operator= (const List& L)
{
   if(this == &L)
   {
      cerr << " Error: Cannot overwrite the state of this List" << endl;
      exit(EXIT_FAILURE);
   }

   if(this != &L )
   {

      List overwriteList = L;

      std::swap(num_elements, overwriteList.num_elements);
      std::swap(frontDummy, overwriteList.frontDummy);
      std::swap(backDummy, overwriteList.backDummy);
   }

   return *this;
}