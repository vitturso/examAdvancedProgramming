#include <iostream>
#include <utility>
#include <memory>
#include <vector>

#ifndef BST_H
#define BST_H_


template<class KeyType, class ValueType, class CompareType = std::less<KeyType>>
class bst;

template<class Node, class KeyType, class ValueType, class CompareType, bool Const>
class __iterator
{
    friend class bst<KeyType, ValueType, CompareType>;
    public:
        using pair_type = std::pair<const KeyType, ValueType>;
        //if Const = true, then value_type is const pair (const iterator)
        // otherwise it is just pair
        using value_type = typename std::conditional<Const, const pair_type, pair_type>::type;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

    private:
        Node * current;
    public:
        __iterator() = default;
        explicit __iterator(Node * node) noexcept : current{node}
            {}

      
        reference operator*() const noexcept
        {
            return current->get_data();
        }

        pointer operator->() const noexcept
        {
            return &(*(*this));
        }

        
        __iterator& operator++() noexcept;

       
        __iterator operator++(int) noexcept
        {
            __iterator it{*this};
            ++(*this);
            return it;
        }
        
        
        friend bool operator==(const __iterator& left, const __iterator& right) noexcept
        {
            return left.current == right.current;
        }


       
       friend bool operator!=(const __iterator& left, const __iterator& right) noexcept
        {
            return !(left.current == right.current);
        }
};

template<class Node, class KeyType, class ValueType, class CompareType, bool Const>
__iterator<Node,KeyType,ValueType,CompareType,Const>& 
__iterator<Node,KeyType,ValueType,CompareType,Const>::operator++() noexcept
{
    if (!current)
    {
        return *this;
    }
    else if (current->get_right())
    {
        current = current->get_right().get();
        while (current->get_left())
        {
            current = current->get_left().get();
        }
    }
    else
    {
        Node *temp = current->get_parent();
        while (temp && current == temp->get_right().get())
        {
            current = temp;
            temp = temp->get_parent();
        }
        current = temp;
    }

    return *this;
}

template<class KeyType, class ValueType, class CompareType>
class bst
{

    private:
        class Node;
        std::unique_ptr<Node> root;
        using iterator = __iterator<Node,KeyType,ValueType,CompareType,false>;
        using const_iterator = __iterator<Node,KeyType,ValueType,CompareType,true>;


        Node *leftmost(Node * node) const;

      

        void swap(Node* successor, Node* current);

        void remove(const KeyType& key, Node* node);

        iterator find(const KeyType& key, Node *current);

        const_iterator find(const KeyType& key, Node *current) const;
    public:
        CompareType comparator;
        
        
        bst() noexcept = default;
        
        
        bst(std::pair<KeyType, ValueType> data, CompareType c = CompareType{}):
            root{std::make_unique<Node>(data)}, comparator{c} {}

        bst(const bst& bst)
        {    
            copy(bst.root);
        }
        
        bst(bst&& bst) noexcept : 
            root{std::move(bst.root)} {}
            
        // ~bst() ;
       
        //1. dell'esame
        std::pair<iterator, bool> insert(const std::pair<const KeyType, ValueType>& data);
       
        std::pair<iterator, bool> insert(std::pair<const KeyType, ValueType>&& data); 
        
        //2. dell'esame 
        template<class... Types>
        std::pair<iterator,bool> emplace(Types&&... args)
        {
            return insert(std::pair<const KeyType, ValueType>{std::forward<Types>(args)...});
        }
        
        //3. dell'esame 
        void clear() noexcept { root.reset(); }

        
        //4. dell'esame
        iterator begin() noexcept
        {
            return iterator{leftmost(root.get())};
        }

       
        const_iterator begin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

       
        const_iterator cbegin() const noexcept
        {
            const_iterator it{leftmost(root.get())};
            return it;
        }

        //5. dell'esame 
        iterator end() noexcept { return iterator{nullptr}; }

