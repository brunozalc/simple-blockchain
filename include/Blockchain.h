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
    std::vector<Transaction> current_transactions;
    size_t get_last_block_index() const;
    std::string hash(const Block &block) const;
    int number_of_blocks;

public:
    Blockchain();
    void add_transaction(const std::string &sender, const std::string &recipient, double amount);
    void create_block(uint64_t proof, const std::string &previous_hash);
    const std::vector<Block> &get_chain() const;
    std::unordered_map<std::string, double> calculate_balances() const;
    const std::vector<Transaction> &get_current_transactions() const;
    std::string get_last_block_hash() const;
    uint64_t proof_of_work(uint64_t lastProof) const;
    uint64_t get_last_proof() const;
    bool is_valid_proof(uint64_t lastProof, uint64_t proof) const;
    int n_of_blocks() const;
};
