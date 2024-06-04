// src/Block.cpp
#include "Block.h"

Block::Block(size_t index, const std::time_t &timestamp, const std::vector<Transaction> &transactions, uint64_t proof, const std::string &previous_hash)
    : index(index), timestamp(timestamp), transactions(transactions), proof(proof), previous_hash(previous_hash) {}

size_t Block::get_index() const {
    return index;
}

std::time_t Block::get_timestamp() const {
    return timestamp;
}

const std::vector<Transaction> &Block::get_transactions() const {
    return transactions;
}

uint64_t Block::get_proof() const {
    return proof;
}

std::string Block::get_previous_hash() const {
    return previous_hash;
}
