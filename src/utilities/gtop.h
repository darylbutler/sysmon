#ifndef GTOP_H
#define GTOP_H


extern "C"{
    // Prototype all C functions here
    void glibtop_get_swap(glibtop_swap*);
    void glibtop_get_cpu(glibtop_cpu*);
    void glibtop_get_mem(gliptop_mem*);
    void glibtop_get_loadavg(gliptop_loadavg*);
    void glibtop_get_fsusage(glibtop_fsusage*, const char*);
    void glibtop_get_uptime(glibtop_uptime*);
    void glibtop_get_netload(glibtop_netload*, const char*);
    const glibtop_sysinfo* glibtop_get_sysinfo();
}

struct GTop
{
    // Direct Accessors
    static glibtop_swap             GetSwap();
    static glibtop_cpu              GetCpu();
    static glibtop_mem              GetMemory();
    static glibtop_loadavg          GetLoadAvg();
    static glibtop_fsusage          GetFSUsage(string device);
    static glibtop_uptime           GetUptime();
    static glibtop_netload          GetNetLoad(string device);
    static const glibtop_sysinfo*   GetSystemInfo();

    // Convience to return single values
    static int GetCPUCount();
};

#endif
