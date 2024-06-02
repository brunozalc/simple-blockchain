// include/Transaction.h
#pragma once
#include <string>

class Transaction {
public:
    double amount;
    std::string sender;
    std::string recipient;

    Transaction(const std::string &sender, const std::string &recipient, double amount);

    std::string getSender() const;
    std::string getRecipient() const;
    double getAmount() const;
};
