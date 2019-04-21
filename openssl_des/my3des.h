//
// Created by gzbd on 2016/12/7.
//

#ifndef RSADEMO_MY3DES_H
#define RSADEMO_MY3DES_H

#include <string>
#include <stdio.h>
#include <stdlib.h>


class My3DES {

public:
	/*
	* ���Զ��������3DES ����
	*/
	static std::string  encryptDES(const std::string& data, std::string  k, int *lenreturn);
	static std::string  decryptDES(const std::string& data, std::string k, int data_len);
	/*
	* �Զ���������ļӽ��ܣ�����ӽ���һ�κ���Զ������µģ���ǰ�����ݽ��ܻ�ʧ��
	*/
	static  std::string encryptDES(const std::string& data, int *lenreturn);
	static  std::string decryptDES(const std::string& data, int data_len);


private:

	static std::string getKey();
};


#endif //RSADEMO_MY3DES_H
