#include <iostream>
#include <set>
#include <map>

using namespace std;

struct TNode {
	char value;
	TNode* left;
	TNode* right;
};

set<char> FindEquivalentSubtreesInternal(map<set<char>, TNode*>& subtrees, pair<TNode*, TNode*>& res, TNode* root) {
	if (root == nullptr) return set<char>();

	set<char> chars;
	set<char> letf_chars = FindEquivalentSubtreesInternal(subtrees, res, root->left);
	set<char> right_chars = FindEquivalentSubtreesInternal(subtrees, res, root->right);

	chars.insert(letf_chars.begin(), letf_chars.end());
	chars.insert(right_chars.begin(), right_chars.end());

	auto it = subtrees.find(chars);
	if (it != subtrees.end()) {
		res = make_pair(it->second, root);
	} else {
		subtrees.insert(make_pair(chars, root));
	}

return chars;
}

// Найти эквивалентные поддеревья. Узлы могут содержать символы [a-z]
std::pair<TNode*, TNode*> FindEquivalentSubtrees(TNode* root) {
	map<set<char>, TNode*> subtrees;
	pair<TNode*, TNode*> res = make_pair(nullptr, nullptr);
	FindEquivalentSubtreesInternal(subtrees, res, root);
	return res;
}

int main() {

}