        const_iterator end() const noexcept
        {
            const_iterator it{nullptr};
            return it;
        }

       
        const_iterator cend() const noexcept
        {         
            const_iterator it{nullptr};    
            return it; 
        }


        //6. dell'esame
        iterator find(const KeyType& key)
        {
            return find(key, root.get());
        }

        //
        const_iterator find(const KeyType& key) const
        {
            return find(key, root.get());
        }
        

        //7. dell'esame
        void balance();
        
        //8. dell'esame
        ValueType& operator[](const KeyType& key) noexcept;
        ValueType& operator[](KeyType&& key) noexcept;
     
       //9. dell'esame 
        /*   friend  std::ostream& operator<<(std::ostream& os, const bst& x);
        {
        os << "[" << x._size << "] ";
        for (const auto &el : x)
        os << x << " ";

        os << std::endl;
        return os;
        }  
        */
       
         //10. dell'esame 
        void copy(const std::unique_ptr<Node> &node);
        
        void remove(const KeyType& key)
        {
            remove(key, root.get());
        }

        
        Node* getRoot() const
        {
            return root.get();
        }

       
        void buildTree(std::vector<std::pair<const KeyType,ValueType>> &nodes, int start, int end);
        
       
        int height(Node* node); 

      
        bool isBalanced(Node* node);
        
};
/*
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::successor(Node * node) const
{
    if (node->right)
    {
        return leftmost(node->right.get());
    }
    Node * p = node->parent;        
    while (p && node == p->right.get())
    {
        node = p;
        p = p->parent;
    }
    return p;
}
*/
template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType,ValueType,CompareType>::Node * bst<KeyType,ValueType,CompareType>::leftmost(Node * node) const
{
    if (node)
    {
        while (node->get_left())
        {
            node = node->get_left().get();
        }
    }

    return node;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::copy(const std::unique_ptr<bst<KeyType,ValueType,CompareType>::Node> &node)
{
    if (node)
    {
        insert(std::forward<const std::pair<const KeyType, ValueType>>(node->get_data()));
        copy(node->get_left());
        copy(node->get_right());
    }
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(const std::pair<const KeyType, ValueType> &data)
{
    // If tree isn't empty, current node will be created
    Node *current = root.get();
    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                current->set_left(data);
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                current->set_right(data);
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(data);
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
std::pair<typename bst<KeyType, ValueType, CompareType>::iterator, bool> 
bst<KeyType, ValueType, CompareType>::insert(std::pair<const KeyType, ValueType> &&data)
{
    // If tree isn't empty, cur node will be created
    Node *current = root.get();
    using pair_type = std::pair<const KeyType, ValueType>;

    while (current)
    {
        if (comparator(data.first, current->get_data().first))
        {
            if (!current->get_left())
            {
                //current->left = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_left(std::forward<pair_type>(data));
                iterator it{current->get_left().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, data.first))
        {
            if (!current->get_right())
            {
                //current->right = std::make_unique<Node>(
                //    std::forward<pair_type>(data), current);
                current->set_right(std::forward<pair_type>(data));
                iterator it{current->get_right().get()};
                return std::pair<iterator, bool>{it, true};
            }

            current = current->get_right().get();
        }
        else
        {
            //the key already exists in the tree
            iterator it{current};
            return std::pair<iterator, bool>{it, false};
        }
    }

    //current is root and it's nullptr
    root = std::make_unique<Node>(std::forward<pair_type>(data));
    iterator it{root.get()};
    return std::pair<iterator, bool>{it, true};
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::iterator 
bst<KeyType, ValueType, CompareType>::find(const KeyType &key, Node *current)
{
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
        }
        else
        {
            // it is equal return current one
            return iterator{current};
        }
    }

    // key does not exist in tree
    return end();
}

template <class KeyType, class ValueType, class CompareType>
typename bst<KeyType, ValueType, CompareType>::const_iterator
bst<KeyType, ValueType, CompareType>::find(const KeyType &key, Node *current) const
{    
    // until current equals to null pointer
    while (current)
    {
        // given key is smaller than current go left
        if (comparator(key, current->get_data().first))
        {
            current = current->get_left().get();
        }
        else if (comparator(current->get_data().first, key))
        {
            current = current->get_right().get();
        }
        else
        {
            // it is equal return current one
            return const_iterator{current};
        }
    }

    // key does not exist in tree
    return cend();
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::swap(Node* successor, Node* current)
{
    Node *succ_left, *succ_right, *succ_parent, *curr_left, *curr_right, *curr_parent;

    //Detach successor's children
    succ_left = successor->detach_left();
    succ_right = successor->detach_right();
    succ_parent = successor->get_parent();

    //detach successor from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (successor->is_right())
    {
        succ_parent->detach_right();
    }
    else if (successor->is_left())
    {
        succ_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    //Detach current's children
    curr_left = current->detach_left();
    curr_right = current->detach_right();
    curr_parent = current->get_parent();

    //detach current from its parent. If it has no parent (it is root)
    //we release the ownership of root
    if (current->is_right())
    {
        curr_parent->detach_right();
    }
    else if (current->is_left())
    {
        curr_parent->detach_left();
    }
    else
    {
        root.release();
    }
    
    //used to avoid cycles
    bool is_succ_child_of_current = succ_parent == current;
    
    if (succ_parent)
    {   
        // if there would not be this check, and succ_parent == current
        // then comparator woould compare the node against the node itself
        // returning therefore false and then assigning the right child of 
        // current to current itself
        if (!is_succ_child_of_current)
        {
            if (comparator(current->get_data().first, succ_parent->get_data().first))
            {
                succ_parent->set_left(current);
            }
            else
            {
                succ_parent->set_right(current);
            }
        }
    }
    else
    {
        root.reset(current);
    }
    current->set_left(succ_left);
    current->set_right(succ_right);

    if (curr_parent)
    {
        if (comparator(successor->get_data().first, curr_parent->get_data().first))
        {
            curr_parent->set_left(successor);
        }
        else
        {
            curr_parent->set_right(successor);
        }
    }
    else
    {
        root.reset(successor);
    }
    successor->set_left(curr_left);
    // curr_right would be null if check == true
    successor->set_right(is_succ_child_of_current ? current: curr_right);
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::remove(const KeyType &key, Node* node)
{
    
    Node* current = find(key, node).current;
    if (!current)
    {
        return;
    }
    Node* parent = current->get_parent();

    //Case 1: current is a leaf
    if (!current->get_left() && !current->get_right())
    {
        if (current != root.get())
        {
            //if current is left child of its parent
            if (parent->get_left().get() == current)
            {
                parent->destroy_left();
            }
            else
            {
                parent->destroy_right();
            }
            
        }
        //if current is the root
        else
        {
            root.reset();
            return;
        }
    }
    //Case 2: current has both right and left child
    else if (current->get_left() && current->get_right())
    {
      
        Node* successor = leftmost(current->get_right().get());
        //we swap successor and current
        swap(successor, current);
        //recursively delete current, which now is either a leaf or a node
        //with only one child
        remove(key, current);
    }
    //Case 3: current has only one child
    else
    {
        Node* child = (current->get_left()) ? current->detach_left() : current->detach_right();

        if (current != root.get())
        {
            if (current == parent->get_left().get())
            {
                parent->detach_left();
                parent->set_left(child);
            }
            else
            {
                parent->detach_right();
                parent->set_right(child);
            }
        }
        else
        {
            root.release();
            child->set_parent(nullptr);
            root.reset(child);
        }

        delete current;
    }
}

template <class KeyType, class ValueType, class CompareType>
std::ostream &operator<<(std::ostream &os, const bst<KeyType,ValueType,CompareType> &x)
{
    for (auto &node : x)
    {
        os << "(" << node.first << ", " << node.second << ")";
    }
    return os;
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType,ValueType,CompareType>::buildTree(std::vector<std::pair<const KeyType, ValueType>> &nodes, int start, int end)
{
    if (start > end)
        return;

    if (start == end)
    {
        insert(nodes[start]);
        return;
    }
    // Get the middle element
   int mid = (start + end) / 2;
    insert(nodes[mid]);

    buildTree(nodes, start, mid - 1);
    buildTree(nodes, mid + 1, end);
}

template <class KeyType, class ValueType, class CompareType>
int bst<KeyType, ValueType, CompareType>::height(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + std::max(height(node->get_left().get()),
                        height(node->get_right().get()));
}

template <class KeyType, class ValueType, class CompareType>
bool bst<KeyType,ValueType,CompareType>::isBalanced(typename bst<KeyType, ValueType, CompareType>::Node* node)
{
    if (!node)
    {
        return true;
    }

    int lh, rh;

    lh = height(node->get_left().get());
    rh = height(node->get_right().get());

    return abs(lh - rh) <= 1 && isBalanced(node->get_left().get()) && isBalanced(node->get_right().get());
}

template <class KeyType, class ValueType, class CompareType>
void bst<KeyType, ValueType, CompareType>::balance()
{
    std::vector<std::pair<const KeyType, ValueType>> nodes;
    for(auto& node : *this)
    {
        nodes.push_back(node);
    }

    clear();

    buildTree(nodes, 0, nodes.size() - 1);
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](const KeyType &key) noexcept
{
    Node *current = root.get();

    while (current)
    {
        if (comparator(key, current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                current->set_left(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, key))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
                current->set_right(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{key, ValueType{}};
    root = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(pair), nullptr);
    return root->get_data().second;
}

template <class KeyType, class ValueType, class CompareType>
ValueType& bst<KeyType,ValueType,CompareType>::operator[](KeyType &&key) noexcept
{
    Node *current = root.get();
    while (current)
    {
        if (comparator(std::forward<KeyType>(key), current->get_data().first))
        {
            if (!current->get_left())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<const KeyType>(key), ValueType{}
                };
                current->set_left(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_left()->get_data().second;
            }
            else
            {
                current = current->get_left().get();
            }
        }
        else if (comparator(current->get_data().first, std::forward<KeyType>(key)))
        {

            if (!current->get_right())
            {
                auto pair = std::pair<const KeyType, ValueType>{
                    std::forward<const KeyType>(key), ValueType{}
                };
                current->set_right(std::forward<std::pair<const KeyType, ValueType>>(pair));
                return current->get_right()->get_data().second;
            }
            else
            {
                current = current->get_right().get();
            }
        }
        else
        {
            //element found
            return current->get_data().second;
        }
    }

    //root is null
    auto pair = std::pair<const KeyType, ValueType>{std::forward<const KeyType>(key), ValueType{}};
    root = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(pair), nullptr);
    return root->get_data().second;
}

template <class KeyType, class ValueType, class CompareType>
class bst<KeyType, ValueType, CompareType>::Node
{
private:
    
    std::pair<const KeyType, ValueType> data;
    
    std::unique_ptr<Node> left, right;
   
    Node *parent;

public:
  
    Node() = default;

   
    Node(std::pair<const KeyType, ValueType> data) : data{data}, left{nullptr}, right{nullptr},
                                               parent{nullptr} {}
   
    Node(std::pair<const KeyType, ValueType> data, Node *parent) : data{data}, left{nullptr}, right{nullptr},
                                                             parent{parent} {}


   
    Node(const Node& node) = delete;
    
    Node(Node&& node) noexcept :
        data{std::move(node.data)},
        left{std::move(node.left)},
        right{std::move(node.right)},
        parent{std::move(parent)} 
    {}

   
    Node& operator=(Node &&node) noexcept
    {
        data = std::move(node.data);
        left = std::move(node.left);
        right = std::move(node.right);
        parent = std::move(node.parent);
        return *this;
    }
    
   
    Node& operator=(const Node&) = delete;

  
    bool is_right() const noexcept
    {
        return (parent && (parent->right.get() == this));
    }

   
    bool is_left() const noexcept
    {
        return (parent && (parent->left.get() == this));
    }

    
    bool is_root() const noexcept
    {
        return !is_left() && !is_right();
    }

  
    const std::pair<const KeyType, ValueType> &get_data() const noexcept
    {
        return data;
    }

  
    std::pair<const KeyType, ValueType> &get_data() noexcept
    {
        return data;
    }

  
    std::unique_ptr<Node> &get_left() noexcept
    {
        return left;
    }

   
    const std::unique_ptr<Node> &get_left() const noexcept
    {
        return left;
    }

   
    std::unique_ptr<Node> &get_right() noexcept
    {
        return right;
    }

    const std::unique_ptr<Node> &get_right() const noexcept
    {
        return right;
    }

    
    Node *get_parent() const noexcept
    {
        return parent;
    }

   
    void set_left(Node *new_node)
    {
        //avoid creation of cycles
        if (parent && parent == new_node)
        {
            throw std::invalid_argument("Parent is equal to the node it is to be inserted");
        }

        if (new_node)
        {
             //can be setted iff left is null
            if (left)
            {
                throw std::invalid_argument("Left node already exists. It is not possible to attach a new one.");
            }

            left.reset(new_node);
            left->parent = this;
        }
        else
        {
            destroy_left();
        }
        
    }

   
    void set_left(std::pair<const KeyType, ValueType> &&data)
    {
        if (!left)
        {
            left = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(data), this);
        }
        else
        {
            throw std::logic_error("Left node already exists. It is not possible to attach a new one.");
        }
        
    }

    
    
    void set_left(const std::pair<const KeyType, ValueType> &data)
    {
        if (!left)
        {
            left = std::make_unique<Node>(data, this);
        }
        else
        {
            throw std::logic_error("Left node already exists. It is not possible to attach a new one.");
        }
        
    }
    
   
    void set_right(Node* new_node)
    {
        //avoid cycle
        if (parent && parent == new_node)
        {
            throw std::invalid_argument("Parent is equal to the node it is to be inserted");
        }

        if (new_node)
        {
            //std::cout << data.first << ": hola" << std::endl;
            if (right)
            {
                throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
            }
            right.reset(new_node);
            right->parent = this;
        }
        else
        {
            destroy_right();
        }
        
    }

   
    void set_right(std::pair<const KeyType, ValueType> &&data)
    {
        if (!right)
        {
            right = std::make_unique<Node>(std::forward<std::pair<const KeyType, ValueType>>(data), this);
        }
        else
        {
            throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
        }
    }

   
    void set_right(const std::pair<const KeyType, ValueType> &data)
    {
        if (!right)
        {
            right = std::make_unique<Node>(data, this);
        }
        else
        {
            throw std::logic_error("Right node already exists. It is not possible to attach a new one.");
        }
    }
    
 
    void set_parent(Node * node) noexcept
    {
        parent = node;
    }

    
    Node* detach_right() noexcept
    {
        Node* ptr = nullptr;
        if (right)
        {
            right->set_parent(nullptr);
            ptr = right.release();
            right = nullptr;
        }
        return ptr;
    
    }

   
    Node* detach_left() noexcept
    {
        Node* ptr = nullptr;
        if (left)
        {
            left->set_parent(nullptr);
            ptr = left.release();
            left = nullptr;
        }
        return ptr;
    }

    
    void detach_children() noexcept
    {
        detach_right();
        detach_left();
    }

   
    void destroy_right() noexcept
    {
        if (right) 
        {
            right.reset();
        }
    }

   
    void destroy_left() noexcept
    {
        if (left)
        {
            left.reset();
        }
        
    }
};


#endif
