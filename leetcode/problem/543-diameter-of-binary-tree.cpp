/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    struct retInfo {
        int longestLen;
        int diameter;
    };

    retInfo recDiameter(TreeNode *root) {
        if (root == nullptr) {
            return {.longestLen = 0, .diameter = 0};
        }

        retInfo leftInfo = recDiameter(root->left);
        retInfo rightInfo = recDiameter(root->right);

        int maxDiameter = max(leftInfo.diameter, rightInfo.diameter);
        int throughRootDiameter = leftInfo.longestLen + rightInfo.longestLen;

        return {.longestLen = max(leftInfo.longestLen, rightInfo.longestLen) + 1, .diameter=max(maxDiameter, throughRootDiameter)};
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return recDiameter(root).diameter;
    }
};
