//头文件
#include <filesystem>//C++17标准库中的文件系统库
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip> 
#include<sstream>

//using namespace std;// 命名空间声明,不过现在注释掉了，所以会有一堆std::

//宏定义
#define _CRT_SECURE_NO_WARNINGS 1// 取消VS2022的警告

//全局变量


//函数声明
int searchByTime();// 按时间段搜索
int searchByName(); // 按名字搜索
int pastDays();//那年今日
std::string searchContentInFile(const std::filesystem::path filePath,const std::string content);// 在文件中搜索指定内容


//函数实现
int searchByTime() {

	std::cout << "输入起始时间和结束时间,实例：20241001 20241005:";
	int start, end;
	std::cin >> start >> end;
	std::cout << "搜索结果:" << std::endl;
	std::filesystem::path filePath = std::filesystem::current_path();//获取当前路径

	for (int i = start; i <= end; i++) {
		std::string result = searchContentInFile(filePath,std::to_string(i));
		if (result != "0")
			std::cout << result << std::endl;
	}

	return 0;
}


int searchByName() {
	std::cout << "输入名字:" ;
	std::string name;
	std::cin >> name;
	std::filesystem::path filePath = std::filesystem::current_path();//获取当前路径
	std::string result = searchContentInFile(filePath,name);
	
	if (result != "0")
		std::cout << result << std::endl;
	else
		std::cout << "没有找到相关内容" << std::endl;
	
	return 0;
}


int pastDays() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);// 转换为 time_t
	std::tm now_tm = *std::localtime(&now_time_t);// 将 time_t 转换为 std::tm 结构
	std::ostringstream trans;
	trans << std::put_time(&now_tm, "%m%d");//转换

	std::filesystem::path filePath = std::filesystem::current_path();
	std::string today=searchContentInFile(filePath,trans.str());

	if (today != "0"){
		std::cout<<"那年今天："<<today<<std::endl;
		return 1;
	}

	return 0;
}



std::string searchContentInFile(const std::filesystem::path filePath,const std::string content) {
	std::filesystem::path filePath_txt = filePath / "lib.txt"; // 拼接文件路径
	std::ifstream file(filePath_txt.string()); // 打开文件
	std::string line;
	std::string result="0";

	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filePath_txt << std::endl;
	}

	while (std::getline(file, line)) { // 逐行读取文件内容查找目标
		if (line.find(content) != std::string::npos) {
			result = line; 
			break;
		}
	}

	file.close(); 
	return result; // 返回包含目标整数的行内容
}


int main() {
	if (pastDays() == 1) {
		std::cout << "为什么不去看下发生过什么？" << std::endl;
	}
	std::cout << "type 1: 按时间段搜索" << std::endl;
	std::cout << "type 2: 按名字" << std::endl;
	std::cout << ">";
	std::string input;//判断类型
	std::cin >> input;
	
	if (input == "1")
		searchByTime();
	else if (input == "2")
		searchByName();
}