#include <iostream>
#include <vector>
#include <list>
using namespace std;

int min(int a, int b)
{
	if(a<b)return a;
	else return b;
}

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
};
class Vertex
{
	public:
	int identity;
	int height;
	// int excess;
	Vertex(int i)
	{
		identity=i;
		height=0;
		// excess=0;
	}

	void exc()
	{

	}

};
class FlowNetwork
{
	public:
  vector <Flowedge*> F[100];
	Vertex* V[100];

  int N;
  FlowNetwork(int N1)
  {
    cout<<"____________class FlowNetwork___________"<<endl;
    N=N1;
    /*for(int i=0;i<N;i++)
    {
      F[i]= new vector<Flowedge>();
    }*/
  	for(int i=0;i<100;i++)
  	{
			V[i]= new Vertex(i);
  		//V[i]->identity=i;
  		// V[i]->height=0;
  		// V[i]->excess=0;
  	}
  }
  void add_edge(Flowedge* e)
  {
    cout<<"____________add_Edge___________"<<endl;
    //cout<<e.from()<<"-->"<<e.to()<<endl;
    F[e->from()].push_back(e);
    //cout<<"here";
    F[e->to()].push_back(e);
  }

  void print()
  {
    cout<<"______print_______"<<endl;
    for(int i=0;i<N;i++)
    {
      cout<<i<<endl;
      for(Flowedge* w : F[i])
      {
        w->print();
      }
    }

  }

	int excess(int v)
	{
		int ex=0;
		for(Flowedge* w : F[v])
		{
			if(w->from()==v)
			{
				ex=ex- w->flow;
			}
			else//edge into v
			{
				ex=ex+ w->flow;
			}

		}
		return ex;

	}

	void vertex_print()
	{
		for(int i=0;i<N*2;i++)
		{
			cout<<V[i]->identity<<" ht : "<<V[i]->height<<" excess : "<<excess(V[i]->identity)<<endl;

		}

	}

};





class Pre_flow_push
{
public:



	 void push(FlowNetwork *G,Vertex *v, Vertex *w)
	{
		cout<<"____push_____"<<endl;
		char etype;Flowedge *e;int delta;
		for(Flowedge *u : G->F[v->identity])
      {
        if((u->from()==v->identity)&&(u->to()==w->identity))
      	{
      		etype='f';
      		e=u;
      		break;
      	}
      	else if ((u->from()==w->identity)&&(u->to()==v->identity))
      	{
      		etype='b';
      		e=u;
      		break;
      	}


      }


		if(etype=='f')
		{
			delta=min(e->Residual_cap(v->identity,w->identity),G->excess(v->identity));
			e->flow=e->flow+delta;

		}
		else if (etype=='e')
		{
			delta=min(e->Residual_cap(v->identity,w->identity),G->excess(v->identity));
			e->flow=e->flow-delta;
		}
		cout<<"---inside push---"<<endl;
		e->print();
	}

	void relabel(Vertex *v)
	{
		cout<<"relabel "<<v->identity<<"init ht "<<v->height<<" new ht ";
		v->height=v->height+1;
		cout<<v->height<<endl;


	}

  void Preflow_push_algo(FlowNetwork *G,int t)
  {
  	// for (int i=0;i<t->identity;i++)
  	// {
		cout<<"______In pre push flow aglo______"<<endl;
		int excess_s=0;
  		for(Flowedge* u:G->F[0])
  		{
  			if(u->from()==0)
  			{
  				u->flow=u->capacity;


  			}
  			else
  			{
  				u->flow=0;
  			}
  		}
			cout<<" PUSHED EVERYTHING POSSIBLE FROM s"<<endl;
			G->print();
			G->vertex_print();
  	// }
		G->V[0]->height=t+1;
		// G->V[0]->excess=excess_s;
  	// int max=G->V[0]->height;
		int max=0;
  	int MHV;
  	bool done=false;
  	while(!done)
		{
			done=true;
			for(int i=0;i<t;i++)
			{
				if((G->V[i]->height>=max)&&(G->excess(G->V[i]->identity)>0))
				{
					done=false;
					MHV=i;
					max=G->V[i]->height;
				}
			}
			cout<<"Max ht "<<max<<" @ "<<MHV<<endl;

			bool rel=true;
			if(done==false)
			{

				for(	Flowedge * w:G->F[MHV])
				{
					if(G->V[w->other(MHV)]->height==(G->V[MHV]->height-1))
					{
						rel=false;
						push(G,G->V[MHV],G->V[w->other(MHV)]);

					}

				}

				if(rel==true)
				{
					relabel(G->V[MHV]);
				}
			}

			G->vertex_print();
		}


		G->vertex_print();
		G->print();
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
	int t;
  int from,to,cap;
  for(int i=0;i<5;i++)
  {
    cin>>from>>to>>cap;
    Flowedge *e=new Flowedge(from,to,cap);
    e->print();
    F->add_edge(e);
  }
	cout<<"Enter the sink node"<<endl;
	cin>>t;

	Pre_flow_push *P=new Pre_flow_push;
	P->Preflow_push_algo(F,t);



  F->print();
	F->vertex_print();

}


int main()
{

  demo();



  return 0;
}
