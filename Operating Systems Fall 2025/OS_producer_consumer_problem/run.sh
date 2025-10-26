#!/bin/bash

show_help() {
    echo "Usage: $0 [run|clean|help]"
    echo
    echo "Options:"
    echo "  help      Display this help message"
    echo "  run       Build and launch producer & consumer"
    echo "  clean     Terminate producers/consumers and remove shared buffer"
}

if [ $# -ne 1 ]; then
    show_help
    exit
fi

mode=$1

if [ "$mode" = "run" ]; then
    echo "[*] Starting Compilation of Producer and Consumer..."
    g++ producer.cpp sharedbuff.hpp -pthread -lrt -o producer && \
    g++ consumer.cpp sharedbuff.hpp -pthread -lrt -o consumer && \
    echo "[*] Executing Producer and Consumer..." && (
        (./producer &)
        (./consumer &)
    )
elif [ "$mode" = "clean" ]; then
    # kill process(s) by name
    killall producer
    killall consumer

    # remove the shared buffer from disk
    rm -f /dev/shm/shared_buffer
else
    show_help
fi
