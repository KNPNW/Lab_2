#include "bitree.h"
#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

template <class K, class V> BiTree<K, V>::BiTree()
{
    root = NULL;
    size = 0;
}

template <class K, class V> BiTree<K, V>::~BiTree(){
    size = 0;
    if (root != NULL)
        delAll(root);
}

template <class K, class V>  void BiTree<K, V>::push(const K& key, const V& value){
    if (root == NULL){
        root = new tree;
        root->key = key;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        size++;
    }else{
        push(key, value, root);
    }
}

template <class K, class V>  void BiTree<K, V>::push(const K& key, const V& value, tree* leaf){
    if (key < leaf->key){
        if (leaf->left == NULL){
            leaf->left = new tree;
            leaf->left->key = key;
            leaf->left->value = value;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
            size++;
        }else{
            push(key, value, leaf->left);
        }
    }else if (key >= leaf->key){
        if (leaf->right == NULL){
            leaf->right = new tree;
            leaf->right->key = key;
            leaf->right->value = value;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
            size++;
        }else{
            push(key, value, leaf->right);
        }
    }
}

template <class K, class V> void BiTree<K, V>::delAll(){
    size = 0;
    if (root != NULL)
        delAll(root);
}

template <class K, class V> void BiTree<K, V>::delAll(tree* leaf){
    if (leaf != NULL){
        delAll(leaf->left);
        delAll(leaf->right);
        delete leaf;
    }
}

template <class K, class V> void BiTree<K, V>::fromFile(const string& nameFile){
        ifstream file(nameFile);
        string value, data, prom;
        int year, month, day;
        if(!file){
            cout << "File didn't find" << endl;
        }else{
            if(size != 0)
                this->delAll();
            while(!file.eof()){
                getline(file, data);
                getline(file, value);
                day = stoi(data.substr(0,1));
                month = stoi(data.substr(3,4));
                year = stoi(data.substr(6,7));
                Data data(day, month, year);
                this->push(data, value);
            }
        }
}
