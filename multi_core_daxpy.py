# multi_core_daxpy.py
from m5.objects import *

# System configuration
system = System()
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

# CPU configuration
system.cpu = [MinorCPU() for i in range(NUM_THREADS)]
system.mem_ctrl = DDR3_1600_8x8()
system.mem_ctrl.range = system.mem_ranges[0]
system.system_port = system.membus.cpu_side_ports

# L2 Cache (optional, depending on needs)
system.l2cache = L2Cache(size='256kB', assoc=4)
for cpu in system.cpu:
    cpu.connectAllPorts(system.membus)

# Connect each CPU to a separate port
system.cpu[0].workload = SEWorkload.init_compatible(EXECUTABLE)
for cpu in system.cpu:
    cpu.createThreads()
system.system_port = system.membus.cpu_side_ports

# Simulation configuration
root = Root(full_system=False, system=system)
m5.instantiate()
