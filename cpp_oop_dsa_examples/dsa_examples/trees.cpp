#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

/**
 * DSA Tip #4: Trees
 *
 * Key concepts:
 * - Binary tree structure and traversal
 * - Binary Search Tree (BST) properties
 * - Balanced trees (AVL, Red-Black)
 * - Tree traversal algorithms (inorder, preorder, postorder, level-order)
 * - Common tree problems and solutions
 *
 * Trick: Use smart pointers for tree nodes to handle memory management
 * automatically and prevent memory leaks.
 */

template <typename T>
struct TreeNode {
    T data;
    std::unique_ptr<TreeNode<T>> left;
    std::unique_ptr<TreeNode<T>> right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    std::unique_ptr<TreeNode<T>> root_;

    // Helper function to insert recursively
    TreeNode<T>* insertHelper(std::unique_ptr<TreeNode<T>>& node, T value) {
        if (!node) {
            node = std::make_unique<TreeNode<T>>(value);
            return node.get();
        }

        if (value < node->data) {
            return insertHelper(node->left, value);
        } else {
            return insertHelper(node->right, value);
        }
    }

    // Helper function to find minimum value node
    TreeNode<T>* findMin(TreeNode<T>* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    // Helper function to remove recursively
    std::unique_ptr<TreeNode<T>> removeHelper(std::unique_ptr<TreeNode<T>> node, T value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = removeHelper(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = removeHelper(std::move(node->right), value);
        } else {
            // Node found - handle three cases
            if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            } else {
                // Two children: find inorder successor
                TreeNode<T>* successor = findMin(node->right.get());
                node->data = successor->data;
                node->right = removeHelper(std::move(node->right), successor->data);
            }
        }

        return node;
    }

    // Helper function for inorder traversal
    void inorderHelper(const TreeNode<T>* node) const {
        if (node) {
            inorderHelper(node->left.get());
            std::cout << node->data << " ";
            inorderHelper(node->right.get());
        }
    }

public:
    void insert(T value) {
        insertHelper(root_, value);
    }

    bool search(T value) const {
        const TreeNode<T>* current = root_.get();
        while (current) {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left.get() : current->right.get();
        }
        return false;
    }

    void remove(T value) {
        root_ = removeHelper(std::move(root_), value);
    }

    void inorderTraversal() const {
        inorderHelper(root_.get());
        std::cout << "\n";
    }

    // Additional traversal methods
    void preorderTraversal() const {
        if (!root_) return;

        std::stack<const TreeNode<T>*> s;
        s.push(root_.get());

        while (!s.empty()) {
            const TreeNode<T>* node = s.top();
            s.pop();

            std::cout << node->data << " ";

            if (node->right) s.push(node->right.get());
            if (node->left) s.push(node->left.get());
        }
        std::cout << "\n";
    }

    void levelOrderTraversal() const {
        if (!root_) return;

        std::queue<const TreeNode<T>*> q;
        q.push(root_.get());

        while (!q.empty()) {
            const TreeNode<T>* node = q.front();
            q.pop();

            std::cout << node->data << " ";

            if (node->left) q.push(node->left.get());
            if (node->right) q.push(node->right.get());
        }
        std::cout << "\n";
    }

    const TreeNode<T>* getRoot() const {
        return root_.get();
    }
};

// Tree utility functions
template <typename T>
int getHeight(const TreeNode<T>* node) {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left.get()), getHeight(node->right.get()));
}

template <typename T>
bool isBalanced(const TreeNode<T>* node) {
    if (!node) return true;

    int leftHeight = getHeight(node->left.get());
    int rightHeight = getHeight(node->right.get());

    return std::abs(leftHeight - rightHeight) <= 1 &&
           isBalanced(node->left.get()) &&
           isBalanced(node->right.get());
}

template <typename T>
int countNodes(const TreeNode<T>* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left.get()) + countNodes(node->right.get());
}

int main() {
    std::cout << "=== Binary Search Tree Demo ===\n\n";

    BinarySearchTree<int> bst;

    // Insert elements
    std::vector<int> elements = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    std::cout << "Inserting elements: ";
    for (int elem : elements) {
        std::cout << elem << " ";
        bst.insert(elem);
    }
    std::cout << "\n\n";

    // Traversals
    std::cout << "Inorder traversal (sorted): ";
    bst.inorderTraversal();

    std::cout << "Preorder traversal: ";
    bst.preorderTraversal();

    std::cout << "Level-order traversal: ";
    bst.levelOrderTraversal();
    std::cout << "\n";

    // Search operations
    std::cout << "Searching for 40: " << (bst.search(40) ? "found" : "not found") << "\n";
    std::cout << "Searching for 90: " << (bst.search(90) ? "found" : "not found") << "\n\n";

    // Remove elements
    std::cout << "Removing 30 (node with two children)\n";
    bst.remove(30);
    std::cout << "Inorder after removal: ";
    bst.inorderTraversal();

    std::cout << "Removing 80 (leaf node)\n";
    bst.remove(80);
    std::cout << "Inorder after removal: ";
    bst.inorderTraversal();

    // Tree properties
    std::cout << "\n Tree height: " << getHeight(bst.getRoot()) << "\n";
    std::cout << "Total nodes: " << countNodes(bst.getRoot()) << "\n";
    std::cout << "Is balanced: " << (isBalanced(bst.getRoot()) ? "yes" : "no") << "\n";

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. BST: left < root < right for O(log n) operations\n";
    std::cout << "2. Use std::unique_ptr for automatic memory management\n";
    std::cout << "3. Inorder traversal gives sorted order in BST\n";
    std::cout << "4. Level-order uses queue, depth-first use stack/recursion\n";
    std::cout << "5. Balance trees (AVL, Red-Black) maintain O(log n) height\n";
    std::cout << "6. Tree rotations maintain balance in self-balancing trees\n";
    std::cout << "7. Use smart pointers to avoid memory leaks in tree operations\n";

    return 0;
}