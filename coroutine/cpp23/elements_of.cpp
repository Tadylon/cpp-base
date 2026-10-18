#include <generator>
#include <ranges>
#include <iostream>
#include <memory>
#include <vector>

struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(int v, std::unique_ptr<TreeNode> l = nullptr,std::unique_ptr<TreeNode> r = nullptr)
        : val(v), left(std::move(l)), right(std::move(r)) {}
};

std::generator<int> inorder_traversal(const TreeNode* root)
{
    if (!root) {
        co_return;
    }

    co_yield std::ranges::elements_of(inorder_traversal(root->left.get()));

    co_yield root->val;

    co_yield std::ranges::elements_of(inorder_traversal(root->right.get()));

}

// elements_of 甚至可以直接把普通容器（如 vector / 数组）拍平产出！
std::generator<const int&> flatten_batches(const std::vector<std::vector<int>>& batches) {
    for (const auto& batch : batches) {
        co_yield std::ranges::elements_of(batch);   // 现在可以编译
    }
}

int main() {
    /* 构造如下二叉树:
            4
           / \
          2   5
         / \
        1   3
    */
    auto root = std::make_unique<TreeNode>(4,
        std::make_unique<TreeNode>(2,
            std::make_unique<TreeNode>(1),
            std::make_unique<TreeNode>(3)
        ),
        std::make_unique<TreeNode>(5)
    );

    std::cout << "二叉树惰性中序遍历（一旦找到 3 就立刻停止遍历后续节点）:\n";
    for (int val : inorder_traversal(root.get())) {
        std::cout << "访问节点: " << val << "\n";
        if (val == 3) {
            std::cout << "-> 已找到目标 3，提前 break！节点 4 和 5 甚至根本不会被遍历到。\n";
            break;
        }
    }

    return 0;
}

