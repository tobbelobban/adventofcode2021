#include<iostream>
#include<stack>
#include<queue>

using namespace std;

                    // number [[[0,[4,5]],[0,0]], [[[4,5],[2,6]],[9,5]]] is represented as bin. tree as below

                    //                     []
                    //     []                              []
                    // 0       []                  []              []              
                    //       4    5           []       []        9    5
                    //                      4    5   2    6

// a tree is either 
//  1) a parenthesis with two non-nullptr children
//  2) a number with two nullptr children

class Tree {
    public:
    
    Tree(int init_val) : val{init_val} {}
    Tree(Tree* const left_, Tree* const right_) : left(left_), right(right_) { left->parent = this; right->parent = this;}
    Tree() = default;
    ~Tree() {delete left; delete right;}

    Tree* parent = nullptr;
    Tree* left = nullptr;
    Tree* right = nullptr;
    int val;
};

void print_tree_helper(const Tree* const root) {
    if(root->left == nullptr && root->right == nullptr) {
        cout << root->val;
    } else {
        cout << '[';
        print_tree_helper(root->left);
        cout << ",";
        print_tree_helper(root->right);
        cout << ']';
    }
}

void print_tree(const Tree* const root) {
    print_tree_helper(root);
    cout << endl;
}

Tree* parse_snailfish_nr(const string& line) {
    stack<Tree*> tree_stack;
    for(unsigned int i = 0;  i < line.length(); ++i) {
        const char c = line[i];
        if(c == '[') {
            tree_stack.push(new Tree());
        } else if(c == ']') {
            Tree* right = tree_stack.top(); tree_stack.pop();
            Tree* left = tree_stack.top(); tree_stack.pop();
            left->parent = tree_stack.top();
            right->parent = tree_stack.top();
            tree_stack.top()->left = left;
            tree_stack.top()->right = right;
        } else if(c == ',') {
            continue;
        } else {
            tree_stack.push(new Tree(c - '0'));
        }
    }
    Tree* root = tree_stack.top(); tree_stack.pop();
    return root;
}

void explode_left(Tree* const node, const int val) {
    Tree* parent = node->parent, * curr = node;
    bool from_left = true;
    while(curr->parent != nullptr) {
        if(parent->left == curr) {
            curr = parent;
            parent = curr->parent;
            from_left = true;
        } else {
            from_left = false;
            break; 
        }
    }
    if(parent == nullptr && from_left) return;   // reached root from left -> was left-most value
    curr = parent->left;
    while(curr->right != nullptr) curr = curr->right;
    curr->val += val;
}

// [[[[[1,1], [2,2]], [3,3]], [4,4]], [5,5]]

//                                     []
//                             []                                []
//                     []                     []              5       5
//                 []              []         4    4
//             []          []      3    3
//         1   1           2 2

void explode_right(Tree* const node, const int val) {
    Tree* parent = node->parent, * curr = node;
    bool from_right = true;
    while(curr->parent != nullptr) {
        if(parent->right == curr) {
            curr = parent;
            parent = curr->parent;
            from_right = true;
        } else {
            from_right = false;
            break; 
        }
    }
    if(parent == nullptr && from_right) return;
    curr = parent->right;
    while(curr->left != nullptr) curr = curr->left;
    curr->val += val;
}

bool explode(Tree* const node, int depth) {
    if(node == nullptr) return false;
    if(node->left != nullptr && node->right != nullptr && depth == 4) {
        // explode
        explode_left(node, node->left->val);
        explode_right(node, node->right->val);
        delete node->left; node->left = nullptr;
        delete node->right; node->right = nullptr;
        node->val = 0;
        return true;
    } else {
        return explode(node->left, depth + 1) || explode(node->right, depth + 1);
    } 
}

bool split(Tree* const node) {
    if(node == nullptr) return false;
    if(node->left == nullptr && node->right == nullptr && node->val > 9) {
        // split
        int left_val = node->val / 2; 
        int right_val = node->val - left_val;
        node->left = new Tree(left_val);
        node->left->parent = node;
        node->right = new Tree(right_val);
        node->right->parent = node;
        return true;
    } else {
        return split(node->left) || split(node->right);
    } 
}

bool reduce(Tree* const node) {
    return explode(node, 0) || split(node);
}

unsigned long magnitude(const Tree* const node) {
    if(node->left == nullptr || node->right == nullptr) return node->val;
    return 3 * magnitude(node->left) + 2 * magnitude(node->right);
}

int main(int argc, char const *argv[]) {
    string line;
    Tree* curr, * next;
    getline(cin,line);
    curr = parse_snailfish_nr(line);
    while(getline(cin,line)) {
        next = parse_snailfish_nr(line);
        curr = new Tree(curr,next); // add the two numbers
        bool reducing = true;
        while(reducing) reducing = reduce(curr); // then reduce
    }
    cout << magnitude(curr) << endl;
    delete curr;
    return 0;
}

