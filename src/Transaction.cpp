// src/Transaction.cpp
#include "Transaction.h"

Transaction::Transaction(const std::string &sender, const std::string &recipient, double amount)
    : sender(sender), recipient(recipient), amount(amount) {}

std::string Transaction::getSender() const {
    return sender;
}

std::string Transaction::getRecipient() const {
    return recipient;
}

double Transaction::getAmount() const {
    return amount;
}
