#ifndef RPN_CALCULATOR_H
#define RPN_CALCULATOR_H

#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

class RPNCalculator {
private:
    std::stack<double> stack;
    std::vector<std::string> history;
    
public:
    RPNCalculator();
    
    // 基础栈操作
    void push(double value);
    double pop();
    void clear();
    void displayStack() const;
    
    // 计算操作
    void calculate(const std::string& operation);
    double evaluateExpression(const std::string& expression);
    
    // 高级功能
    double fibonacci(int n);
    void calculateFibonacci();
    void calculatePascalTriangle();
    
    // 工具函数
    size_t stackSize() const;
    const std::vector<std::string>& getHistory() const;
};

// 异常处理类
class RPNException : public std::runtime_error {
public:
    explicit RPNException(const std::string& message) 
        : std::runtime_error(message) {}
};

class DivisionByZeroException : public RPNException {
public:
    DivisionByZeroException() 
        : RPNException("错误: 除以零") {}
};

class StackUnderflowException : public RPNException {
public:
    StackUnderflowException() 
        : RPNException("错误: 栈下溢 - 操作数不足") {}
};

class InvalidOperatorException : public RPNException {
public:
    InvalidOperatorException(const std::string& op) 
        : RPNException("错误: 无效操作符 - " + op) {}
};

#endif
