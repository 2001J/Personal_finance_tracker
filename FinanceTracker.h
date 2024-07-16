// FinanceTracker.h
#pragma once
#include "Transaction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> // Include for std::transform

class FinanceTracker
{
private:
  std::vector<Transaction> transactions;
  std::string filePath;

  // Utility function to convert a string to lowercase
  std::string toLowerCase(const std::string &str) const
  {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return lowerStr;
  }

public:
  // Constructor
  FinanceTracker(const std::string &filePath) : filePath(filePath) {}

  // Add a transaction
  void addTransaction(const Transaction &transaction)
  {
    transactions.push_back(transaction);
  }

  // Save transactions to file
  void saveTransactionsToFile()
  {
    std::ofstream file(filePath);
    for (const auto &transaction : transactions)
    {
      file << transaction.serialize() << std::endl;
    }
    file.close();
  }

  // Load transactions from file
  void loadTransactionsFromFile()
  {
    std::ifstream file(filePath);
    std::string line;
    transactions.clear();
    while (std::getline(file, line))
    {
      transactions.push_back(Transaction::deserialize(line));
    }
    file.close();
  }

  // View transactions with optional filters
  void viewTransactions(const std::string &filterType = "", const std::string &filterCategory = "", const std::string &startDate = "", const std::string &endDate = "")
  {
    for (const auto &transaction : transactions)
    {
      if ((filterType.empty() || toLowerCase(transaction.getType()) == toLowerCase(filterType)) &&
          (filterCategory.empty() || toLowerCase(transaction.getCategory()) == toLowerCase(filterCategory)) &&
          (startDate.empty() || transaction.getDate() >= startDate) &&
          (endDate.empty() || transaction.getDate() <= endDate))
      {
        std::cout << transaction.serialize() << std::endl;
      }
    }
  }

  // Generate summary report
  void generateSummaryReport(const std::string &startDate, const std::string &endDate)
  {
    double income = 0.0, expenses = 0.0;
    for (const auto &transaction : transactions)
    {
      std::string typeLower = toLowerCase(transaction.getType());
      if (transaction.getDate() >= startDate && transaction.getDate() <= endDate)
      {
        if (typeLower == "income")
        {
          income += transaction.getAmount();
        }
        else if (typeLower == "expense")
        {
          expenses += transaction.getAmount();
        }
      }
    }
    std::cout << "Summary from " << startDate << " to " << endDate << ":\n"
              << "Total Income: " << income << "\nTotal Expenses: " << expenses << "\nNet: " << (income - expenses) << std::endl;
  }

  // Delete a transaction by index
  void deleteTransaction(size_t index)
  {
    if (index < transactions.size())
    {
      transactions.erase(transactions.begin() + index);
    }
  }

  // Calculate total income
  double calculateTotalIncome() const
  {
    double totalIncome = 0.0;
    for (const auto &transaction : transactions)
    {
      if (toLowerCase(transaction.getType()) == "income")
      {
        totalIncome += transaction.getAmount();
      }
    }
    return totalIncome;
  }

  // Calculate total expenses
  double calculateTotalExpenses() const
  {
    double totalExpenses = 0.0;
    for (const auto &transaction : transactions)
    {
      if (toLowerCase(transaction.getType()) == "expense")
      {
        totalExpenses += transaction.getAmount();
      }
    }
    return totalExpenses;
  }
};