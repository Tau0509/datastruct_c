//Your code begin.
//示例仅供参考，你也可以自行修改设计。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
typedef struct arc //作为邻接表头节点所指向的边
{
    char NextStop[20];//存储指向的节点
    float dist;
    struct arc *next;
} arc;

typedef struct Head //作为邻接表头节点
{
    char name[20]; //存储站点名称
    arc * add;
} Head;

Head station[25]; //存储站点信息的全局数组变量

int LocateStation(char *name) //定位站点
{
    for (int i = 0; i < 25; i++)
    {
        if (strcmp(station[i].name, name) == 0)
            return i;
    }
    return -1;
}//end:LocateStation

int StationExist(char *name) //判断站点是否存在
{
    for (int i = 0; i < 25; i++)
    {   if(station[i].name[0]=='\0') return 0;
        if (strcmp(station[i].name, name) == 0)
            return 1;
    }
    return 0;
}//end:StationExist


void Addstation(char *name) //添加站点
{
    for (int i = 0; i < 25; i++)
    {
        if (station[i].name[0] == '\0')
        {
            strcpy(station[i].name, name); //将name复制到station[i].name
            return;
        }
    }
}//end:Addstation



void AddWay(char *start, char *end, float dist) //添加边
{
    if (strcmp(start, end) == 0) //如果起点和终点相同，直接返回
        return;

    if (StationExist(start) == 0 || StationExist(end) == 0) //如果起点或终点不存在，直接返回
        return;
    int startindex = LocateStation(start);  //获取起点的下标

    if(station[startindex].add==NULL){  //如果起点的邻接表为空,直接添加
        station[startindex].add=(arc*)malloc(sizeof(arc));
        station[startindex].add->next=NULL;
        strcpy(station[startindex].add->NextStop,end);
        station[startindex].add->dist=dist;
    }
    else{ //如果起点的邻接表不为空，找到最后一个节点，添加
        arc* p=station[startindex].add;
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=(arc*)malloc(sizeof(arc));
        p=p->next;
        p->next=NULL;
        strcpy(p->NextStop,end);
        p->dist=dist;
    }
}//end:AddWay

void CreateGraph(){//创建图

    char start[20];
    char end[20];
    float dist=0.0; //存储距离

    while(1)
    {
     scanf("%s",start);
     if(strcmp(start,"END!")==0) return; //如果输入END!，结束

     scanf("%s",end);
     scanf("%f",&dist);

     if(StationExist(start)==0) Addstation(start); //如果起点终点不存在，添加
     if(StationExist(end)==0) Addstation(end);

     AddWay(start,end,dist);
     AddWay(end,start,dist);
    }
}//end:CreateGraph

int HowManyExchanges(char *name) {//计算换乘次数
    int index=LocateStation(name);
    if(index==-1) return -1;
    arc* p=station[index].add; //获取邻接表
    int count=0;
    while(p!=NULL){ //遍历邻接表
        count++;
        p=p->next;
    }
    return count;
}//end:HowManyExchanges

void DispalyExchange(){ //显示换乘次数大于2的站点
    for(int i=0;i<25;i++){
        if(station[i].name[0]=='\0') return;
        if(HowManyExchanges(station[i].name)<=2) continue;
        printf("%s %d\n",station[i].name,HowManyExchanges(station[i].name));
    }
}//end:DispalyExchange

void  PrintShortestPathWithDijkstra(int start ,int end ){//用Dijkstra算法打印最短路径长度与路径
    float dist[25]; //存储最短路径长度
    int path[25]; //存储路径
    bool visited[25]; //标记是否访问过
    for(int i=0;i<25;i++){
        dist[i]=INT_MAX;      //初始化
        path[i]=-1;
        visited[i]=false;
    }
    dist[start]=0;
    for(int i=0;i<25;i++){
        int min=INT_MAX;     //初始化
        int u=-1;
        for(int j=0;j<25;j++){
            if(visited[j]==false&&dist[j]<min){ //找到未访问的最小距禇
                min=dist[j];
                u=j;
            }
        }
        if(u==-1) break; //如果没有找到未访问的最小距离，结束
        visited[u]=true; //标记访问过
        arc* p=station[u].add; //遍历邻接表
        while(p!=NULL){
            int v=LocateStation(p->NextStop);//获取下一个节点的下标
            if(visited[v]==false&&dist[u]+p->dist<dist[v]){//更新最短路径
                dist[v]=dist[u]+p->dist;
                path[v]=u;
            }
            p=p->next; //下一个节点
        }
    }
    if(dist[end]==INT_MAX){//如果没有路径
        printf("No such path\n");
        return;
    }

    int stack[25];
    int top=0;
    stack[top++]=end;
    int tem=end;
    while(path[tem]!=-1){//获取路径
        stack[top++]=path[tem];
        tem=path[tem];
    }
    for(int i=top-1;i>=0;i--){
        printf("%s ",station[stack[i]].name);
    }
    printf("%.1f",dist[end]);
}//end:PrintShortestPathWithDijkstra


int main(void)
{

    CreateGraph();
    char start[20];
    char end[20];
    scanf("%s %s",start,end);
    PrintShortestPathWithDijkstra(LocateStation(start),LocateStation(end));
    return 0;
}
//Your code end.