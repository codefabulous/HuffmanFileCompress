#include <iostream>
#include <stdlib.h>
#include "Compress.h"
#include "Huffman.h"
#include "File.h"

using namespace std;

//常用文件路径：/Users/xinrong/desktop/Pic.bmp

int main() {
    cout<<"========哈夫曼文件压缩========\n"<<endl;
//    cout<<"请输入文件名的完整路径"<<endl;
//    char filename[256];
//    cin>>filename;


    huffmanTree ht=new HTNode[512];
    huffmanCode hc = new HTCode[512];


    //init
    //输入文件名，获得权值
    int * weight = new int[256];
    char * filename = new char[256];
    filename = getFileName();
    weight = getFileWeight(filename);
    //建立huffmanTree
    ht=CreateHuffmanTree(ht,weight);
    //code huffmanTree
    hc=HuffmanCode(ht,hc);


    while(true){

        cout<<endl<<"~~~~~~~~~~~~功能~~~~~~~~~~~~"<<endl;
        cout<<"1.查看文件每个字符对应权值"<<endl;
        cout<<"2.查看文件生成的哈夫曼树节点信息"<<endl;
        cout<<"3.查看文件生成的哈夫曼树叶子节点编码"<<endl;
        cout<<"4.一键压缩"<<endl;
        cout<<"5.退出"<<endl;
        cout<<"请选择：（输入1/2/3/4/5）"<<endl;

        int choose=0;
        cin>>choose;

        if(choose==1){
            //查看文件每个字符对应权值
            printWeight(filename);
        }
        if(choose==2){
            //查看哈夫曼数每个节点的信息
            printf(" number\t    weight\t    parent\t    lchild\t    child\t  \n");
            for (int i = 0; i < 512; ++i) {
                printf("%5d       %6d       %5d       %5d       %5d\n",i,ht[i].weight,ht[i].parent,ht[i].lchild,ht[i].rchild);
                //cout<<"weight: "<<ht[i].weight<<" parent:"<<ht[i].parent<<" lchild: "<<ht[i].lchild<<"rchild: "<<ht[i].rchild <<endl;
            }
        }
        if(choose==3){
            //查看叶子节点编码
            printf("number\t    code\t \n");
            for(int i=1; i<=256; i++){
                printf("%3d\t\t\t",i);
                //cout<<i<<"       ";
                for(int j=hc[i].length-1;j>=0; j--){
                    cout<<hc[i].code[j];
                    //printf("%d",hc[i].code[j]);
                }
                printf("\n");
            }
        }
        if(choose==4){
            Compress(filename);
        }
        if(choose==5){
            break;
        }

    }


///this is for testing
//    huffmanTree testHT = new HTNode[9];
//    int * testWEI = new int[5];
//    for(int i=0; i<5; i++){
//        testWEI[i]=i+5;
//        cout<<testWEI[i]<<" ";
//    }


//输入文件名，获得权值
//    int * weight = new int[256];
//    char * filename = new char[256];
//    filename = getFileName();
//    weight = getFileWeight(filename);
//    //查看文件每个字符对应权值
//    printWeight(filename);



    ///testing: weight of init-ing
//    for (int i = 0; i < 512; ++i) {
//        cout<<"weight: "<<ht[i].weight<<endl;
//    }

    ///testing： huffman,find needing to =end, or it will be wrong when meeting the last word
//    testHT=TestSelect(testHT,testWEI);
//
//
//    printf(" number\t    weight\t    parent\t    lchild\t    child\t  \n");
//    for (int i = 0; i < 9; ++i) {
//        printf("%5d       %5d       %5d       %5d       %5d\n",i,testHT[i].weight,testHT[i].parent,testHT[i].lchild,testHT[i].rchild);
//        //cout<<"weight: "<<ht[i].weight<<" parent:"<<ht[i].parent<<" lchild: "<<ht[i].lchild<<"rchild: "<<ht[i].rchild <<endl;
//    }




    //TesthufTreeN(511,ht);






//    FILE *in = fopen("/Users/xinrong/desktop/Pic.bmp","rb");
//    int ch;
//    char cd[2048];
//    huffmanTree ht=new HTNode[512];
//    huffmanCode hc = new HTCode[512];
//    int * weight = new int[256];
////    char * filename = new char[256];
////    filename = getFileName();
//    weight = getFileWeight("/Users/xinrong/desktop/Pic.bmp");
//
//    ht=CreateHuffmanTree(ht,weight);
//    hc=HuffmanCode(ht,hc);
//    cout<<"right!";
//    while((ch=fgetc(in)!=EOF)){
//        strcat(cd,hc[ch].code);
//    }
//    fclose(in);///?
//    cout<<cd;













    return 0;
}