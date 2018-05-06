//
// Created by 馨 on 2018/4/28.
//

#include "File.h"
#include <iostream>
using namespace std;

char * getFileName(){
    char *filename = new char[256];
    cout<<"请输入文件名的完整路径"<<endl;
    cin>>filename;
    return filename;
}

int * getFileWeight(char* filename){
//use filename to open; use weight[] to save weight
    int *weight = new int[256];
    //打开文件（二进制流形式),统计每个字节出现的频率
    FILE *in = fopen(filename,"rb");
    int ch=0;
    while(ch!=EOF){
        ch=getc(in);
        weight[ch]++;
    }
    fclose(in);
    return  weight;
}


void printWeight(char *filename){
    int * weight = getFileWeight(filename);
    //打印出频率的结果
    cout<<"原文件读取结果：每个字符和频率分别为："<<endl;
    cout<<"Byte"<<" Weight"<<endl;
    for(int i=0; i<256; i++){
        printf("0x%02X %d\n",i,weight[i]);//%02X：表示输出两位16进制，用大写表示
    }
}