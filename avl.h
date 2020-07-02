#include<bits/stdc++.h>
#include<math.h>
#define ll int32_t
#include<iostream>
#include <climits>
#include<math.h>
using namespace std;
class AVL
{
private:
   typedef struct TreeNode
  {
  	public:
    ll data;
    struct TreeNode* left;
    struct TreeNode* right;
    ll h;
  }tree;
tree *root=NULL,*pre=NULL,*suc=NULL;
public :
AVL()
{
    root=NULL;
}
ll max(ll l,ll r)
{
	return l>r?l:r;
}
ll height(tree* root)
{
  ll l,r;
  if(root==NULL)
    return 0;
  else 
  {
    l=height(root->left);
    r=height(root->right);
  }
  return max(l,r)+1;
}
void insert(ll value)
{
    root=insert_node(root,value);
} 
tree *newNode(ll item) 
{ 
  tree *temp = (tree*)malloc(sizeof(tree)); 
  temp->data = item; 
  temp->left = temp->right = NULL; 
  temp->h=0;
  return temp; 
}

tree* srotationright(tree* z)
{
  tree* y=z->right;
  tree* temp=y->left;
  y->left=z;
  z->right=temp;
   z->h=max(height(z->left),height(z->right))+1;
  y->h=max(height(y->left),z->h)+1;
  return y;
}
tree* srotationleft(tree* z)
{
  tree* y=z->left;
  tree* temp=y->right;
  y->right=z;
  z->left=temp;
  z->h=max(height(z->left),height(z->right))+1;
  y->h=max(height(y->left),z->h)+1;
  return y;
}
tree* drotationleft(tree* z)
{
  z->left=srotationright(z->left);
  return srotationleft(z);
}
tree* drotationright(tree* z)
{
 z->right=srotationleft(z->right);
 return srotationright(z);
}
tree* insert_node(tree* node, ll key) 
{ 
  
  if (node == NULL)
      return newNode(key); 
  if (key < node->data) 
    {
      node->left = insert_node(node->left,key);
      if(abs(height(node->left)-height(node->right))>1)
      {
        if (node->left->data>key)
         node= srotationleft(node);
        else 
          node=drotationleft(node);
      }
    } 
  else if(key>node->data)
  {
    node->right = insert_node(node->right,key); 
    if(abs(height(node->left)-height(node->right))>1)
      {
        if (node->right->data<key)
          node=srotationright(node);
        else 
          node=drotationright(node);
      }
  }
  else 
  {  cout<<"\n duplicate value not allowed ";
    return node;
  }
  node->h=max(height(node->left),height(node->right))+1;
  return node; 
}
tree* search(tree* root, ll key) 
{ 
    if (root == NULL || root->data== key) 
       return root; 
    if (root->data < key) 
       return search(root->right, key); 
    return search(root->left, key); 
}
tree* min(tree* root)
{
  tree *temp=root;
  while(temp->left)
  {
    temp=temp->left;
  }
  return temp;
}
tree* max(tree* root)
{
  tree *temp=root;
  while(temp->right)
  {
    temp=temp->right;
  }
  return temp;
} 
tree* delete_node(tree* root, ll key) 
{ 
  if (root == NULL)
   return root; 
  if (key < root->data) 
      root->left = delete_node(root->left, key);
  else if (key > root->data) 
      root->right = delete_node(root->right, key);
  else
  { 
    if (root->left == NULL) 
    { 
      tree *temp = root->right; 
      free(root); 
      return temp; 
    } 
    else if (root->right == NULL) 
    { 
      tree *temp = root->left; 
      free(root); 
      return temp; 
    }  
    tree* temp = min(root->right); 
    root->data= temp->data; 
    root->right = delete_node(root->right, temp->data); 
  }
  if(root!=NULL)
  {
    root->h=max(height(root->left),height(root->right))+1;
    if((height(root->left)-height(root->right))>1)
    { 
       if((height(root->left->left)-height(root->left->right))>=0)
            root=srotationleft(root);
       else if((height(root->left->left)-height(root->left->right))<0)
            root=drotationleft(root);
    }
    else if((height(root->left)-height(root->right))<-1)
    {  
      if((height(root->right->left)-height(root->right->right))>0)
           root=drotationright(root);
       else if((height(root->right->left)-height(root->right->right))<=0)
          root=srotationright(root);
    }
  }
  return root;
}
void preorder(tree* root)
{
  if(root)
  {
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
  }
}
/*
void build()
{
  int y=1,x;
  while(y)
  { 
  printf("\nenter the value");
           scanf("%d",&x);
           root=insert(root,x);
  cout<<" continue y/n (any no/0)";
  cin>>y;
  }         
}*/
/*void findPre(tree* root, ll key) 
{ 
  if (root == NULL)
     return ; 
  if (root->data == key) 
  { 
    if (root->left != NULL) 
    { 
      tree* temp = root->left; 
      while (temp->right) 
        temp = temp->right; 
      pre = temp ; 
    }
    return ; 
  } 
  else if (root->data > key) 
    findPre(root->left,key) ; 
  else  
  { 
    pre = root ; 
    findPre(root->right,key) ; 
  } 
}  
void  findSuc(tree* root, ll key) 
{ 
  if (root == NULL)
   return ; 
  if (root->data== key) 
  {     
    if (root->right != NULL) 
    { 
      tree* temp = root->right ; 
      while (temp->left) 
        temp = temp->left ; 
      suc = temp ; 
    } 
    return;
  }
  else if (root->data >key) 
  { 
    suc = root ; 
    findSuc(root->left, key) ; 
  } 
  else  
    findSuc(root->right, key) ; 
}*/
ll minval()
{
    return min(root)->data;
}
bool isempty()
{
    if(root==NULL)
        return true;
    else
        return false;
}

void del(ll value)
{
    root=delete_node(root,value);
}
};
