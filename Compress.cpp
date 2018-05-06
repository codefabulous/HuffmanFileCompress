//
// Created by 馨 on 2018/4/28.
//

#include "Compress.h"
#include "Huffman.h"
#include "File.h"
#include <iostream>
using namespace std;

//char str2byte(char * pBinStr){
//    char b=0x00;
//    for(int i=0; i<8; i++){//8个字符转换为1个字符
//        b=b <<1;
//        if(pBinStr[i]=='1'){
//            b=b|0x01;///?
//        }
//    }
//
//    return b;///一开始忘记写，导致返回没有编码
//}

unsigned char str2byte(char * pBinStr){
    unsigned char b=0x00;
    for(int i=0; i<8; i++){//8个字符转换为1个字符
        b=b <<1;
        if(pBinStr[i]=='1'){
            b=b|0x01;///?
        }
    }

    return b;///一开始忘记写，导致返回没有编码
}

//void Encode(char* filename, huffmanCode hc, char*pBuffer, int nSize, int len){
//    ///...???
//    //开辟缓冲区
//    pBuffer = (char*) malloc(nSize* sizeof(char));
//    if(!pBuffer){
//        cerr<<"开辟缓冲区失败"<<endl;
//    }
//
//    char *cd=new char[len];//所有编码的字符串
//    int pos=0;//缓冲区指针
//    int ch;
//      //扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中
////    FILE *in = fopen(filename,"rb");
////
////    while((ch=fgetc(in)!=EOF)){
////        strcat(cd,hc[ch].code);
////    }
////    fclose(in);///?
//
//
//    int count=0;
//    for(int i=1; i<=256; i++){
//        for(int j=hc[i-1].length-1; j>=0; j--){
//            //strcat(cd,hc[i-1].code);
//            cd[count++]=  hc[i - 1].code[j];
//        }
//    }
//
//
//    //压缩编码成字节
//    int m=len/8, n=len%8;//m个8，剩余n个
//    for(int i=0; i<m; i++){//将前m个8压缩
//        for(int j=0; j<8; j++){//装到前8个里面
//            cd[j]=cd[j+i*8];
//        }
//        pBuffer[pos++]=str2byte(cd);//压缩
//    }
//    if(n!=0){
//        char temp[8]={0};
//        for(int i=0; i<n; i++){
//            temp[i]=cd[8*m+i];
//        }
//        pBuffer[pos]=str2byte(temp);
//    }
//
//}

unsigned char* Encode(char* filename, huffmanCode hc, unsigned char*pBuffer, int nSize){
    ///...???
    //开辟缓冲区
    pBuffer = (unsigned char*) malloc(nSize* sizeof(unsigned char));
    if(!pBuffer){
        cerr<<"开辟缓冲区失败"<<endl;
    }

    //int m=len/8, n=len%8;//m个8，剩余n个
    char *cd=  new char[8];//所有编码的字符串
    int pos=0;//缓冲区指针
//    int ch;
//    //扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中
//    FILE *in = fopen(filename,"rb");
//
//    while((ch=fgetc(in)!=EOF)){
//        strcat(cd,hc[ch].code);
//    }
//    fclose(in);///?


    int count=0;
    for(int i=1; i<=256; i++){
        for(int j=hc[i-1].length-1; j>=0; j--){
            //strcat(cd,hc[i-1].code);
            cd[count++]=  hc[i - 1].code[j];
            cout<<cd[count-1]<<endl;
            while(count==8){
                pBuffer[pos++]=str2byte(cd);///压缩
                //cout<<pBuffer[pos-1]<<endl;
                printf("0x%02X\n",pBuffer[pos-1]);
                count=0;
            }
        }
    }
    if(count>0){
        for(int i=count; i<8; i++){
            cd[i]=0;
        }
        pBuffer[pos]=str2byte(cd);///压缩
    }

    return pBuffer;



}

