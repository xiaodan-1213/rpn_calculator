#include <iostream>
#include <string>
#include "rpn_calculator.h"

// 显示欢迎信息和帮助
void printWelcome() {
    std::cout << "==========================================" << std::endl;
    std::cout << "        RPN 计算器 - C++ 编程作业" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "🎯 基础功能 (作业要求):" << std::endl;
    std::cout << "  +, -, *, /  : 四则运算" << std::endl;
    std::cout << "  clear       : 清空栈" << std::endl;
    std::cout << "  show        : 显示当前栈" << std::endl;
    std::cout << "🎯 高级功能 (作业加分项):" << std::endl;
    std::cout << "  ^           : 幂运算 (2 3 ^ = 8)" << std::endl;
    std::cout << "  sqrt        : 平方根 (9 sqrt = 3)" << std::endl;
    std::cout << "  fib         : 斐波那契数列 (5 fib = 5)" << std::endl;
    std::cout << "  pascal      : 杨辉三角 (4 pascal)" << std::endl;
    std::cout << "🔧 系统命令:" << std::endl;
    std::cout << "  history     : 显示计算历史" << std::endl;
    std::cout << "  q / quit    : 退出程序" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "📝 作业示例:" << std::endl;
    std::cout << "  输入: 5 1 2 + 4 * + 3 -" << std::endl;
    std::cout << "  步骤: 1 2 + = 3 → 3 4 * = 12 → 5 12 + = 17 → 17 3 - = 14" << std::endl;
    std::cout << "  结果: 14" << std::endl;
    std::cout << "==========================================" << std::endl;
}

// 显示计算历史
void printHistory(const RPNCalculator& calc) {
    const auto& history = calc.getHistory();
    if (history.empty()) {
        std::cout << "📭 计算历史为空" << std::endl;
        return;
    }
    
    std::cout << "📜 计算历史:" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    for (size_t i = 0; i < history.size(); i++) {
        std::cout << "  " << i + 1 << ". " << history[i] << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

// 主函数
int main() {
    RPNCalculator calculator;
    std::string input;
    
    // 显示欢迎信息
    printWelcome();
    
    // 主循环
    while (true) {
        std::cout << "\n🔢 输入RPN表达式> ";
        std::getline(std::cin, input);
        
        // 跳过空输入
        if (input.empty()) {
            continue;
        }
        
        // 处理退出命令
        if (input == "q" || input == "quit") {
            std::cout << "👋 感谢使用 RPN 计算器！作业完成。" << std::endl;
            break;
        }
        
        // 处理历史命令
        if (input == "history") {
            printHistory(calculator);
            continue;
        }
        
        // 处理清空栈命令
        if (input == "clear") {
            calculator.clear();
            std::cout << "🗑️  栈已清空" << std::endl;
            continue;
        }
        
        // 处理显示栈命令
        if (input == "show") {
            calculator.displayStack();
            continue;
        }
        
        // 处理 RPN 表达式计算
        try {
            double result = calculator.evaluateExpression(input);
            std::cout << "✅ 计算结果: " << result << std::endl;
        } 
        // 捕获自定义异常
        catch (const RPNException& e) {
            std::cerr << "❌ " << e.what() << std::endl;
        }
        // 捕获其他异常
        catch (const std::exception& e) {
            std::cerr << "💥 系统错误: " << e.what() << std::endl;
        }
    }
    
    return 0;
}

// 测试函数（可选）
void runTests() {
    std::cout << "\n🧪 运行自动化测试..." << std::endl;
    
    RPNCalculator testCalc;
    
    // 测试用例
    std::vector<std::pair<std::string, double>> testCases = {
        {"5 3 +", 8},          // 加法
        {"10 4 -", 6},         // 减法
        {"3 4 *", 12},         // 乘法
        {"15 3 /", 5},         // 除法
        {"2 3 ^", 8},          // 幂运算
        {"9 sqrt", 3},         // 平方根
        {"5 fib", 5},          // 斐波那契
        {"5 1 2 + 4 * + 3 -", 14}  // 复杂表达式
    };
    
    for (const auto& testCase : testCases) {
        try {
            testCalc.clear();
            double result = testCalc.evaluateExpression(testCase.first);
            if (result == testCase.second) {
                std::cout << "✅ 测试通过: " << testCase.first << " = " << result << std::endl;
            } else {
                std::cout << "❌ 测试失败: " << testCase.first << " 期望 " << testCase.second << " 得到 " << result << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "💥 测试异常: " << testCase.first << " - " << e.what() << std::endl;
        }
    }
}
