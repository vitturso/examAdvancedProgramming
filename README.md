# examAdvancedProgramming
In my project I tried to implement the binary search tree using the namespace `std`; after which I defined the class bst by means of a **template**. In this class I have defined the TreeNode structure
 and various public functions including: the insertion of a node, the cancellation of a node, the size of the nodes, the Preorder functions (node, left, right),
In-order (left, node, right),
Postorder (left, right, node) and more. So always with the templates I defined these functions which I then called in main. To define these functions I used the easiest method for me but completely
analogous to the one mentioned in the text,  for example for the insert function - which can be written in the following various ways:
Insert
std::pair<iterator, bool> insert (value_type const& value);
std::pair<iterator, bool> insert (value_type&& value);
iterator insert (const_iterator hint, value_type const& value);
iterator insert (const_iterator hint, value_type&& value);
void insert (InputIterator first, InputIterator last);
void insert (std::initializer_list<value_type>);
I used the fifth version.
With the comado make I can run the program.
