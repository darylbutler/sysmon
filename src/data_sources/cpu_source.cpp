    /*
     * CpuSource is a Data Source that collects data about the cpu load
     * from GTop.
     *
     * It's a pretty simple class.  It holds data for CpuCount + 1, with 0
     * being the aggregate cpu load (All cores combined) and then 1 = cpu1,
     * etc...
     *
     * Notice that it first calculates the difference in jiffies from out last
     * update.  This allows us to monitor the changes to the jiffies, not the
     * total jiffies.
     *
     */

#include <string>
#include <vector>
#include <memory>
#include <glibtop/cpu.h>

#include "cpu_source.h"
#include "../utilities/gtop.cpp"
#include "data_source.cpp"

// Method: DoWork()
// (Inherited from DataStore)
// DataCollection -> CpuSource
//
// Called when we should update our internal values
void CpuSource::DoWork()
{
    update_cpu_jiffie_counts();
}

void CpuSource::update_cpu_counts()
{
    // Get the structure from gtop
    unique_ptr<glibtop_cpu> stats = &(GTop.GetCpu());

    update_cpu_counts_aggregate(stats.get());
}

void CpuSource::update_cpu_counts_aggregate(const glibtop_cpu *stats)
{
    // We are considering work the first three values in /proc/stat, so
    // user, nice, and system.
    unsigned int new_total, new_work;

    new_total = stats->total - aggregate_cpu.total;
    new_work = (stats->user + stats->nice + stats->sys) - aggregate_cpu.work;

    aggregate_cpu.total = new_total;
    aggregate_cpu.work  = new_work;
    aggregate_cpu.UpdatePercent();
    aggregate_cpu.frequency = stats->
}

// Methods: calculate_cpu_load()
// uses the cpu_jiffies vectors total and work, averages the difference of
// these two time period (ie, work and last_work)
void CpuSource::update_cpu_load()
{
    // Special Case:  If either of the cpu_jiffies_last_* are empty, then
    // this is the first time we've tried to calc the load, but we need two
    // jiffie counts (ie, work and last_work), so return because there's
    // nothing we can do
    if (cpu_jiffies_last_total->size() <= 0) return;

    // For every cpu, create a manual entry in *cpu_load (use a temp vector
    // and swap with *cpu_load at the end)
    auto load = unique_ptr<vector<double>>(new vector<double>(cpu_jiffies_total->size()));
    load->clear();

    // Assert that all *cpu_jiffies_* are the same size()!
    for (int cpu = 0; cpu < (int) cpu_jiffies_total->size(); cpu++)
    {
        // Calculate the amount of jiffies that were counted since we last checked
        double total_done = cpu_jiffies_total->at(cpu) - cpu_jiffies_last_total->at(cpu);
        double work_done = cpu_jiffies_work->at(cpu) - cpu_jiffies_last_work->at(cpu);


        // Calc the ratio (Should always be < 1)
        double cpu_load = work_done / total_done;

        // Store them in the temporary vector array
        load->insert(load->begin() + cpu, cpu_load);
    }

    // We have now calculated the current load on each cpu, and it is stored in
    // the local vector *load.  We need to swap the class member *cpu_load
    // with *load.  If this class ever goes threaded, you need to lock
    // *cpu_load with a mutex now and release after swap returns
    cpu_load->swap(*load);
}


// ----------------------------------------------------------------------------
// DataWidget -> DataSource
//
// GetValue(value)
// returns requested cpu load or error string if value is not valid
// accepts value =
//      "all"   - Returns formatted string of aggregate load, or cpu_load if
//                  system has a single cpu
//      "cpuX"  - Returns an individual cpu.  Cpu0 will always return the
//                  aggregate cpu load
string CpuSource::GetValue(string value)
{
    double result = GetValueAsNumber(value);

    if (result == -1) return "error";

    result = result * 100.0;

    stringstream formatted;
    formatted.precision(2);
    formatted << fixed << result << "%";

    return formatted.str();
}


double CpuSource::GetValueAsNumber(string value)
{
    if (value == "all" || value == "")
        return cpu_load->at(0);

    if (value.compare(0, 3, "cpu") == 0)
    {
        int core = atoi(&value[3]) + 1;

        if (core >= (int) cpu_load->size())
            return -1;  // cpu index out_of_bounds
        else
            return cpu_load->at(core);
    }

    // Unknown value
    return -1;
}

// ----------------------------------------------------------------------------
// Constructor
CpuSource::CpuSource()
{
    cpu_count = GTop.GetCPUCount();
    cores.assign(cpu_count, cpu()); // Fill our cores array with empty cpu structs

}

