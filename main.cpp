#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<cctype>
#include<sstream>
using namespace std;

//Make string case insensitive
string to_lower(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

//Node - post in an user's AVL Tree
struct Post{
    string content;
    long long timestamp;
    Post* left;
    Post* right;
    int height;

    Post(string c, long long t) : content(c), timestamp(t), left(nullptr), right(nullptr), height(1){}

};

//User's - AVL Tree
class AVLTree{
private:
    Post* root = nullptr;

    int height(Post* node){
        if(node!=nullptr){
            return node->height;
        }
        else{
            return 0;
        }
    }

    int balancedfactor(Post* node){
        if(node!= nullptr){
            return height(node->left) - height(node->right);
        }
        else{
            return 0;
        }
    }

    Post* rightrotate(Post* x){
        Post* y = x->left;
        Post* z = y->right;

        y->right = x;
        x->left = z;

        x->height = 1+ max(height(x->left),height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Post* leftrotate(Post* x){
        Post* y = x->right;
        Post* z = y->left;

        y->left = x;
        x->right = z;

        x->height = 1+ max(height(x->left),height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Post* insertnodehelper(Post* node, string cont, long long ts){
        if(node == nullptr){
            Post* newnode = new Post(cont, ts);
            return newnode;
        }
        else if(ts<node->timestamp){
            node->left = insertnodehelper(node->left, cont, ts);
        }
        else if(ts>node->timestamp){
            node->right = insertnodehelper(node->right, cont, ts);
        }
        node->height = 1+ max(height(node->left), height(node->right));
        int bf = balancedfactor(node);

        if(bf>1 && ts<node->left->timestamp){
            node = rightrotate(node);
        }
        else if(bf>1 && ts>node->left->timestamp){
            node->left = leftrotate(node->left);
            node = rightrotate(node);
        }
        else if(bf<-1 && ts>node->right->timestamp){
            node = leftrotate(node);
        }
        else if(bf<-1 && ts<node->right->timestamp){
            node->right = rightrotate(node->right);
            node = leftrotate(node);
        }
        return node;
    }

    void reverseinorder(Post* node, vector<string> &posts, int& count, int N){
        if(node == nullptr || (N!= -1 && count>= N)){
            return;
        }
        reverseinorder(node->right, posts, count, N);
        if(N== -1 || count < N){
            posts.push_back(node->content);
            count++;
        }

        reverseinorder(node->left, posts, count, N);
    }

    void deletetree(Post* node){
        if(node!= nullptr){
            deletetree(node->left);
            deletetree(node->right);
            delete node;
        }
    }
    
public:
    AVLTree(){
    }

    ~AVLTree(){
        deletetree(root);
    }

    void insertpost(string cont, long long ts){
        root = insertnodehelper(root, cont, ts);
    }

    vector<string> getPosts(int N){
        vector<string> posts;
        int count = 0;
        reverseinorder(root, posts, count, N);
        return posts;
    }

};

//User Node struct

struct User{
    string name;
    vector<string> friends;
    AVLTree UserPosts;
    // User(string username) {
    //     transform(username.begin(), username.end(), username.begin(), ::to_lower);
    //     name  = username;
    // }
    User(string username){
        name = to_lower(username);
    }

    void addFriend(const string& fname){
        if(find(friends.begin(), friends.end(), fname) == friends.end()){
            friends.push_back(fname);
        }
    }
};

//Graph - class

class SocialNetwork{
private:
    unordered_map<string, User*> users;

    int bfs(const string& user1, const string& user2){
        if(!users.count(user1) || !users.count(user2)){
            return -1;
        }
        queue<pair<string, int>> q;
        unordered_map<string, bool> visited;
        q.push({user1,0});
        visited[user1] = true;
        while(!q.empty()){
            pair<string, int> frontpair = q.front();
            string u = frontpair.first;
            int d = frontpair.second;
            q.pop();
            if(u == user2){
                return d;
            }
            for(auto &f : users[u]->friends){
                if(!visited[f]){
                    visited[f] = true;
                    q.push({f,d+1});
                }
            }
        }
        return -1;
    }

public:
    void addUser(string username){
        string uname = to_lower(username);
        if(!users.count(uname)){
            users[uname] = new User(uname);
        }
    }

    void addFriend(string user1, string user2){
        string u1 = to_lower(user1);
        string u2 = to_lower(user2);
        if(!users.count(u1) || !users.count(u2)){
            return;
        }
        users[u1]->addFriend(u2);
        users[u2]->addFriend(u1);
    }

    void listFriends(string username){
        string uname = to_lower(username);
        if(!users.count(uname)){
            return;
        }
        auto& fr = users[uname]->friends;
        sort(fr.begin(), fr.end());
        for(auto &f : fr){
            cout << f << " ";
        }
        cout << "\n";
    }

    void suggestFriends(string username, int n){
        string uname = to_lower(username);
        if(!users.count(uname) || n==0){
            return;
        }
        auto &friends = users[uname]->friends;
        unordered_map<string, int> mutualf;
        for(auto &f : friends){
            for(auto &fof : users[f]->friends){
                if(fof!= uname && find(friends.begin(), friends.end(), fof) == friends.end()){
                    mutualf[fof]++;
                }
            }
        }

        vector<pair<string, int>> v(mutualf.begin(), mutualf.end());
        sort(v.begin(), v.end(), [](auto &a, auto &b){
            if(a.second != b.second){
                return a.second > b.second;
            }
            return a.first < b.first;
        });

        int count = 0;
        for(auto &p : v){
            if(count++ >= n){
                break;
            }
            cout<< p.first << "\n";
        }
    }

    void dos(string user1, string user2){
        string u1 = to_lower(user1);
        string u2 = to_lower(user2);
        cout << bfs(u1,u2) << "\n";
    }

    void addposts(string username, string cont, long long ts){
        string uname = to_lower(username);
        if(!users.count(uname)){
            return;
        }
        users[uname]->UserPosts.insertpost(cont,ts);
    }

    void outputposts(string username, int n){
        string uname = to_lower(username);
        if(!users.count(uname)){
            return;
        }
        auto posts = users[uname]->UserPosts.getPosts(n);
        for(auto &p : posts){
            cout << p << "\n";
        }
    }

    bool userExists(const string& username) {
        string uname = to_lower(username);
        return users.count(uname) > 0;
    }

};

//main 

int main() {

    SocialNetwork sn;
    string line; 
    long long global_time = 0;

    while (getline(cin, line)) {
        if (line.empty()){
            continue;
        }
        stringstream ss(line);
        string a;
        ss >> a;

        // a = to_lower(a);
        // b = to_lower(b);

        if (a == "ADD_USER") {
            string username;
            ss >> username;
            
            if(username.empty()){
                cout << "No User Found" << endl;
            }
            else{
                sn.addUser(username);
                cout << "User Added" << endl;
            }
            

        } else if (a == "ADD_FRIEND") {
            string user1, user2;
            ss >> user1 >> user2;
            if(user1.empty() || user2.empty()){
                cout << "User Not Found" << endl;
            }
            else if(user1 == user2) {
                cout << "Cannot friend oneself" << endl;
            }       
            else{
                sn.addFriend(user1, user2);
                cout << "Friend Added" << endl;
            }

        } else if (a == "LIST_FRIENDS") {
            string username;
            ss >> username;
            if(username.empty() || !sn.userExists(username)){
                cout << "User Not Found" << endl;
            }
            else{
                sn.listFriends(username);
            }
            
        } else if (a == "SUGGEST_FRIENDS") {
            string username;
            int N;
            ss >> username >> N;
            if(username.empty() || !sn.userExists(username)){
                cout << "User Not Found" << endl;
            }
            else{
                sn.suggestFriends(username, N);
            }

        } else if (a == "DEGREES_OF_SEPARATION") {
            string user1, user2;
            ss >> user1 >> user2;
            if(user1.empty() || user2.empty() || !sn.userExists(user1) || !sn.userExists(user2)){
                cout << "User Not Found" << endl;
            }
            else{
                sn.dos(user1, user2);
            }
            
        } else if (a == "ADD_POST") {
                string username;
                ss >> username;
                if (!sn.userExists(username)) {
                    cout << "User Not Found" << endl;
                    continue;
                }
                size_t first = line.find("\"");
                size_t last = line.rfind("\"");
                if (first != string::npos && last != string::npos && last > first) {
                    string content = line.substr(first + 1, last - first - 1);
                    sn.addposts(username, content, global_time++);
                    cout << "Post Added" << endl;
                } else {
                    cout << "Invalid Post Format" << endl;
                }


        } else if (a == "OUTPUT_POSTS") {
            string username;
            int N;
            ss >> username >> N;
            if(username.empty() || !sn.userExists(username)){
                cout << "User Not Found" << endl;
            }
            else{
                sn.outputposts(username, N);
            }
        } else{
            cout << "INVALID COMMAND" << endl;
        }
    }

    return 0;
}

