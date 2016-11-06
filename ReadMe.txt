This program is a implementation of memory based database for supermarket products.
It uses boost multi index container for quick lookup for items by id, name, and price.
Comapred with traditional set and map structure that can only lookup by one porperty of
the objects for example by id, the multi index container can lookup by multiple properties
like id, name and price with the same O(logN) time complexity.

    And also it uses dictionary trie based on products' type and name property to compare 
the similarities between two items which is very useful in recommendation algorithms.


Language: C++ with c++11 standard

OS:
    Tested on Ubuntu 14.04
    Windows and MacOS and other Linux distributions should be OK but not tested.

Dependancy:
    Libraries: 
        boost 
        glog:   for logging
        gflags: for parsing program arguments
    To install these libraries on Ubuntu:
        sudo apt-get install libboost-dev
        sudo apt-get install libgflags-dev
        sudo apt-get install libgoogle-glog-dev
    And make sure the "/usr/local/lib" path is in your $LD_LIBRARY_PATH environment variable.

Compile: (On Ubuntu)
    cd into project directory and run:
        make
    That will generate "demo.bin" executable.

Usage:
    To start the program, run:
        ./demo.bin -data data/product.txt
    You can replace the data file path "data/product.txt" with your actual data file path.
    
    To start the program with log to the console, run:
        GLOG_logtostderr=1 ./demo.bin -data $your_data_file_location

    When the program started, it starts a mini shell, you can run various command in this shell.

Examples:
    Query products name starts with "Huggies", input:
        query name Huggies
    Query products name between "H*" and "J*", input:
        query name H J
    Query products with type "Spices"
        query type Spices
    Query products with the price of 29.99
        query price 29.99
    Query products whose price between 20 and 30
        query price 20 30

    Print the whole trie structure, input:
        print_trie
    Output the readable trie to a file, input:
        print_trie $output_filename
    To compare two items, input:
        similar $id1 $id2
        (Replace $id with read id)

Enjoy!

