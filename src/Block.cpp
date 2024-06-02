// src/Block.cpp
#include "Block.h"

Block::Block(size_t index, const std::time_t &timestamp, const std::vector<Transaction> &transactions, uint64_t proof, const std::string &previousHash)
    : index(index), timestamp(timestamp), transactions(transactions), proof(proof), previousHash(previousHash) {}

size_t Block::getIndex() const {
    return index;
}

std::time_t Block::getTimestamp() const {
    return timestamp;
}

const std::vector<Transaction> &Block::getTransactions() const {
    return transactions;
}

uint64_t Block::getProof() const {
    return proof;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}
