//ͷ�ļ�
#include <filesystem>//C++17��׼���е��ļ�ϵͳ��
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip> 
#include<sstream>

//using namespace std;// �����ռ�����,��������ע�͵��ˣ����Ի���һ��std::

//�궨��
#define _CRT_SECURE_NO_WARNINGS 1// ȡ��VS2022�ľ���

//ȫ�ֱ���


//��������
int searchByTime();// ��ʱ�������
int searchByName(); // ����������
int pastDays();//�������
std::string searchContentInFile(const std::filesystem::path filePath,const std::string content);// ���ļ�������ָ������


//����ʵ��
int searchByTime() {

	std::cout << "������ʼʱ��ͽ���ʱ��,ʵ����20241001 20241005:";
	int start, end;
	std::cin >> start >> end;
	std::cout << "�������:" << std::endl;
	std::filesystem::path filePath = std::filesystem::current_path();//��ȡ��ǰ·��

	for (int i = start; i <= end; i++) {
		std::string result = searchContentInFile(filePath,std::to_string(i));
		if (result != "0")
			std::cout << result << std::endl;
	}

	return 0;
}


int searchByName() {
	std::cout << "��������:" ;
	std::string name;
	std::cin >> name;
	std::filesystem::path filePath = std::filesystem::current_path();//��ȡ��ǰ·��
	std::string result = searchContentInFile(filePath,name);
	
	if (result != "0")
		std::cout << result << std::endl;
	else
		std::cout << "û���ҵ��������" << std::endl;
	
	return 0;
}


int pastDays() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);// ת��Ϊ time_t
	std::tm now_tm = *std::localtime(&now_time_t);// �� time_t ת��Ϊ std::tm �ṹ
	std::ostringstream trans;
	trans << std::put_time(&now_tm, "%m%d");//ת��

	std::filesystem::path filePath = std::filesystem::current_path();
	std::string today=searchContentInFile(filePath,trans.str());

	if (today != "0"){
		std::cout<<"������죺"<<today<<std::endl;
		return 1;
	}

	return 0;
}



std::string searchContentInFile(const std::filesystem::path filePath,const std::string content) {
	std::filesystem::path filePath_txt = filePath / "lib.txt"; // ƴ���ļ�·��
	std::ifstream file(filePath_txt.string()); // ���ļ�
	std::string line;
	std::string result="0";

	if (!file.is_open()) {
		std::cerr << "�޷����ļ�: " << filePath_txt << std::endl;
	}

	while (std::getline(file, line)) { // ���ж�ȡ�ļ����ݲ���Ŀ��
		if (line.find(content) != std::string::npos) {
			result = line; 
			break;
		}
	}

	file.close(); 
	return result; // ���ذ���Ŀ��������������
}


int main() {
	if (pastDays() == 1) {
		std::cout << "Ϊʲô��ȥ���·�����ʲô��" << std::endl;
	}
	std::cout << "type 1: ��ʱ�������" << std::endl;
	std::cout << "type 2: ������" << std::endl;
	std::cout << ">";
	std::string input;//�ж�����
	std::cin >> input;
	
	if (input == "1")
		searchByTime();
	else if (input == "2")
		searchByName();
}