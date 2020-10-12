#include <cstdlib>
#include <ctime>
#include <iostream>
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

const int maxNumberOfNodes = 100;

int main()
{
    node *tree = nullptr;
    bool exitProgram = false;
    int choice = 0;
    int numberOfNodes = 0;

    while(!exitProgram)
    {
        choice = 0;
        if (tree == nullptr)
        {
            numberOfNodes = 0;
        }
        else
        {
            numberOfNodes = tree->count_of_nodes;
        }
        cout << "Please choose from the following options:\n";
        cout << "0. Exit\n";
        cout << "1. Add entry\n";
        if (numberOfNodes > 0)
        {
            cout << "2. Update entry\n";
            cout << "3. Delete entry\n";
            cout << "4. Display entry\n";
        }
        cin >> choice;
        cin.clear();
        cin.ignore(80, '\n');

        cout << '\n';

        switch (choice)
        {
        case 0:
            exitProgram = true;
            break;
        case 1:
            tree = add_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 2:
            tree = update_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 3:
            tree = delete_entry(tree);
            cout << "Display tree in sorted order\n";
            printSorted(tree);
            cout << '\n';
            break;
        case 4:
            display_entry(tree);
            break;
        default:
            exitProgram = true;
            break;
        }
    }

    destroyTreePostOrder(tree);
}

void printSorted(node *tree)
{
    int currentCount = 0;
    string nodeKeys[maxNumberOfNodes];
    InOrder (tree, &currentCount, nodeKeys);

    for (int i = 0; i < currentCount; i++)
    {
        cout << "key | value = " << nodeKeys[i] << '\n';
    }
    cout <<"\n\n";
}

