#ifndef BINARYTREE
#define BINARYTREE

#include <functional>
#include <ios>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

template <typename T> struct Node
{
    T Data;
    std::shared_ptr<Node<T>> LeftChild;
    std::shared_ptr<Node<T>> RightChild;

    Node<T>() { LeftChild = RightChild = std::shared_ptr<Node<T>>(nullptr); }
};

template <typename T> class BinaryTree
{
    typedef std::shared_ptr<Node<T>> NodePtr;

  private:
    NodePtr _Root;
    size_t _Count;

    NodePtr _GetChild(std::string path = "") const
    {
        NodePtr pointer = _Root;
        for (size_t i = 0; i < path.length(); i++)
        {
            if (path[i] == 'L' || path[i] == 'l')
            {
                if (pointer->LeftChild != nullptr)
                {
                    pointer = pointer->LeftChild;
                }
                else
                {
                    throw std::out_of_range(
                        "Data with the path does not exist.");
                }
            }
            else if (path[i] == 'R' || path[i] == 'r')
            {
                if (pointer->RightChild != nullptr)
                {
                    pointer = pointer->RightChild;
                }
                else
                {
                    throw std::out_of_range(
                        "Data with the path does not exist.");
                }
            }
            else
            {
                throw std::invalid_argument("Invalid path.");
            }
        }
        return pointer;
    }

  public:
    BinaryTree()
    {
        _Root = NodePtr(new Node<T>);
        _Root->LeftChild = nullptr;
        _Root->RightChild = nullptr;
        _Count = 1;
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

    void NonRecurringInOrderTraverse(std::function<void(const T &)> func,
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

    void Revolut() { RecureForRevolut(_Root); }

    void RecureForRevolut(const NodePtr node)
    {
        if (node != nullptr)
        {
            if (node->LeftChild != nullptr && node->RightChild != nullptr)
            {
                T tmp = node->LeftChild->Data;
                node->LeftChild->Data = node->RightChild->Data;
                node->RightChild->Data = tmp;
            }
            RecureForRevolut(node->LeftChild);
            RecureForRevolut(node->RightChild);
        }
    }

    int Width() const
    {
        std::shared_ptr<int[]> width(new int[_Count]{0});
        for (size_t i = 0; i < _Count; i++)
        {
            width[i] = 0;
        }
        
        int depth = 0;
        RecureForWidth(_Root, depth, width);
        
        int max = 0;
        for (size_t i = 0; i < _Count; i++)
        {
            if (width[i] > max)
            {
                max = width[i];
            }
        }
        return max;
    }

    void RecureForWidth(const NodePtr node, int &depth,
                        std::shared_ptr<int[]> &width) const
    {
        if (node != nullptr)
        {
            width[depth] += 1;
            depth++;
            RecureForWidth(node->LeftChild, depth, width);
            RecureForWidth(node->RightChild, depth, width);
            depth--;
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
                out << pointer->Data << " ";
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
        return out;
    }

    T &GetData(std::string path = "") const { return _GetChild(path)->Data; }

    void AddChild(std::string path, char side, T data)
    {
        NodePtr pointer = _GetChild(path);
        if (side == 'L' || side == 'l')
        {
            if (pointer->LeftChild == nullptr)
            {
                pointer->LeftChild = NodePtr(new Node<T>);
                pointer->LeftChild->Data = data;
            }
            else
            {
                throw std::out_of_range("Data with the path already exists.");
            }
        }
        else if (side == 'R' || side == 'r')
        {
            if (pointer->RightChild == nullptr)
            {
                pointer->RightChild = NodePtr(new Node<T>);
                pointer->RightChild->Data = data;
            }
            else
            {
                throw std::out_of_range("Data with the path already exists.");
            }
        }
        else
        {
            throw std::invalid_argument("Invalid side.");
        }
        _Count++;
    }

    void SetChild(std::string path, T data) { _GetChild(path)->Data = data; }

    size_t Count() const { return _Count; }

    NodePtr Root() const { return _Root; }
};

#endif