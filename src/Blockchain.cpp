#include "Blockchain.h"
#include <functional>
#include <iomanip>
#include <ncurses.h>
#include <random>
#include <sstream>

Blockchain::Blockchain() {
    createBlock(100, "1"); // genesis block: the block that starts the blockchain
}

void Blockchain::addTransaction(const std::string &sender, const std::string &recipient, double amount) {
    currentTransactions.emplace_back(sender, recipient, amount);
}

void Blockchain::createBlock(uint64_t proof, const std::string &previousHash) {
    std::vector<std::string> miners = {"minerA", "minerB", "minerC"};

    // randomly select a miner
    if (previousHash != "1") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, miners.size() - 1);
        std::string selectedMiner = miners[dis(gen)];

        // add a reward for the miner
        addTransaction("blockchain funds", selectedMiner, 0.5);
    }

    Block newBlock(chain.size(), std::time(0), currentTransactions, proof, previousHash);
    currentTransactions.clear();
    chain.push_back(newBlock);
}

const std::vector<Block> &Blockchain::getChain() const {
    return chain;
}

std::unordered_map<std::string, double> Blockchain::calculateBalances() const {
    std::unordered_map<std::string, double> balances;
    for (const auto &block : chain) {
        for (const auto &transaction : block.getTransactions()) {
            balances[transaction.getSender()] -= transaction.getAmount();
            balances[transaction.getRecipient()] += transaction.getAmount();
        }
    }
    return balances;
}

const std::vector<Transaction> &Blockchain::getCurrentTransactions() const {
    return currentTransactions;
}

size_t Blockchain::getLastBlockIndex() const {
    return chain.size() - 1;
}

std::string Blockchain::getLastBlockHash() const {
    return hash(chain.back());
}

uint64_t Blockchain::proofOfWork(uint64_t lastProof) const {
    uint64_t proof = 0;
    int step = 100;
    while (!isValidProof(lastProof, proof)) {
        ++proof;
    }
    return proof;
}

uint64_t Blockchain::getLastProof() const {
    return chain.back().getProof();
}

bool Blockchain::isValidProof(uint64_t lastProof, uint64_t proof) const {
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
    ss << block.getIndex() << block.getTimestamp() << block.getProof() << block.getPreviousHash();
    for (const auto &tx : block.getTransactions()) {
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
