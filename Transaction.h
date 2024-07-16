// Transaction.h
#pragma once
#include <string>
#include <sstream>

class Transaction
{
private:
  std::string type; // "Income" or "Expense"
  double amount;
  std::string category;
  std::string date; // Format: YYYY-MM-DD
  std::string description;

public:
  Transaction(std::string type, double amount, std::string category, std::string date, std::string description)
      : type(type), amount(amount), category(category), date(date), description(description) {}

  std::string getType() const { return type; }
  double getAmount() const { return amount; }
  std::string getCategory() const { return category; }
  std::string getDate() const { return date; }
  std::string getDescription() const { return description; }

  std::string serialize() const
  {
    std::stringstream ss;
    ss << type << "," << amount << "," << category << "," << date << "," << description;
    return ss.str();
  }

  static Transaction deserialize(const std::string &data)
  {
    std::stringstream ss(data);
    std::string type, category, date, description, temp;
    double amount;

    std::getline(ss, type, ',');
    std::getline(ss, temp, ',');
    amount = std::stod(temp);
    std::getline(ss, category, ',');
    std::getline(ss, date, ',');
    std::getline(ss, description);

    return Transaction(type, amount, category, date, description);
  }
};