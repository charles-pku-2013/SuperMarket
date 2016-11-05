#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>
#include "common.hpp"
#include "product.h"


Product::Product(const std::string &csv) : Product()
{
    using namespace std;

    DLOG(INFO) << "Product constructor csv = " << csv;

    char *pCsv = const_cast<char*>(csv.c_str());
    char *saveEnd1 = NULL;
    char *pField = NULL;

    // read id
    pField = strtok_r(pCsv, ",", &saveEnd1);
    if (!pField) 
        THROW_RUNTIME_ERROR("Cannot read id field!");
    m_nID = boost::lexical_cast<IdType>(pField);
    if (m_nID < 0)
        THROW_RUNTIME_ERROR("Invalid ID value!");
    // read type
    pField = strtok_r(NULL, ",", &saveEnd1);
    if (!pField) 
        THROW_RUNTIME_ERROR("Cannot read type field!");
    m_strType = pField;
    // read name
    pField = strtok_r(NULL, "\"", &saveEnd1);
    if (!pField) 
        THROW_RUNTIME_ERROR("Cannot read name field!");
    m_strName = pField;
    // read price
    pField = strtok_r(NULL, ",", &saveEnd1);
    if (!pField) 
        THROW_RUNTIME_ERROR("Cannot read price field!");
    m_fPrice = boost::lexical_cast<float>(pField);
    if (m_fPrice < 0.0)
        THROW_RUNTIME_ERROR("Invalid price value!");
    // read price unit
    // pField = strtok_r(NULL, ",", &saveEnd1);
    // m_ePriceUnit = s_mapPriceUnit[pField];
}

