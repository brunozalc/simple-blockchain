#include "Blockchain.h"
#include <functional>
#include <iomanip>
#include <ncurses.h>
#include <random>
#include <sstream>

Blockchain::Blockchain() : number_of_blocks(0) {
    create_block(100, "1"); // genesis block: the block that starts the blockchain
}

int Blockchain::n_of_blocks() const {
    return number_of_blocks;
}

void Blockchain::add_transaction(const std::string &sender, const std::string &recipient, double amount) {
    current_transactions.emplace_back(sender, recipient, amount);
}

void Blockchain::create_block(uint64_t proof, const std::string &previous_hash) {
    std::vector<std::string> miners = {"minerA", "minerB", "minerC"};

    // randomly select a miner
    if (previous_hash != "1") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, miners.size() - 1);
        std::string selectedMiner = miners[dis(gen)];

        // add a reward for the miner
        add_transaction("blockchain funds", selectedMiner, 0.5);
    }

    Block newBlock(chain.size(), std::time(0), current_transactions, proof, previous_hash);
    current_transactions.clear();
    chain.push_back(newBlock);
    ++number_of_blocks;
}

const std::vector<Block> &Blockchain::get_chain() const {
    return chain;
}

std::unordered_map<std::string, double> Blockchain::calculate_balances() const {
    std::unordered_map<std::string, double> balances;
    for (const auto &block : chain) {
        for (const auto &transaction : block.get_transactions()) {
            balances[transaction.getSender()] -= transaction.getAmount();
            balances[transaction.getRecipient()] += transaction.getAmount();
        }
    }
    return balances;
}

const std::vector<Transaction> &Blockchain::get_current_transactions() const {
    return current_transactions;
}

size_t Blockchain::get_last_block_index() const {
    return chain.size() - 1;
}

std::string Blockchain::get_last_block_hash() const {
    return hash(chain.back());
}

uint64_t Blockchain::proof_of_work(uint64_t lastProof) const {
    uint64_t proof = 0;
    int step = 100;
    while (!is_valid_proof(lastProof, proof)) {
        ++proof;
    }
    return proof;
}

uint64_t Blockchain::get_last_proof() const {
    return chain.back().get_proof();
}

bool Blockchain::is_valid_proof(uint64_t lastProof, uint64_t proof) const {
    std::string guess = std::to_string(lastProof) + std::to_string(proof);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)guess.c_str(), guess.size(), hash);

    // convert the hash to a string of hex digits
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::string guessHash = ss.str();

    const size_t difficulty = 4;
    std::string prefix(difficulty, '0');
    return guessHash.substr(0, difficulty) == prefix;
}

std::string Blockchain::hash(const Block &block) const {
    std::stringstream ss;
    ss << block.get_index() << block.get_timestamp() << block.get_proof() << block.get_previous_hash();
    for (const auto &tx : block.get_transactions()) {
        ss << tx.getSender() << tx.getRecipient() << tx.getAmount();
    }
    std::string blockData = ss.str();

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)blockData.c_str(), blockData.size(), hash);

    // convert the hash to a string of hex digits
    std::stringstream hashStringStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hashStringStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return hashStringStream.str();
}
