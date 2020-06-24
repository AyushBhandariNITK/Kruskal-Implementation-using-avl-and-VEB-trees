#include "MyHeaders.h"
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
	//cout<<"Size ="<<u<<endl;
	struct vEBnode *newnode=new vEBnode;
	newnode->u=u;
	//cout<<"check"<<endl;
	newnode->min=-1;
	newnode->max=-1;
	
	if(u==2)
	{
		newnode->summary=NULL;
		newnode->cluster=NULL;
	}
	else
	{
		ll len=upsqrt(u);
		ll lens=lowsqrt(u);
		//cout<<"Summary size="<<len<<endl;;
		newnode->summary=create_node(len);
		vEBnode **arr=new vEBnode*[len];
		for(ll i=0;i<len;i++)
		{
			arr[i]=create_node(lens);
			//cout<<arr[i]<<endl;
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
	//cout<<"Insert "<<x<<endl;
	if(V->min==-1)
	{
		//cout<<"Empty insert at "<<x<<endl;
		empty_insert(V,x);
	}
	else
	{
		//cout<<"Here"<<endl;
		if(x<V->min)
		{
			//cout<<"swap"<<endl;
			swap(x,V->min);
		}
		if(V->u>2)
		{
			//cout<<"In greater than 2"<<endl;
			if(V->cluster[high(x,V->u)]->min==-1)
			{
				//cout<<"Insert at summary "<<high(x,V->u)<<endl;
				insert(V->summary,high(x,V->u));
				//cout<<" Empty Insert at cluster "<<high(x,V->u)<<" position "<<low(x,V->u)<<endl;
				empty_insert(V->cluster[high(x,V->u)],low(x,V->u));
			}
			else
			{
				//cout<<"Insert at cluster "<<high(x,V->u)<<" position "<<low(x,V->u)<<endl;
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
	// if(sq[u]!=-1)
	// 	return sq[u];
	ll x=(ll)sqrt(u);
	// sq[u]=x;
	return x;
}
ll lowsqrt(ll u)
{
	// if(sq[u]!=-1)
	// 	return sq[u];
	ll x= (ll)sqrt(u);
	// sq[u]=x;
	return x;
}
ll high(ll x, ll u)
{
	return floor(x/lowsqrt(u));
}
ll low(ll x, ll u)
{
	return x%lowsqrt(u);
}
ll index(ll x, ll y, ll u)
{
	return (x*lowsqrt(u)+y);
}
ll vEB_min(vEBnode *&V)
{
return V->min;
}
ll vEB_max(vEBnode *&V)
{
return V->max;
}
void display(vEBnode *V)
{
	cout<<V->u<<"\t"<<V->min<<"\t"<<V->max<<endl;
	if(V->summary!=NULL)
	{
		cout<<"Summary "<<V->u<<endl;
		display(V->summary);
	}
	ll child=upsqrt(V->u);
	if(V->cluster==NULL)
		return;
	for(ll i=0;i<child;i++)
	{
		cout<<"Children "<<V->u<<endl;
			display(V->cluster[i]);
	}
}
// int main()
// {
// 	vEBnode *root=create_node(16);
// 	insert(root,15);
// 	cout<<root->min<<endl;
// 	insert(root,5);
// 	cout<<root->min<<endl;
// 	insert(root,12);
// 	cout<<root->min<<endl;
// 	insert(root,2);
// 	cout<<root->min<<endl;
// 	insert(root,1);
// 	cout<<root->min<<endl;
// 	return 0;
// }
