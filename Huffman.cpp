//
// Created by 馨 on 2018/4/28.
//

#include "Huffman.h"
#include <iostream>
using namespace std;
huffmanTree HuffmanTree(){

}

//print to test
void TesthufTreeN(int root, huffmanTree ht){
    cout<<ht[root].weight<<" ";
    if(ht[root].lchild!=0){///wrong!!! ht[i].lchild 而不是ht->lchild
       TesthufTreeN(ht[root].lchild,ht);
    }
    if(ht[root].rchild!=0){
        TesthufTreeN(ht[root].rchild,ht);
    }
}

//void TestHufCode(int root, huffmanTree ht, huffmanCode hc){
//    if(ht[root].lchild==0&&ht[root].rchild==0){
//
//    }
//}

///由于哈夫曼树中没有度为1得结点. 只有度为0和度为2得结点. 则一棵有n个叶子结点得哈夫曼树共有2n-1个结点，所以设置一共2n个结点
huffmanTree InitHt(huffmanTree ht, int * weight){
    //ht[0]闲置不用
    ht[0].weight=-1;///=256?
    ht[0].lchild=0;
    ht[0].rchild=0;
    ht[0].parent=0;

    for(int i=1; i<=256*2-1; i++){
        if(i<=256){
            ht[i].weight = weight[i-1];
            //cout<<ht[i].weight<<endl;
        }
        else
            ht[i].weight=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
        ht[i].parent=0;
    }
    return ht;

}

huffmanTree CreateHuffmanTree(huffmanTree ht,int* weight){
    int m=256*2-1,n=256,i;
    int s1,s2;
    //0号单元弃用
    ht=InitHt(ht,weight);///? &ht ?
    for(i=n+1; i<=m; i++){
        Select(ht,i-1,&s1,&s2);
        ht[s1].parent=ht[s2].parent=i;
        ht[i].lchild=s1;
        ht[i].rchild=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;
    }

    return ht;

}

huffmanTree TestSelect(huffmanTree testHT,int * testWEI){
    int s1,s2;
    for(int i=0; i<9; i++){
        if(i<5)
            testHT[i].weight=testWEI[i];
        else
            testHT[i].weight=0;
        testHT[i].parent=0;
        testHT[i].lchild=0;
        testHT[i].rchild=0;
    }
    for(int i=5; i<9; i++){
        Select(testHT,i-1, &s1,&s2);
        testHT[s1].parent=testHT[s2].parent=i;
        testHT[i].lchild=s1;
        testHT[i].rchild=s2;
        testHT[i].weight=testHT[s1].weight+testHT[s2].weight;
    }
    return testHT;

}

//返回较小的两个数
void Select(huffmanTree ht, int end, int *order1, int *order2){
//    int minValue = 0x7FFFFFFF;
//    int min = 0;
//    for(int i=1; i<nSize; i++){
//        if(ht[i].parent==0 && ht[i].weight<min){
//            minValue=ht[i].weight; ///???why minValue is not permitted to be changed???
//            min=i;
//        }
//    }
//    return min;
//    int i,count;
//    int m,n,tmp;
//    //先选出两个parent为0的点
//    for(i=1,count=1; i<=end; i++){
//        if(ht[i].parent==0){
//            if(count==1)
//                m=i;
//            if(count==2)
//                n=i;
//            count++;
//        }
//        if(count>2)
//            break;
//    }
//
//    if(ht[m].weight>ht[n].weight){
//        tmp=n;n=m;m=tmp;
//    }
//
//    i=(m>n? m:n)+1;
//
//    while(i<=end){
//        if(ht[i].parent==0&&ht[i].weight!=0){///加了&&ht[i].weight!=0
//            if(ht[i].weight<ht[m].weight){
//                n=m;
//                m=i;
//            }
//            else{
//                if(ht[i].weight>=ht[m].weight&&ht[i].weight<ht[n].weight)
//                    n=i;
//            }
//        }
//        i++;
//    }
//    *order1=ht[m].weight<=ht[n].weight? m:n;
//    *order2=ht[m].weight>=ht[n].weight? m:n;


    int min2=0x7FFFFFFF,min=0x7FFFFFFF;
    for(int i=1; i<=end; i++){
        if(ht[i].parent==0&&ht[i].weight<min){
            min=i;
        }
    }
    for(int i=1; i<=end; i++){
        if(i!=min&&ht[i].parent==0&&ht[i].weight<min2){
            min2=i;
        }
    }
    *order1 = min;
    *order2 = min2;
}

huffmanCode HuffmanCode(huffmanTree ht,huffmanCode hc) {//逆序
    int i=0, chi=0, par=0;
    //string s = "";
    for (i = 1; i <=256 ; i++) {///1~256
        //s = "";
        chi = i;
        int count=0;
        while (ht[chi].parent != 0) {
            par = ht[chi].parent;
            if (chi == ht[par].lchild){
                //s = s + "0";
                hc[i].code[count]='0';
                count++;
            }
            else{
                //s = s + "1";
                hc[i].code[count]='1';
                count++;
            }
            chi = ht[chi].parent;
        }
        hc[i].length=count;
    }
    return hc;
}




//127 string Huff_Decode(Node huffTree[], int n,string s)
//128 {
//129     cout << "解码后为：";
//130     string temp = "",str="";//保存解码后的字符串
//131     for (int i = 0; i < s.size(); i++)
//132     {
//133         temp = temp + s[i];
//134         for (int j = 0; j < n; j++)
//135         {
//136             if (temp == huffTree[j].code)
//137             {
//138                 str=str+ huffTree[j].ch;
//139                 temp = "";
//140                 break;
//141             }
//142             else if (i == s.size()-1&&j==n-1&&temp!="")//全部遍历后没有
//143             {
//144                 str= "解码错误！";
//145             }
//146         }
//147     }
//148     return str;
//149 }
















