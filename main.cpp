#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
// 程序支持的密码个数
#define NumberOfLetterSupported 26

// 程序自带的密码库
struct code {
    char sourceCode; //原字符
    char desCode; //混淆后字符
};

struct code source[NumberOfLetterSupported] = {
    {'a', 'q'}, {'b', 'w'}, {'c', 'e'}, {'d', 'r'}, {'e', 't'}, {'f', 'y'}, {'g', 'u'}, {'h', 'i'}, {'i', 'o'},
    {'j', 'p'}, {'k', 'a'}, {'l', 's'}, {'m', 'd'}, {'n', 'f'}, {'o', 'g'}, {'p', 'h'}, {'q', 'j'}, {'r', 'k'},
    {'s', 'l'}, {'t', 'z'}, {'u', 'x'}, {'v', 'c'}, {'w', 'v'}, {'x', 'b'}, {'y', 'n'}, {'z', 'm'},
};

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void enterToContinue() {
    printf("按回车键继续...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    getchar();
}

// 编码密码
void encode(const char *a, int number) {
    for (int i = 0; i < number; i++) {
        int find = 0;
        for (auto &j: source) {
            // 在密码库结构体中找到原文并打印密码
            if (j.sourceCode == *(a + i)) {
                printf("%c", j.desCode);
                break;
            }
            // 找不到原文
            else {
                find++;
            }
        }
        // 在密码库结构体里找不到的字符处理
        if (find == NumberOfLetterSupported) {
            printf("%c", *(a + i));
        }
    }
}

// 解码密码
void decode(const char *a, int number) {
    for (int i = 0; i < number; i++) {
        int find = 0;
        for (auto &j: source) {
            // 在密码库结构体中找到密码并打印原文
            if (j.desCode == *(a + i)) {
                printf("%c", j.sourceCode);
                break;
            }
            // 找不到密码
            else {
                find++;
            }
        }
        // 在密码库结构体里找不到的字符处理
        if (find == NumberOfLetterSupported) {
            printf("%c", *(a + i));
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    clearConsole();
    printf("Copyright (C) 2024-2026 BlazeSnow. 保留所有权利。\n");
    printf("https://github.com/BlazeSnow/Custom-interchange-password\n\n");
    // first_use字符变量用于判断是否创建自定义密码文件
    char first_use = '0';
    printf("是否创建自定义密码文件?\n");
    printf("1\t创建自定义密码文件\n");
    printf("0\t仅读取自定义密码文件\n");
    printf("请输入:\n");
    scanf(" %c", &first_use);
    // first_use变量等于'1'时创建自定义密码文件
    if (first_use == '1') {
        // 创建自定义密码文件
        fstream file("Custom-interchange-password.csv", ios_base::out);
        // 如果文件创建成功
        if (file.is_open()) {
            for (auto &i: source) {
                file << i.sourceCode << ',' << i.desCode << endl;
            }
            file.close();
            printf("创建密码文件成功\n");
            // 打印文件路径,path变量用于存储路径
            std::filesystem::path path = std::filesystem::current_path();
            printf("密码文件路径: %s\n", path.string().c_str());
            printf("密码文件名称: Custom-interchange-password.csv\n");
            printf("可用表格处理软件Excel处理该文件\n");
            printf("该表格的左列为源码,右列为密码\n");
            enterToContinue();
            return 0;
        }
        // 文件创建失败,报错abort
        else {
            printf("ERROR:创建文件失败\n");
            enterToContinue();
            exit(1);
        }
    }
    // first_use变量等于'0'时读取自定义密码文件
    else if (first_use == '0') {
        // 读取密码文件
        fstream file("Custom-interchange-password.csv", ios_base::in);
        // 文件读取成功
        if (file.is_open()) {
            // 把密码文件覆写到source结构体
            for (auto &i: source) {
                char temp;
                file >> i.sourceCode;
                file >> temp;
                file >> i.desCode;
            }
            printf("读取密码文件成功\n");
        }
        // 文件读取失败,报错abort
        else {
            printf("ERROR:读取密码文件失败\n");
            enterToContinue();
            exit(1);
        }
        // 处理的字符串长度100
        int number = 100;
        char *a = (char *) calloc(sizeof(char), number);
        // calloc创建检查,失败报错abort
        if (!a) {
            printf("ERROR:calloc\n");
            enterToContinue();
            exit(1);
        }
        // 输入需要处理的内容
        printf("请输入需要编码或解码的内容:\n");
        // 清空输入缓冲区中残留的回车符
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        for (int i = 0; i < number; i++) {
            *(a + i) = (char) getchar();
            // 检测到回车时结束输入
            if (*(a + i) == '\n') {
                number = i;
                break;
            }
        }
        // 处理内容并输出
        printf("编码结果为:\n");
        encode(a, number);
        printf("\n");
        printf("解码结果为:\n");
        decode(a, number);
        printf("\n");
        // calloc收尾
        free(a);
    }
    // first_use变量等于其他字符时,报错abort
    else {
        printf("ERROR:检测到非法字符\n");
        enterToContinue();
        exit(1);
    }
    enterToContinue();
    return 0;
}
