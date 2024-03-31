#ifndef IO_H
#define IO_H

#include <vector>
#include <string>

namespace zlatov {

  // ���� ������ ��� key1 � key2
  typedef double Key1Type;
  typedef unsigned long long Key2Type;

  // ��������� DataStruct
  struct DataStruct {
    Key1Type key1;
    Key2Type key2;
    std::string key3;
  };

  // ������� ��� ������� ������ � ���������� ��������� DataStruct
  DataStruct parseDataStruct(const std::string& input);

  // ������� ��� ������ ��������� DataStruct
  void printDataStruct(const DataStruct& data);

  // ���������� ��� ����������
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);

  // ������� �������
  void processData();

} // namespace zlatov

// ���������� ��������� ������ ��� ��������� DataStruct
std::ostream& operator<<(std::ostream& os, const zlatov::DataStruct& data);

// ���������� ��������� ����� ��� ��������� DataStruct
std::istream& operator>>(std::istream& is, zlatov::DataStruct& data);

#endif // IO_H
