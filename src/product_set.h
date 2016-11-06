#ifndef _PRODUCT_SET_H_
#define _PRODUCT_SET_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include "product.h"


#define MIDX boost::multi_index
typedef MIDX::multi_index_container <
    Product::pointer,
    MIDX::indexed_by <
        // sort by Product::operator <      get<0>
        MIDX::ordered_unique< MIDX::identity<Product> >,
        // sort by type     get<1>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, const std::string&, &Product::type> >,
        // sort by name       get<2>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, const std::string&, &Product::name> >,
        // sort on price       get<3>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, float, &Product::price> >
    > 
> ProductSet;
#undef MIDX


struct ProductCmpById {
    // compare an ID and an Product
    bool operator()(int x,const Product& p2) const
    { return x < p2.id(); }
    // compare an Product and an ID
    bool operator()(const Product& p1,int x) const
    { return p1.id() < x;}
};


#endif

