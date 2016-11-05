#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "common.hpp"
#include "trie.hpp"
#include "product.h"

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


int main(int argc, char **argv)
try {
    using namespace std;

    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    Test::test();

    LOG(INFO) << argv[0] << " done!";
    return 0;    

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


