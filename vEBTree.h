#include<bits/stdc++.h>
#include<math.h>
#define ll int32_t
#include<iostream>
#include <climits>
using namespace std;
vector<ll> sq;
struct vEBnode
{
	ll u;
	ll min,max;
	vEBnode *summary;
	vEBnode **cluster;
};
struct vEBnode* create_node(ll u);
void empty_insert(vEBnode* V, ll x);
void insert(vEBnode* V, ll x);
ll successor(vEBnode *V, ll x);
ll predecessor(vEBnode *V,ll x);
void del_element(vEBnode *V, ll x);
ll upsqrt(ll u);
ll lowsqrt(ll u);
ll high(ll x, ll u);
ll low(ll x, ll u);
ll index(ll x, ll y, ll u);
struct vEBnode* create_node(ll u)
{
	
	struct vEBnode *newnode=new vEBnode;
	newnode->u=u;
	
	newnode->min=-1;
	newnode->max=-1;
	
	if(u<=2)//base case::set summary to null as there is no more summary of size 2.
	{
		newnode->summary=NULL;
		newnode->cluster=NULL;
	}
	else
	{
		ll len=upsqrt(u);
		ll lens=lowsqrt(u);
		
		newnode->summary=create_node(len);
		vEBnode **arr=new vEBnode*[len]; 
		for(ll i=0;i<len;i++)		{
			arr[i]=create_node(lens);
			
		}
		newnode->cluster=arr;
	}
	return newnode;
}
void setlogs()
{
	sq.resize(65537,-1);
}
void freelogs()
{
	sq.clear();
}
void empty_insert(vEBnode* V, ll x)
{
	V->min=x;
	V->max=x;
	return;
}
void insert(vEBnode* V, ll x)
{
	
	if(V->min==-1)
	{
		empty_insert(V,x);
	}
	else
	{
		
		if(x<V->min)
		{
			 
			swap(x,V->min);
		}
		if(V->u>2)
		{
			if(V->cluster[high(x,V->u)]->min==-1)
			{
				insert(V->summary,high(x,V->u));
				empty_insert(V->cluster[high(x,V->u)],low(x,V->u));
			}
			else
			{
				insert(V->cluster[high(x,V->u)],low(x,V->u));							
			}
		}
		if(x>V->max)
		{
			V->max=x;
		}

	}
}
ll successor(vEBnode *V, ll x)
{
	if(V->u==2)
	{
		if(x==0 && V->max==1)
			return 1;
		else
		 return -1;
	}
	else if(V->min!=-1 && x<V->min)
		return V->min;
	else
	{ 
		ll maxlow=V->cluster[high(x,V->u)]->max;
		if(maxlow!=-1 && low(x,V->u)<maxlow)
		{
			ll offset=successor(V->cluster[high(x,V->u)],low(x,V->u));
			return index(high(x,V->u),offset,V->u);
		}
		else
		{
			ll succ_cluster=successor(V->summary,high(x,V->u));
			if(succ_cluster==-1)
				return -1;
			else
			{
				ll offset=V->cluster[succ_cluster]->min;
				return index(succ_cluster,offset,V->u);
			}
		}
	}
}
ll predecessor(vEBnode *V,ll x)
{
	if(V->u==2)
	{
		if(x=1 && V->min==0)
			return 0;
		else
			return -1;
	}
	else if(V->max!=-1 && x>V->max)
		return V->max;
	else
	{
		ll minlow=V->cluster[high(x,V->u)]->min;
		if(minlow!=-1 && low(x,V->u)>minlow)
		{
			ll offset=predecessor(V->cluster[high(x,V->u)],low(x,V->u));
			return index(high(x,V->u),offset,V->u);
		}
		else
		{
			ll pred_cluster=predecessor(V->summary,high(x,V->u));
			if(pred_cluster==-1)
			{
				if(V->min!=-1 && x> V->min)
					return V->min;
				else
					return -1;

			}
			else
			{
				ll offset=V->cluster[pred_cluster]->max;
				return index(pred_cluster,offset,V->u);
			}
		}
	}
}
void del_element(vEBnode *V, ll x)
{
	if(V->min==V->max)
	{
		V->min=-1;
		V->max=-1;
	}
	else if(V->u==2)
	{
		if(x==0)
			V->min=1;
		else
			V->min=0;
		V->max=V->min;
	}
	else
	{
		if(x==V->min)
		{
			ll first_cluster=V->summary->min;
			x=index(first_cluster,V->cluster[first_cluster]->min,V->u);
			V->min=x;
		}
		del_element(V->cluster[high(x,V->u)],low(x,V->u));
		if(V->cluster[high(x,V->u)]->min==-1)
		{
			del_element(V->summary,high(x,V->u));
			if(x==V->max)
			{
				ll summary_max=V->summary->max;
				if(summary_max==-1)
					V->max=V->min;
				else
					V->max=index(summary_max,V->cluster[summary_max]->max,V->u);
			}
		}
		else if(x==V->max)
		{
			V->max=index(high(x,V->u),V->cluster[high(x,V->u)]->max,V->u);
		}
	}
}
bool isMember(vEBnode *V,ll x)
{
	if(x==V->min || x==V->max)
		return true;
	else if(V->u==2)
		return false;
	else
		return isMember(V->cluster[high(x,V->u)],low(x,V->u));
}
ll upsqrt(ll u)
{
	
	ll x=ceil(sqrt(u));

	return x;
}
ll lowsqrt(ll u)
{
	
	ll x= ceil(sqrt(u));

	return x;
}
ll high(ll x, ll u)
{
	
    ll div = ceil(sqrt(u)); 
	return x / div; 
}
ll low(ll x, ll u)
{

	ll mod = ceil(sqrt(u)); 
	return x % mod; 
}
ll index(ll x, ll y, ll u)
{
	
	ll ru = ceil(sqrt(u)); 
	return x * ru + y; 
}
ll vEB_min(vEBnode *&V)
{
return V->min;
}
ll vEB_max(vEBnode *&V)
{
return V->max;
}

