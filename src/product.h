#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>
#include <string>
#include <memory>


class Product {
public:
    typedef std::shared_ptr<Product>    pointer;
    typedef uint64_t                    IdType;

public:
    static void init_price_unit();

    friend std::ostream& operator << (std::ostream &os, const Product &p)
    {
        os << "id:" << p.id() << " name:\"" << p.name() << "\""
            << " type:" << p.type() << " price:" << p.price();
        return os;
    }

    Product() : m_nID(0), m_fPrice(0.0) {};
    Product(const std::string &csv);

    IdType id() const { return m_nID; }
    const std::string& type() const { return m_strType; }
    const std::string& name() const { return m_strName; }
    float price() const { return m_fPrice; }

    void setId(IdType id) { m_nID = id; }
    void setType(const std::string &type) { m_strType = type; }
    void setName(const std::string &name) { m_strName = name; }
    void setPrice(float price) { m_fPrice = price; }

    bool operator<(const Product &rhs) const
    { return id() < rhs.id(); }

private:
    IdType          m_nID;
    std::string     m_strType;
    std::string     m_strName;
    float           m_fPrice;
};


#endif

