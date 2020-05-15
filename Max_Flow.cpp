#include <iostream>
#include <vector>
#include <list>
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
    cout<<v<<"---"<<capacity<<"--->"<<w<<endl;
  }
};


class FlowNetwork
{

  vector <Flowedge> F[100];

  public:
  int N;
  FlowNetwork(int N1)
  {
    cout<<"____________class FlowNetwork___________"<<endl;
    N=N1;
    /*for(int i=0;i<N;i++)
    {
      F[i]= new vector<Flowedge>();
    }*/
  }
  void add_edge(Flowedge e)
  {
    cout<<"____________add_Edge___________"<<endl;
    //cout<<e.from()<<"-->"<<e.to()<<endl;
    F[e.from()].push_back(e);
    //cout<<"here";
    F[e.to()].push_back(e);
  }

  void print()
  {
    cout<<"______print_______"<<endl;
    for(int i=0;i<N;i++)
    {
      cout<<i<<endl;
      for(Flowedge w : F[i])
      {
        cout<<w.from()<<"->"<<w.to()<<endl;
      }
    }

  }


};

void demo()
{
  cout<<"____________In main___________"<<endl;
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
    e->print();
    F->add_edge(*e);
  }

  F->print();

}





int main()
{

  demo();
  return 0;
}
