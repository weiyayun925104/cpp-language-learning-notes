#pragma once
#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <string>

using namespace std;

struct node
{
    int depth_of_node;
    int count_of_nodes;
    string key;
    string value;
    node *p_parent;
    node *p_left;
    node *p_right;
};

static const int maxNumberOfNodes = 100;

node *insert (node *p_tree, string key, string value);
node *search (node *p_tree, string key);
void destroy_tree (node *p_tree);
node *remove (node *p_tree, string key);
node *find_max (node *p_tree);
node *remove_max_node (node *p_tree, node *p_max_node);

node* add_entry(node* p_tree);
node* update_entry(node* p_tree);
node* delete_entry(node* p_tree);
void display_entry(node* p_tree);

void printSorted(node *tree);
void InOrder (node *p_tree, int *currentCount, string nodeKeys[]);
void InOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[]);
void postOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[]);
void preOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[]);
void destroyTreePostOrder (node *p_tree);

#endif
