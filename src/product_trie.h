#ifndef _PRODUCT_TRIE_H_
#define _PRODUCT_TRIE_H_

#include <iostream>
#include <vector>
#include "trie.hpp"
#include "product.h"

struct ProductElem {
    ProductElem(const std::string &_Alias) : alias(_Alias) {}

    bool operator<(const ProductElem &rhs) const
    { return alias < rhs.alias; }

    friend std::ostream& operator << (std::ostream &os, const ProductElem &e)
    {
        os << e.alias;
        if (e.pProduct)
            os << " " << *(e.pProduct);
        return os;
    }

    std::string      alias;
    Product::pointer pProduct;
};


class ProductTrie : public Trie<ProductElem> {
public:
    // struct NodeCmpByProductId {
        // bool operator()(const Node::pointer &lhs, const Node::pointer &rhs) const
        // { return lhs->data().pProduct->id() < rhs->data().pProduct->id(); }
    // };

public:
    std::pair<typename Node::pointer, bool>
    addProduct(const Product::pointer &p);
    Node::pointer getNodeById(Product::IdType id);

private:
    std::vector<Node::pointer>     m_vecLeafNodes;
};


#endif

