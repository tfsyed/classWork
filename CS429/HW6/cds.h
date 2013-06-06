#ifndef _CDS_H_
#define _CDS_H_

/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* The Cache Description Structure */
/* The description of a cache. */

/* define the Cache Replacement Policy */
enum CRP
{
    CRP_FIFO,
    CRP_LFU,
    CRP_RANDOM,
    CRP_LRU //add LRU policy
};

/* (modified) define the types of cache */
enum CACHETYPE
{
    FULL,
    DIRECT,
    OTHER
};



/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */
/* Each cache is defined by a number of integers:

   1. The number of entries.
   2. The number of ways.  If we have n entries and m ways, we have n/m sets.
   3. The cache line size.
   4. If the cache is write-back, or write-thru.

   Not that adjusting the number of ways allows us to get the three
   main types (assume the number of entries is n):

   1. Fully-associative -- number of ways = n.
   2. Direct-mapped  -- number of ways = 1.
   3. Set associative -- any other value of n.

   Note that we have to have (number of entries) be evenly divisible by the
   number of ways.  We can't have 15 lines and 4 ways.

   And we need the cache line size as a power of two.
   And the number of ways must be a power of two.
*/

/* With this description, a cache is then a dynamically allocated
   array of "number of entries" cache lines.  Each cache line is
   (a) an array of bytes (the cache line),
   (b) an address tag (let's just keep the full address of the first byte),
   (c) a dirty bit
   (d) maybe some info for the replacement policy.
*/

struct cache_line
{
    Boolean valid;
    memory_address tag;
    Boolean dirty;
    int     replacement_data;
    byte   *actual_data;
};
typedef struct cache_line cache_line;




/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */
/* The actual cache description structure */

struct CDS
{
    struct CDS *next;  /* linked list of all the CDS */

    String      name;
    int         cache_line_size;
    int         number_of_cache_entries;
    int         number_of_ways;
    Boolean     write_back;
    enum CRP    replacement_policy;
    //modified (add new enum type)
    enum CACHETYPE type;

    //new added fields
    int             number_of_low_order_bits;
    int             number_of_sets;
    memory_address  sets_bits_mask;
    memory_address  low_order_mask;

    /* how often to decrease the counts for LFU */
    int         LFU_Decay_Interval;

    /* array of cache lines */
    cache_line *c;

    /* statistics for each cache policy */
    counter_t number_of_memory_reference;
    counter_t number_of_type[NUMBER_OF_MEMORY_ACCESS_TYPE];

    counter_t number_cache_hits;
    counter_t number_cache_misses;
    counter_t number_memory_reads;
    counter_t number_memory_writes;
};
typedef struct CDS CDS;



/* ***************************************************************** */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* a linked list of all the cache descriptors */
struct CDS *CDS_root;

#endif
