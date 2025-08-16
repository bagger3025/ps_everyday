class MyTreeNode {
public:
    MyTreeNode *par = nullptr;

    vector<MyTreeNode *> children;

    int lazyval = 0;
    int val = 0;
};

class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        const int n = edges.size() + 1;
        
        vector<vector<int>> adjs(n);
        for (auto &e: edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        MyTreeNode *childrens = new MyTreeNode[n];
        
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int t = q.front(); q.pop();
            visited[t] = true;

            for (auto &y: adjs[t]) {
                if (visited[y]) continue;
                MyTreeNode &ch = childrens[y];
                ch.par = &childrens[t];
                childrens[t].children.push_back(&ch);
                q.push(y);
            }
        }

        MyTreeNode *root = &childrens[0];
        for (auto &g: guesses) {
            MyTreeNode *p = &childrens[g[0]];
            MyTreeNode *ch = &childrens[g[1]];
            if (ch->par == p) {
                ch->lazyval--;
                root->lazyval++;
            } else {
                p->lazyval++;
            }
        }

        queue<MyTreeNode *> q2; q2.push(&childrens[0]);
        while (!q2.empty()) {
            MyTreeNode *node = q2.front(); q2.pop();
            node->val = node->lazyval;
            for (auto &child: node->children) {
                child->lazyval += node->lazyval;
                q2.push(child);
            }
        }

        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (childrens[i].val >= k) ret++;
        }

        delete[] childrens;

        return ret;
    }
};
