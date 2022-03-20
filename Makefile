
all: gcc -o dnsp2 dnsp2.c dnsutil.c rr_linkedlist.c


DNS Utility Test: gcc dnsutil.c -D RUN_UTIL_TEST


DEBUG GDB: Segmentation Fault(core dumped)
1: gcc -o dnsp2 rr_linkedlist.c dnsutil.c dnsp2.c -g
2: gdb --args dnsp2 12345 ics651.uhm/1.2.3.4

FIXED: dynamically allocated char* for main args
       dnsp2.c Line:45



