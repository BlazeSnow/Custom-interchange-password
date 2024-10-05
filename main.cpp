// Copyright (C) 2024 BlazeSnow
// 保留所有权利
// 本程序以GNU General Public License v3.0的条款发布
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<filesystem>

using namespace std;
//程序支持的密码个数
#define NumberOfLetterSupported 26

//程序自带的密码库
struct code {
	char sourceCode;
	char code;
};
struct code source[NumberOfLetterSupported] = { {'a', 'q'},
											   {'b', 'w'},
											   {'c', 'e'},
											   {'d', 'r'},
											   {'e', 't'},
											   {'f', 'y'},
											   {'g', 'u'},
											   {'h', 'i'},
											   {'i', 'o'},
											   {'j', 'p'},
											   {'k', 'a'},
											   {'l', 's'},
											   {'m', 'd'},
											   {'n', 'f'},
											   {'o', 'g'},
											   {'p', 'h'},
											   {'q', 'j'},
											   {'r', 'k'},
											   {'s', 'l'},
											   {'t', 'z'},
											   {'u', 'x'},
											   {'v', 'c'},
											   {'w', 'v'},
											   {'x', 'b'},
											   {'y', 'n'},
											   {'z', 'm'}, };

//编码密码
void encode(const char* a, int number) {
	for (int i = 0; i < number; i++) {
		int find = 0;
		for (auto& j : source) {
			//在密码库结构体中找到原文并打印密码
			if (j.sourceCode == *(a + i)) {
				cout << j.code;
				break;
			}
			//找不到原文
			else {
				find++;
			}
		}
		//在密码库结构体里找不到的字符处理
		if (find == NumberOfLetterSupported) {
			cout << *(a + i);
		}
	}
}

//解码密码
void decode(const char* a, int number) {
	for (int i = 0; i < number; i++) {
		int find = 0;
		for (auto& j : source) {
			//在密码库结构体中找到密码并打印原文
			if (j.code == *(a + i)) {
				cout << j.sourceCode;
				break;
			}
			//找不到密码
			else {
				find++;
			}
		}
		//在密码库结构体里找不到的字符处理
		if (find == NumberOfLetterSupported) {
			cout << *(a + i);
		}
	}
}

int main() {
	system("chcp 54936");
	cout << "Copyright (C) 2024 BlazeSnow.保留所有权利。" << endl;
	cout << "本程序以GNU General Public License v3.0的条款发布。" << endl;
	cout << "当前程序版本号：v1.0.0" << endl;
	cout << "https://github.com/BlazeSnow/Custom-interchange-password" << endl
		<< endl;
	//first_use字符变量用于判断是否创建自定义密码文件
	char first_use = '0';
	cout << "是否创建自定义密码文件?" << endl;
	cout << "1\t创建自定义密码文件" << endl;
	cout << "0\t仅读取自定义密码文件" << endl;
	cout << "请输入:" << endl;
	cin >> first_use;
	//first_use变量等于'1'时创建自定义密码文件
	if (first_use == '1') {
		//创建自定义密码文件
		fstream file("自定义密码文件.csv", ios_base::out);
		//如果文件创建成功
		if (file.is_open()) {
			for (auto& i : source) {
				file << i.sourceCode << ',' << i.code << endl;
			}
			file.close();
			cout << "创建密码文件成功" << endl;
			//打印文件路径,path变量用于存储路径
			std::filesystem::path path = std::filesystem::current_path();
			cout << "密码文件路径:" << path << endl;
			cout << "密码文件名称:自定义密码文件.csv" << endl;
			cout << "可用表格处理软件Excel处理该文件" << endl;
			cout << "该表格的左列为源码,右列为密码" << endl;
			return 0;
		}
		//文件创建失败,报错abort
		else {
			cout << "ERROR:创建文件失败" << endl;
			system("pause");
			exit(1);
		}
	}
	//first_use变量等于'0'时读取自定义密码文件
	else if (first_use == '0') {
		//读取密码文件
		fstream file("自定义密码文件.csv", ios_base::in);
		//文件读取成功
		if (file.is_open()) {
			//把密码文件覆写到source结构体
			for (auto& i : source) {
				char temp;
				file >> i.sourceCode;
				file >> temp;
				file >> i.code;
			}
			cout << "读取密码文件成功" << endl;
		}
		//文件读取失败,报错abort
		else {
			cout << "ERROR:读取密码文件失败" << endl;
			system("pause");
			exit(1);
		}
		//处理的字符串长度100
		int number = 100;
		char* a = (char*)calloc(sizeof(char), number);
		//calloc创建检查,失败报错abort
		if (!a) {
			cout << "ERROR:calloc" << endl;
			system("pause");
			exit(1);
		}
		//输入需要处理的内容
		cout << "请输入需要编码或解码的内容:" << endl;
		//清空cin序列
		cin.ignore();
		for (int i = 0; i < number; i++) {
			*(a + i) = (char)cin.get();
			//检测到回车时结束输入
			if (*(a + i) == '\n') {
				number = i;
				break;
			}
		}
		//处理内容并输出
		cout << "编码结果为:" << endl;
		encode(a, number);
		cout << endl;
		cout << "解码结果为:" << endl;
		decode(a, number);
		cout << endl;
		//calloc收尾
		free(a);
	}
	//first_use变量等于其他字符时,报错abort
	else {
		cout << "ERROR:检测到非法字符" << endl;
		system("pause");
		exit(1);
	}
	system("pause");
	return 0;
}