// Simple wrapper for the C-library GTop

#include <glib-2.0/glib.h>
#include <glibtop.h>

#include <glibtop/loadavg.h>
#include <glibtop/netload.h>
#include <glibtop/uptime.h>
#include <glibtop/sysinfo.h>
#include <glibtop/version.h>
#include <glibtop/prockernel.h>
#include <glibtop/fsusage.h>
#include <glibtop/mem.h>
#include <glibtop/mountlist.h>
#include <glibtop/cpu.h>
#include <glibtop/swap.h>

#include "gtop.h"

static glibtop_swap GTop::GetSwap()
{
    glibtop_swap info;
    glibtop_get_swap(&info);
    return info;
}
static glibtop_cpu GTop::GetCpu()
{
    glibtop_cpu info;
    glibtop_get_cpu(&info);
    return info;
}
static glibtop_mem GTop::GetMemory()
{
    glibtop_mem info;
    glibtop_get_mem(&info);
    return info;
}
static glibtop_loadavg GTop::GetLoadAvg()
{
    glibtop_loadavg info;
    glibtop_get_loadavg(&info);
    return info;
}
static glibtop_fsusage GTop::GetFSUsage()
{
    glibtop_fsusage info;
    glibtop_get_fsusage(&info);
    return info;
}
static glibtop_uptime GTop::GetUptime()
{
    glibtop_uptime info;
    glibtop_get_uptime(&info);
    return info;
}
static glibtop_netload GTop::GetNetLoad()
{
    glibtop_netload info;
    glibtop_get_netload(&info);
    return info;
}
static const glibtop_sysinfo* GTop::GetSystemInfo()
{
    return glibtop_get_sysinfo();
}
static int GetCPUCount()
{
    glibtop_sysinfo* info = glibtop_get_sysinfo();
    int ncpus = info->ncpu;
    delete info;
    return ncpus;
}
