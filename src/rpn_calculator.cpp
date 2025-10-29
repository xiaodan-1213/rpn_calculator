#include "rpn_calculator.h"

// 构造函数
RPNCalculator::RPNCalculator() {
    // 构造函数可以留空或初始化成员变量
}

// 将值压入栈
void RPNCalculator::push(double value) { 
    stack.push(value); 
}

// 从栈中弹出值
double RPNCalculator::pop() {
    if (stack.empty()) {
        throw StackUnderflowException();
    }
    double value = stack.top();
    stack.pop();
    return value;
}

// 清空栈
void RPNCalculator::clear() {
    while (!stack.empty()) {
        stack.pop();
    }
}

// 显示当前栈内容
void RPNCalculator::displayStack() const {
    if (stack.empty()) {
        std::cout << "栈为空" << std::endl;
        return;
    }
    
    std::cout << "当前栈 (从顶到底): ";
    std::stack<double> temp = stack;
    std::vector<double> elements;
    
    // 将栈内容复制到向量中以便显示
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }
    
    // 反向显示，让栈顶在右边
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// 执行计算操作
void RPNCalculator::calculate(const std::string& operation) {
    if (operation == "clear") {
        clear();
        history.push_back("清空栈");
        return;
    }
    
    if (operation == "show") {
        displayStack();
        return;
    }
    
    // 加法
    if (operation == "+") {
        if (stack.size() < 2) throw StackUnderflowException();
        double b = pop();
        double a = pop();
        double result = a + b;
        push(result);
        history.push_back("加法: " + std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(result));
    }
    // 减法
    else if (operation == "-") {
        if (stack.size() < 2) throw StackUnderflowException();
        double b = pop();
        double a = pop();
        double result = a - b;
        push(result);
        history.push_back("减法: " + std::to_string(a) + " - " + std::to_string(b) + " = " + std::to_string(result));
    }
    // 乘法
    else if (operation == "*") {
        if (stack.size() < 2) throw StackUnderflowException();
        double b = pop();
        double a = pop();
        double result = a * b;
        push(result);
        history.push_back("乘法: " + std::to_string(a) + " * " + std::to_string(b) + " = " + std::to_string(result));
    }
    // 除法
    else if (operation == "/") {
        if (stack.size() < 2) throw StackUnderflowException();
        double b = pop();
        double a = pop();
        if (b == 0) throw DivisionByZeroException();
        double result = a / b;
        push(result);
        history.push_back("除法: " + std::to_string(a) + " / " + std::to_string(b) + " = " + std::to_string(result));
    }
    // 幂运算
    else if (operation == "^") {
        if (stack.size() < 2) throw StackUnderflowException();
        double exponent = pop();
        double base = pop();
        double result = std::pow(base, exponent);
        push(result);
        history.push_back("幂运算: " + std::to_string(base) + " ^ " + std::to_string(exponent) + " = " + std::to_string(result));
    }
    // 平方根
    else if (operation == "sqrt") {
        if (stack.size() < 1) throw StackUnderflowException();
        double value = pop();
        if (value < 0) throw RPNException("错误: 负数不能开平方根");
        double result = std::sqrt(value);
        push(result);
        history.push_back("平方根: sqrt(" + std::to_string(value) + ") = " + std::to_string(result));
    }
    // 斐波那契数列
    else if (operation == "fib") {
        calculateFibonacci();
    }
    // 杨辉三角
    else if (operation == "pascal") {
        calculatePascalTriangle();
    }
    // 无效操作符
    else {
        throw InvalidOperatorException(operation);
    }
}

// 计算整个 RPN 表达式
double RPNCalculator::evaluateExpression(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        // 检查退出命令
        if (token == "q" || token == "quit") {
            return 0;
        }
        
        // 尝试将 token 转换为数字
        try {
            double number = std::stod(token);
            push(number);
            continue;
        } catch (const std::invalid_argument&) {
            // 不是数字，继续检查操作符
        }
        
        // 处理操作符
        try {
            calculate(token);
        } catch (const RPNException& e) {
            std::cerr << e.what() << std::endl;
            throw;
        }
    }
    
    // 检查栈是否为空
    if (stack.empty()) {
        throw StackUnderflowException();
    }
    
    // 返回最终结果
    double result = stack.top();
    history.push_back("表达式结果: " + expression + " = " + std::to_string(result));
    return result;
}

// 计算斐波那契数列第 n 项
double RPNCalculator::fibonacci(int n) {
    if (n < 0) throw RPNException("错误: 斐波那契数列索引不能为负数");
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    double a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        double temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// 计算斐波那契数列
void RPNCalculator::calculateFibonacci() {
    if (stack.size() < 1) throw StackUnderflowException();
    int n = static_cast<int>(pop());
    if (n < 0) throw RPNException("错误: 斐波那契数列索引不能为负数");
    double result = fibonacci(n);
    push(result);
    history.push_back("斐波那契: fib(" + std::to_string(n) + ") = " + std::to_string(result));
    std::cout << "斐波那契数列第 " << n << " 项: " << result << std::endl;
}

// 计算杨辉三角
void RPNCalculator::calculatePascalTriangle() {
    if (stack.size() < 1) throw StackUnderflowException();
    int n = static_cast<int>(pop());
    if (n < 0) throw RPNException("错误: 杨辉三角行数不能为负数");
    
    std::cout << "杨辉三角第 " << n << " 行: ";
    std::vector<double> row(n + 1, 1);
    
    // 计算杨辉三角的系数
    for (int i = 1; i < n; i++) {
        row[i] = row[i - 1] * (n - i + 1) / i;
    }
    
    // 输出结果
    for (int i = 0; i <= n; i++) {
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
    
    // 将中间值推入栈中以便后续使用
    push(row[n / 2]);
    history.push_back("杨辉三角: 显示第 " + std::to_string(n) + " 行");
}

// 返回栈的大小
size_t RPNCalculator::stackSize() const { 
    return stack.size(); 
}

// 返回计算历史
const std::vector<std::string>& RPNCalculator::getHistory() const { 
    return history; 
}

