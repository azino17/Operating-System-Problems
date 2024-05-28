#!/bin/bash

# Create named pipes for communication between reader and writer processes
mkfifo data_fifo
mkfifo read_signal_fifo

# Writer process
writer() {
    while true; do
        echo "Writing data..."
        echo "Data written" > data_fifo
        sleep 1
    done
}

# Reader process
reader() {
    while true; do
        if read line < data_fifo; then
            echo "Reading data: $line"
            echo "Data read" > read_signal_fifo
        fi
    done
}

# Main program
writer &
writer_pid=$!

reader &
reader_pid=$!

# Cleanup function to remove FIFOs when script exits
cleanup() {
    kill $writer_pid $reader_pid
    rm -f data_fifo read_signal_fifo
}

# Trap cleanup function on script exit
trap cleanup EXIT

# Wait for child processes to finish
Wait
