/*
 * Copyright (C) 2024 pdnguyen of the HCMC University of Technology
 */
/*
 * Source Code License Grant: Authors hereby grants to Licensee 
 * a personal to use and modify the Licensed Source Code for 
 * the sole purpose of studying during attending the course CO2018.
 */
//#ifdef MM_TLB
/*
 * Memory physical based TLB Cache
 * TLB cache module tlb/tlbcache.c
 *
 * TLB cache is physically memory phy
 * supports random access 
 * and runs at high speed
 */


#include "mm.h"
#include <stdlib.h>
#include <stdio.h>

#define init_tlbcache(mp,sz,...) init_memphy(mp, sz, (1, ##__VA_ARGS__))


int calc_index(int pid, int pgnum, int max_tlb_size) {
   return (pid*MAX_PAGES_TLB + pgnum) % max_tlb_size;
}

/*
 *  tlb_cache_read read TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
int tlb_cache_read(struct memphy_struct * mp, int pid, int pgnum, BYTE *value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
    */

   if (mp == NULL || value == NULL)
      return -1;

   // Calculate the cache line index using direct mapped mapping
   int index = calc_index(pid, pgnum, mp->maxsz);

   if (mp->storage != NULL) {
      // TLB hit
      *value = mp->storage[index];
      return 0; 
    } else {
      // TLB miss
      int addr = (pid * (1<<PAGE_ENTRY_SIZE) + pgnum * sizeof(BYTE));
      return TLBMEMPHY_read(mp, addr, value);
   }
   return 0;
}

/*
 *  tlb_cache_write write TLB cache device
 *  @mp: memphy struct
 *  @pid: process id
 *  @pgnum: page number
 *  @value: obtained value
 */
int tlb_cache_write(struct memphy_struct *mp, int pid, int pgnum, BYTE value)
{
   /* TODO: the identify info is mapped to 
    *      cache line by employing:
    *      direct mapped, associated mapping etc.
    */
   if (mp == NULL)
      return -1;

   int index = calc_index(pid, pgnum, mp->maxsz);

   if (mp->storage != NULL) {
      // TLB hit
      mp->storage[index] = value;
    } else {
      // TLB miss
      int addr = pid * (1<<PAGE_ENTRY_SIZE) + pgnum * sizeof(BYTE);
      TLBMEMPHY_write(mp, addr, value);
      // mp->storage[index] = value;
   }

   return 0;
}

/*
 *  TLBMEMPHY_read natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @value: obtained value
 */
int TLBMEMPHY_read(struct memphy_struct * mp, int addr, BYTE *value)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   *value = mp->storage[addr];

   return 0;
}

/*
 *  TLBMEMPHY_write natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 *  @addr: address
 *  @data: written data
 */
int TLBMEMPHY_write(struct memphy_struct * mp, int addr, BYTE data)
{
   if (mp == NULL)
     return -1;

   /* TLB cached is random access by native */
   mp->storage[addr] = data;

   return 0;
}

/*
 *  TLBMEMPHY_format natively supports MEMPHY device interfaces
 *  @mp: memphy struct
 */
int TLBMEMPHY_dump(struct memphy_struct * mp)
{
   /*TODO dump memphy contnt mp->storage 
    *     for tracing the memory content
    */

   printf("===== TLB MEMORY DUMP =====\n");

   if (mp == NULL) {
      printf("Error: Null pointer encountered.\n");
      return -1;
   }

   // Loop through the storage and print each value
   for (int i = 0; i < mp->maxsz; ++i) {
      if (mp->storage[i] != 0) printf("Address %d: %d\n", i, mp->storage[i]);

   }

   printf("===== TLB MEMORY DUMP =====\n");


   return 0;
}

/*
 *  Init TLBMEMPHY struct
 */
int init_tlbmemphy(struct memphy_struct *mp, int max_size)
{
   mp->storage = (BYTE *)malloc(max_size*sizeof(BYTE));
   mp->maxsz = max_size;

   mp->rdmflg = 1;

   return 0;
}

//#endif
