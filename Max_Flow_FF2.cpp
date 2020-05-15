#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
using namespace std;
class Flowedge
{

  public:
  int v,w,capacity;
  int flow;
  Flowedge(int v1,int v2,int a)
  {
    //cout<<"____________class FlowEdge___________"<<endl;
    v=v1;
    w=v2;
    capacity=a;
    flow=0;
  }

  void add_ResidFlow(int from,int to,int d)
  {
    if(from==v&&to==w)
    flow+=d;//forward edge
    else if(from==w&&to==v)
    flow-=d;//backward edge
  }
  int Residual_cap(int from,int to)
  {
    if(from==v&&to==w)
    return capacity-flow;//forward edge
    else if(from==w&&to==v)
    return flow;

  }
  int other(int vertex)
  {
    if(vertex==v)
    return w;
    else if(vertex==w)
    return v;
  }

  int from() {return v;}
  int to() {return w;}

  void print()
  {
    cout<<v<<"---"<<flow<<"--->"<<w<<endl;
  }
  void print_res()
  {
    cout<<v<<"---"<<Residual_cap(v,w)<<"---->"<<w<<endl;
    cout<<v<<"<--"<<Residual_cap(w,v)<<"----"<<w<<endl;

  }



};

class FlowNetwork
{
  public:
  vector <Flowedge*> F[100];


  int N;
  FlowNetwork(int N1)
  {
    // cout<<"____________class FlowNetwork___________"<<endl;
    N=N1;
    /*for(int i=0;i<N;i++)
    {
      F[i]= new vector<Flowedge>();
    }*/
  }
  void add_edge(Flowedge* e)
  {
    // cout<<"____________add_Edge___________"<<endl;
    //cout<<e.from()<<"-->"<<e.to()<<endl;
    F[e->from()].push_back(e);
    //cout<<"here";
    F[e->to()].push_back(e);
  }

  void print()
  {
    // cout<<"______print_______"<<endl;
    for(int i=0;i<N;i++)
    {
      cout<<i<<endl;
      for(Flowedge* w : F[i])
      {
        cout<<w->from()<<"----"<<w->flow<<"---->"<<w->to()<<endl;
      }
    }

  }
  void print_resg()
  {
    for(int i=0;i<N;i++)
    {
      //cout<<i<<endl;
      for(Flowedge* w : F[i])
      {
        w->print_res();
      }
    }
  }
  // void update(int v,Flowedge e,int flow)
  // {
  //   int index1,index2=0;
  //   for(Flowedge w: F[v])
  //   {
  //
  //     if(w==e)
  //     break;
  //     index1++;
  //   }
  //   for(Flowedge w: F[e.other(v)])
  //   {
  //
  //     if(w==e)
  //     break;
  //     index2++;
  //   }
  //
  //   e.add_ResidFlow(e.other(v),v,flow);
  //
  //   F[v].erase(index1)
  //   F[v].push_back(e)
  //
  //   F[v].erase(index2)
  //   F[v].push_back(e)
  //
  // }


};

void demo()
{
  // cout<<"____________In main___________"<<endl;
  FlowNetwork *F=new FlowNetwork(10);
  int from,to,cap;
  for(int i=0;i<5;i++)
  {
    cin>>from>>to>>cap;
    Flowedge *e=new Flowedge(from,to,cap);
    e->print();
    F->add_edge(e);
  }

  F->print();

}

class FF
{
  public:
vector<Flowedge*> path[100];

bool hasAugment(FlowNetwork *G,int s,int t)//,Flowedge*path)
{
  // cout<<"_____has_augment_____"<<endl;
  //G->print();
  bool marked[100];
  for( int i=0;i<G->N;i++)
    marked[i]=false;
  queue <int> Q;
  Q.push(s);
  marked[s]=true;
  while(!Q.empty())
  {
    int u=Q.front();
    Q.pop();
    for(Flowedge* w: G->F[u])
    {
      int vert=w->other(u);
      if( w->Residual_cap(u,vert)>0&&!marked[vert])//only if its non zero does there exist a path
      {
        if(!path[vert].empty())
        path[vert].clear();

        path[vert].push_back(w);
        // the edge w used to come to vert
        marked[vert]=true;
        Q.push(vert);

      }
    }

  }
  // cout<<"has_Augment: "<<marked[t]<<endl;
  return marked[t];
}

int augment(FlowNetwork *G,int s,int t)//,Flowedge path[])
{
  // cout<<"___augment__"<<endl;
  int bottle=10000000;
  for(int v=t ;v!=s;v=path[v].front()->other(v))//find the bottleneck capacity of the path
  {
    // cout<<v<<" ";
    if(bottle>path[v].front()->Residual_cap(path[v].front()->other(v),v))
    bottle=path[v].front()->Residual_cap(path[v].front()->other(v),v);
  }
  // cout<<"Bottle Neck value: "<<bottle<<endl;
  for(int v=t ;v!=s;v=path[v].front()->other(v))//find the bottleneck capacity of the path
  {


    path[v].front()->add_ResidFlow(path[v].front()->other(v),v,bottle);

    // path[v].front()->print_res();


  }

  return bottle;

}

int maxflow(FlowNetwork *G,int s,int t)
{


  // cout<<"___max_flow___"<<endl;
  int f=0;
  // int bottle=10000000;
  while(hasAugment(G,s,t))
  {

    f+=augment(G,s,t);
    // bottle;
    // cout<<"flow "<<f<<endl;
    // G->print();
  }

  return f;
}

};







int main()
{


  // cout<<"____________In main___________"<<endl;
  FlowNetwork *F=new FlowNetwork(10);


  // e->print();
  // F->add_edge(*e);
  // e=new Flowedge(0,2,10)
  //e->print();
  int from,to,cap;
  for(int i=0;i<5;i++)
  {
    cin>>from>>to>>cap;
    Flowedge *e=new Flowedge(from,to,cap);
    //e->print();
    F->add_edge(e);
  }
  int s,t;
  cout<<"Enter the source of the graph: ";
  cin>>s;
  cout<<"Enter the sink of the graph: ";
  cin>>t;
  cout<<endl;
  //F->print();
  FF *ford_fulk=new FF;
  cout<<"MAX FLOW "<<ford_fulk->maxflow(F,s,t)<<endl;
  F->print_resg();















  return 0;
}
