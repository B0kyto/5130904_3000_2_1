#include "io.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace zlatov {

  DataStruct parseDataStruct(const std::string& input) {
    // ���������� ��� �������� ������
    Key1Type key1;
    Key2Type key2;
    std::string key3;

    // ������ ������ � ����� ������
    size_t start = input.find('(');
    size_t end = input.find(')');

    // �������� ������� ������
    if (start == std::string::npos || end == std::string::npos) {
      return {};
    }

    // �������� ������ �� ����������� ������ ������
    std::string content = input.substr(start + 1, end - start - 1);

    // �������� ��� ������ �����������
    auto it = content.begin();

    // ���� �� ��������� ����� ������
    while (it != content.end()) {
      // ���� �����������
      auto colonPos = std::find(it, content.end(), ':');

      // ���� ����������� �� ������, ������� �� �����
      if (colonPos == content.end()) {
        break;
      }

      // �������� ��� ����
      std::string fieldName(it, colonPos);
      it = colonPos + 1;

      // ���������� ���������� �������
      while (it != content.end() && std::isspace(*it)) {
        ++it;
      }

      // ���� ��������� ����� ������, ������� �� �����
      if (it == content.end()) {
        break;
      }

      // �������� �������� ����
      std::string fieldValue;
      if (*it == '\'' || *it == '"') { // ���� ������
        auto closingQuote = std::find(it + 1, content.end(), *it);
        if (closingQuote == content.end()) {
          return {}; // ���� �� ������� ����������� �������, ���������� ������
        }
        fieldValue = std::string(it + 1, closingQuote);
        it = closingQuote + 1;
      }
      else { // ���� �����
        auto fieldEnd = std::find_if(it, content.end(), [](char c) { return std::isspace(c) || c == ':'; });
        fieldValue = std::string(it, fieldEnd);
        it = fieldEnd;
      }

      // ���������� ���������� �������
      while (it != content.end() && std::isspace(*it)) {
        ++it;
      }

      // ��������� ��������������� ���� ���������
      if (fieldName == "key1") {
        std::istringstream iss(fieldValue);
        char suffix;
        iss >> key1 >> suffix;
        if (suffix != 'd' && suffix != 'D') {
          return {}; // ���� ������� �� ������������� ������� [DBL LIT], ���������� ������
        }
      }
      else if (fieldName == "key2") {
        try {
          size_t pos;
          key2 = std::stoull(fieldValue, &pos, 16);
          if (pos != fieldValue.size()) {
            return {}; // ���� ����� ����� ���� ������ �������, ���������� ������
          }
        }
        catch (...) {
          return {}; // ���� �� ������� ������������� ��������, ���������� ������
        }
      }
      else if (fieldName == "key3") {
        key3 = fieldValue;
      }
      else {
        return {}; // ���� ����������� ����, ���������� ������
      }
    }

    // ������� � ���������� ��������� DataStruct
    return { key1, key2, key3 };
  }

  void printDataStruct(const DataStruct& data) {
    std::cout << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d"
      << ":key2 " << std::hex << data.key2 << ":key3 " << data.key3 << ":)" << std::endl;
  }

  bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
      return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2) {
      return a.key2 < b.key2;
    }
    else {
      return a.key3.size() < b.key3.size();
    }
  }

  void processData() {
    // ������ ��� �������� �������� DataStruct
    std::vector<DataStruct> dataVector;

    // ��������� ������ � ��������� ������
    std::string input;
    while (std::getline(std::cin, input)) {
      DataStruct data = parseDataStruct(input);
      if (!data.key3.empty()) {
        dataVector.push_back(data);
      }
    }

    // ��������� ������
    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    // ������� ��������������� ������
    std::for_each(dataVector.begin(), dataVector.end(), printDataStruct);
  }

} // namespace zlatov

// ���������� ��������� ������ ��� ��������� DataStruct
std::ostream& operator<<(std::ostream& os, const zlatov::DataStruct& data) {
  os << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d"
    << ":key2 " << std::hex << data.key2 << ":key3 " << data.key3 << ":)";
  return os;
}

// ���������� ��������� ����� ��� ��������� DataStruct
std::istream& operator>>(std::istream& is, zlatov::DataStruct& data) {
  // ������ ���������� ��������� �����
  is >> data.key1 >> data.key2 >> data.key3;
  return is;
}
