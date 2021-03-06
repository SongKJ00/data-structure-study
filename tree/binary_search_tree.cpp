#include <iostream>
#include <exception>
#include <map>

class Node
{
public:
  enum class CHILD_TYPE{
    LEFT,
    RIGHT
  };

  int data_;
  std::map<Node::CHILD_TYPE, Node*> children;
public:
  Node(int data) :
    data_(data)
  {
    children[Node::CHILD_TYPE::LEFT] = nullptr;
    children[Node::CHILD_TYPE::RIGHT] = nullptr;
  }
};

class Tree
{
public:
  Node* head_;

public:
  Tree(int data) :
    head_(new Node(0))
  {
    SetRootNode(new Node(data));
  }

  Node* GetRootNode()
  {
    // 왼쪽에 루트 노드가 있는 경우
    if((head_->children[Node::CHILD_TYPE::LEFT] != nullptr) && (head_->children[Node::CHILD_TYPE::RIGHT] == nullptr))
    {
      return head_->children[Node::CHILD_TYPE::LEFT];
    }
    // 오른쪽에 루트 노드가 있는 경우
    else if((head_->children[Node::CHILD_TYPE::LEFT] == nullptr) && (head_->children[Node::CHILD_TYPE::RIGHT] != nullptr))
    {
      return head_->children[Node::CHILD_TYPE::RIGHT];
    }
    // 루트 노드가 없는 경우
    else if((head_->children[Node::CHILD_TYPE::LEFT] == nullptr) && (head_->children[Node::CHILD_TYPE::RIGHT] == nullptr))
    {
      throw std::runtime_error("[GetRootNode] cannot find root node");
    }
    // 루트 노드가 2개인 경우(Invalid state)
    else
    {
      throw std::runtime_error("[GetRootNode] root node is more than 2");
    }
  }

  void SetRootNode(Node* node)
  {
    Node::CHILD_TYPE direction;

    if((head_->children[Node::CHILD_TYPE::LEFT] != nullptr) || (head_->children[Node::CHILD_TYPE::RIGHT] != nullptr))
    {
      throw std::runtime_error("[SetRootNode] another root node is already assigned");
    }

    if(node->data_ <= head_->data_)
    {
      direction = Node::CHILD_TYPE::LEFT;
    }
    else
    {
      direction = Node::CHILD_TYPE::RIGHT;
    }
    head_->children[direction] = node;
  }

  void Inorder(Node* node)
  {
    if(node != nullptr)
    {
      Inorder(node->children[Node::CHILD_TYPE::LEFT]);
      std::cout << node->data_ << " ";
      Inorder(node->children[Node::CHILD_TYPE::RIGHT]);
    }
  }

  void InsertNode(int data)
  {
    try
    {
      DoInsertNode(data);
    }
    catch(std::exception& e)
    {
      std::cout << "[INSERT NODE ERR] : " << e.what() << std::endl;
    }
  }

  void DeleteNode(int data)
  {
    try
    {
      DoDeleteNode(data);
    }
    catch(std::exception& e)
    {
      std::cout << "[DELETE NODE ERR] : " << e.what() << std::endl;
    }
  }

private:
  void DoInsertNode(int data)
  {
    Node* currParentNode = head_;   // 현재 노드의 부모를 저장할 포인터
    Node* currNode = GetRootNode(); // 현재 노드를 저장할 포인터

    // 현재 노드가 null일 때까지(더 이상 트리의 밑으로 내려갈 수 없을 때까지)
    while(currNode)
    {
      // data가 중복되는 경우(트리에 이미 있는 경우)
      if(data == currNode->data_)
      {
        throw std::runtime_error("data is already existed. data : " + std::to_string(data));
      }

      currParentNode = currNode;

      // 현재 노드보다 값이 작은 경우 -> 현재 노드의 왼쪽으로 이동
      if(data < currNode->data_)
      {
        currNode = currNode->children[Node::CHILD_TYPE::LEFT];
      }
      // 현재 노드보다 값이 큰 경우 -> 현재 노드의 오른쪽으로 이동
      else
      {
        currNode = currNode->children[Node::CHILD_TYPE::RIGHT];
      }
    }

    Node* newNode = new Node(data);
    // 현재 노드의 부모보다 값이 작은 경우 -> 부모의 왼쪽에 할당
    if(data < currParentNode->data_)
    {
      currParentNode->children[Node::CHILD_TYPE::LEFT] = newNode;
    }
    // 현재 노드의 부모보다 값이 큰 경우 -> 부모의 오른쪽에 할당
    else
    {
      currParentNode->children[Node::CHILD_TYPE::RIGHT] = newNode;
    }
  }

