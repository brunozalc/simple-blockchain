# Simple Blockchain in C++

This project implements a simple blockchain with a TUI made using ncurses. Heavily inspired by [this](https://github.com/benWindsorCode/rustBlockchain) simple blockchain implementation in Rust.

## Menu

- **New Transaction:** Create a new transaction between wallets.
- **Pending Transactions:** View transactions that are pending and not yet included in a block.
- **Show Balances:** Display the balances of different wallets on the blockchain.
- **Create Block:** Mine a new block, which includes the current transactions and adds them to the blockchain, crediting some tokens to a randomly generated miner.
- **View Chain:** View the entire blockchain, including all blocks and their transactions.
- **Quit:** Exit the program (or press `ctrl + C`).

## How to Run

### Prerequisites

- **C++ Compiler:** Ensure you have a C++ compiler installed, such as g++, gcc or clang.

- **CMake:** This project uses CMake to manage the build process.

- **ncurses:** The ncurses library should be installed. On Ubuntu or Debian-based systems, you can install it using:

    ```bash
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```

- For Arch-based systems, you can install it using:

    ```bash
    sudo pacman -S ncurses
    ```

### Build and Run the Project

Clone the Repository:

```bash
git clone https://github.com/brunozalc/simple-blockchain
cd simple-blockchain
```

Create a Build directory and run CMake:

```bash
mkdir build
cd build
cmake ..
```

Build the project:

```bash
cmake --build .
```

Run the executable:

```bash
    ./simple-blockchain
```

### Project Structure

```lua
/path/to/project
|-- include/
|   |-- Blockchain.h
|   |-- Block.h
|   |-- Transaction.h
|-- src/
|   |-- Blockchain.cpp
|   |-- Block.cpp
|   |-- Transaction.cpp
|-- main.cpp
|-- CMakeLists.txt
|-- README.md
|-- build/
```
