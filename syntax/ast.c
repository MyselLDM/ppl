#include "ast.h"
#include "putils.h"
#include <stdlib.h>
#include <stdio.h>

// ========================
// AST Management Functions
// ========================

/**
 * ast_create_node
 * ----------------
 * Creates and initializes a new AST node.
 * 
 * This function allocates memory for a new AST node and initializes all its fields.
 * The node is created with the specified type and optional token reference.
 * The children array is initially NULL and will be allocated dynamically as children are added.
 * 
 * @param type The type of AST node to create (e.g., AST_PROGRAM, AST_STATEMENT_LIST)
 * @param token Pointer to the token associated with this node (can be NULL for non-terminal nodes)
 * @return Pointer to the newly created and initialized ASTNode
 */
ASTNode* ast_create_node(ASTNodeType type, Token* token)
{
  // Allocate memory for the new node using safe_malloc (exits on failure)
  ASTNode* node = (ASTNode*)safe_malloc(sizeof(ASTNode));
  
  // Initialize node fields
  node->type = type;
  node->token = token;  // May be NULL for container nodes
  node->children = NULL;  // Children array starts empty
  node->child_count = 0;  // No children initially
  
  return node;
}

/**
 * ast_add_child
 * --------------
 * Adds a child node to a parent node's children array.
 * 
 * This function dynamically expands the parent's children array to accommodate
 * the new child. It uses resize_array to safely reallocate memory for the growing
 * array. This is essential for building the hierarchical AST structure.
 * 
 * @param parent Pointer to the parent ASTNode that will receive the child
 * @param child Pointer to the child ASTNode to be added
 */
void ast_add_child(ASTNode* parent, ASTNode* child)
{
  // Safety check: ensure both parent and child are valid
  if (!parent || !child)
  {
    return;
  }
  
  // Resize the children array to accommodate one more child
  parent->children = (ASTNode**)resize_array((void**)parent->children, parent->child_count + 1);
  
  // Add the new child at the end of the array
  parent->children[parent->child_count] = child;
  
  // Increment the child count
  parent->child_count++;
}

/**
 * ast_free
 * ---------
 * Recursively frees an entire AST and all its allocated memory.
 * 
 * This function performs a post-order traversal (children first, then parent)
 * to safely free all nodes in the AST. It frees the children array and the node
 * itself, but NOT the tokens, as those are managed by the Tokens structure.
 * 
 * @param root Pointer to the root ASTNode to free (can be any subtree)
 */
void ast_free(ASTNode* root)
{
  // Base case: NULL node requires no action
  if (!root)
  {
    return;
  }
  
  // Recursively free all children first (post-order traversal)
  for (size_t i = 0; i < root->child_count; i++)
  {
    ast_free(root->children[i]);
  }
  
  // Free the children array itself
  if (root->children)
  {
    free(root->children);
  }
  
  // Finally, free the node itself
  // Note: We don't free the token pointer as tokens are managed separately
  free(root);
}
