// openssl_des.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include "my3des.h"
#include "base64.h"
#include <windows.h>

std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "运行my3des............" << std::endl;
	My3DES des;
	int lenreturn = 0;
	std::string password = "a123okiuytrew12546iuygtre";
	std::string data = "这是一个测试 dd lkpasoidjf[oq $%^$#&*&#";
	std::cout << "原始数据：  " << data << "  长度：" << data.size() << std::endl;
	std::string utf = string_To_UTF8(data);
	std::string e_result = des.encryptDES(utf, password, &lenreturn);
	std::string encoded = base64_encode((unsigned char *)e_result.c_str(), e_result.size());
	std::string rest2_decoded = base64_decode(encoded);
	std::string d_result = des.decryptDES(rest2_decoded, password, rest2_decoded.size());
	std::string last_result = UTF8_To_string(d_result);
	std::cout << "解密数据：  " << last_result << std::endl;
	///////////////////////////////////////////////////////////////////////
	
	if (strcmp(data.c_str(), last_result.c_str()) == 0)
	{
		std::cout << "原始数据与解码数据相同.................. "  << std::endl;
	}
	else
	{
		std::cout << "00000000000000000000000000000000000000000 " << std::endl;

	}
	
	return 0;
}

