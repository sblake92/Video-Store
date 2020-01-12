//--------------------------------bintree.h--------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Header file for BinTree, a Binary Search Tree. It uses a separate
//         object class called Merchandise to hold its data, and a struct called
//         Node for each node in the Binary Tree. Modified from its original
//         use in CSS343 Assignment 2.
//---------------------------------------------------------------------------
//Notes: Assumption: Merchandise provides proper data checking and overloads
//       appropriate operators for comparison.
//---------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "merchandise.h"
using namespace std;

class BinTree
{
public:
  //Constructors
  BinTree();
  ~BinTree();
  //Getters
  bool retrieve(const Merchandise &target, Merchandise* &location) const;
  bool isEmpty() const;
  //Setters
  bool insert(Merchandise* data);
  void makeEmpty();
  //Operator Overloads
  friend ostream& operator<<(ostream &print, const BinTree &bin);
  BinTree& operator=(const BinTree &);
private:
  struct Node
  {
    Merchandise* data;
    Node* left;
    Node* right;
  };
  Node* root;
  //Private and Helper Functions
  void inOrderPrint(Node* root, ostream &print) const;
  void emptyTree(Node* &root);
  bool findData(Node* root, const Merchandise &target, Merchandise* &location, Node* &nodeLocation) const;
  Node* copyUtil(Node *);
};
#endif
