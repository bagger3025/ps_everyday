int charToInt(char c) {
    if (c == '/') return 0;
    return c - 'a' + 1;
}

class TrieNode {
public:
    TrieNode() {}
    bool isEnd = false;
    TrieNode *children[27] = { nullptr };
    ~TrieNode() {
        for (int i = 0; i < 27; i++) {
            delete children[i];
        }
    }
private:
};

class Trie {
    TrieNode *head;
public:
    Trie() {
        head = new TrieNode();
    }
    ~Trie() {
        delete head;
    }

    bool insert(const string &s) {
        TrieNode *t = head;

        bool isNew = false;
        for (int i = 0; i < s.size(); i++) {
            int idx = charToInt(s[i]);
            if (s[i] == '/' && !isNew) {
                if (t->isEnd) return false;
            }
            if (t->children[idx] == nullptr)
                t->children[idx] = new TrieNode();
            t = t->children[idx];
        }
        t->isEnd = true;
        
        return true;
    }
};

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        vector<string> ans;

        Trie t;
        sort(folder.begin(), folder.end());
        for (int i = 0; i < folder.size(); i++) {
            if (t.insert(folder[i])) {
                ans.push_back(folder[i]);
            }
        }

        return ans;
    }
};
