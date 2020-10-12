#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

struct node
{
    int key_value;
    node *p_left;
    node *p_right;
};

node *insert (node *p_tree, int key);
node *search (node *p_tree, int key);
void destroy_tree (node *p_tree);
node *remove (node *p_tree, int key);
node *find_max (node *p_tree);
node *remove_max_node (node *p_tree, node *p_max_node);

node *createBinaryTree(int numberOfNodes);
void InOrder (node *p_tree, int *currentCount, int nodeKeys[]);
void InOrder (node *p_tree, int *currentCount);

const int maxNumberOfNodes = 100;

int main()
{
    srand( time(nullptr) );
    int numberOfNodes = maxNumberOfNodes;
    do
    {
        cout << "Please specify the number of nodes to create for the binary tree (between 1 and " << maxNumberOfNodes << "):\n";
        cin >> numberOfNodes;
    }
    while (numberOfNodes <= 0 || numberOfNodes > maxNumberOfNodes);
    cin.clear();
    cin.ignore(80, '\n');
    node *tree = createBinaryTree(numberOfNodes);

    int countOfNodes = 0;
    InOrder (tree, &countOfNodes);
    cout << "The number of nodes in the binary tree is: " << countOfNodes << '\n';

    destroy_tree(tree);
}
node *createBinaryTree(int numberOfNodes)
{
    node *tree = nullptr;
    for (int i = 0; i < numberOfNodes; i++)
    {
        tree = insert(tree, rand());
    }

    return tree;
}
node *insert (node *p_tree, int key)
{
    if ( p_tree == nullptr )
    {
        node *p_new_tree = new node;
        p_new_tree->p_left = nullptr;
        p_new_tree->p_right = nullptr;
        p_new_tree->key_value = key;
        return p_new_tree;
    }
    if( key < p_tree->key_value )
    {
        p_tree->p_left = insert( p_tree->p_left, key );
        return p_tree;
    }
    else
    {
        p_tree->p_right = insert( p_tree->p_right, key );
        return p_tree;
    }
}

node *search (node *p_tree, int key)
{
    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    else if ( key == p_tree->key_value )
    {
        return p_tree;
    }
    else if ( key < p_tree->key_value )
    {
        return search( p_tree->p_left, key );
    }
    else
    {
        return search( p_tree->p_right, key );
    }
}
void InOrder (node *p_tree, int *currentCount, int nodeKeys[])
{
    if (p_tree != nullptr)
    {
        InOrder (p_tree->p_left, currentCount, nodeKeys);
        nodeKeys[ (*currentCount) ] = p_tree->key_value;
        (*currentCount)++;
        InOrder (p_tree->p_right, currentCount, nodeKeys);
    }
}
void InOrder (node *p_tree, int *currentCount)
{
    if (p_tree != nullptr)
    {
        InOrder (p_tree->p_left, currentCount);
        (*currentCount)++;
        InOrder (p_tree->p_right, currentCount);
    }
}
void destroy_tree (node *p_tree)
{
    if ( p_tree != nullptr )
    {
        destroy_tree( p_tree->p_left );
        destroy_tree( p_tree->p_right );
        delete p_tree;
    }
}

node *find_max (node *p_tree)
{
    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    if ( p_tree->p_right == nullptr )
    {
        return p_tree;
    }
    else
    {
        return find_max( p_tree->p_right );
    }
}
node *remove_max_node (node *p_tree, node *p_max_node)
{
    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    if ( p_tree == p_max_node )
    {
        return p_max_node->p_left;
    }
    else
    {
        p_tree->p_right = remove_max_node( p_tree->p_right, p_max_node);
        return p_tree;
    }
}
node *remove (node *p_tree, int key)
{
    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    if ( p_tree->key_value == key )
    {
        if ( p_tree->p_left == nullptr )
        {
            node *p_right_subtree = p_tree->p_right;
            delete p_tree;
            return p_right_subtree;
        }
        if ( p_tree->p_right == nullptr )
        {
            node *p_left_subtree = p_tree->p_left;
            delete p_tree;
            return p_left_subtree;
        }
        node *p_left_subtree = p_tree->p_left;
        node *p_right_subtree = p_tree->p_right;
        node *p_max_node = find_max( p_left_subtree );
        p_max_node->p_left = remove_max_node( p_tree->p_left, p_max_node );
        p_max_node->p_right = p_right_subtree;
        delete p_tree;
        return p_max_node;
    }
    else if ( key < p_tree->key_value )
    {
        p_tree->p_left = remove( p_tree->p_left, key);
        return p_tree;
    }
    else
    {
        p_tree->p_right = remove( p_tree->p_right, key);
        return p_tree;
    }
}
