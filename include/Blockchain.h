// include/Blockchain.h
#pragma once
#include "Block.h"
#include "Transaction.h"
#include <openssl/sha.h>
#include <unordered_map>
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> currentTransactions;
    size_t getLastBlockIndex() const;
    std::string hash(const Block &block) const;

public:
    Blockchain();
    void addTransaction(const std::string &sender, const std::string &recipient, double amount);
    void createBlock(uint64_t proof, const std::string &previousHash);
    const std::vector<Block> &getChain() const;
    std::unordered_map<std::string, double> calculateBalances() const;
    const std::vector<Transaction> &getCurrentTransactions() const;
    std::string getLastBlockHash() const;
    uint64_t proofOfWork(uint64_t lastProof) const;
    uint64_t getLastProof() const;
    bool isValidProof(uint64_t lastProof, uint64_t proof) const;
};
