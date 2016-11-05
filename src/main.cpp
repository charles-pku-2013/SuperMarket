#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
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


int main(int argc, char **argv)
try {
    using namespace std;

    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    load_data(FLAGS_data);

    // Test::test_query_by_type();
    // Test::test_query_by_price();
    // Test::test();
    Test::test_trie();

    // LOG(INFO) << argv[0] << " done!";
    return 0;    

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


