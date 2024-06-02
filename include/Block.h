#pragma once
#include "Transaction.h"
#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

class Block {
private:
    size_t index;
    std::time_t timestamp;
    std::vector<Transaction> transactions;
    uint64_t proof;
    std::string previousHash;

public:
    Block(size_t index, const std::time_t &timestamp, const std::vector<Transaction> &transactions, uint64_t proof, const std::string &previousHash);

    size_t getIndex() const;
    std::time_t getTimestamp() const;
    const std::vector<Transaction> &getTransactions() const;
    uint64_t getProof() const;
    std::string getPreviousHash() const;
};
