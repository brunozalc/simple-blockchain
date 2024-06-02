#include "Blockchain.h"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <vector>

void printMenu(WINDOW *menu_win, int highlight, std::vector<std::string> choices);
void newTransaction(Blockchain &chain);
void viewCurrentTransactions(Blockchain &chain);
void showBalances(Blockchain &chain);
void createBlock(Blockchain &chain);
void viewChain(Blockchain &chain);

int main() {
    Blockchain chain;
    const int width = 30;
    const int height = 10;
    int startx = (80 - width) / 2;
    int starty = (24 - height) / 2;
    int highlight = 1;
    int choice = 0;
    int c;
    bool show_menu = false;
    std::vector<std::string> choices = {"New Transaction", "Pending Transactions", "Show Balances", "Create Block", "View Chain", "Quit"};

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mvprintw(0, 0, "Press ESC to access menu");
    refresh();

    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);

    while (1) {
        if (show_menu) {
            printMenu(menu_win, highlight, choices);
        } else {
            mvprintw(0, 0, "Press ESC to access menu");
            refresh();
        }

        c = wgetch(stdscr);
        if (c == 27) { // ESC key
            show_menu = !show_menu;
            if (!show_menu) {
                werase(menu_win);
                wrefresh(menu_win);
            }
        }

        if (show_menu) {
            switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = choices.size();
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == choices.size())
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10: // Enter
                choice = highlight;
                show_menu = false;
                werase(menu_win);
                wrefresh(menu_win);
                break;
            default:
                break;
            }
            printMenu(menu_win, highlight, choices);
        }

        if (choice != 0) { // User made a choice
            switch (choice) {
            case 1:
                newTransaction(chain);
                break;
            case 2:
                viewCurrentTransactions(chain);
                break;
            case 3:
                showBalances(chain);
                break;
            case 4:
                createBlock(chain);
                break;
            case 5:
                viewChain(chain);
                break;
            case 6:
                endwin();
                return 0;
            default:
                break;
            }
            choice = 0; // Reset choice
        }
    }
    endwin();
    return 0;
}

void printMenu(WINDOW *menu_win, int highlight, std::vector<std::string> choices) {
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for (size_t i = 0; i < choices.size(); ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        }
        ++y;
    }
    wrefresh(menu_win);
}

void newTransaction(Blockchain &chain) {
    clear();
    char sender[30], recipient[30];
    double amount;
    echo();
    mvprintw(0, 0, "Enter Sender: ");
    getstr(sender);
    mvprintw(1, 0, "Enter Recipient: ");
    getstr(recipient);
    mvprintw(2, 0, "Enter Amount: ");
    scanw("%lf", &amount);
    noecho();

    chain.addTransaction(sender, recipient, amount);

    mvprintw(4, 0, "Transaction added. It will remain pending until the next block is mined. Press any key to continue.");
    getch();
    clear();
    refresh();
}

void viewCurrentTransactions(Blockchain &chain) {
    clear();
    mvprintw(0, 0, "Current Transactions:");

    int y = 1;
    for (const auto &tx : chain.getCurrentTransactions()) {
        mvprintw(y++, 0, "%s -> %s : %f", tx.getSender().c_str(), tx.getRecipient().c_str(), tx.getAmount());
    }

    mvprintw(y + 1, 0, "Press any key to continue.");
    getch();
    clear();
    refresh();
}

void showBalances(Blockchain &chain) {
    clear();
    mvprintw(0, 0, "Balances:");

    int y = 1;
    auto balances = chain.calculateBalances();
    for (const auto &balance : balances) {
        mvprintw(y++, 0, "%s : %f", balance.first.c_str(), balance.second);
    }

    mvprintw(y + 1, 0, "Press any key to continue.");
    getch();
    clear();
    refresh();
}

void createBlock(Blockchain &chain) {
    clear();
    mvprintw(0, 0, "Creating block, please wait...");
    refresh();
    sleep(2);

    uint64_t lastProof = chain.getLastProof();
    uint64_t newProof = chain.proofOfWork(lastProof);
    chain.createBlock(newProof, chain.getLastBlockHash());

    mvprintw(0, 0, "Block created. Pending transactions have been added to the new block. Press any key to continue.");
    getch();
    clear();
    refresh();
}

void viewChain(Blockchain &chain) {
    clear();
    mvprintw(0, 0, "Blockchain:");

    int y = 1;
    for (const auto &block : chain.getChain()) {
        mvprintw(y++, 0, "Block %lu [Proof: %lu]", block.getIndex(), block.getProof());
        for (const auto &tx : block.getTransactions()) {
            mvprintw(y++, 0, "%s -> %s : %f", tx.getSender().c_str(), tx.getRecipient().c_str(), tx.getAmount());
        }
    }

    mvprintw(y + 1, 0, "Press any key to continue.");
    getch();
    clear();
    refresh();
}
