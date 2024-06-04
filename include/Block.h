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
    std::string previous_hash;

public:
    Block(size_t index, const std::time_t &timestamp, const std::vector<Transaction> &transactions, uint64_t proof, const std::string &previous_hash);

    size_t get_index() const;
    std::time_t get_timestamp() const;
    const std::vector<Transaction> &get_transactions() const;
    uint64_t get_proof() const;
    std::string get_previous_hash() const;
};
