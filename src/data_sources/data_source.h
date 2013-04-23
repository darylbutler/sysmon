#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

using namespace std;

class DataSource
{
protected:
    // Not sure if anything makes sense here.
public:
  // Constructor 
  DataSource();
  virtual ~DataSource();

  // DataWidget -> DataSource
  virtual string GetValue(string value = "");   // Widget wants data
  virtual string* GetValues();  // wants all data you provide as strings
  virtual double GetValueAsNumber(string value = "");// Return as number
  virtual double* GetValuesAsNumbers(); // All data as numbers

  // DataCollection -> DataSource
  void DoWork();  // Get your ass to work!
};

#endif