/*int main()
{
	int ch;
	vEBnode *root;
	cout<<"0.create_node\n1.insert\n2.delete_element\n3.successor\n4.predecessor\n5.minimum\n.6.maximum\n7.exit "<<endl;
	cout<<"enter your choice:";
	cin>>ch;
	while(ch!=7)
	{
		switch(ch)
		{
			case 0:
			       ll x;
			       cout<<"enter your universe size that you want:"<<endl;
                   cin>>x;
			       root=create_node(x);
			       break;
			case 1:
			       ll val;
			       cout<<"insert your element:";
			       cin>>val;
			       insert(root,val);
			       break;
			case 2:
			       ll val2;
			       cout<<"enter the element to delete:";
			       cin>>val2;
                   del_element(root,val2);
                   break;
			case 3:
			       ll x2;
			       cout<<"enter any element from universe:";
			       cin>>x2;

			       cout<<"successor for the element-- "<<x2<<" --is:"<<successor(root,x2)<<endl;
			       break;
			case 4:
			       ll x3;
			       cout<<"enter any element from universe:";
			       cin>>x3;

			       cout<<"successor for the element--"<<x3<<"--is:"<<predecessor(root,x3)<<endl;
			       break;
			case 5:
                   cout<<root->min<<endl;
                   break;
            case 6:
			       cout<<root->max<<endl;
			       break;
			default:
			       cout<<"..invalid choice.."<<endl;
			       break;

		}
		cout<<"0.create_node\n1.insert\n2.delete_element\n3.successor\n4.predecessor\n5.minimum\n.6.maximum\n7.exit "<<endl;
		cout<<"enter your choice:";
	    cin>>ch;

	}
 	
 	return 0;
  }
*/
//if we enter first element out of the universe then it wouldn't give error because it is stored in min.