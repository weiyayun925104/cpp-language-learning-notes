#include <iostream>

struct Node
{
    int value;
    Node *subLeft{nullptr};
    Node *subRight{nullptr};
    Node(int i = 0) : value{i}
    {
    }
    int getValue() const
    {
        return value;
    }
    //...
    // traverse helpers:
    static constexpr auto left = &Node::subLeft;
    static constexpr auto right = &Node::subRight;

    // traverse tree, using fold expression:
    template<typename T, typename... TP>
    static Node *traverse (T np, TP... paths)
    {
        return (np ->* ... ->* paths);      // np ->* paths1 ->* paths2 ...
    }
};

int main()
{
  // init binary tree structure:
  Node* root = new Node{0};
  root->subLeft = new Node{1};
  root->subLeft->subRight = new Node{2};
  //...
  // traverse binary tree:
  Node* node = Node::traverse(root, Node::left, Node::right);
  std::cout << node->getValue() << '\n';
  node = root ->* Node::left ->* Node::right;
  std::cout << node->getValue() << '\n';
  node = root -> subLeft -> subRight;
  std::cout << node->getValue() << '\n';
}

