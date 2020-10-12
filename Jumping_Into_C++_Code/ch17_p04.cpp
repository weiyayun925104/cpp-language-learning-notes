#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

struct node
{
    int depth_of_node;
    int count_of_nodes;
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
void printTree(node *tree, string level = "");
void printSorted(node *tree, int numberOfNodes);
void printReverseSorted(node *tree, int numberOfNodes);
void printNode(string level);
void InOrder (node *p_tree, int *currentCount, int nodeKeys[]);
void InOrder (node *p_tree, int *currentCount);
void checkTreeBalanced(node *p_tree);
bool checkTreeSorted(node *p_tree);

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

    cout << "Display the binary tree\n";
    printTree(tree);
    cout << '\n';

    cout << "Display tree in sorted order\n";
    printSorted(tree, numberOfNodes);
    cout << '\n';

    cout << "Display tree in reverse sorted order\n";
    printReverseSorted(tree, numberOfNodes);
    cout << '\n';

    cout << "Check tree is sorted\n";
    if ( checkTreeSorted(tree) )
    {
        cout << "The tree is sorted\n";
    }
    else
    {
        cout << "The tree is not sorted\n";
    }

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
void printTree(node *tree, string level)
{
    if (level != "")
    {
        level += "-";
    }
    if (tree == nullptr)
    {
        level += "null";
        printNode(level);
        return;
    }

    level += to_string(tree->depth_of_node);
    level += ", ";
    level += to_string(tree->count_of_nodes);
    level += ": ";
    level += to_string(tree->key_value);
    printNode(level);
    checkTreeBalanced(tree);

    cout << "Left\n";
    printTree(tree->p_left, level);

    cout << "Right\n";
    printTree(tree->p_right, level);
}
void printSorted(node *tree, int numberOfNodes)
{
    int currentCount = 0;
    int nodeKeys[maxNumberOfNodes];
    InOrder (tree, &currentCount, nodeKeys);

    for (int i = 0; i < numberOfNodes; i++)
    {
        printNode( to_string( nodeKeys[i] ) );
    }
}
void printReverseSorted(node *tree, int numberOfNodes)
{
    int currentCount = 0;
    int nodeKeys[maxNumberOfNodes];
    InOrder (tree, &currentCount, nodeKeys);

    for (int i = 0; i < numberOfNodes; i++)
    {
        printNode( to_string( nodeKeys[numberOfNodes - 1 - i] ) );
    }
}
void printNode(string level)
{
    cout << "Node: " << level << "\n";
}
node *insert (node *p_tree, int key)
{
    int left_depth, right_depth;
    int left_count, right_count;

    if ( p_tree == nullptr )
    {
        node *p_new_tree = new node;
        p_new_tree->depth_of_node = 0;
        p_new_tree->count_of_nodes = 1;
        p_new_tree->p_left = nullptr;
        p_new_tree->p_right = nullptr;
        p_new_tree->key_value = key;
        return p_new_tree;
    }
    if ( key == p_tree->key_value )
    {
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
        return p_tree;
    }
    else if( key < p_tree->key_value )
    {
        p_tree->p_left = insert( p_tree->p_left, key );
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
        return p_tree;
    }
    else
    {
        p_tree->p_right = insert( p_tree->p_right, key );
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
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
void checkTreeBalanced(node *p_tree)
{
    int left_depth, right_depth;
    int left_count, right_count;
    int temp_depth, temp_count;

    if ( p_tree != nullptr )
    {
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            temp_depth = ( right_depth - left_depth );
        }
        else
        {
            temp_depth = ( left_depth - right_depth );
        }
        if (left_count < right_count)
        {
            temp_count = ( right_count - left_count );
        }
        else
        {
            temp_count = ( left_count - right_count );
        }
        if (temp_depth >= -1 && temp_depth <= 1)
        {
            cout << "checkTreeBalanced: " << temp_depth << ", " << temp_count << " is balanced\n";
        }
        else
        {
            cout << "checkTreeBalanced: " << temp_depth << ", " << temp_count << " is not balanced\n";
        }
    }
}
bool checkTreeSorted(node *p_tree)
{
    bool temp_result;

    if (p_tree == nullptr)
    {
        return true;
    }
    if (p_tree->p_left == nullptr && p_tree->p_right == nullptr)
    {
        return true;
    }

    if (p_tree->p_left != nullptr && p_tree->p_left->key_value > p_tree->key_value)
    {

        cout << "checkTreeSorted left = " << p_tree->p_left->key_value << " > " << p_tree->key_value << '\n';
        return false;
    }
    if (p_tree->p_right != nullptr && p_tree->p_right->key_value < p_tree->key_value)
    {
        cout << "checkTreeSorted right = " << p_tree->p_right->key_value << " < " << p_tree->key_value << '\n';
        return false;
    }
    return ( checkTreeSorted(p_tree->p_left) && checkTreeSorted(p_tree->p_right) );
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
    int left_depth, right_depth;
    int left_count, right_count;

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
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
        return p_tree;
    }
}
node *remove (node *p_tree, int key)
{
    int left_depth, right_depth;
    int left_count, right_count;

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
        if (p_max_node->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_max_node->p_left->depth_of_node;
            left_count = p_max_node->p_left->count_of_nodes;
        }
        if (p_max_node->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_max_node->p_right->depth_of_node;
            right_count = p_max_node->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_max_node->depth_of_node = right_depth + 1;
        }
        else
        {
            p_max_node->depth_of_node = left_depth + 1;
        }
        p_max_node->count_of_nodes = left_count + right_count + 1;
        delete p_tree;
        return p_max_node;
    }
    else if ( key < p_tree->key_value )
    {
        p_tree->p_left = remove( p_tree->p_left, key);
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
        return p_tree;
    }
    else
    {
        p_tree->p_right = remove( p_tree->p_right, key);
        if (p_tree->p_left == nullptr)
        {
            left_depth = -1;
            left_count = 0;
        }
        else
        {
            left_depth = p_tree->p_left->depth_of_node;
            left_count = p_tree->p_left->count_of_nodes;
        }
        if (p_tree->p_right == nullptr)
        {
            right_depth = -1;
            right_count = 0;
        }
        else
        {
            right_depth = p_tree->p_right->depth_of_node;
            right_count = p_tree->p_right->count_of_nodes;
        }
        if (left_depth < right_depth)
        {
            p_tree->depth_of_node = right_depth + 1;
        }
        else
        {
            p_tree->depth_of_node = left_depth + 1;
        }
        p_tree->count_of_nodes = left_count + right_count + 1;
        return p_tree;
    }
}
