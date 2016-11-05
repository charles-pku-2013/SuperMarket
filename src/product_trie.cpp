#include <cctype>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include "product_trie.h"


std::pair<typename ProductTrie::Node::pointer, bool>
ProductTrie::addProduct(const Product::pointer &p)
{
    using namespace std;

    auto pRoot = root();
    auto pElemType = std::make_shared<ProductElem>(p->type());
    auto ret = addNode(pRoot, pElemType);
    auto pCurNode = ret.first;

    istringstream ss(p->name());
    string word;
    while (ss >> word) {
        boost::trim_if(word, [](char ch){
            return !isalpha(ch) && !isdigit(ch);
        });
        if (word.empty()) continue;
        auto pElem = std::make_shared<ProductElem>(word);
        auto ret = addNode(pCurNode, pElem);
        pCurNode = ret.first;
    } // while

    pCurNode->data().pProduct = p;

    return ret;
}

