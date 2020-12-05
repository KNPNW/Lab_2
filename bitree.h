#ifndef BITREE_H
#define BITREE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "stdlib.h"
#include "data.h"
using namespace std;

template <class K, class V> class BiTree {
public:

    struct tree{
        K key;
        V value;
        tree* left;
        tree* right;
    };

    BiTree();//+
    BiTree(const BiTree& tree);//+
    ~ BiTree();//+

    void push(K& key, const V& value);//+
    void del(K& key);
    void delAll();//+
    bool isKey(K& key);//+
    bool operator==(const BiTree& tree);//+
    V& operator[](K& key);//+

    void toFile(const string& nameFile);//+
    void fromFile(const string& nameFile);//+
    vector<string> fromMinToMax();//+

    vector<K> getKeys() const;//+
    vector<V> getValues() const;//+
    int getSize() const {return size;}//+

private:
    tree* root;
    int size;

    void push(K& key, const V& value, tree* leaf);
    void delAll(tree** leaf);
    void del(tree* leaf, vector<K>& keys, vector<V>& values);
    bool isKey(K& key, tree* leaf);
    void getKeys(tree* leaf, vector<K>& keys) const;
    void getValues(tree* leaf, vector<V>& values) const;
    V& helpOperator(K& key, tree* leaf) const;
    void toFile(ofstream& file, tree* leaf, int& sizeHelp);
    void copyObj(tree* leaf);
    void copyValue(tree* leaf, vector<V>& result);
    void comparison(tree* leafF, tree* leafS, vector<int>& result);
};

template <class K, class V> BiTree<K, V>::BiTree()
{
    root = NULL;
    size = 0;
}
template <class K, class V> BiTree<K, V>::BiTree(const BiTree& tree){
    size = 0;
    if(tree.root != NULL){
        this->push(tree.root->key, tree.root->value);
        copyObj(tree.root->left);
        copyObj(tree.root->right);
    }else
        root = NULL;
}

template <class K, class V> void BiTree<K, V>::copyObj(tree* leaf){
    if(leaf != NULL){
        this->push(leaf->key, leaf->value);
        copyObj(leaf->left);
        copyObj(leaf->right);
    }
}

template <class K, class V> void BiTree<K, V>::copyValue(tree* leaf, vector<V>& result){
    if(leaf != NULL){
        copyValue(leaf->left, result);
        result.push_back(leaf->value);
        copyValue(leaf->right, result);
    }
}

template <class K, class V> BiTree<K, V>::~BiTree(){
    size = 0;
    if (root != NULL)
        delAll(&root);
}

template <class K, class V>  void BiTree<K, V>::push(K& key, const V& value){
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

template <class K, class V>  void BiTree<K, V>::push(K& key, const V& value, tree* leaf){
    if (key<leaf->key){
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
    }else if (key>leaf->key){
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
    }else if(key==leaf->key)
        leaf->value = value;
}

template <class K, class V> void BiTree<K, V>::delAll(){
    size = 0;
    if (root != NULL)
        delAll(&root);
}

template <class K, class V> void BiTree<K, V>::delAll(tree** leaf){
    if (*leaf != NULL){
        delAll(&(*leaf)->left);
        delAll(&(*leaf)->right);
        delete *leaf;
        *leaf = NULL;
    }
}

template <class K, class V> void BiTree<K, V>::del(K& key){
    vector<K> keys;
    vector<V> values;
    if((isKey(key, root)) == true){
        if (root != NULL){
            keys.push_back(root->key);
            values.push_back(root->value);
            del(root->left, keys, values);
            del(root->right, keys, values);
        }
        delAll(&root);
        for(int i = 0; i < int(keys.size()); i++){
            if(keys[i]!=key){
                this->push(keys[i], values[i]);
            }
        }
    }else
        throw out_of_range("Key error");
}

template <class K, class V> void BiTree<K, V>::del(tree* leaf, vector<K>& keys, vector<V>& values){
    if (leaf != NULL){
        keys.push_back(leaf->key);
        values.push_back(leaf->value);
        del(leaf->left, keys, values);
        del(leaf->right, keys, values);
    }
}

template <class K, class V> vector<K> BiTree<K, V>::getKeys() const{
    vector<K> keys;
    if (root != NULL){
        getKeys(root->left, keys);
        keys.push_back(root->key);
        getKeys(root->right, keys);
    }
    return keys;
}

template <class K, class V> void BiTree<K, V>::getKeys(tree*leaf, vector<K>& keys) const{
    if (leaf != NULL){
        getKeys(leaf->left, keys);
        keys.push_back(leaf->key);
        getKeys(leaf->right, keys);
    }
}

template <class K, class V> vector<V> BiTree<K, V>::getValues() const{
    vector<V> values;
    if (root != NULL){
        getValues(root->left, values);
        values.push_back(root->value);
        getValues(root->right, values);
    }
    return values;
}

template <class K, class V> void BiTree<K, V>::getValues(tree*leaf, vector<V>& values) const{
    if (leaf != NULL){
        getValues(leaf->left, values);
        values.push_back(leaf->value);
        getValues(leaf->right, values);
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
                day = stoi(data.substr(0,2));
                month = stoi(data.substr(3,5));
                year = stoi(data.substr(6,8));
                Data data(day, month, year);
                this->push(data, value);
            }
        }
        file.close();
}

