#!/bin/bash

# small wrapper to compile and run the Banker's demo
show_help() {
    echo "Usage: $0 [compile|run_all|help]"
    echo
    echo "Commands:"
    echo "  help          Display this help text"
    echo "  compile       Build the Bankers binary"
    echo "  run_all       Build and run Bankers with data1-3.txt"
    echo
    echo "Example:"
    echo "  ./bankers data1.txt"
}

if [ $# -ne 1 ]; then
    show_help
    exit
fi

mode=$1

if [ "$mode" = "compile" ]; then
    echo "-Compiling Bankers program..."
    g++ main.cpp bankers.cpp -o bankers -Wall
elif [ "$mode" = "run_all" ]; then
    echo "-Compiling Bankers program..."
    g++ main.cpp bankers.cpp -o bankers -Wall && (
        echo "-Running Bankers with data1-3.txt files..."
        echo "============================================"
        ./bankers ./data1.txt; echo
        ./bankers ./data2.txt; echo
        ./bankers ./data3.txt; echo
    )
else
    show_help
fi