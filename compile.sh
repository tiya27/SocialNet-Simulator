# for Linux/Mac OS
#Social Network Project - COL106 Assignment

echo "Compiling Social Network project..."

g++ -std=c++17 -Wall -O2 main.cpp -o main

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
else
    echo "Compilation successful. Run ./main to start."
fi
