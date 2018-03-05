// code author kamrul_ashraf
// id 201514083
// run with c++ 11



#include <bits/stdc++.h>
using namespace  std;

#define N 3000000
#define inf 2e9
#define rep(i,x,y)  for(int i = x ; i< y ; i++)
#define F(i,x)  for(int i = 0 ; i< x ; i++)
#define ff first
#define ss second
#define pii pair < int , int>
#define ll long long
#define ull unsigned ll
#define MP make_pair
#define PB push_back
#define magic map < int,map<int,int> >
#define BOUNDARY(x,y) (x >= 0 && x <r && y >= 0 && y < c)
int fx[] = {0,0,1,-1};
int fy[] = {1,-1,0,0};


struct node
{
    int fscore, gscore;
    magic arr;
    node(int a , int b, magic c){
        fscore = a;
        gscore = b;
        arr = c;
    }
    node(){
    }

};

class comp
{
public:
   bool operator()(const node& a ,const node& b){
        return a.fscore > b.fscore;
   }

};

class State{

public:
    magic a, target;
    bool solveAble = true;
    map < magic , magic> par;
    int r , c;

    State(){
        int cnt=0;
        r = 4; c = 4;

        rep(i,0,r)
          rep(j,0,c)
            target[i][j] = ++cnt;
        target[3][3]=0;
    }

    void input(){
        int savex , savey;
        rep(i,0,r)
          rep(j,0,c){
            scanf("%d",&a[i][j]);
            if(a[i][j] == 0){
               savex = i;
               savey = j;
            }
          }

         solveAble = isSolveAble(4-savex);

    }

    bool isSolveAble(int faka){
        int cnt = 0;
        vector < int> v;
        rep(i,0,r) rep(j,0,c)
          if(a[i][j])
            v.push_back(a[i][j]);
        rep(i,0,v.size()){
             rep(j,i+1,v.size())
                if(v[i] > v[j]) cnt++;

        }



        if(faka%2==0){
           return (cnt&1);
        }
        else{
           return (cnt%2==0);
        }

    }

    void print(magic var){

        rep(i,0,r){
            rep(j,0,c){
                printf("%4d ",var[i][j]);
            }
            printf("\n");
        }

        printf("#######################\n");
    }

    int Heuristics(magic var){
           int cnt = 0;

           rep(i,0,r){
             rep(j,0,c){
                if(var[i][j]){
                    int tr = (var[i][j]-1)/c;
                    int tc = (var[i][j]-1)%c;
                    cnt += abs(tr-i)+abs(tc-j);
                }
             }
           }


           return cnt;
    }

    vector < magic > generateNextState(magic var){
          magic temp = var;
          vector < magic > v;
          rep(i,0,r){
             rep(j,0,c){
                if(var[i][j]==0){
                    rep(k,0,4){
                        int tempx = fx[k]+i;
                        int tempy = fy[k]+j;
                        if(BOUNDARY(tempx,tempy)){
                            swap(temp[i][j],temp[tempx][tempy]);
                            v.push_back(temp);
                        }
                        temp = var;
                    }
                }
             }
          }

          return v;
    }

    void algo(){
        priority_queue < node , vector <node> ,comp > q;
        node s(Heuristics(a),0,a);

        q.push(s);
        map < magic , int > vis;
        vis[s.arr] = 1;
        while(!q.empty()){
            node u = q.top();
            if(u.arr == target) break;
            q.pop();
            vector<magic> temp= generateNextState(u.arr);
            for(int i =0;i<temp.size();i++){
                  node v;
                  v.gscore = u.gscore+1;
                  v.fscore = v.gscore+ Heuristics(temp[i]);
                  v.arr = temp[i];

                  if(vis[v.arr] == 0){
                     q.push(v);
                     vis[v.arr] = 1;
                     par[v.arr] = u.arr;
                  }
            }
        }
    }


    void pathPrint(){
       magic temp = target;
       vector < magic > v;
       v.push_back(temp);
       while(temp != a){
            temp = par[temp];
            v.push_back(temp);
       }
       reverse(v.begin() , v.end());
       for(int i = 0 ; i< v.size() ; i++){
          print(v[i]);
       }
    }

};
int main()
{
    freopen("in.txt","r",stdin);
   printf("ENTER PUZZLE:\n");
    State s;
    s.input();
//    s.print(s.target);
    if(s.solveAble == true){
        s.algo();
        printf("SOLUTION PRINT\n");
        s.pathPrint();
    }
    else{
       printf("THIS IS NOT SOLVEABLE");
    }

}
