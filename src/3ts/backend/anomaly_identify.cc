/*
 * Tencent is pleased to support the open source community by making 3TS available.
 *
 * Copyright (C) 2020 THL A29 Limited, a Tencent company.  All rights reserved. The below software
 * in this distribution may have been modified by THL A29 Limited ("Tencent Modifications"). All
 * Tencent Modifications are Copyright (C) THL A29 Limited.
 *
 * Author: farrisli@tencent.com
 *
 */
#include "anomaly_identify.h"

int main() {
  Printer printer;
  Checker checker;
  printer.PrintStartInfo();

  while (true) {
    std::cout << "Please type a history for anomaly identification." << std::endl;
    std::cout << "3ts> ";
    std::string text = "";
    std::getline(std::cin, text);
    if ("help" == text || "h" == text) {
        Printer::PrintHelpInfo();
    } else if ("\\q" == text || "quit" == text) {
      break;
    } else if (text.find("\\d") != text.npos || text.find("definition") != text.npos) {
      const auto index_space = text.find_first_of(" ");
      if (index_space != text.npos) {
        std::string input = text.substr(index_space);
        Printer::TrimSpace(input);
        if (printer.InfoMap().count(input) == 0) {
            Printer::Print("Unknown Definition");
        } else {
            Printer::Print(printer.InfoMap()[input]);
        }
      } else {
          Printer::Print("Please check input format, such as \\d History");
      }
    } else if (text.find("\\a") != text.npos || text.find("anomaly") != text.npos) {
      const auto index_space = text.find_first_of(" ");
      if (index_space != text.npos) {
        std::string input = text.substr(index_space);
        Printer::TrimSpace(input);
        if (printer.AnomalyMap().count(input) == 0) {
            Printer::Print("Unknown Anomaly");
        } else {
          std::cout << "Type  SubType  History Example                     Definition" << std::endl;
          std::cout << "-------------------------------------------------------------" << std::endl;
          Printer::Print(printer.AnomalyMap()[input]);
        }
      } else {
          Printer::Print("Please check input format, such as \\a Dirty Write");
      }
    } else if (text.find("\\g") != text.npos || text.find("algorithm") != text.npos) {
      const auto index_space = text.find_first_of(" ");
      if (index_space != text.npos) {
        std::string input = text.substr(index_space);
        Printer::TrimSpace(input);
        if ("DLI" == input) {
          printer.SetAlg(AlgType::DLI);
        } else if ("DLI2" == input) {
          printer.SetAlg(AlgType::DLI2);
        } else if ("All" == input) {
          printer.SetAlg(AlgType::ALL);
        } else {
            Printer::Print("Unknown Algorithm");
        }
      } else {
          Printer::Print("Please check input format, such as \\g DLI");
      }
    } else if (text.find("\\t") != text.npos || text.find("table") != text.npos) {
      std::vector<std::string> anomaly_list = Printer::InitAnomalyList();
      const auto index_space = text.find_first_of(" ");
      if (index_space != text.npos) {
        std::string input = text.substr(index_space);
        Printer::TrimSpace(input);
        if ("Anomalies" == input) {
            Printer::PrintAnomalyTableInfo(anomaly_list);
        } else {
            Printer::Print("Unknown Table");
        }
      }
    } else if (text.find("\\A") != text.npos || text.find("authors") != text.npos) {
        Printer::PrintAuthorInfo();
    } else {
        if (printer.Alg() == AlgType::DLI) {
          checker.ExecDLI(text);
        } else if (printer.Alg() == AlgType::DLI2) {
          // to do
        } else if (printer.Alg() == AlgType::ALL) {
         // to do
        } else {
            Printer::Print("alg has Unknown value");
        }
    }
  }
  return 0;
}