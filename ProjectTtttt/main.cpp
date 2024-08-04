#include<iostream>
#include<Windows.h>
#include<string>
#include "tinyxml.h"

// ��ȡINI�ļ�
void ReadIniValue(const wchar_t* iniFilePath, const wchar_t* section, const wchar_t* key) {
    wchar_t buffer[512] = { 0 };
    GetPrivateProfileString(section, key, TEXT(""), buffer, sizeof(buffer), iniFilePath);
    std::wcout << buffer<<std::endl;
}

// д��INI�ļ�
void WriteIniValue(const  wchar_t* iniFilePath,const wchar_t* section,const wchar_t* key,const wchar_t* value) {
    WritePrivateProfileString(section, key, value, iniFilePath);
}


// ����ini�ļ���д
void TEST_INI() {
    const wchar_t* iniPath = TEXT("./test.ini");
    WriteIniValue(iniPath, L"Settings", L"Language", L"English");
    WriteIniValue(iniPath, L"SettingsPlus", L"Language", L"English");
    WriteIniValue(iniPath, L"Settings", L"Name", L"Like");
    ReadIniValue(iniPath, L"Settings", L"Language");
    ReadIniValue(iniPath, L"Settings", L"Age");
}


// ����xml�ļ���д
void TEST_XML() {
    /*
    <?xml version="1.0" encoding="utf-8"?>
    <site>
	    <name>RUNOOB</name>
	    <url>https://www.runoob.com</url>
	    <logo>runoob-logo.png</logo>
	    <desc>���ѧϰ��վ</desc>
    </site>
    */

    // ����
    TiXmlDocument* tinyXmlDoc = new TiXmlDocument("./test.xml");
    // xml������(�������ԣ��汾�������ʽ�������մ�����)
    TiXmlDeclaration* tinyXmlDeclare = new TiXmlDeclaration("1.0", "utf-8", "");	// ����ͷ����ʽ
    // �����ĵ�����
    tinyXmlDoc->LinkEndChild(tinyXmlDeclare);

    tinyXmlDoc->SaveFile();

}






int main() {
    
    TEST_XML();
	system("pause");
	return 0;
}