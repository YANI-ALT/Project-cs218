import numpy as np
import maxflow
import networkx

#airport dept,airport arrival, dept time,arrival time
vertex=dict()
flight=[]
# data=pd.read_csv('Schedule.csv')
import csv
count=1;
k=int(input("Enter : "))
g=maxflow.GraphInt()
with open('Schedule.csv','r') as file:
    reader=csv.reader(file)
    for row in reader:
        t=(row[0],row[2],'dept')
        t2=(row[1],row[3],'arriv')#convert the row[3] to a time object
        if(t not in vertex.keys()):
            from_vert=g.add_nodes(1)[0]
            vertex[t]=from_vert

                #count=count+1
        else:
            from_vert=vertex[t]

        if(t2 not in vertex.keys()):
            to_vert=g.add_nodes(1)[0]
            vertex[t2]=to_vert

                #count=count+1
        else:
            to_vert=vertex[t2]

        flight.append((from_vert,to_vert))

 #constructing the max flow graph
print(vertex)
dum_vert=g.add_nodes(1)[0]
dum2=g.add_nodes(1)[0]
# dum3=g.add_nodes(1)[0]
print(flight)
for e in flight:
    g.add_edge(e[0],e[1],0,0)
    g.add_tedge(e[0],cap_source=1,cap_sink=0)
    g.add_tedge(e[1],cap_source=0,cap_sink=1)
    g.add_edge(dum2,e[1],1,0)
    g.add_edge(e[0],dum_vert,1,0)
maint=0
g.add_tedge(dum_vert,cap_source=0,cap_sink=k)
g.add_tedge(dum2,cap_source=k,cap_sink=0)#dummt source
# g.add_tedge(dum3,k,k)

for st in vertex.keys():
    if st[2]=='arriv':
        for fly in vertex.keys():
            if st ==fly:
                continue;
            if(fly[2]=='dept' and int(st[1])+maint<int(fly[1])):
                print("adding from {} to {}".format(st,fly))
                g.add_edge(vertex[st],vertex[fly],1,0)
print(g.maxflow())
print(g.get_nx_graph())
