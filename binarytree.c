/*Name: Suman Kafle
CS 251
Lab -8
binarytree.c*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binarytree.h"

/* Alloc a new node with given data. */
struct TreeNode* createNode(char data)
{
  struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, char data)
{
  /* to check if  the tree is empty if so to create a new node */
  if (root == NULL)
    {
      return createNode(data);
    }

  /* to check if  the data is less than the root node's*/
  if (data < root->data)
    {
      root->left = insertBST(root->left, data);
    }
  /*to check the data is greater than or equal to the root node's data, insert into the right subtree*/
  else
    {
      root->right = insertBST(root->right, data);
    }
  return root;
}

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   successor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, char data)
{
  struct TreeNode* current = *rootRef;
  struct TreeNode* head = NULL;
  struct TreeNode* successor = NULL;
  struct TreeNode* child = NULL;
  /* to check if the current data is equal to the given data*/
  while (current && current->data != data)
    {
      /* to update the head*/
      head = current;
      if (data < current->data)
	{
	  current = current->left;
	}
      else
	{
	  current = current->right;
	}
    }

  /* condition if the data is not found*/
  if (!current)
    {
      return 0;
    }

  /*to  check if the node has two children*/
  if (current->left && current->right)
    {
      /* to find the in-order successor*/
      successor = current->right;
      while (successor->left)
	{
	  successor = successor->left;
	}
      current->data = successor->data;
      /*to recursively remove the successor node*/
      return removeBST(&current->right, successor->data);
    }

  /*to check for the node with zero or one child*/
  child = current->left ? current->left : current->right;
  if (!head)
    {
      *rootRef = child;
    }
  else if (current == head->left)
    {
      head->left = child;
    }
  else
    {
      head->right = child;
    }
  /* to free the current memory*/
  free(current);
  return 1;


}

/* Return minimum value in non-empty binary search tree. */
char minValueBST(struct TreeNode* root)
{
  if (root == NULL)
    {
      return '\0';
    }

  while (root->left != NULL)
    {
      root = root->left;
    }

  return root->data;
}

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root)
{
  int depth;
  int leftDepth;
  int rightDepth;


  if (root == NULL)
    {
      return 0;
    }

  depth = 0;
  leftDepth = maxDepth(root->left);
  rightDepth = maxDepth(root->right);

  if (leftDepth > rightDepth)
    {
      /* to update the depth*/
      depth = leftDepth;
    }
  else
    {
      depth = rightDepth;
    }
  /*to return the depth of the data*/
  return depth + 1;
}

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root)
{
  int leftDepth =0;
  int rightDepth= 0;

  if (root == NULL)
    {
      return 1;
    }

  leftDepth = maxDepth(root->left);
  rightDepth = maxDepth(root->right);

  if (abs(leftDepth - rightDepth) > 1)
    {
      return 0;
    }

  return isBalanced(root->left) && isBalanced(root->right);

}

/* helper function to return 1 if tree is a binary search tree, 0 if not. */
int isBSTHelper(struct TreeNode* root, int minVal, int maxVal)
{
  if (root == NULL)
    {
      return 1;
    }
  /* to check if the data is smaller in the left side and bigger in the tight side */
  if (root->data < minVal || root->data > maxVal)
    {
      return 0;
    }
  /* to return where 1 or 0  */
  return isBSTHelper(root->left, minVal, root->data - 1) &&isBSTHelper(root->right, root->data + 1, maxVal);
}


/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root)
{
  return isBSTHelper(root, INT_MIN, INT_MAX);
}

/* helper function to print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTreeHelper(struct TreeNode* root)
{
  if(root== NULL)
    {
      return;
    }
  printTreeHelper(root->left);
  printf("%c ", root->data);
  printTreeHelper(root->right);
}


/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root)

{
  printTreeHelper(root);
  printf("\n");
}

/* helper function to print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void leavesHelper(struct TreeNode* root)
{
  if (root == NULL)
    {
      return;
    }

  if (root->left == NULL && root->right == NULL)
    {
      printf("%c ", root->data);
    }

  leavesHelper(root->left);
  leavesHelper(root->right);
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root)
{
  leavesHelper(root);
  printf("\n");
}

/* helper function to print the traversal on a single line,
 * separated with spaces, ending with newline.*/
void verboseHelper(struct TreeNode* root, int depth)
{
  if (root == NULL)
    {
      return;
    }

  printf("(%c,%d) ", root->data, depth);
  /* recursively printing the data inpre-order form*/
  verboseHelper(root->left, depth + 1);
  verboseHelper(root->right, depth + 1);
}

/* Print data for a preorder tree traversal on a single line
 * as a sequence of (data, depth) pairs
 * separated with spaces, ending with newline.
 * (The root node has a depth of 1)
 *
 *  So, the tree
 *
 *      A
 *     / \
 *    B   C
 *   / \
 *  D   E
 *
 * will produce the output
 * (A,1) (B,2) (D,3) (E,3) (C,2) 
 */
void printTreeVerbose(struct TreeNode* root)
{
  verboseHelper(root,1);
  printf("\n");
}

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
  if (root == NULL) return;
  freeTree(root ->left);
  freeTree(root ->right );
  free(root);
}
