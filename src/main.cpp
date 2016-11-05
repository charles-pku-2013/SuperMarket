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

DEFINE_string(data, "", "data file name.");


// global vars
static ProductSet       g_ProductSet;


namespace Test {
using namespace std;

void test()
{
    ifstream ifs("data/PRODUCT_MST.csv");
    string line;
    getline(ifs, line);
    getline(ifs, line);
    auto p = std::make_shared<Product>(line);
    cout << *p << endl;
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
    } // while

    DLOG(INFO) << g_ProductSet.size();
}


int main(int argc, char **argv)
try {
    using namespace std;

    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    // Test::test();
    load_data(FLAGS_data);

    LOG(INFO) << argv[0] << " done!";
    return 0;    

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


