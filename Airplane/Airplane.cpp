#include <iostream>
#include <fstream>
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


  void change_cap_e(int from ,int to,int new_cap)
  {
    for(Flowedge* w : F[from])
    {
      if(w->to()==to)
      {
        w->capacity=new_cap;
      }
    }
    for(Flowedge* w : F[to])
    {
      if(w->from()==from)
      {
        w->capacity=new_cap;
      }

    }


  }

  void reset_graph()
  {

      for(int i=0;i<N;i++)
      {
        //cout<<i<<endl;
        for(Flowedge* w : F[i])
        {
          w->flow=0;
        }
      }


  }

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




void max_Flow_schedule(FlowNetwork *F,int n,int* from_to,map<string,int>*vert,map<int,string>* rev_vert)
{
  FF ford_fulk;
  cout<<"Max_flow "<<ford_fulk.maxflow(F,0,1)<<endl;
  F->print();




}





void graph_construct(FlowNetwork *F)
{// read csv and construct the graph
  fstream fin;

    // Open an existing file
    fin.open("Schedule.csv", ios::in);

    int flights=0;
    vector<string> row;
    string line, word, temp,str_name,str_name2;
    map<string,int> vertices;//flight to identity of vertex mapping
    map<int,string> rev_vert;//reverse mapping
    int from_to[100];
    int n,count=4;//first four are for the vertices as source s,s'and sink t,t'
    fin>>n;

    while (fin >> temp)
    {
        flights++;
        if(flights==n)
        {
          cout<<"DONE WITH all"<<n<<" flights  "<<endl;
          break;
        }
        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);
        // used for breaking words
        stringstream s(line);

        while (getline(s, word, ', '))
        {
            row.push_back(word);
        }

        time1 = stoi(row[1]);
        time3 =stoi(row[3]);
        str_name=row[1]+'$D$'+row[0];//time+Deptstat+Airport
        str_name2=row[3]+'$A$'+row[2];//time+Arriv+Airport

        if(vertices.find(str_name)==vertices.end())//this string has not been previously seen so make a new vertex for it
        {
          vertices[str_name]=count;//maps the string to the number of the vertex since graph is built on numbers
          rev_vert[count]=str_name;
          count++;
          from=count;
          // G->addEdge(prev,count);
          // prev=count;
        }
        else
        {
          from=vertices[str_name];
        }

        if(vertices.find(str_name2)==vertices.end())//this string has not been previously seen so make a new vertex for it
        {
          vertices[str_name2]=count;//maps the string to the number of the vertex since graph is built on numbers
          rev_vert[count]=str_name2;
          count++;
          to=count;
          // G->addEdge(prev,count);
          // prev=count;
        }
        else
        {
          to=vertices[str_name2];
        }
        // 0 is for teh main source
        // 1 is for the main sink
        //2 is for the airplane supply
        //3 is for the hanger at the days end
        from_to[from]=to;//the flight edges
        cout<<" from "<<from<<" - "<<rev_vert[from];
        cout<<" to "<<to<<" - "<<rev_vertex[to];
        //Flowedge *e=new Flowedge(from,to,1);
        Flowedge *e1=new Flowedge(2,from,1);
        Flowedge *e2=new Flowedge(from,1,1);
        Flowedge *e3=new Flowedge(0,to,1);
        Flowedge *e4=new Flowedge(to,3,1);
        //e->print();
        e1->print();
        e2->print();
        e3->print();
        e4->print();
        //F->add_edge(e);
        F->add_edge(e1);
        F->add_edge(e2);
        F->add_edge(e3);
        F->add_edge(e4);

      }//end while
      int delay=0;//the inter-travel delay
      for(int i=4;i<count;i++)
      {
        stringstream s1(rev_vertex[i]);
        vector<string> flig_code,flig_code2;

        while (getline(s1, word, '$'))
        {
            cout<<word;
            flig_code.push_back(word);
        }

        if(flig_code[1]=='D')
        continue;

        cout<<endl;

        for(int j=4;j<count;j++)
        {
          stringstream s1(rev_vertex[j]);
          while (getline(s1, word, '$'))
          {
              cout<<word;
              flig_code2.push_back(word);
          }
          if(flig_code2[1]=='A')
          {
            if(stoi(flig_code2[0])>delay+stoi(flig_code[0]))
            {
              cout<<" Creating a possible route "<<endl;
              Flowedge *e=new Flowedge(i,j,1);
              F->add_edge(e);
            }
          }

        }

      }
      //Flowedge *e=new Flowedge(i,j,1);

      max_Flow_schedule(F);

}








int main()
{

  return 0;
}
