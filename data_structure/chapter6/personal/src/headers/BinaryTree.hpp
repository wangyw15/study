#ifndef BINARYTREE
#define BINARYTREE

#include <functional>
#include <ios>
#include <memory>
#include <queue>

template <typename T> struct Node
{
    T Data;
    std::shared_ptr<Node<T>> LeftChild;
    std::shared_ptr<Node<T>> RightChild;

    Node<T>() { LeftChild = RightChild = shared_ptr<Node<T>>(nullptr); }
};

template <typename T> class BinaryTree
{
    typedef std::shared_ptr<Node<T>> NodePtr;

  private:
    NodePtr _Root;

  public:
    BinaryTree()
    {
        _Root = NodePtr(new Node<T>);
        _Root->LeftChild = nullptr;
        _Root->RightChild = nullptr;
    }

    void PreOrderTraverse(std::function<void(const T &)> func,
                          const NodePtr node) const
    {
        if (node != nullptr)
        {
            func(node->Data);
            PreOrderTraverse(func, node->LeftChild);
            PreOrderTraverse(func, node->RightChild);
        }
    }

    void InOrderTraverse(std::function<void(const T &)> func,
                         const NodePtr node) const
    {
        if (node != nullptr)
        {
            InOrderTraverse(func, node->LeftChild);
            func(node->Data);
            InOrderTraverse(func, node->RightChild);
        }
    }

    void PostOrderTraverse(std::function<void(const T &)> func,
                           const NodePtr node) const
    {
        if (node != nullptr)
        {
            PostOrderTraverse(func, node->LeftChild);
            PostOrderTraverse(func, node->RightChild);
            func(node->Data);
        }
    }

    void LevelOrverTraverse(std::function<void(const T &)> func,
                            const NodePtr node) const
    {
        std::queue<NodePtr> q;
        NodePtr pointer;
        if (_Root != nullptr)
        {
            q.push(_Root);
            while (!q.empty())
            {
                pointer = q.front();
                q.pop();
                func(pointer->Data);
                if (pointer->LeftChild != nullptr)
                {
                    q.push(pointer->LeftChild);
                }
                if (pointer->RightChild != nullptr)
                {
                    q.push(pointer->RightChild);
                }
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    const BinaryTree<T> &tree)
    {
        std::queue<NodePtr> q;
        NodePtr pointer;
        if (tree._Root != nullptr)
        {
            q.push(tree._Root);
            while (!q.empty())
            {
                pointer = q.front();
                q.pop();
                out << pointer->Data;
                if (pointer->LeftChild != nullptr)
                {
                    q.push(pointer->LeftChild);
                }
                if (pointer->RightChild != nullptr)
                {
                    q.push(pointer->RightChild);
                }
                out << "\n";
            }
        }
        return out;
    }

    NodePtr Root() const { return _Root; }
};

#endif