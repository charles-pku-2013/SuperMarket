#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "common.hpp"
#include "trie.hpp"
#include "product_set.h"
#include "product_trie.h"

DEFINE_string(data, "", "data file name.");


// global vars
static ProductSet       g_ProductSet;
static ProductTrie      g_ProductTrie;


namespace Test {
using namespace std;

void test_query_by_type()
{
    auto& idx = g_ProductSet.get<1>();
    auto i0 = idx.lower_bound("Spices");
    auto i1 = idx.upper_bound("Spices");
    for (; i0 != i1; ++i0)
        cout << **i0 << endl;
}

void test_query_by_price()
{
    auto& idx = g_ProductSet.get<3>();
    auto beg = idx.lower_bound(15);
    auto end = idx.lower_bound(20);
    for (; beg != end; ++beg)
        cout << **beg << endl;
}

void test_trie()
{
    g_ProductTrie.traverse(cout);
    cout << endl;
}

void test_trie_common_root()
{
    Product::IdType id1, id2;
    cin >> id1 >> id2;
    auto p1 = g_ProductTrie.getNodeById(id1);
    auto p2 = g_ProductTrie.getNodeById(id2);
    auto pComm = g_ProductTrie.commonRoot(p1, p2);
    if (pComm)
        cout << pComm->data() << endl;
    else
        cout << "No common root" << endl;
}

void test()
{
    auto& idx = g_ProductSet.get<2>();
    for (auto it = idx.begin(); it != idx.end(); ++it)
        cout << (*it)->name() << endl;
}

} // namespace Test


static
void load_data(const std::string &fname)
{
    using namespace std;

    if (fname.empty())
        THROW_RUNTIME_ERROR("You have to specify data file name by -data");

    ifstream ifs(fname, ios::in);
    string line;

    // skip the title
    getline(ifs, line);

    while (getline(ifs, line)) {
        auto pProduct = std::make_shared<Product>(line);
        g_ProductSet.emplace(pProduct);
        g_ProductTrie.addProduct(pProduct);
        // g_ProductTrie.traverse(cout);
        // getchar();
        // cout << *pProduct << endl;
    } // while

    // DLOG(INFO) << g_ProductSet.size();
}


static
void handle_query_id(Product::IdType id1, Product::IdType id2)
{
    using namespace std;

    auto i0 = g_ProductSet.lower_bound(id1, ProductCmpById());
    auto i1 = g_ProductSet.upper_bound(id2, ProductCmpById());

    if (i0 == i1) {
        cout << "No item found!" << endl;
        return;
    } // if

    for (; i0 != i1 && i0 != g_ProductSet.end(); ++i0)
        cout << **i0 << endl;
}


static
void handle_query_name(const std::string &s1, const std::string &s2)
{
    // TODO  name including spaces
    
    using namespace std;

    // DLOG(INFO) << "handle_query_name " << s1 << " " << s2;

    struct CmpStringPartial {
        bool operator()(const std::string &s1, const std::string &s2) const
        {
            std::size_t len1 = s1.length();
            std::size_t len2 = s2.length();
            std::size_t len = len1 < len2 ? len1 : len2;
            return strncmp(s1.c_str(), s2.c_str(), len) < 0;
        }
    };

    auto &idx = g_ProductSet.get<2>();
    auto i0 = idx.lower_bound(s1, CmpStringPartial());
    auto i1 = idx.upper_bound(s2, CmpStringPartial());

    if (i0 == i1) {
        cout << "No item found!" << endl;
        return;
    } // if

    for (; i0 != i1 && i0 != idx.end(); ++i0)
        cout << **i0 << endl;
}


static
void handle_query_price(float v1, float v2)
{
    using namespace std;

    // DLOG(INFO) << "handle_query_price() " << v1 << " " << v2;

    auto &idx = g_ProductSet.get<3>();
    auto i0 = idx.lower_bound(v1);
    auto i1 = idx.upper_bound(v2);

    if (i0 == i1) {
        cout << "No item found!" << endl;
        return;
    } // if

    for (; i0 != i1 && i0 != idx.end(); ++i0)
        cout << **i0 << endl;
}


static
void handle_query(std::stringstream &ss)
{
    using namespace std;

    string item, arg1, arg2;

    ss >> item >> arg1;
    if (ss.fail() || ss.bad()) {
        cout << "Invalid command!" << endl;
        return;
    } // if ss

    ss >> arg2;
    if (arg2.empty())
        arg2 = arg1;

    if ("id" == item) {
        Product::IdType id1 = 0, id2 = 0;
        try {
            id1 = boost::lexical_cast<Product::IdType>(arg1);
            id2 = boost::lexical_cast<Product::IdType>(arg2);
        } catch (std::bad_cast &err) {
            cout << "Invalid arg: " << err.what() << endl;
        } // try
        handle_query_id(id1, id2);
    } else if ("name" == item) {
        handle_query_name(arg1, arg2);
    } else if ("price" == item) {
        float v1 = 0.0, v2 = 0.0;
        try {
            v1 = boost::lexical_cast<float>(arg1);
            v2 = boost::lexical_cast<float>(arg2);
        } catch (std::bad_cast &err) {
            cout << "Invalid arg: " << err.what() << endl;
        } // try
        handle_query_price(v1, v2);
    } else {
        cout << "Invalid query item!" << endl;
    } // if
}


static
void handle_similar(std::stringstream &ss)
{
    
}


static
void handle_cmd()
{
    using namespace std;
    string line, cmd;

    while (true) {
        cout << "\nSuperMarket shell: " << flush;
        if (!getline(cin, line))
            break;

        boost::trim(line);
        if (line.empty())
            continue;

        stringstream ss(line);
        ss >> cmd;

        if (ss.fail() || ss.bad()) {
            cout << "Invalid command!" << endl;
            return;
        } // if ss

        if ("query" == cmd) {
            handle_query(ss);
        } else if ("similar" == cmd) {
            handle_similar(ss);
        } else if ("quit" == cmd) {
            return;
        } else {
            cout << "Invalid command!" << endl;
        } // if
    } // while
}


int main(int argc, char **argv)
try {
    using namespace std;

    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    load_data(FLAGS_data);

    // Test::test_query_by_type();
    // Test::test_query_by_price();
    // Test::test();
    // Test::test_trie();
    // Test::test_trie_common_root();
    
    handle_cmd();

    // LOG(INFO) << argv[0] << " done!";
    return 0;    

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


