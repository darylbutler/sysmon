#ifndef CPU_SOURCE_H
#define CPU_SOURCE_H

#include "data_source.h"

using namespace std;

struct cpu
{
    unsigned int total, // Sum of all report jiffies
                 work;  // Sum of all productive jiffies
    int frequency;      // CPU Frequency (May change based on govenor scaling
    double percent;     // Calculated CPU Load %

    cpu(): total(0), work(0), frequency(0), percent(0.0d) {};
    void UpdatePercent() {
        percent = static_cast<double>(work) - static_cast<double>(total);
    }
};

class CpuSource : public DataSource
{
protected:
    // Members
    int cpu_count;              // Number of cpus we will track
    cpu aggregate_cpu;          // System Aggregate of all cpus
    vector<cpu> cores;          // The stats tracked for each individual cpu

    // Methods
    void update_cpu_counts();
    void update_cpu_counts_aggregate(const glibtop_cpu*);
    void update_cpu_load();

public:
    // Constructor
    CpuSource();

    // DataCollection -> DataSource
    virtual void DoWork();

    // DataWidget -> CpuSource
    virtual string GetValue(string value);
    //virtual string* GetValues();
    virtual double GetValueAsNumber(string value);
    //virtual double* GetValuesAsNumbers();
};

#endif
