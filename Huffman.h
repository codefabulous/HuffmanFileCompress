//
// Created by 馨 on 2018/4/28.
//实现Huffman算法相关: 结点->哈夫曼树
//

#ifndef HUFFMANCOMPRESSCPRO_HUFFMAN_H
#define HUFFMANCOMPRESSCPRO_HUFFMAN_H

#include <stdio.h>
#include <string>

struct HTNode{
    int weight;//weight
    int parent;//parent node
    int lchild;//left child
    int rchild;//right child
};
typedef HTNode* huffmanTree;

struct HTCode{
    char code[256];
    int length;
};
typedef HTCode* huffmanCode;

/*
 * to create Huffman tree
 */
huffmanTree CreateHuffmanTree(huffmanTree ht,int* weight);

huffmanTree InitHt(huffmanTree ht,int* weight);

huffmanTree TestSelect(huffmanTree testHT,int * testWEI);

/*
 * to create Huffman code
 */
huffmanCode HuffmanCode(huffmanTree ht,huffmanCode hc);


/*
 * 在ht中选出end之前的结点中较小的两个数
 */
void Select(huffmanTree ht, int end, int *order1, int *order2);


/*
 * 先序遍历哈夫曼树，输出每个节点的信息
 */
void TesthufTreeN(int root, huffmanTree ht);

/*
 * 测试输出每个叶子节点的编码
 */
//void TestHufCode(int root, huffmanTree ht, huffmanCode hc);

/*
 * 测试输出每个叶子节点的编码
 */
//void TestHufCode(int root, HuffmanTree ht, )

class Huffman {

};


#endif //HUFFMANCOMPRESSCPRO_HUFFMAN_H
