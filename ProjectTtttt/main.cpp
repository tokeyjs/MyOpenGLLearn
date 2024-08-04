#include<iostream>
#include<Windows.h>
#include<string>
#include "tinyxml.h"

// 读取INI文件
void ReadIniValue(const wchar_t* iniFilePath, const wchar_t* section, const wchar_t* key) {
    wchar_t buffer[512] = { 0 };
    GetPrivateProfileString(section, key, TEXT(""), buffer, sizeof(buffer), iniFilePath);
    std::wcout << buffer<<std::endl;
}

// 写入INI文件
void WriteIniValue(const  wchar_t* iniFilePath,const wchar_t* section,const wchar_t* key,const wchar_t* value) {
    WritePrivateProfileString(section, key, value, iniFilePath);
}


// 测试ini文件读写
void TEST_INI() {
    const wchar_t* iniPath = TEXT("./test.ini");
    WriteIniValue(iniPath, L"Settings", L"Language", L"English");
    WriteIniValue(iniPath, L"SettingsPlus", L"Language", L"English");
    WriteIniValue(iniPath, L"Settings", L"Name", L"Like");
    ReadIniValue(iniPath, L"Settings", L"Language");
    ReadIniValue(iniPath, L"Settings", L"Age");
}


// 测试xml文件读写
void TEST_XML() {
    /*
    <?xml version="1.0" encoding="utf-8"?>
    <site>
	    <name>RUNOOB</name>
	    <url>https://www.runoob.com</url>
	    <logo>runoob-logo.png</logo>
	    <desc>编程学习网站</desc>
    </site>
    */

    // 插入
    TiXmlDocument* tinyXmlDoc = new TiXmlDocument("./test.xml");
    // xml的声明(三个属性：版本，编码格式，保留空串即可)
    TiXmlDeclaration* tinyXmlDeclare = new TiXmlDeclaration("1.0", "utf-8", "");	// 声明头部格式
    // 插入文档类中
    tinyXmlDoc->LinkEndChild(tinyXmlDeclare);

    tinyXmlDoc->SaveFile();

}






int main() {
    
    TEST_XML();
	system("pause");
	return 0;
}