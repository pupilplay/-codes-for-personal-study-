//可能需要#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;
class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {};
    TreeNode(int val) : val(val), left(NULL), right(NULL) {};
    TreeNode(int val, TreeNode* left, TreeNode* right) :val(val), left(left), right(right) {};
    void createByLevel(char* str)
        //注意：该函数将传入的字符串的','改为'\0'
    {
        if (*str == 0) return;
        vector<char*>nums;
        bool end = false;
        char* next = str;
        do
        {
            while (*next && *next != ',')
                next++;
            if (*next == 0) end = true;
            *next = 0;
            if (*str != '#')
            {
                nums.push_back(new char[strlen(str) + 1]);
                strcpy(nums.back(), str);
            }
            else
            {
                nums.push_back(new char[2]);
                nums.back()[0] = '#';
                nums.back()[1] = 0;
            }
            next++;
            str = next;
        } while (!end);
        createByLevel(nums);
    }
    void createByLevel(string str)
    {
        if (str.length()==0) return;
        vector<string>nums;
        int start = 0;
        int end = 0;
        while (end != string::npos)
        {
            end = str.find(',', start);
            nums.push_back(str.substr(start,end-start));
            start = end + 1;
        }
        createByLevel(nums);
    }
    void createByLevel(vector<string> nums)
    {
        int numsSize = nums.size();
        if (numsSize == 0) return;
        queue<TreeNode*>q;
        q.push(this);
        istringstream(nums[0]) >> this->val;
        int cur = 1;
        int level_count;
        TreeNode* tmp;
        while (cur < numsSize)
        {
            tmp = q.front();
            if (nums[cur].front() != '#')
            {
                tmp->left = new TreeNode();
                istringstream(nums[cur]) >> tmp->left->val;
                q.push(tmp->left);
            }
            cur++;
            if (cur < numsSize && nums[cur].front() != '#')
            {
                tmp->right = new TreeNode();
                istringstream(nums[cur]) >> tmp->right->val;
                q.push(tmp->right);
            }
            cur++;
            q.pop();
        }
        return;
    }
    void createByLevel(vector<char*> nums)
    {
        int numsSize = nums.size();
        if (numsSize == 0) return;
        queue<TreeNode*>q;
        q.push(this);
        this->val = atoi(nums[0]);
        int cur = 1;
        int level_count;
        TreeNode* tmp;
        while (cur < numsSize)
        {
            tmp = q.front();
            if (*nums[cur] != '#')
            {
                tmp->left = new TreeNode(atoi(nums[cur]));
                q.push(tmp->left);
            }
            cur++;
            if (cur < numsSize && *nums[cur] != '#')
            {
                tmp->right = new TreeNode(atoi(nums[cur]));
                q.push(tmp->right);
            }
            cur++;
            q.pop();
        }
        return;
    }
    void createByLevel(char** nums, int numsSize)
        //此处不能直接传入二维数组名，因为二维数组名是一个数组指针，必须通过malloc或new的方式间接开辟字符串数组
    {
        if (numsSize == 0) return;
        queue<TreeNode*>q;
        q.push(this);
        this->val = atoi(nums[0]);
        int cur = 1;
        int level_count;
        TreeNode* tmp;
        while (cur < numsSize)
        {
            tmp = q.front();
            if (*nums[cur] != '#')
            {
                tmp->left = new TreeNode(atoi(nums[cur]));
                q.push(tmp->left);
            }
            cur++;
            if (cur < numsSize && *nums[cur] != '#')
            {
                tmp->right = new TreeNode(atoi(nums[cur]));
                q.push(tmp->right);
            }
            cur++;
            q.pop();
        }
        return;
    }
    void printByLevel(bool levelEndl = false, bool printNull = true)
        //层序打印，levelEndl表示是否换行，printNull表示是否打印NULL指针
    {
        queue<TreeNode*>q;
        q.push(this);
        while (!q.empty())
        {
            int level_count = q.size();
            for (int i = 0; i < level_count; i++)
            {
                TreeNode* tmp = q.front();
                if (tmp == NULL)
                {
                    printf("%s ", "#");
                    q.pop();
                    continue;
                }
                printf("%d ", tmp->val);
                if (tmp->left != NULL) q.push(tmp->left);
                else if (printNull) q.push(NULL);
                if (tmp->right != NULL) q.push(tmp->right);
                else if (printNull) q.push(NULL);
                q.pop();
            }
            if (levelEndl) putchar('\n');
        }
    }
    void pirntAsTree()
    {
        //undefined;
    }
};
