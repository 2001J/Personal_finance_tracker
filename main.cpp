#include "FinanceTracker.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype> // For std::tolower


bool isValidAmount(const std::string &str)
{
  // Check if the string is a valid number
  char *p;
  strtod(str.c_str(), &p);
  return *p == 0;
}

std::string toLowerCase(const std::string &str)
{
  std::string lowerCaseStr;
  for (char c : str)
  {
    lowerCaseStr += std::tolower(c);
  }
  return lowerCaseStr;
}

int main()
{
  FinanceTracker tracker("transactions.txt");
  tracker.loadTransactionsFromFile();

  std::string type, category, date, description, startDate, endDate, amountStr;
  double amount;
  char continueInput = 'y';

  while (continueInput == 'y' || continueInput == 'Y')
  {
    do
    {
      std::cout << "Enter transaction type (Income/Expense): ";
      std::cin >> type;
      type = toLowerCase(type);
    } while (type != "income" && type != "expense");

    do
    {
      std::cout << "Enter amount: ";
      std::cin >> amountStr;
      if (!isValidAmount(amountStr))
      {
        std::cout << "Invalid amount. Please enter a numeric value.\n";
        continue;
      }
      amount = std::stod(amountStr);
    } while (amount <= 0);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Enter category: ";
    std::getline(std::cin, category);
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    tracker.addTransaction(Transaction(type, amount, category, date, description));

    std::cout << "Transaction added. Do you want to add another? (y/n): ";
    std::cin >> continueInput;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
  }

  tracker.saveTransactionsToFile();
  tracker.viewTransactions();

  // Prompt the user for the report start and end dates
  std::cout << "Enter report start date (YYYY-MM-DD): ";
  std::getline(std::cin, startDate);
  std::cout << "Enter report end date (YYYY-MM-DD): ";
  std::getline(std::cin, endDate);

  // Generate the summary report based on the user-specified dates
  tracker.generateSummaryReport(startDate, endDate);

  return 0;
}