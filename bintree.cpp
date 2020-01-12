//--------------------------------bintree.cpp--------------------------------
//Author: Scott Blake
//Created: 03/07/2019
//Modified: 03/07/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for BinTree, a Binary Search Tree. It uses a
//         separate object class called Merchandise to hold its data, and a
//         struct called Node for each node in the Binary Tree. Modified
//         from its original use in CSS343 Assignment 2.
//---------------------------------------------------------------------------
//Notes: Assumption: Merchandise provides proper data checking and overloads
//       appropriate operators for comparison.
//---------------------------------------------------------------------------
#include <iostream>
#include "bintree.h"
using namespace std;

//-------------------------------BinTree-------------------------------------
//Description: Empty Constructor - set default values.
//---------------------------------------------------------------------------
BinTree::BinTree()
{
  this->root = nullptr;
} //end of BinTree

//--------------------------------~BinTree-----------------------------------
//Description: Destructor - calls makeEmpty helper to empty tree.
//---------------------------------------------------------------------------
BinTree::~BinTree()
{
  if (!isEmpty())
  {
    makeEmpty();
  }
} //end of ~BinTree

//--------------------------------retrieve-----------------------------------
//Description: Searches for, and assigns if located, the desired target value
//             in the BST. Returns true if found, false if not. Calls findData
//             helper.
//---------------------------------------------------------------------------
bool BinTree::retrieve(const Merchandise &target, Merchandise* &location) const
{
  if (isEmpty()) //If the BST is empty, return false.
  {
    return false;
  }
  Node* nodeLocation; //Node for the node location of the target Merchandise
  bool found = findData(root, target, location, nodeLocation); //Otherwise, call
  if (!found)                                                  //call the helper
  {                                                            //function to find
    return false;
  }
  return true;
} //end of retrieve

//--------------------------------findData-----------------------------------
//Description: Recursive elper function to locate specified Merchandise and identify
//             the Node it's at. Returns true if found, false if not.
//---------------------------------------------------------------------------
bool BinTree::findData(Node* root, const Merchandise &target, Merchandise* &location, Node* &nodeLocation) const
{
  if (root == nullptr) //Base case: If the node is empty, it's not in BST
  {
    return false;
  }

  if (target == *root->data) //If target is found, set the node location,
  {                               //and the Merchandise value, and return true
    location = root->data;
    nodeLocation = root;
    return true;
  }
  else if (target < *root->data) //If the node's value is larger than the target
  {                              //then go left
    return findData(root->left, target, location, nodeLocation);
  }
  else //Otherwise, go right
  {
    return findData(root->right, target, location, nodeLocation);
  }
} //end of findData

//-------------------------------isEmpty-------------------------------------
//Description: Determines if the BST is empty, returns true is yes, false if no.
//---------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
  return (this->root == nullptr);
} //end of isEmpty

//--------------------------------insert-------------------------------------
//Description: Inserts Merchandise object into the BST in the correct location
//             if it does not already exist. Does so by iterations instead
//             of recursion.
//---------------------------------------------------------------------------
bool BinTree::insert(Merchandise* data)
{
  Node* newNode = new Node; //Allocate memory for the new node to be inserted
  newNode->data = data;     //and assign it the Merchandise being passed in
  newNode->left = nullptr;
  newNode->right = nullptr; //Initialize left and right pointers to nullptr
  if (isEmpty())
  {
    this->root = newNode; //If the BST is empty, insert the node at the root
  }
  else
  {
    Node* current = root;  //Create a node pointer to traverse from the root
    bool inserted = false; //Flag indicating whether or not the node is inserted
    while (!inserted) //Keep going through the BST until the node is inserted
    {
      if (*current->data == *data) //If the Merchandise is in the BST, do not insert
      {
        delete newNode; //And delete the node created
        newNode = nullptr;
        return false;
      }
      else if (*data < *current->data) //If the Merchandise is less than the current node
      {
        if (current->left == nullptr) //We've reached a leaf, and we can insert
        {
          current->left = newNode;
          inserted = true;
        }
        else //Otherwise, we continue going left
        {
          current = current->left;
        }
      }
      else //Otherwise, the Merchandise is greater than the current node
      {
        if (current->right == nullptr) //We've reached a leaf, and we can insert
        {
          current->right = newNode;
          inserted = true;
        }
        else //Otherwise, we continue going left
        {
          current = current->right;
        }
      }
    }
  }
  return true; //If we've made it here, then the Node was inserted successfully
} //end of insert

//-------------------------------makeEmpty-----------------------------------
//Description: Public function for emptying the BST, which removes all nodes
//             and Merchandise from the BST. Calls the emptyTree helper.
//---------------------------------------------------------------------------
void BinTree::makeEmpty()
{
  emptyTree(root);
} //end of makeEmpty

//--------------------------------emptyTree----------------------------------
//Description: Recursive helper function for emptying the BST, which removes
//             all nodes and Merchandise from the BST. Uses Post-Order traversal
//             to delete Merchandise in each leaf, then going up to the node.
//---------------------------------------------------------------------------
void BinTree::emptyTree(Node* &root)
{
  if (root == nullptr) //Base case: If the node is empty, go back
  {
    return;
  }
  else //Otherwise, traverse the BST is post-order so that the children are
  {    //deleted before the parent nodes
    emptyTree(root->left); //Post-order: traverse left, then right, then the node
    emptyTree(root->right);
    delete root->data; //Delete data first, then the node
    root->data = nullptr; //Assign each to a nullptr once deleted
    delete root;
    root = nullptr;
  }
} //end of emptyTree

//-------------------------------operator<<----------------------------------
//Description: Operator overload for printing to the console. Calls helper
//             inOrderPrint.
//---------------------------------------------------------------------------
ostream& operator<<(ostream &print, const BinTree &bin)
{
  bin.inOrderPrint(bin.root, print); //Call recursive helper
  print << endl; //Go to a new line after printing per instructions
  return print;
} //end of operator<<

//----------------------------- operator= ------------------------------------------------------------------------------
// Description: Assigns a given tree to this tree using util function.
//----------------------------------------------------------------------------------------------------------------------
BinTree &BinTree::operator= (const BinTree &rhs)
{
  if (rhs.root != nullptr)
  {
    makeEmpty();
    this->root = copyUtil(rhs.root);
  }
  return *this;
} // End of operator=

//-------------------------------inOrderPrint--------------------------------
//Description: Recursive helper function to print each value in the BST using
//             in-order traversal.
//---------------------------------------------------------------------------
void BinTree::inOrderPrint(Node* node, ostream &print) const
{
  if (node == root)
  {
    node->data->displayHeader(); //Display header before traversing the rest of
  }                              //the tree
  if (node == nullptr) //Base case: If node is empty, go back
  {
    return;
  }
  inOrderPrint(node->left, print); //In-order: Go left until out of leftward Nodes
  print << *node->data; //Then print the Node
  inOrderPrint(node->right, print); //Then go right
} //end of inOrderPrint

//----------------------------- copyUtil -------------------------------------------------------------------------------
// Description: Recursively performs deep copy of a first given tree into second given tree
//----------------------------------------------------------------------------------------------------------------------
BinTree::Node* BinTree::copyUtil (BinTree::Node *sourceRoot)
{
  Node *newTree;
  if(sourceRoot != nullptr)
  {
    newTree = new Node;
    newTree->data = sourceRoot->data;
    newTree->left = copyUtil (sourceRoot->left);
    newTree->right = copyUtil (sourceRoot->right);
  }
  else
  {
    return nullptr;
  }
  return newTree;
}// End of copyUtil
