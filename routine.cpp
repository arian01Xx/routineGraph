#include <isotream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

class SolutionOne{
private:
    bool dfs(int curr, vector<char>& color, vector<int> adjList[], vector<int>& ans){
        color[curr]='G';
        for(int next: adjList[curr]){
            if(color[next]=='G' || (color[next]=='W' && dfs(next,color,adjList,ans))){
                return true;
            }
        }
        ans.push_back(curr);
        color[curr]='B';
        return false;
    }
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        for(int i=0; i<n; i++){
            if(group[i]==-1) group[i]=m++; //reemplaza el -1 por la cantidad de columnas +1
        }

        vector<int> itemList[n], groupList[m], itemOrder, groupOrder, ans;
        for(int i=0; i<n; i++){
            for(int j: beforeItems[i]){
                itemList[j].push_back(i);
                if(group[i]!=group[j]){
                    groupList[group[j]].push_back(group[i]);
                }
            }
        }

        vector<char> itemVisited(n,'W'), groupVisited(m,'W');
        for(int i=0; i<n; i++){
            if(itemVisited[i]=='W' && dfs(i,itemVisited,itemList,itemOrder)){
                return {};
            }
        }
        for(int i=0; i<m; i++){
            if(groupVisited[i]=='W' && dfs(i,groupVisited,groupList,groupOrder)){
                return {};
            }
        }

        reverse(itemOrder.begin(), itemOrder.end());
        reverse(groupOrder.begin(), groupOrder.end());
        unordered_map<int,vector<int>> map;
        for(int it: itemOrder){
            map[group[it]].push_back(it);
        }
        for(int it: groupOrder){
            for(int j: map[it]) ans.push_back(j);
        }
        return ans;
    }
};

int main(){
    return 0;
}