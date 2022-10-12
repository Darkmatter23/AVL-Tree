//add va find moshkel darand
//remove naghes as
//rotation ha va balance ha check shavand

#include<iostream>
#include<string>
#include <algorithm>
#include<vector>
using namespace std;

struct node
{
	double data;
	node* left;
	node* right;
	node* parent;
	int height;
	int balance_factor;
	node(double x) { data = x; parent = left = right = NULL; height = 1; balance_factor = 0; }
};
class AVL {
public:
	node* root;
	int size;
	vector<int> mylist;
	AVL() :root(NULL), size(0) {}
	int get_height(node* mynode)
	{
		int height = 0;
		if (root != NULL)
		{
			height = 1 + max(get_height(mynode->left), get_height(mynode->right));
		}
		return height;
	}
	void set_height(node* mynode)
	{
		mynode->height = get_height(mynode);
	}
	int balance_factor(node* mynode)
	{
		return get_height(mynode->left) - get_height(mynode->right);
	}
	node* insert(node* mynode, double x)
	{
		if (!mynode) {
			cout << "added" << endl;
			return new node(x);
		}
		if (x < mynode->data)
			mynode->left = insert(mynode->left, x);
		else if (x > mynode->data)
			mynode->right = insert(mynode->right, x);
		else
		{
			cout << "already in there" << endl;
			return mynode;
		}
		return mynode;

	}
	node* findmin()
	{
		node* curr = root;
		while (curr->left != NULL)
			curr = curr->left;
		return curr;
	}
	void delete_node(node* mynode) {
		if (mynode) {
			delete_node(mynode->left);
			delete_node(mynode->right);
			delete mynode; // Post Order Deletion
		}
	}
	bool exist(double x)
	{
		if (root == NULL)
			return false;
		node* cur = root;
		while (cur != NULL)
		{
			if (x == cur->data)
				return true;
			else if (x < cur->data)
				cur = cur->left;
			else
				cur = cur->right;
		}
		return false;
	}
	void inorder(node* mynode)
	{
		if (mynode == NULL)
			return;
		inorder(mynode->left);
		cout << mynode->data << " ";
		inorder(mynode->right);
	}

	void remove(node* mynode,double x)
	{
		if (!exist(x) || mynode == NULL || root == NULL)
		{
			cout << "does not exist" << endl;
			return;
		}
	
		node* parent = mynode->parent;
		if (mynode->left == nullptr && mynode->right == nullptr) {
			if (parent == nullptr)
				root = nullptr;
			else if (parent->left == mynode)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete mynode;
			balance(parent);
			size--;
		}

		else if (mynode->right == nullptr) {
			if (parent == nullptr) {
				root = mynode->left;
				root->parent = nullptr;
			}
			else if (parent->left == mynode) {
				parent->left = mynode->left;
				mynode->left->parent = parent;
			}
			else {
				parent->right = mynode->left;
				mynode->left->parent = parent;
			}
			delete mynode;
			balance(parent);
			size--;
		}
		else if (mynode->left == nullptr) {
			if (parent == nullptr) {
				root = mynode->right;
				root->parent = nullptr;
			}
			else if (parent->left == mynode) {
				parent->left = mynode->right;
				mynode->right->parent = parent;
			}
			else {
				parent->right = mynode->right;
				mynode->right->parent = parent;
			}
			delete mynode;
			balance(parent);
			size--;
		}
		else {
			node* temp = mynode->right;
			while (temp->left != nullptr)
				temp = temp->left;
			mynode->data = temp->data;
			remove(temp,temp->data);
		}
	
	}











	//Find Node(NOPE!)
	void find(double x)
	{
		if (exist(x))
		{
			cout << x << endl;
			return;
		}
		


		cout << "not found" << endl;
		//mylist.clear();
	}
	
	





	/*Print Reversed(DONE!)
	void print_reverse(node* root)
	{
		for (int i = 0; i < mylist.size(); i++)
			cout << mylist[i] << endl;
	}

	Vector Of Reverse Sorted Numbers(DONE!)
	void sorted_list(node* mynode)
	{
		if (mynode == NULL)
			return;
		sorted_list(mynode->left);
		mylist.push_back(mynode->data);
		sorted_list(mynode->left);
	}*/






	//Balancing(NOT Tested!)
	void balance(node* mynode)
	{
		if (balance_factor(mynode) == 2)
		{
			if (balance_factor(mynode->right) < 0)
				right_rotation(mynode->right);
			left_rotation(mynode);
			cout << "balancing " << mynode->data << endl;
		}
		if (balance_factor(mynode) == -2)
		{
			if (balance_factor(mynode->left) > 0)
				left_rotation(mynode->left);
			right_rotation(mynode);
			cout << "balancing " << mynode->data << endl;
		}
	}
	//Left Rotation(NOT Tested!)
	void left_rotation(node* mynode)
	{
		node* newnode = mynode->right;
		mynode->right = newnode->left;
		newnode->left = mynode;
	}
	//Right Rotation(NOT Tested!)
	void right_rotation(node* mynode)
	{
		node* newnode = mynode->left;
		mynode->left = newnode->right;
		newnode->right = mynode;
	}
};


int main()
{
	AVL mytree;
	int n;
	string command;
	double number;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> command ;
		if (command == "add")
		{
			cin >> number;
			mytree.root=mytree.insert(mytree.root,number);
		}
		if (command == "remove")	
		{
			cin >> number;
			mytree.remove(mytree.root,number);
		}
		if (command == "find")
		{
			cin >> number;
			mytree.find(number);
		}
		if (command == "print")
		{
			mytree.inorder(mytree.root);
			cout << endl;
		}
	}
	return 0;
}