node *insert (node *p_tree, string key, string value)
{
    int left_depth, right_depth;
    int left_count, right_count;

    if ( p_tree == nullptr )
    {
        node *p_new_tree = new node;
        p_new_tree->depth_of_node = 0;
        p_new_tree->count_of_nodes = 1;
        p_new_tree->p_parent = nullptr;
        p_new_tree->p_left = nullptr;
        p_new_tree->p_right = nullptr;
        p_new_tree->key = key;
        p_new_tree->value = value;
        return p_new_tree;
    }
    if ( key == p_tree->key )
    {
        p_tree->value = value;
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
    else if( key < p_tree->key )
    {
        p_tree->p_left = insert( p_tree->p_left, key, value);
        if (p_tree->p_left != nullptr)
        {
            p_tree->p_left->p_parent = p_tree;
        }
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
        p_tree->p_right = insert( p_tree->p_right, key, value );
        if (p_tree->p_right != nullptr)
        {
            p_tree->p_right->p_parent = p_tree;
        }
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

node *search (node *p_tree, string key)
{
    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    else if ( key == p_tree->key )
    {
        return p_tree;
    }
    else if ( key < p_tree->key )
    {
        return search( p_tree->p_left, key );
    }
    else
    {
        return search( p_tree->p_right, key );
    }
}
void preOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[])
{
   node *last_node;
    node *check_node;

    if (p_tree == nullptr)
    {
        return;
    }
    last_node = nullptr;
    check_node = p_tree;
    nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
    (*currentCount)++;
    if (check_node->p_left != nullptr)
    {
        last_node = check_node;
        check_node = check_node->p_left;
    }
    else
    {
        if (check_node->p_right != nullptr)
        {
            last_node = check_node;
            check_node = check_node->p_right;
        }
        else
        {
            return;
        }
    }
    while(last_node != nullptr && check_node != nullptr)
    {
        if(last_node == check_node->p_parent)
        {
            nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
            (*currentCount)++;
            if (check_node->p_left != nullptr)
            {
                last_node = check_node;
                check_node = check_node->p_left;
            }
            else
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
        }
        else
        {
            if(last_node == check_node->p_left)
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
            else
            {
                last_node = check_node;
                check_node = check_node->p_parent;
            }
        }
    }
}
void postOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[])
{
    node *last_node;
    node *check_node;

    if (p_tree == nullptr)
    {
        return;
    }
    last_node = nullptr;
    check_node = p_tree;
    if (check_node->p_left != nullptr)
    {
        last_node = check_node;
        check_node = check_node->p_left;
    }
    else
    {
        if (check_node->p_right != nullptr)
        {
            last_node = check_node;
            check_node = check_node->p_right;
        }
        else
        {
            nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
            (*currentCount)++;
            return;
        }
    }
    while(last_node != nullptr && check_node != nullptr)
    {
        if(last_node == check_node->p_parent)
        {
            if (check_node->p_left != nullptr)
            {
                last_node = check_node;
                check_node = check_node->p_left;
            }
            else
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
                    (*currentCount)++;
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
        }
        else
        {
            if(last_node == check_node->p_left)
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
                    (*currentCount)++;
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
            else
            {
                nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
                (*currentCount)++;
                last_node = check_node;
                check_node = check_node->p_parent;
            }
        }
    }
}
void destroyTreePostOrder (node *p_tree)
{
    node *last_node;
    node *check_node;
    node *temp_node;

    if (p_tree == nullptr)
    {
        return;
    }
    last_node = nullptr;
    check_node = p_tree;
    if (check_node->p_left != nullptr)
    {
        last_node = check_node;
        check_node = check_node->p_left;
    }
    else
    {
        if (check_node->p_right != nullptr)
        {
            last_node = check_node;
            check_node = check_node->p_right;
        }
        else
        {
            temp_node = check_node;
            cout << temp_node->key << '\n';
            delete temp_node;
            return;
        }
    }
    while(last_node != nullptr && check_node != nullptr)
    {
        if(last_node == check_node->p_parent)
        {
            if (check_node->p_left != nullptr)
            {
                last_node = check_node;
                check_node = check_node->p_left;
            }
            else
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    temp_node = check_node;
                    last_node = check_node;
                    check_node = check_node->p_parent;
                    cout << temp_node->key << '\n';
                    delete temp_node;
                }
            }
        }
        else
        {
            if(last_node == check_node->p_left)
            {
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    temp_node = check_node;
                    last_node = check_node;
                    check_node = check_node->p_parent;
                    cout << temp_node->key << '\n';
                    delete temp_node;
                }
            }
            else
            {
                temp_node = check_node;
                last_node = check_node;
                check_node = check_node->p_parent;
                cout << temp_node->key << '\n';
                delete temp_node;
            }
        }
    }
}
void InOrderNonRecursive (node *p_tree, int *currentCount, string nodeKeys[])
{
    node *last_node;
    node *check_node;

    if (p_tree == nullptr)
    {
        return;
    }
    last_node = nullptr;
    check_node = p_tree;
    if (check_node->p_left != nullptr)
    {
        last_node = check_node;
        check_node = check_node->p_left;
    }
    else
    {
        nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
        (*currentCount)++;
        if (check_node->p_right != nullptr)
        {
            last_node = check_node;
            check_node = check_node->p_right;
        }
        else
        {
            return;
        }
    }
    while(last_node != nullptr && check_node != nullptr)
    {
        if(last_node == check_node->p_parent)
        {
            if (check_node->p_left != nullptr)
            {
                last_node = check_node;
                check_node = check_node->p_left;
            }
            else
            {
                nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
                (*currentCount)++;
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
        }
        else
        {
            if(last_node == check_node->p_left)
            {
                nodeKeys[ (*currentCount) ] = check_node->key + " | " + check_node->value;
                (*currentCount)++;
                if (check_node->p_right != nullptr)
                {
                    last_node = check_node;
                    check_node = check_node->p_right;
                }
                else
                {
                    last_node = check_node;
                    check_node = check_node->p_parent;
                }
            }
            else
            {
                last_node = check_node;
                check_node = check_node->p_parent;
            }
        }
    }
}

void InOrder (node *p_tree, int *currentCount, string nodeKeys[])
{
    if (p_tree != nullptr)
    {
        InOrder (p_tree->p_left, currentCount, nodeKeys);
        nodeKeys[ (*currentCount) ] = p_tree->key + " | " + p_tree->value;
        (*currentCount)++;
        InOrder (p_tree->p_right, currentCount, nodeKeys);
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
        if (p_tree->p_right != nullptr)
        {
            p_tree->p_right->p_parent = p_tree;
        }
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
node *remove (node *p_tree, string key)
{
    int left_depth, right_depth;
    int left_count, right_count;

    if ( p_tree == nullptr )
    {
        return nullptr;
    }
    if ( p_tree->key == key )
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
        if (p_max_node->p_left != nullptr)
        {
            p_max_node->p_left->p_parent = p_max_node;
        }
        p_max_node->p_right = p_right_subtree;
        if (p_max_node->p_right != nullptr)
        {
            p_max_node->p_right->p_parent = p_max_node;
        }
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
    else if ( key < p_tree->key )
    {
        p_tree->p_left = remove( p_tree->p_left, key);
        if (p_tree->p_left != nullptr)
        {
            p_tree->p_left->p_parent = p_tree;
        }
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
        if (p_tree->p_right != nullptr)
        {
            p_tree->p_right->p_parent = p_tree;
        }
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

void display_entry(node *p_tree)
{
    string name = "";
    node *temp_node;

    do
    {
        name = "";
        cout << "Please enter a name from the address book to display:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( temp_node = search(p_tree, name) ) == nullptr )
        {
            cout << "The name can not find in the address book.\n";
            continue;
        }

        cout << '\n';
        cout << name << " | " << temp_node->value << "\n\n";
    }
    while (name != "");
}
node *add_entry(node *p_tree)
{
    string name = "";
    string email = "";
    node *temp_node;

    do
    {
        name = "";
        cout << "Please enter a name for the address book:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( temp_node = search(p_tree, name) ) != nullptr )
        {
            cout << "The name already exists.\n";
            cout << "Please enter a unique name to add.\n";
            continue;
        }
        email = "";
        cout << "Please enter an email address for the name:\n";
        getline(cin, email, '\n');
        if (email == "")
        {
            break;
        }

        p_tree = insert(p_tree, name, email);
        cout << "\n\n";
    }
    while (name != "");

    return p_tree;
}
node *update_entry(node *p_tree)
{
    string name = "";
    string email = "";
    node *temp_node;

    do
    {
        name = "";
        cout << "Please enter a name to update:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( temp_node = search(p_tree, name) ) == nullptr )
        {
            cout << "The name can not find in the address book.\n";
            cout << "Please enter an existing name to update.\n";
            continue;
        }
        email = "";
        cout << "Please enter a new email address for the name:\n";
        getline(cin, email, '\n');
        if (email == "")
        {
            break;
        }

        p_tree = insert(p_tree, name, email);
        cout << "\n\n";
    }
    while (name != "");

    return p_tree;
}
node *delete_entry(node *p_tree)
{
    string name = "";
    node *temp_node;

    do
    {
        name = "";
        cout << "Please enter a name to delete:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( temp_node = search(p_tree, name) ) == nullptr )
        {
            cout << "The name can not find in the address book.\n";
            cout << "Please enter an existing name to delete.\n";
            continue;
        }

        p_tree = remove(p_tree, name);
        cout << name << " has been removed from the address book.\n\n";
    }
    while (name != "");

    return p_tree;
}
