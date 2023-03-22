#ifndef BINARYTREE
#define BINARYTREE

#include <functional>
#include <ios>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>

template <typename T> struct Node
{
    T Data;
    std::shared_ptr<Node<T>> LeftChild;
    std::shared_ptr<Node<T>> RightChild;

    Node<T>() { LeftChild = RightChild = std::shared_ptr<Node<T>>(nullptr); }
};

template <typename T> class BinaryTree
{
    using NodePtr = std::shared_ptr<Node<T>>;

  private:
    NodePtr _Root;
    size_t _Count;
    const int PRINT_WIDTH = 5;

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

    void _Display(std::ostream &out, const NodePtr &ptr, int depth = 0) const
    {
        if (ptr != nullptr)
        {
            _Display(out, ptr->RightChild, depth + 1);
            for (int i = 0; i < depth; i++)
            {
                out << "  ";
            }
            out << ptr->Data << std::endl;
            _Display(out, ptr->LeftChild, depth + 1);
        }
    }

    int _CalculateDepth(const NodePtr &ptr) const
    {
        if (ptr == nullptr)
        {
            return 0;
        }
        int leftDepth = _CalculateDepth(ptr->LeftChild);
        int rightDepth = _CalculateDepth(ptr->RightChild);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }

    void _RecureForRevolut(const NodePtr node)
    {
        if (node != nullptr)
        {
            NodePtr tmp = node->LeftChild;
            node->LeftChild = node->RightChild;
            node->RightChild = tmp;
            _RecureForRevolut(node->LeftChild);
            _RecureForRevolut(node->RightChild);
        }
    }

    void _CountLeaves(size_t &count, const NodePtr node) const
    {
        if (node != nullptr)
        {
            if (node->LeftChild == nullptr && node->RightChild == nullptr)
            {
                count++;
            }
            _CountLeaves(count, node->LeftChild);
            _CountLeaves(count, node->RightChild);
        }
    }

    void _RecureForWidth(const NodePtr node, int &depth,
                        std::shared_ptr<int[]> &width) const
    {
        if (node != nullptr)
        {
            width[depth] += 1;
            depth++;
            _RecureForWidth(node->LeftChild, depth, width);
            _RecureForWidth(node->RightChild, depth, width);
            depth--;
        }
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

    void LevelOrderTraverse(std::function<void(const T &)> func) const
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

    void Revolut() { _RecureForRevolut(_Root); }

    int Width() const
    {
        std::shared_ptr<int[]> width(new int[_Count]{0});
        for (size_t i = 0; i < _Count; i++)
        {
            width[i] = 0;
        }

        int depth = 0;
        _RecureForWidth(_Root, depth, width);

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

    void NonRecurringInOrderTraverse(std::function<void(const T &)> func)
    {
        std::stack<NodePtr> s;
        NodePtr ptr = _Root;
        while (!s.empty() || ptr != nullptr)
        {
            if (ptr != nullptr)
            {
                s.push(ptr);
                ptr = ptr->LeftChild;
            }
            else
            {
                ptr = s.top();
                s.pop();
                func(ptr->Data);
                ptr = ptr->RightChild;
            }
        }
    }

    int Depth() const { return _CalculateDepth(_Root); }

    friend std::ostream &operator<<(std::ostream &out,
                                    const BinaryTree<T> &tree)
    {
        tree._Display(out, tree._Root);
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

    size_t LeafCount() const
    {
        size_t count = 0;
        _CountLeaves(count, _Root);
        return count;
    }

    void SetChild(std::string path, T data) { _GetChild(path)->Data = data; }

    size_t Count() const { return _Count; }

    NodePtr Root() const { return _Root; }

    int TreeDepth() const
    {
        NodePtr node = _Root;
        int depth = 0;
        while (node != nullptr)
        {
            depth++;
            node = node->LeftChild;
        }
        return depth;
    }

    int TreeDegree() const
    {
        
    }
};

#endif