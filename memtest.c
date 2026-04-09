#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int mem_before_sbrk;
  int mem_after_sbrk;
  int pages_before_malloc;
  int pages_after_malloc;
  int parent_pte_before_fork;
  int parent_pte_after_fork;
  int child_pte_count;
  int child_pid;
  char *sbrk_result;
  char *malloc_buffer;

  printf(1, "========================================\n");
  printf(1, "memtest: Process Memory Information Lab\n");
  printf(1, "========================================\n");

  printf(1, "\n");
  printf(1, "Test 1: getmemsize with sbrk\n");
  mem_before_sbrk = getmemsize();
  printf(1, "Memory size before sbrk : %d bytes\n", mem_before_sbrk);

  sbrk_result = sbrk(4096);
  if(sbrk_result == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  mem_after_sbrk = getmemsize();
  printf(1, "Memory size after sbrk  : %d bytes\n", mem_after_sbrk);
  printf(1, "Increase in size        : %d bytes\n",
         mem_after_sbrk - mem_before_sbrk);

  printf(1, "\n");
  printf(1, "Test 2: getvirtpages with malloc\n");
  pages_before_malloc = getvirtpages();
  printf(1, "Virtual pages before malloc : %d\n", pages_before_malloc);

  malloc_buffer = malloc(8192);
  if(malloc_buffer == 0){
    printf(1, "malloc failed\n");
    exit();
  }

  memset(malloc_buffer, 1, 8192);

  pages_after_malloc = getvirtpages();
  printf(1, "Virtual pages after malloc  : %d\n", pages_after_malloc);
  printf(1, "Increase in pages           : %d\n",
         pages_after_malloc - pages_before_malloc);
  printf(1, "Note: xv6 malloc may ask sbrk for extra pages.\n");

  free(malloc_buffer);

  printf(1, "\n");
  printf(1, "Test 3: getptecount with fork\n");
  parent_pte_before_fork = getptecount();
  printf(1, "Parent PTE count before fork : %d\n", parent_pte_before_fork);

  child_pid = fork();
  if(child_pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(child_pid == 0){
    child_pte_count = getptecount();
    printf(1, "Child PTE count after fork   : %d\n", child_pte_count);
    exit();
  }

  wait();
  parent_pte_after_fork = getptecount();
  printf(1, "Parent PTE count after fork  : %d\n", parent_pte_after_fork);

  printf(1, "\n");
  printf(1, "Final summary\n");
  printf(1, "Current memory size : %d bytes\n", getmemsize());
  printf(1, "Current virtual pages: %d\n", getvirtpages());
  printf(1, "Current valid PTEs   : %d\n", getptecount());

  printf(1, "\n");
  printf(1, "memtest finished\n");
  exit();
}
