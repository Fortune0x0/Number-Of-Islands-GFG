#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Disjoint_set {
public:
    vector<int> parent, size;
    Disjoint_set(int n) {
        size.resize(n, 1);
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int findPar(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findPar(parent[node]);
    }
    void UnionbySize(int u, int v) {
        int ult_u = findPar(u);
        int ult_v = findPar(v);
        if (ult_u == ult_v) return;

        if (size[ult_u] < size[ult_v]) {
            parent[ult_u] = ult_v;
            size[ult_v] += size[ult_u];
        }
        else {
            parent[ult_v] = ult_u;
            size[ult_u] += size[ult_v];
        }
    }
};
class Solution {

public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
        vector<vector<int>> vec(n, vector<int>(m, 0));
        vector<int> ans;
        vector<pair<int, int>> moves = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

        int set_size = operators.size();
        Disjoint_set st(set_size);
        int node = -1;
        map<pair<int, int>, int> my_map;

        for (auto it : operators) {
            int row = it[0];
            int col = it[1];
            vec[row][col] = 1;
            ++node;
            if (my_map.find({ row, col }) == my_map.end()) my_map[{row, col}] = node;

            for (auto a : moves ) {
                int nrow = row + a.first;
                int ncol = col + a.second;

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vec[nrow][ncol] == 1) {
                    if (my_map.find({nrow, ncol}) == my_map.end()) {
                        ++node;
                        my_map[{nrow, ncol}] = node;
                    }
                    int u = my_map[{row, col}];
                    int v = my_map[{nrow, ncol}];
                    st.UnionbySize(u, v);

                }
            }
            set<int> my_set;
            for (auto it : my_map) {
                int parent = st.findPar(it.second);
                my_set.insert(parent);
            }
            ans.push_back(my_set.size());

        }
        
        
       



        return ans;
    }

};







int main() {

    Solution solu;

    vector<vector<int>> operations = { {1,1}, {0, 3}, {2, 3}, {2, 4}, {2, 4}, { 2, 1 }, {1, 4}, {0, 0}, {1, 2}, {2, 0} };

    vector<int> ans = solu.numOfIslands(3, 5, operations);
    for (auto it : ans) cout << it << " ";
    

    


}