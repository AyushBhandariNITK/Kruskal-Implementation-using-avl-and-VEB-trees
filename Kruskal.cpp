#include "vEBTree.h"
#include "avl.h"
#define uni_size 65536
using namespace std;
ll findparent(vector<ll> &parent, ll v)
{
	while(parent[v]!=-1)
	{
		v=parent[v];
	}
	return v;
}
void Union(vector<ll> &parent,ll a,ll b)
{
	if(a!=b)
		parent[a]=b;	
}
pair<ll,ll> withAVL(string file)
{
	ifstream myfile(file);
	if(!myfile.is_open())
	{
		cout<<"File not found\n";
		return make_pair(-1,-1);
	}
	ll nodes,edges,maxweight;
	myfile>>nodes>>edges;
	ll a,b,weight;
	AVL root;
	auto start = std::chrono::high_resolution_clock::now();
	unordered_map<ll,forward_list<pair<ll,ll>>> wtedge;
	for(ll i=0;i<edges;i++)
	{
		myfile>>a>>b>>weight;
		if(wtedge.find(weight)==wtedge.end())//weight doesn't exist
		{
			//new entry
			forward_list<pair<ll,ll>> temp;
			root.insert(weight);
			temp.push_front(make_pair(a,b)); // new list with a ,b
			wtedge[weight]=temp;//insert in map
		}
		else
		{
			forward_list<pair<ll,ll>> temp=wtedge.at(weight);
			temp.push_front(make_pair(a,b));
			wtedge[weight]=temp;
		}
	}
	myfile.close();
	forward_list<pair<ll,ll>> temp;
	vector<ll> parent(nodes,-1);
	ll num=0,mstweight=0;
	ll minweight,pa,pb;
	while(num<(nodes-1) && !root.isempty())
	{
		minweight=root.minval();
		temp=wtedge[minweight];
		a=temp.front().first;
		b=temp.front().second;
		temp.pop_front();
		wtedge[minweight]=temp;
		if(temp.empty())
		{
			wtedge.erase(minweight);
			root.del(minweight);
		}
		pa=findparent(parent,a);
		pb=findparent(parent,b);
		if(pa!=pb) // no cycle
		{
			Union(parent,pa,pb);
			mstweight+=minweight;
			num++;
		}
	}

	cout<<"\n min cost = "<<mstweight<<"  edges "<<edges;
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout<<" AVL Tree ="<<ms<<endl;
	return make_pair(edges,(ll)ms);
}
pair<ll,ll> withVEB(string file)
{
	
	vEBnode *root=create_node(uni_size);
	ifstream myfile(file);
	if(!myfile.is_open())
	{
		cout<<"File not found\n";
		return make_pair(-1,-1);
	}
	ll nodes,edges,maxweight;
	myfile>>nodes>>edges;
	ll a,b,weight;
	std::ios::sync_with_stdio(false);
	auto start = std::chrono::high_resolution_clock::now();
	unordered_map<ll,forward_list<pair<ll,ll>>> wtedge;
	for(ll i=0;i<edges;i++)
	{
		myfile>>a>>b>>weight;
		if(wtedge.find(weight)==wtedge.end())//weight doesn't exist
		{
			//new entry
			forward_list<pair<ll,ll>> temp;
			insert(root,weight);
			temp.push_front(make_pair(a,b)); // new list with a ,b
			wtedge[weight]=temp;//insert in map
		}
		else
		{
			forward_list<pair<ll,ll>> temp=wtedge.at(weight);
			temp.push_front(make_pair(a,b));
			wtedge[weight]=temp;
		}
	}
	myfile.close();
	forward_list<pair<ll,ll>> temp;
	vector<ll> parent(nodes,-1);
	ll num=0,mstweight=0;
	ll minweight,pa,pb;
	while(num<(nodes-1) && root->min!=-1)
	{
		minweight=root->min;
		temp=wtedge[minweight];
		a=temp.front().first;
		b=temp.front().second;
		temp.pop_front();
		wtedge[minweight]=temp;
		if(temp.empty())
		{
			wtedge.erase(minweight);
			del_element(root,minweight);
		}
		pa=findparent(parent,a);
		pb=findparent(parent,b);
		if(pa!=pb) // no cycle
		{
			Union(parent,pa,pb);
			mstweight+=minweight;
			num++;
		}
	}
	cout<<"\n min cost = "<<mstweight;
	cout<<"  edges "<<edges ;
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	
	// freelogs()
	std::ios::sync_with_stdio(true);
	cout<<" vEB tree "<<ms<<endl;
	return make_pair(edges,(ll)ms);
	
}
int main()
{
	int j=5,n;
	ll edges, nodes, a,b, weight;
	ofstream fp;

	pair<ll,ll> res;

	cout<<"1.User input 2.File input ";
	cout<<"\nenter the choice ";
	cin>>n;
	switch(n)
	{
		case 1:
				 fp.open("f.txt", ios::out | ios::in);
					cout<<" nodes and edges ";
					cin>>nodes;
					cin>>edges;
					fp <<nodes<< "\n";
					fp << edges<< "\n";
					for(ll i=0; i<edges; i++)
					{
						cout<<"values of a and b and weight  ";
						cin>>a>>b>>weight;

						fp << a << " ";	
						fp << b << " ";
						fp << weight << "\n ";
					}
				fp.close();
				
				for(int i=149;i<=149;i++)
				{
					cout<<"\n*****************************************************";
					string fl="f.txt";
					res=withVEB(fl);
					res=withAVL(fl);
					cout<<"*****************************************************\n";

				}
				break;
		case 2:
				for(int i=0;i<=5;i++)
				{
					cout<<"\n*****************************************************";
					string fl="inpwt"+to_string(j)+"/inpwt"+to_string(i)+".txt";
					res=withVEB(fl);
					res=withAVL(fl);
					cout<<"*****************************************************\n";
				}
			
				break;
		default: cout<<"invlaid entry "; 
	}
	return 0;
}