  void DoDeleteNode(int data)
  {
    std::pair<Node*, Node*> p = SearchNode(data); // 삭제할 노드 검색
    Node* parent = p.first;
    Node* target = p.second;
    bool isTargetLeftOfParent = parent->children[Node::CHILD_TYPE::LEFT] == target ? true : false;

    // 잎 노드인 경우
    if((target->children[Node::CHILD_TYPE::LEFT] == nullptr) && (target->children[Node::CHILD_TYPE::RIGHT] == nullptr))
    {
      if(isTargetLeftOfParent)
      {
        parent->children[Node::CHILD_TYPE::LEFT] = nullptr;
      }
      else
      {
        parent->children[Node::CHILD_TYPE::RIGHT] = nullptr;
      }
      delete target;
    }
      // 왼쪽 서브 트리만 있는 경우
    else if((target->children[Node::CHILD_TYPE::LEFT] != nullptr) && (target->children[Node::CHILD_TYPE::RIGHT] == nullptr))
    {
      Node* swapNode = GetSwapNode(target->children[Node::CHILD_TYPE::LEFT], Node::CHILD_TYPE::LEFT);
      if(isTargetLeftOfParent)
      {
        parent->children[Node::CHILD_TYPE::LEFT] = swapNode;
      }
      else
      {
        parent->children[Node::CHILD_TYPE::RIGHT] = swapNode;
      }

      if(target->children[Node::CHILD_TYPE::LEFT] != swapNode)
      {
        swapNode->children[Node::CHILD_TYPE::LEFT] = target->children[Node::CHILD_TYPE::LEFT];
      }
      delete target;
    }
      // 오른쪽 서브 트리만 있는 경우
    else if((target->children[Node::CHILD_TYPE::LEFT] == nullptr) && (target->children[Node::CHILD_TYPE::RIGHT] != nullptr))
    {
      Node* swapNode = GetSwapNode(target->children[Node::CHILD_TYPE::RIGHT], Node::CHILD_TYPE::LEFT);
      if(isTargetLeftOfParent)
      {
        parent->children[Node::CHILD_TYPE::LEFT] = swapNode;
      }
      else
      {
        parent->children[Node::CHILD_TYPE::RIGHT] = swapNode;
      }

      if(target->children[Node::CHILD_TYPE::RIGHT] != swapNode)
      {
        swapNode->children[Node::CHILD_TYPE::RIGHT] = target->children[Node::CHILD_TYPE::RIGHT];
      }
      delete target;
    }
      // 양 쪽에 서브 트리가 있는 경우
    else
    {
      Node* swapNode = GetSwapNode(target->children[Node::CHILD_TYPE::RIGHT], Node::CHILD_TYPE::LEFT);
      if(isTargetLeftOfParent)
      {
        parent->children[Node::CHILD_TYPE::LEFT] = swapNode;
      }
      else
      {
        parent->children[Node::CHILD_TYPE::RIGHT] = swapNode;
      }

      if(swapNode != target->children[Node::CHILD_TYPE::LEFT])
      {
        swapNode->children[Node::CHILD_TYPE::LEFT] = target->children[Node::CHILD_TYPE::LEFT];
      }
      if(swapNode != target->children[Node::CHILD_TYPE::RIGHT])
      {
        swapNode->children[Node::CHILD_TYPE::RIGHT] = target->children[Node::CHILD_TYPE::RIGHT];
      }
      delete target;
    }
  }

  Node* GetSwapNode(Node* root, Node::CHILD_TYPE direction)
  {
    Node* parentNode = root;

    if(parentNode->children[direction] == nullptr)
    {
      return parentNode;
    }

    while(parentNode->children[direction])
    {
      Node* swapNode = parentNode->children[direction];
      if(swapNode->children[direction] == nullptr)
      {
        parentNode->children[direction] = nullptr;
        return swapNode;
      }
      parentNode = parentNode->children[direction];
    }

    throw std::runtime_error("Cannot find swap node!");
  }

  /* Find node that data is equal with argument */
  /* return type : first - parent pointer, second - current pointer */
  std::pair<Node*, Node*> SearchNode(int data)
  {
    Node* currParentNode = head_;
    Node* currNode = GetRootNode();

    while(currNode)
    {
      // data is equal with argument
      // return current node pointer
      if(currNode->data_ == data)
      {
        return std::make_pair(currParentNode, currNode);
      }

      currParentNode = currNode;

      if(data < currNode->data_)
      {
        currNode = currNode->children[Node::CHILD_TYPE::LEFT];
      }
      else
      {
        currNode = currNode->children[Node::CHILD_TYPE::RIGHT];
      }
    }

    throw std::runtime_error("Cannot find " + std::to_string(data));
  }
};

int main(void)
{
  /*
   *         HEAD
   *        /
   *       5 <- ROOT
   *     /   \
   *    3    10
   *   / \   / \
   *  1   4 9   11
   */
  /* Insert */
  Tree t(5);
  t.InsertNode(3);
  t.InsertNode(1);
  t.InsertNode(10);
  t.InsertNode(9);
  t.InsertNode(4);
  t.InsertNode(11);

  /* Print Inorder result */
  std::cout << "Before delete" << std::endl;
  t.Inorder(t.GetRootNode());
  std::cout << std::endl;

  /* Delete */
  t.DeleteNode(5);    // Delete 5(root)
  t.DeleteNode(13);   // Delete 13 - No 13 in tree
  t.DeleteNode(10);   // Delete 10

  /* Print Inorder result */
  std::cout << "After delete" << std::endl;
  t.Inorder(t.GetRootNode());
  std::cout << std::endl;
}