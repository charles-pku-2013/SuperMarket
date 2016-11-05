#ifndef _PRODUCT_SET_H_
#define _PRODUCT_SET_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include "product.h"


#if 0
typedef boost::multi_index::multi_index_container <
    Product::pointer,
    boost::multi_index::indexed_by <
        // sort by Product::operator <      get<0>
        boost::multi_index::ordered_unique< boost::multi_index::identity<Product> >,
        // sort by less<string> on name     get<1>
        boost::multi_index::ordered_non_unique< boost::multi_index::const_mem_fun<Product, const std::string&, &Product::name> >,
        // sort by less<int> on type       get<2>
        boost::multi_index::ordered_non_unique< boost::multi_index::const_mem_fun<Product, const std::string&, &Product::type> >,
        // sort by less<int> on type       get<3>
        boost::multi_index::ordered_non_unique< boost::multi_index::const_mem_fun<Product, float, &Product::price> >
    > 
> ProductSet;
#endif


#define MIDX boost::multi_index
typedef MIDX::multi_index_container <
    Product::pointer,
    MIDX::indexed_by <
        // sort by Product::operator <      get<0>
        MIDX::ordered_unique< MIDX::identity<Product> >,
        // sort name     get<1>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, const std::string&, &Product::name> >,
        // sort on type       get<2>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, const std::string&, &Product::type> >,
        // sort on price       get<3>
        MIDX::ordered_non_unique< MIDX::const_mem_fun<Product, float, &Product::price> >
    > 
> ProductSet;
#undef MIDX


#endif