template <class K, class V> void BiTree<K, V>::toFile(const string& nameFile){
  ofstream file(nameFile);
  int sizeHelp = 0;
  if (root != NULL){
      sizeHelp++;
      int day = root->key.getDay();
      int month = root->key.getMonth();
      int year = root->key.getYear();
      if (day < 10)
          file << "0" << day << ".";
      else
          file << day << ".";
      if (month < 10)
          file << "0" << month << ".";
      else
          file << month << ".";
      if(year < 10)
          file << "0" << year << endl;
      else
          file << year << endl;
      if (sizeHelp == size)
          file << root->value;
      else{
          file << root->value << endl;
          toFile(file, root->left, sizeHelp);
          toFile(file, root->right, sizeHelp);
      }
  }
  file.close();
}

template <class K, class V> void BiTree<K, V>::toFile(ofstream& file, tree* leaf, int& sizeHelp){
    if (leaf != NULL){
        sizeHelp++;
        int day = leaf->key.getDay();
        int month = leaf->key.getMonth();
        int year = leaf->key.getYear();
        if (day < 10)
            file << "0" << day << ".";
        else
            file << day << ".";
        if (month < 10)
            file << "0" << month << ".";
        else
            file << month << ".";
        if(year < 10)
            file << "0" << year << endl;
        else
            file << year << endl;
        if (sizeHelp == size)
            file << leaf->value;
        else{
            file << leaf->value << endl;
            toFile(file, leaf->left, sizeHelp);
            toFile(file, leaf->right, sizeHelp);
        }
    }
}

template <class K, class V> vector<string> BiTree<K, V>::fromMinToMax(){
    vector <V> result;
    if(root != NULL){
        copyValue(root->left, result);
        result.push_back(root->value);
        copyValue(root->right, result);
    }
    return result;
}


template <class K, class V> bool BiTree<K, V>::isKey(K& key){
    return isKey(key, root);
}

template <class K, class V> bool BiTree<K, V>::isKey(K& key, tree* leaf){
    if(leaf != NULL){
        if (key==leaf->key)
            return true;
        if (key<leaf->key)
            return isKey(key, leaf->left);
        else if (key>leaf->key)
            return isKey(key, leaf->right);
    }else
        return false;
}

template <class K, class V> V& BiTree<K, V>::operator[](K& key){
    if((isKey(key, root))==true){
        return helpOperator(key, root);
    }else
        throw out_of_range("Key error");
}

template <class K, class V> bool BiTree<K, V>::operator==(const BiTree& tree){
    vector<int> result;
    if(size == tree.size){
        if(root == NULL && tree.root == NULL)
            return true;
        else if(root != NULL && tree.root != NULL){
            if(root->key==tree.root->key && root->value==tree.root->value){
                result.push_back(1);
                comparison(root->left, tree.root->left, result);
                comparison(root->right, tree.root->right, result);
            }
        }else
            return false;
    }else
        return false;
    for(int i = 0; i < int(result.size()); i++)
        if(result[i] == 0)
            return false;
    return true;
}

template<class K, class V> void  BiTree<K, V>::comparison(tree* leafF, tree* leafS, vector<int>& result){
    if(leafF == NULL && leafS == NULL)
        result.push_back(1);
    else if(leafF != NULL && leafS != NULL){
        if(leafF->key==leafS->key && leafF->value==leafS->value)
            result.push_back(1);
        else
            result.push_back(0);
        comparison(leafF->left, leafS->left, result);
        comparison(leafF->right, leafS->right, result);
    }
    else
        result.push_back(0);
}

template <class K, class V> V& BiTree<K, V>::helpOperator(K& key, tree* leaf) const{
    if (key==leaf->key)
        return leaf->value;
    if (key<leaf->key)
        return helpOperator(key, leaf->left);
    else if (key>leaf->key)
        return helpOperator(key, leaf->right);
}

#endif // BITREE_H