void Encode2(char* filename, huffmanCode hc, char*pBuffer, int nSize){
    ///...???
    //开辟缓冲区
    pBuffer = (char*) malloc(nSize* sizeof(char));
    if(!pBuffer){
        cerr<<"开辟缓冲区失败"<<endl;
    }

    char cd[256]={0};//所有编码的字符串
    int pos=0;//缓冲区指针
    int ch;
      //扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中
    FILE *in = fopen(filename,"rb");

    while((ch=fgetc(in)!=EOF)){
        strcat(cd,hc[ch].code);
        while(strlen(cd)>=8){
            //截取字符串左边的8个字符，编成字节
            pBuffer[pos++]=str2byte(cd);
            //字符串整体左移8字节
            for(int i=0; i<256-8; i++){
                cd[i]=cd[i+8];
            }
        }
    }
    if(strlen(cd)>0){
        pBuffer[pos++]=strlen(cd);
    }

    fclose(in);///?

}






void Compress(char *filename){
    //huffman -> code
    huffmanTree ht=new HTNode[512];
    huffmanCode hc = new HTCode[512];
    int * weight = new int[256];
//    char * filename = new char[256];
//    filename = getFileName();
    weight = getFileWeight(filename);

    ht=CreateHuffmanTree(ht,weight);
    hc=HuffmanCode(ht,hc);


    //计算编码缓冲区大小
    int nSize=0,len=0,preFlen=0;
    for(int i=1; i<=256;i++){
        nSize += weight[i] * strlen(hc[i].code);
        len += hc[i].length;
    }
    //preFlen=nSize;
    nSize = (nSize%8)? nSize/8+1 : nSize/8;//总字节数


    unsigned char* pBuffer=NULL;
    pBuffer=Encode(filename,hc,pBuffer,nSize);
    //Encode2(filename,hc,pBuffer,nSize);
    if(!pBuffer){
        cout<<"wrong"<<endl;
    }
//    for(int i=0; i<200; i++){
//        printf("0x%02X\n",pBuffer[i]);
//    }
//        ///wonrg:cout<<pBuffer[i];

    FILE *in = fopen(filename,"rb");
    int ch=0;
    while(ch!=EOF){
        ch=getc(in);
        preFlen++;
    }
    fclose(in);

    preFlen=strlen(filename)+preFlen;
    cout<<"压缩前文件长度："<<preFlen<<"字节"<<endl;



    HEAD sHead;
    InitHead(filename,sHead);
    int fileLen=0;
    fileLen=WriteFile(filename,sHead,pBuffer,nSize);
    cout<<"压缩后文件长度："<<fileLen<<"字节"<<endl;

    cout<<"压缩率："<<(double)(preFlen-fileLen)/preFlen*100<<"%"<<endl;











}


void InitHead(char* filename, HEAD &sHead){
    //文件头
    strcpy(sHead.type,"HUF");//文件类型
    sHead.length=0;
    for(int i=0; i<256; i++){
        sHead.weight[i]=0;
    }
    FILE *in=fopen(filename,"rb");
    //...???
    int ch;
    while ((ch=fgetc(in))!=EOF){
        sHead.weight[ch]++;
        sHead.length++;
    }
    fclose(in);
    in=NULL;
}


int WriteFile(char* pfilename, HEAD sHead, unsigned char* pBuffer, int nSize){
    //生成文件名
    char filename[256]={0};
    strcpy(filename,pfilename);
    strcat(filename,".huf");

    //二进制流形式打开文件
    FILE *out = fopen(filename,"wb");
    //...
    //写文件头
    fwrite(&sHead, sizeof(HEAD),1,out);
    //写压缩后的编码
    fwrite(pBuffer, sizeof(char),nSize,out);
    //关闭文件。释放文件指针
    fclose(out);
    out=NULL;

    cout<<"生成压缩文件："<<filename<<endl;
    int len = sizeof(HEAD)+strlen(pfilename)+1+nSize;
    return len;
}














