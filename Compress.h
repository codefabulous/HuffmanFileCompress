//
// Created by 馨 on 2018/4/28.
//实现文件的压缩算法
//

#ifndef HUFFMANCOMPRESSCPRO_COMPRESS_H
#define HUFFMANCOMPRESSCPRO_COMPRESS_H
#include "Huffman.h"
#include <iostream>
using namespace std;

struct HEAD{
    char type[4];//文件类型
    int length;//原文件长度
    int weight[256];//权值数值
};


void InitHead(char* filename, HEAD &sHead);
int WriteFile(char* pfilename, HEAD sHead, unsigned char* pBuffer, int nSize);




/*
 * use Encode() to compress files
 */
void Compress(char *filename);

/*
 * to read the previous file and init file HEAD data
 * (including previous file length and weights of 256 nodes?)
 */
void InitHead();

/*
 * use Huffman to compress files
 * need: strcat + str2byte(char)
 */
//char* Encode(char* filename, huffmanCode hc, char*pBuffer, int nSize);
unsigned char* Encode(char* filename, huffmanCode hc, unsigned char*pBuffer, int nSize);

void Encode2(char* filename, huffmanCode hc, char*pBuffer, int nSize);

/*
 * change 8 char to 1 char
 */
unsigned char str2byte(char* pBinStr);

/*
 * write data to the new file
 * return len
 */
int WriteFile();




//???why need class here???
class Compress{};



#endif //HUFFMANCOMPRESSCPRO_COMPRESS_H
