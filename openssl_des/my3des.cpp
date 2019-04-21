//
// Created by gzbd on 2016/12/7.
//

#include <des.h>
#include "my3des.h"
#include <time.h>
#include <random>
#include<iostream>
#include <openssl/rand.h>

static std::string key;
#define BUFSIZE 1024

std::string My3DES::getKey()
{
	std::string passwordString = "abcdefFGNJghijklmn132sds133g232opqrstuvwxyz13236516fsfghbbx5165615ABCDEFffgfGHIJKLM14986321fsshh4892NOPQRSTUVydfewqWXYZ012345hhj6789";
	srand((unsigned)time(0));  //�������ÿ�β��������������
	int ran = rand() % passwordString.length();
	std::string key = passwordString.substr(ran % (passwordString.length() - 24), 24);
	return  key;
}

/*
* ���Զ��������3DES ����
*/

std::string  My3DES::encryptDES(const std::string& data, std::string k, int *lenreturn){

	int docontinue = 1;
	int data_len;
	int data_rest;
	unsigned char ch;
	unsigned char *src = NULL; /* ���������� */
	unsigned char *dst = NULL; /* ���ܺ������ */
	int len;
	unsigned char tmp[8];
	unsigned char in[8];
	unsigned char out[8];
	int key_len;
#define LEN_OF_KEY 24

	unsigned char block_key[9];
	DES_key_schedule ks, ks2, ks3;
	/* ���첹������Կ */
	key_len = k.length();
	for (int i = 0; i <LEN_OF_KEY - key_len; i++) 
	{

		k += "0";
	}
	/* ����������������ռ估����������� */
	//data_len = strlen(data.c_str());//ԭʼ���ݳ���
	data_len = data.size();//ԭʼ���ݳ���
	data_rest = data_len % 8;
	len = data_len + (8 - data_rest);
	ch = 8 - data_rest;
	src = (unsigned char *)malloc(len);
	dst = (unsigned char *)malloc(len);
	memset(dst, 0, len);
	if (NULL == src || NULL == dst) 
	{
		docontinue = 0;
	}

	if (docontinue) 
	{
		int count;
		int i;
		/* ���첹���ļ������� */
		memset(src, 0, len);
		memcpy(src, data.c_str(), data_len);
		memset(src + data_len, ch, 8 - data_rest);
		/* ��Կ�û� */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, k.c_str() + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, k.c_str() + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, k.c_str() + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);
		/* ѭ������/���ܣ�ÿ8�ֽ�һ�� */
		count = len / 8;
		for (i = 0; i < count; i++) 
		{
			memset(tmp, 0, 8);
			memset(in, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* ���� */
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)in, &ks,
				&ks2, &ks3,
				DES_ENCRYPT);
			memcpy(dst + 8 * i, in, 8);
		}
	}
	*lenreturn = len;


	if (NULL != src) 
	{
		free(src);
		src = NULL;
	}

	if (NULL != dst) 
	{
		/*static std::string eresult;
		eresult.clear();*/

		//eresult.assign((char *)dst);
		//eresult.assign(reinterpret_cast<char*>(dst));
		std::string eresult(reinterpret_cast<char*>(dst),len);
		free(dst);
		return eresult;
	}
	return NULL;

}
std::string    My3DES::decryptDES(const std::string& data, std::string  k, int data_len)
{

	int docontinue = 1;
	int data_rest;
	unsigned char ch;
	unsigned char *src = NULL; /* ���������� */
	unsigned char *dst = NULL; /* ���ܺ������ */
	int len;
	unsigned char tmp[8];
	unsigned char in[8];
	unsigned char out[8];
	int key_len;
#define LEN_OF_KEY 24
	unsigned char block_key[9];
	DES_key_schedule ks, ks2, ks3;
	/* ���첹������Կ */
	key_len = k.size();
	for (int i = 0; i <LEN_OF_KEY - key_len; i++) 
	{
		k += "0";
	}

	/* ����������������ռ估����������� */
	data_rest = data_len % 8;
	len = data_len;
	src = (unsigned char *)malloc(len);
	dst = (unsigned char *)malloc(len);
	memset(dst, 0, len);
	if (NULL == src || NULL == dst) 
	{
		docontinue = 0;
	}
	if (docontinue) 
	{
		int count;
		int i;
		/* ���첹���ļ������� */
		memset(src, 0, len);
		memcpy(src, data.c_str(), data_len);
		/* ��Կ�û� */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, k.c_str() + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, k.c_str() + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, k.c_str() + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);

		/* ѭ������/���ܣ�ÿ8�ֽ�һ�� */
		count = len / 8;
		for (i = 0; i < count; i++) 
		{
			memset(tmp, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* ���� */
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)out, &ks,
				&ks2, &ks3,
				DES_DECRYPT);
			/* �����ܵ����ݿ��������ܺ������ */
			memcpy((dst + 8 * i), out, 8);

		}
		for (i = 0; i < len; i++) 
		{
			if (*(dst + i) < 9) 
			{
				*(dst + i) = 0;
				break;
			}
		}
	}

	if (NULL != src) 
	{
		free(src);
		src = NULL;
	}
	if (NULL != dst) 
	{
		static std::string dresult;
		dresult.clear();
		dresult.assign((char *)dst);
		free(dst);
		return dresult;
	}
	return NULL;
}
/*
* �Զ���������ļӽ��ܣ�����ӽ���һ�κ���Զ������µģ���ǰ�����ݽ��ܻ�ʧ��
*/
std::string   My3DES::encryptDES(const std::string& data, int *lenreturn){


	key = getKey();


	int docontinue = 1;
	//  char *data = "gubojun"; /* ���� */
	int data_len;
	int data_rest;
	unsigned char ch;
	unsigned char *src = NULL; /* ���������� */
	unsigned char *dst = NULL; /* ���ܺ������ */
	int len;
	unsigned char tmp[8];
	unsigned char in[8];
	unsigned char out[8];

	//	char *k = "12345678"; /* ԭʼ��Կ */

	int key_len;
#define LEN_OF_KEY 24
	//	unsigned char key[LEN_OF_KEY]; /* ��������Կ */

	unsigned char block_key[9];
	DES_key_schedule ks, ks2, ks3;
	/* ���첹������Կ */




	key_len = key.length();


	for (int i = 0; i <LEN_OF_KEY - key_len; i++) {

		key += "0";
	}




	/* ����������������ռ估����������� */
	data_len = strlen(data.c_str());
	data_rest = data_len % 8;
	len = data_len + (8 - data_rest);
	ch = 8 - data_rest;
	src = (unsigned char *)malloc(len);
	dst = (unsigned char *)malloc(len);
	if (NULL == src || NULL == dst) {
		docontinue = 0;
	}

	if (docontinue) {
		int count;
		int i;
		/* ���첹���ļ������� */
		memset(src, 0, len);
		memcpy(src, data.c_str(), data_len);
		memset(src + data_len, ch, 8 - data_rest);
		/* ��Կ�û� */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, key.c_str() + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, key.c_str() + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, key.c_str() + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);
		/* ѭ������/���ܣ�ÿ8�ֽ�һ�� */
		count = len / 8;
		for (i = 0; i < count; i++) {
			memset(tmp, 0, 8);
			memset(in, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* ���� */
			//
			//			DES_ecb_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in,
			//					&schedule, DES_ENCRYPT);
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)in, &ks,
				&ks2, &ks3,
				DES_ENCRYPT);

			/* ���� */
			//          DES_ecb3_encrypt((const_DES_cblock*) in, (DES_cblock*) out, &ks,
			//                  &ks2, &ks3, DES_DECRYPT);
			/* �����ܵ����ݿ��������ܺ������ */
			//          memcpy(dst + 8 * i, out, 8);
			memcpy(dst + 8 * i, in, 8);
		}
	}

	*lenreturn = len;
	if (NULL != src) {
		free(src);
		src = NULL;
	}

	if (NULL != dst) {

		static std::string result;
		result.clear();

		result.assign(
			(char *)dst);
		free(dst);
		return result;

	}



	return NULL;



}
std::string   My3DES::decryptDES(const std::string& data, int data_len){


	int docontinue = 1;
	//  char *data = "gubojun"; /* ���� */
	//  int data_len;
	int data_rest;
	unsigned char ch;
	unsigned char *src = NULL; /* ���������� */
	unsigned char *dst = NULL; /* ���ܺ������ */



	int len;
	unsigned char tmp[8];
	unsigned char in[8];
	unsigned char out[8];
	//char *k = "12345678"; /* ԭʼ��Կ */
	int key_len;
#define LEN_OF_KEY 24
	//	unsigned char key[LEN_OF_KEY]; /* ��������Կ */
	unsigned char block_key[9];
	DES_key_schedule ks, ks2, ks3;
	/* ���첹������Կ */



	key_len = key.length();

	for (int i = 0; i <LEN_OF_KEY - key_len; i++) {

		key += "0";
	}


	/* ����������������ռ估����������� */
	data_rest = data_len % 8;
	len = data_len;
	src = (unsigned char *)malloc(len);
	dst = (unsigned char *)malloc(len);
	if (NULL == src || NULL == dst) {
		docontinue = 0;
	}
	if (docontinue) {
		int count;
		int i;
		/* ���첹���ļ������� */
		memset(src, 0, len);
		memcpy(src, data.c_str(), data_len);
		/* ��Կ�û� */
		memset(block_key, 0, sizeof(block_key));
		memcpy(block_key, key.c_str() + 0, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks);
		memcpy(block_key, key.c_str() + 8, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks2);
		memcpy(block_key, key.c_str() + 16, 8);
		DES_set_key_unchecked((const_DES_cblock*)block_key, &ks3);

		/* ѭ������/���ܣ�ÿ8�ֽ�һ�� */
		count = len / 8;
		for (i = 0; i < count; i++) {
			memset(tmp, 0, 8);
			memset(out, 0, 8);
			memcpy(tmp, src + 8 * i, 8);
			/* ���� */
			//          DES_ecb3_encrypt((const_DES_cblock*) tmp, (DES_cblock*) in, &ks,
			//                  &ks2, &ks3, DES_ENCRYPT);
			/* ���� */
			DES_ecb3_encrypt((const_DES_cblock*)tmp, (DES_cblock*)out, &ks,
				&ks2, &ks3,
				DES_DECRYPT);
			/* �����ܵ����ݿ��������ܺ������ */
			memcpy((dst + 8 * i), out, 8);


		}
		for (i = 0; i < len; i++) {
			if (*(dst + i) < 9) {
				*(dst + i) = 0;

				break;
			}
		}
	}

	if (NULL != src) {
		free(src);
		src = NULL;
	}
	if (NULL != dst) {


		static std::string result;
		result.clear();
		result.assign((char *)dst);
		free(dst);
		return result;
	}

	return NULL;



}