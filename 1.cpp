#include <iostream>
#include <string>
#include "stack.hpp"
using namespace std;
/*用于记录符号的优先级，这里浪费了一些内存，可以优化*/
static char priority[128] = {0};
void priorityInit()
{
    /*初始化优先级，值越小，优先级越高*/
    priority['+'] = 4;
    priority['-'] = 4;
    priority['*'] = 3;
    priority['/'] = 3;
    priority['('] = 1;
    priority[')'] = 1;
}
/*比较运算符的优先级,op1优先级大于op2时，返回大于0的值*/
int priorityCompare(char op1, char op2)
{
    return priority[op2] - priority[op1];
}
/*出栈操作符和操作数进行计算*/
int calcOp(Stack<int> &nums, Stack<int> &ops, int nowOp)
{
    int a, b, op;
    op = ops.top();
    ops.pop();
    b = nums.top();
    if (!nums.pop())
    {
        return -1;
    }
    a = nums.top();
    if (!nums.pop())
    {
        return 0;
    }
    switch (op)
    {
    case '+':
    {
        nums.push(a + b);
        break;
    }
    case '-':
    {
        nums.push(a - b);
        break;
    }
    case '*':
    {
        nums.push(a * b);
        break;
    }
    case '/':
    {
        if(b==0)
            return 0;
        nums.push(a / b);
        break;
    }
    }
    return 1;
}
int calc(string exp)
{
    if (exp.size() == 0)
        return -1;
    /*创建栈，用于保存数*/
    Stack<int> nums;
    /*用于保存操作符*/
    Stack<int> ops;
    int index = 0;
    /*用于标记，判断上一个是否为数字*/
    int flag = 0;
    int temp = 0;
    int op;
    for (int i = 0; i < exp.size(); i++)
    {
        /*如果是数字*/
        if (isdigit(exp[i]))
        {
            /*如果上一个还是数字，则取出栈顶数据*/
            if (1 == flag)
            {

                temp = nums.top();
                nums.pop();
            }
            else
                temp = 0;
            flag = 1;
            temp = 10 * temp + exp[i] - '0';
            nums.push(temp);
        }
        /*如果是操作符*/
        else if ('/' == exp[i] || '*' == exp[i] || '+' == exp[i] || '-' == exp[i])
        {
            flag = 0;
            while (ops.s_top(op) && '(' != op && ')' != op && (priorityCompare(exp[i], op) < 0))
            {
                calcOp(nums, ops, exp[i]);
            }
            ops.push(exp[i]);
        }
        /*左括号直接入栈*/
        else if ('(' == exp[i])
        {
            flag = 0;
            ops.push(exp[i]);
        }
        /*右括号，计算*/
        else if (')' == exp[i])
        {
            flag = 0;
            /*右括号时，不断计算，直到遇见左括号*/
            while (ops.s_top(op) && '(' != op)
            {
                calcOp(nums, ops, exp[i]);
            }
            op = ops.top();
            ops.pop();
        }
        else
        {
            flag = 0;
        }
    }
    /*计算剩余两个栈的内容*/
    while ((!ops.empty()) && (!nums.empty()))
    {
        if (!calcOp(nums, ops, 0))
        {
            printf("error\n");
            return -9999999;
        }
    }
    temp = nums.top();
    nums.pop();
    /*如果栈中还有内容，说明表达式错误*/
    if ((!ops.empty()) || (!nums.empty()))
        if (nums.pop())
            return temp;
    return temp;
}
int main(int argc, char *argv[])
{

    priorityInit();
    string exp;
    while (cin >> exp)
    {
        int ans = calc(exp);
        if (ans != -9999999)
        {
            cout << ans << endl;
        }
    }
    return 0;
}