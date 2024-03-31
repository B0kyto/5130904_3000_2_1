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
  // ���������� true, ���� ������ ���� ������� ����������, ����� false
  bool parseDataStruct(const std::string& input, DataStruct& data);

  // ������� ��� ������ ��������� DataStruct
  void printDataStruct(const DataStruct& data);

  // ���������� ��� ����������
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);

  // ������� �������
  void processData();

} // namespace zlatov

#endif // IO_H
