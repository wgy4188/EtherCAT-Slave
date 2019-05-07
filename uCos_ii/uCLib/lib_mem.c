/*
*********************************************************************************************************
*                                               uC/LIB
*                                       CUSTOM LIBRARY MODULES
*
*                          (c) Copyright 2004-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/LIB is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/LIB in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/LIB.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     STANDARD MEMORY OPERATIONS
*
* Filename      : lib_mem.c
* Version       : V1.25
* Programmer(s) : ITJ
*                 FGK
*********************************************************************************************************
* Note(s)       : (1) NO compiler-supplied standard library functions are used in library or product software.
*
*                     (a) ALL standard library functions are implemented in the custom library modules :
*
*                         (1) \<Custom Library Directory>\lib*.*
*
*                         (2) \<Custom Library Directory>\Ports\<cpu>\<compiler>\lib*_a.*
*
*                               where
*                                       <Custom Library Directory>      directory path for custom library software
*                                       <cpu>                           directory name for specific processor (CPU)
*                                       <compiler>                      directory name for specific compiler
*
*                     (b) Product-specific library functions are implemented in individual products.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    LIB_MEM_MODULE
#include  <lib_mem.h>


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
MEM_POOL    *Mem_PoolTbl;                                               /* Mem      pool/seg tbl.                       */
MEM_POOL     Mem_PoolHeap;                                              /* Mem heap pool/seg.                           */
CPU_INT08U   Mem_Heap[LIB_MEM_CFG_HEAP_SIZE];                           /* Mem heap.                                    */
#endif


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)                                /* -------------- MEM POOL FNCTS -------------- */

static  CPU_SIZE_T    Mem_PoolSegCalcTotSize(void        *pmem_addr,
                                             CPU_SIZE_T   blk_nbr,
                                             CPU_SIZE_T   blk_size,
                                             CPU_SIZE_T   blk_align);

static  void         *Mem_PoolSegAlloc      (MEM_POOL    *pmem_pool,
                                             CPU_SIZE_T   size,
                                             CPU_SIZE_T   align);

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
static  CPU_BOOLEAN   Mem_PoolBlkIsValidAddr(MEM_POOL    *pmem_pool,
                                             void        *pmem_blk);
#endif

#endif


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Mem_Init()
*
* Description : (1) Initialize Memory Management Module :
*
*                   (a) Initialize heap memory pool
*                   (b) Initialize      memory pool table
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  Mem_Init (void)
{
#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
    MEM_POOL  *pmem_pool;

                                                                        /* --------- INIT MEM HEAP SEG / POOL --------- */
    pmem_pool                   = (MEM_POOL   *)&Mem_PoolHeap;
    pmem_pool->Type             = (LIB_MEM_TYPE) LIB_MEM_TYPE_HEAP;
    pmem_pool->SegPrevPtr       = (MEM_POOL   *) 0;
    pmem_pool->SegNextPtr       = (MEM_POOL   *) 0;
    pmem_pool->PoolPrevPtr      = (MEM_POOL   *) 0;
    pmem_pool->PoolNextPtr      = (MEM_POOL   *) 0;
    pmem_pool->PoolAddrStart    = (void       *) 0;
    pmem_pool->PoolAddrEnd      = (void       *) 0;
    pmem_pool->PoolPtrs         = (void      **) 0;
    pmem_pool->BlkSize          = (CPU_SIZE_T  ) 0;
    pmem_pool->BlkNbr           = (CPU_SIZE_T  ) 0;
    pmem_pool->BlkIx            = (MEM_POOL_IX ) 0;
    pmem_pool->SegAddr          = (void       *)&Mem_Heap[0];
    pmem_pool->SegAddrNextAvail = (void       *)&Mem_Heap[0];
    pmem_pool->SegSizeTot       = (CPU_SIZE_T  ) LIB_MEM_CFG_HEAP_SIZE;
    pmem_pool->SegSizeRem       = (CPU_SIZE_T  ) LIB_MEM_CFG_HEAP_SIZE;

                                                                        /* ------------ INIT MEM POOL TBL ------------- */
    Mem_PoolTbl = &Mem_PoolHeap;
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Clr()
*
* Description : Clear data buffer (see Note #2).
*
* Argument(s) : pmem        Pointer to memory buffer to clear.
*
*               size        Number of data buffer octets to clear.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null clears allowed (i.e. 0-octet size).
*
*                   See also 'Mem_Set()  Note #1'.
*
*               (2) Clear data by setting each data octet to 0.
*********************************************************************************************************
*/

void  Mem_Clr (void        *pmem,
               CPU_SIZE_T   size)
{
    Mem_Set((void     *)pmem,
            (CPU_INT08U)0,                                      /* See Note #2.                                         */
            (CPU_SIZE_T)size);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Set()
*
* Description : Fill data buffer with specified data octet.
*
* Argument(s) : pmem        Pointer to memory buffer to fill with specified data octet.
*
*               data_val    Data fill octet value.
*
*               size        Number of data buffer octets to fill.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null sets allowed (i.e. 0-octet size).
*
*               (2) For best CPU performance, optimized to fill data buffer using 'CPU_ALIGN'-sized data
*                   words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (3) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus,
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                   mem_align_modulo arithmetic operation.
*********************************************************************************************************
*/

void  Mem_Set (void        *pmem,
               CPU_INT08U   data_val,
               CPU_SIZE_T   size)
{
    CPU_SIZE_T   size_rem;
    CPU_ALIGN    data_align;
    CPU_ALIGN   *pmem_align;
    CPU_INT08U  *pmem_08;
    CPU_INT08U   mem_align_modulo;
    CPU_INT08U   i;


    if (size < 1) {                                             /* See Note #1.                                         */
        return;
    }
    if (pmem == (void *)0) {
        return;
    }


    data_align = 0;
    for (i = 0; i < sizeof(CPU_ALIGN); i++) {                   /* Fill each data_align octet with data val.            */
        data_align <<=  DEF_OCTET_NBR_BITS;
        data_align  |= (CPU_ALIGN)data_val;
    }

    size_rem         = (CPU_SIZE_T)size;
    mem_align_modulo = (CPU_INT08U)((CPU_ADDR)pmem % sizeof(CPU_ALIGN));    /* See Note #3.                             */

    pmem_08 = (CPU_INT08U *)pmem;
    if (mem_align_modulo != 0) {                                /* If leading octets avail,                   ...       */
        i = mem_align_modulo;
        while ((size_rem > 0) &&                                /* ... start mem buf fill with leading octets ...       */
               (i        < sizeof(CPU_ALIGN ))) {               /* ... until next CPU_ALIGN word boundary.              */
           *pmem_08++ = data_val;
            size_rem -= sizeof(CPU_INT08U);
            i++;
        }
    }

    pmem_align = (CPU_ALIGN *)pmem_08;                          /* See Note #2a.                                        */
    while (size_rem >= sizeof(CPU_ALIGN)) {                     /* While mem buf aligned on CPU_ALIGN word boundaries,  */
       *pmem_align++ = data_align;                              /* ... fill mem buf with    CPU_ALIGN-sized data.       */
        size_rem    -= sizeof(CPU_ALIGN);
    }

    pmem_08 = (CPU_INT08U *)pmem_align;
    while (size_rem > 0) {                                      /* Finish mem buf fill with trailing octets.            */
       *pmem_08++   = data_val;
        size_rem   -= sizeof(CPU_INT08U);
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Mem_Copy()
*
* Description : Copy data octets from one memory buffer to another memory buffer.
*
* Argument(s) : pdest       Pointer to destination memory buffer.
*
*               psrc        Pointer to source      memory buffer.
*
*               size        Number of data buffer octets to copy.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null copies allowed (i.e. 0-octet size).
*
*               (2) Memory buffers NOT checked for overlapping.
*
*               (3) For best CPU performance, optimized to copy data buffer using 'CPU_ALIGN'-sized data
*                   words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (4) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus,
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                   mem_align_modulo arithmetic operation.
*********************************************************************************************************
*/
/*$PAGE*/
#if ((!defined(uC_CFG_OPTIMIZE_ASM_EN)) || \
     ((defined(uC_CFG_OPTIMIZE_ASM_EN)) && \
              (uC_CFG_OPTIMIZE_ASM_EN   != DEF_ENABLED)))
void  Mem_Copy (void        *pdest,
                void        *psrc,
                CPU_SIZE_T   size)
{
    CPU_SIZE_T    size_rem;
    CPU_ALIGN    *pmem_align_dest;
    CPU_ALIGN    *pmem_align_src;
    CPU_INT08U   *pmem_08_dest;
    CPU_INT08U   *pmem_08_src;
    CPU_INT08U    i;
    CPU_INT08U    mem_align_modulo_dest;
    CPU_INT08U    mem_align_modulo_src;
    CPU_BOOLEAN   mem_aligned;


    if (size < 1) {                                             /* See Note #1.                                         */
        return;
    }
    if (pdest == (void *)0) {
        return;
    }
    if (psrc  == (void *)0) {
        return;
    }


    size_rem              = (CPU_SIZE_T  )size;

    pmem_08_dest          = (CPU_INT08U *)pdest;
    pmem_08_src           = (CPU_INT08U *)psrc;
                                                                /* See Note #4.                                         */
    mem_align_modulo_dest = (CPU_INT08U  )((CPU_ADDR)pmem_08_dest % sizeof(CPU_ALIGN));
    mem_align_modulo_src  = (CPU_INT08U  )((CPU_ADDR)pmem_08_src  % sizeof(CPU_ALIGN));

    mem_aligned           = (mem_align_modulo_dest == mem_align_modulo_src) ? DEF_YES : DEF_NO;

    if (mem_aligned == DEF_YES) {                               /* If mem bufs' alignment offset equal, ...             */
                                                                /* ... optimize copy for mem buf alignment.             */
        if (mem_align_modulo_dest != 0) {                       /* If leading octets avail,                   ...       */
            i = mem_align_modulo_dest;
            while ((size_rem   >  0) &&                         /* ... start mem buf copy with leading octets ...       */
                   (i          <  sizeof(CPU_ALIGN ))) {        /* ... until next CPU_ALIGN word boundary.              */
               *pmem_08_dest++ = *pmem_08_src++;
                size_rem      -=  sizeof(CPU_INT08U);
                i++;
            }
        }

        pmem_align_dest = (CPU_ALIGN *)pmem_08_dest;            /* See Note #3a.                                        */
        pmem_align_src  = (CPU_ALIGN *)pmem_08_src;
        while (size_rem      >=  sizeof(CPU_ALIGN)) {           /* While mem bufs aligned on CPU_ALIGN word boundaries, */
           *pmem_align_dest++ = *pmem_align_src++;              /* ... copy psrc to pdest with CPU_ALIGN-sized words.   */
            size_rem         -=  sizeof(CPU_ALIGN);
        }

        pmem_08_dest = (CPU_INT08U *)pmem_align_dest;
        pmem_08_src  = (CPU_INT08U *)pmem_align_src;
    }

    while (size_rem > 0) {                                      /* For unaligned mem bufs or trailing octets, ...       */
       *pmem_08_dest++ = *pmem_08_src++;                        /* ... copy psrc to pdest by octets.                    */
        size_rem      -=  sizeof(CPU_INT08U);
    }
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Cmp()
*
* Description : Verify that ALL data octets in two memory buffers are identical in sequence.
*
* Argument(s) : p1_mem      Pointer to first  memory buffer.
*
*               p2_mem      Pointer to second memory buffer.
*
*               size        Number of data buffer octets to compare.
*
* Return(s)   : DEF_YES, if 'size' number of data octets are identical in both memory buffers.
*
*               DEF_NO,  otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null compares allowed (i.e. 0-octet size); 'DEF_YES' returned to indicate identical
*                   null compare.
*
*               (2) Many memory buffer comparisons vary ONLY in the least significant octets -- e.g.
*                   network address buffers.  Consequently, memory buffer comparison is more efficient
*                   if the comparison starts from the end of the memory buffers which will abort sooner
*                   on dissimilar memory buffers that vary only in the least significant octets.
*
*               (3) For best CPU performance, optimized to compare data buffers using 'CPU_ALIGN'-sized
*                   data words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (4) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus,
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                   mem_align_modulo arithmetic operation.
********************************************************************************************************
*/
/*$PAGE*/
CPU_BOOLEAN  Mem_Cmp (void        *p1_mem,
                      void        *p2_mem,
                      CPU_SIZE_T   size)
{
    CPU_SIZE_T    size_rem;
    CPU_ALIGN    *p1_mem_align;
    CPU_ALIGN    *p2_mem_align;
    CPU_INT08U   *p1_mem_08;
    CPU_INT08U   *p2_mem_08;
    CPU_INT08U    i;
    CPU_INT08U    mem_align_modulo_1;
    CPU_INT08U    mem_align_modulo_2;
    CPU_BOOLEAN   mem_aligned;
    CPU_BOOLEAN   mem_cmp;


    if (size < 1) {                                             /* See Note #1.                                         */
        return (DEF_YES);
    }
    if (p1_mem == (void *)0) {
        return (DEF_NO);
    }
    if (p2_mem == (void *)0) {
        return (DEF_NO);
    }


    mem_cmp            =  DEF_YES;                              /* Assume mem bufs are identical until cmp fails.       */
    size_rem           =  size;
                                                                /* Start @ end of mem bufs (see Note #2).               */
    p1_mem_08          = (CPU_INT08U *)p1_mem + size;
    p2_mem_08          = (CPU_INT08U *)p2_mem + size;
                                                                /* See Note #4.                                         */
    mem_align_modulo_1 = (CPU_INT08U  )((CPU_ADDR)p1_mem_08 % sizeof(CPU_ALIGN));
    mem_align_modulo_2 = (CPU_INT08U  )((CPU_ADDR)p2_mem_08 % sizeof(CPU_ALIGN));

    mem_aligned        = (mem_align_modulo_1 == mem_align_modulo_2) ? DEF_YES : DEF_NO;

    if (mem_aligned == DEF_YES) {                               /* If mem bufs' alignment offset equal, ...             */
                                                                /* ... optimize cmp for mem buf alignment.              */
        if (mem_align_modulo_1 != 0) {                          /* If trailing octets avail,                  ...       */
            i = mem_align_modulo_1;
            while ((mem_cmp == DEF_YES) &&                      /* ... cmp mem bufs while identical &         ...       */
                   (size_rem > 0)       &&                      /* ... start mem buf cmp with trailing octets ...       */
                   (i        > 0)) {                            /* ... until next CPU_ALIGN word boundary.              */
                p1_mem_08--;
                p2_mem_08--;
                if (*p1_mem_08 != *p2_mem_08) {                 /* If ANY data octet(s) NOT identical, cmp fails.       */
                     mem_cmp = DEF_NO;
                }
                size_rem -= sizeof(CPU_INT08U);
                i--;
            }
        }

        if (mem_cmp == DEF_YES) {                               /* If cmp still identical, cmp aligned mem bufs.        */
            p1_mem_align = (CPU_ALIGN *)p1_mem_08;              /* See Note #3a.                                        */
            p2_mem_align = (CPU_ALIGN *)p2_mem_08;

            while ((mem_cmp  == DEF_YES) &&                     /* Cmp mem bufs while identical & ...                   */
                   (size_rem >= sizeof(CPU_ALIGN))) {           /* ... mem bufs aligned on CPU_ALIGN word boundaries.   */
                p1_mem_align--;
                p2_mem_align--;
                if (*p1_mem_align != *p2_mem_align) {           /* If ANY data octet(s) NOT identical, cmp fails.       */
                     mem_cmp = DEF_NO;
                }
                size_rem -= sizeof(CPU_ALIGN);
            }

            p1_mem_08 = (CPU_INT08U *)p1_mem_align;
            p2_mem_08 = (CPU_INT08U *)p2_mem_align;
        }
    }

    while ((mem_cmp == DEF_YES) &&                              /* Cmp mem bufs while identical ...                     */
           (size_rem > 0)) {                                    /* ... for unaligned mem bufs or trailing octets.       */
        p1_mem_08--;
        p2_mem_08--;
        if (*p1_mem_08 != *p2_mem_08) {                         /* If ANY data octet(s) NOT identical, cmp fails.       */
             mem_cmp = DEF_NO;
        }
        size_rem -= sizeof(CPU_INT08U);
    }

    return (mem_cmp);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolCreate()
*
* Description : (1) Create a memory pool :
*
*                   (a) Create    memory pool from heap or dedicated memory
*                   (b) Allocate  memory pool memory blocks
*                   (c) Update    memory pool table
*                   (d) Configure memory pool
*
*
*               (2) Memory pools are indexed by the Memory Segments they use.
*
*                   (a) The memory pool table is composed by a two-dimensional list :
*
*                       (1) Memory segments manage the following memory segment/pool information :
*
*                           (A) Memory segment base           address
*                           (B) Memory segment next available address
*                           (C) Memory segment total     size
*                           (D) Memory segment remaining size
*
*                       (2) Memory pools share memory from memory segments but do NOT manage any memory
*                           segment information.  To access the memory segment information, the head
*                           memory segment must be accessed.
*
*                   (b) In the diagram below, memory pools in vertical columns represent they share the same
*                       memory segment for the memory blocks they have.  The heads of the memory pool are
*                       linked horizontally to form a memory pool table.
*
*                       (1) 'Mem_PoolTbl' points to the head of the Memory Pool table.
*
*                       (2) Memory Pools' 'SegPrevPtr'  & 'SegNextPtr'  doubly-link each memory segment to
*                           form the list of memory segments.
*
*                       (3) Memory Pools' 'PoolPrevPtr' & 'PoolNextPtr' doubly-link the  memory pools of
*                           each memory segment.
*
*                   (c) New memory pools, which do not share a memory segment, are inserted in the Memory
*                       Segments Primary List.  The point of insertion is such to keep ascended order by
*                       memory segment base address.
*
*                   (d) Memory pool pointers to memory blocks 'PoolPtrs' must be allocated for each created
*                       memory pool.  These pointers are stored in the memory pool heap segment 'Mem_PoolHeap'.
*
*                       (1) A memory pool can also have its memory blocks allocated from the memory pool heap.
*                           'pmem_base_addr' must be set to NULL & 'mem_size' must be set to (0) to create the
*                           memory pool.
*
*
*                                        |                                                                 |
*                                        |<----------------------- Memory Segments ----------------------->|
*                                        |                         (see Note #2a1)                         |
*
*                                 Lowest Memory Segment                                      Highest Memory Segment
*                                     Base Address                                                Base Address
*                                    (see Note #2c)                                              (see Note #2c)
*
*                                           |             SegNextPtr             Heap Memory Pool       |
*                                           |          (see Note #2b2)            (see Note #2d)        |
*                                           |                     |                                     |
*                                           v                     |                      |              v
*                                                                 |                      v
*        ---          Head of Memory     -------        -------   v    -------        -------        -------
*         ^             Pool Table   --->|     |------->|     |------->|     |------->|     |------->|     |
*         |          (see Note #2b1)     |     |        |     |        |     |        |  H  |        |     |
*         |                              |     |<-------|     |<-------|     |<-------|  E  |<-------|     |
*         |                              |     |        |     |   ^    |     |        |  A  |        |     |
*         |                              |     |        |     |   |    |     |        |  P  |        |     |
*         |                              |     |        |     |   |    |     |        |     |        |     |
*         |                              -------        -------   |    -------        -------        -------
*         |                                | ^                    |      | ^
*         |                                | |            SegPrevPtr     | |
*         |                                v |         (see Note #2b2)   v |
*         |                              -------                       -------
*                                        |     |                       |     |
*    Memory Pools                        |     |                       |     |
*  (see Note #2a2)                       |     |                       |     |
*                                        |     |                       |     |
*         |                              |     |                       |     |
*         |                              -------                       -------
*         |                                | ^
*         |               PoolNextPtr ---> | | <--- PoolPrevPtr
*         |             (see Note #2b3)    v |    (see Note #2b3)
*         |                              -------
*         |                              |     |
*         |                              |     |
*         |                              |     |
*         |                              |     |
*         v                              |     |
*        ---                             -------
*
*$PAGE*
* Argument(s) : pmem_pool           Pointer to a memory pool structure to create (see Note #3).
*
*               pmem_base_addr      Memory pool base address :
*
*                                       (a)     Null address    Memory pool allocated from general-purpose heap.
*                                       (b) Non-null address    Memory pool allocated from dedicated memory
*                                                                   specified by its base address.
*
*               mem_size            Size      of memory pool segment              (in octets).
*
*               blk_nbr             Number    of memory pool blocks to initialize.
*
*               blk_size            Size      of memory pool blocks to initialize (in octets).
*
*               blk_align           Alignment of memory pool blocks to initialize (in octets).
*
*               poctets_reqd        Pointer to a variable to ... :
*
*                                       (a) Return the number of octets required to successfully
*                                               allocate the memory pool, if any errors;
*                                       (b) Return 0, otherwise.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                    Memory pool successfully created.
*                               LIB_MEM_ERR_NULL_PTR                Argument 'pmem_pool' passed a NULL
*                                                                       pointer.
*
*                               LIB_MEM_ERR_HEAP_NOT_FOUND          Heap   segment NOT found.
*                               LIB_MEM_ERR_HEAP_EMPTY              Heap   segment empty; NO available memory
*                                                                       from heap.
*                               LIB_MEM_ERR_SEG_EMPTY               Memory segment empty; NO available memory
*                                                                       from segment for memory pools.
*
*                               LIB_MEM_ERR_INVALID_SEG_SIZE        Invalid memory segment size.
*                               LIB_MEM_ERR_INVALID_SEG_OVERLAP     Memory segment overlaps other memory
*                                                                       segment(s) in memory pool table.
*                               LIB_MEM_ERR_INVALID_BLK_NBR         Invalid memory pool number of blocks.
*                               LIB_MEM_ERR_INVALID_BLK_SIZE        Invalid memory pool block size.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (3) 'pmem_pool' MUST be passed a pointer to the address of a declared 'MEM_POOL' variable.
*
*               (4) Pointers to variables that return values MUST be initialized to return PRIOR to all
*                   other validation or function handling in case of any error(s).
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
void  Mem_PoolCreate (MEM_POOL    *pmem_pool,
                      void        *pmem_base_addr,
                      CPU_SIZE_T   mem_size,
                      CPU_SIZE_T   blk_nbr,
                      CPU_SIZE_T   blk_size,
                      CPU_SIZE_T   blk_align,
                      CPU_SIZE_T  *poctets_reqd,
                      LIB_ERR     *perr)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
    CPU_SR        cpu_sr;
#endif
    MEM_POOL     *pmem_pool_heap;
    MEM_POOL     *pmem_pool_prev;
    MEM_POOL     *pmem_pool_next;
    MEM_POOL     *pmem_pool_blk;
    void        **ppool_ptr;
    void         *pmem_blk;
    CPU_INT08U   *pmem_addr_ptrs;
    CPU_INT08U   *pmem_addr_pool;
    CPU_INT08U   *pmem_base_addr_start;
    CPU_INT08U   *pmem_base_addr_end;
    CPU_INT08U   *pmem_seg_addr_start;
    CPU_INT08U   *pmem_seg_addr_end;
    CPU_SIZE_T    size_tot;
    CPU_SIZE_T    size_tot_ptrs;
    CPU_SIZE_T    size_tot_pool;
    CPU_SIZE_T    size_rem;
    CPU_SIZE_T    size_pool_ptrs;
    CPU_SIZE_T    i;


/*$PAGE*/
                                                                    /* Init octets req'd for err (see Note #4).         */
    if (poctets_reqd != (CPU_SIZE_T *)0) {
       *poctets_reqd  = (CPU_SIZE_T  )0;
    }


                                                                    /* -------------- VALIDATE MEM POOL --------------- */
    if (pmem_pool != (MEM_POOL *)0) {
                                                                    /* Init mem pool     for err (see Note #4).         */
        pmem_pool->Type             = (LIB_MEM_TYPE)LIB_MEM_TYPE_NONE;
        pmem_pool->SegPrevPtr       = (MEM_POOL   *)0;
        pmem_pool->SegNextPtr       = (MEM_POOL   *)0;
        pmem_pool->PoolPrevPtr      = (MEM_POOL   *)0;
        pmem_pool->PoolNextPtr      = (MEM_POOL   *)0;
        pmem_pool->PoolAddrStart    = (void       *)0;
        pmem_pool->PoolAddrEnd      = (void       *)0;
        pmem_pool->PoolPtrs         = (void      **)0;
        pmem_pool->PoolSize         = (CPU_SIZE_T  )0;
        pmem_pool->BlkAlign         = (CPU_SIZE_T  )0;
        pmem_pool->BlkSize          = (CPU_SIZE_T  )0;
        pmem_pool->BlkNbr           = (CPU_SIZE_T  )0;
        pmem_pool->BlkIx            = (MEM_POOL_IX )0;
        pmem_pool->SegAddr          = (void       *)0;
        pmem_pool->SegAddrNextAvail = (void       *)0;
        pmem_pool->SegSizeTot       = (CPU_SIZE_T  )0;
        pmem_pool->SegSizeRem       = (CPU_SIZE_T  )0;

    } else {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }


    if (pmem_base_addr != (void *)0) {
        if (mem_size < 1) {
           *perr = LIB_MEM_ERR_INVALID_SEG_SIZE;
            return;
        }
    }

    if (blk_nbr < 1) {
       *perr = LIB_MEM_ERR_INVALID_BLK_NBR;
        return;
    }

    if (blk_size < 1) {
       *perr = LIB_MEM_ERR_INVALID_BLK_SIZE;
        return;
    }

    if (blk_align < 1) {
        blk_align = 1;
    }

                                                                    /* ------------ VALIDATE MEM POOL TBL ------------- */
    if (Mem_PoolTbl == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_HEAP_NOT_FOUND;
        return;
    }



/*$PAGE*/
                                                                    /* ---------------- CREATE MEM POOL --------------- */
    pmem_pool_heap = (MEM_POOL *)&Mem_PoolHeap;

    CPU_CRITICAL_ENTER();

    if (pmem_base_addr == (void *)0) {                              /* If no base addr, cfg mem pool from heap.         */
        pmem_pool_blk   =  pmem_pool_heap;
        pmem_pool_prev  =  pmem_pool_heap;
        pmem_pool_next  =  pmem_pool_heap;

                                                                    /* Calc tot mem   size for mem pool ptrs.           */
        pmem_addr_ptrs  = (CPU_INT08U *)pmem_pool_heap->SegAddrNextAvail;
        size_tot_ptrs   =  Mem_PoolSegCalcTotSize((void     *)pmem_addr_ptrs,
                                                  (CPU_SIZE_T)blk_nbr,
                                                  (CPU_SIZE_T)sizeof(void *),
                                                  (CPU_SIZE_T)sizeof(void *));
                                                                    /* Calc tot mem   size for mem blks.                */
        pmem_addr_pool  =  pmem_addr_ptrs + size_tot_ptrs;          /* Adj next avail addr for mem pool blks.           */
        size_tot_pool   =  Mem_PoolSegCalcTotSize((void     *)pmem_addr_pool,
                                                  (CPU_SIZE_T)blk_nbr,
                                                  (CPU_SIZE_T)blk_size,
                                                  (CPU_SIZE_T)blk_align);

        size_tot = size_tot_ptrs + size_tot_pool;
        size_rem = pmem_pool_heap->SegSizeRem;

        if (size_tot > size_rem) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_EMPTY;

            if (poctets_reqd != (CPU_SIZE_T *)0) {
               *poctets_reqd  =  size_tot - size_rem;
            }
            return;
        }


    } else {                                                        /* Else cfg mem pool from dedicated mem.            */

        pmem_base_addr_start = (CPU_INT08U *)pmem_base_addr;
        pmem_base_addr_end   = (CPU_INT08U *)pmem_base_addr + mem_size - 1;

        pmem_pool_blk        = (MEM_POOL *)0;
        pmem_pool_prev       = (MEM_POOL *)0;
        pmem_pool_next       =  Mem_PoolTbl;

        while (pmem_pool_next != (MEM_POOL *)0) {                   /* Srch tbl for mem seg with same base addr/size.   */

            if ((pmem_base_addr == pmem_pool_next->SegAddr) &&
                (mem_size       == pmem_pool_next->SegSizeTot)) {

                 pmem_pool_blk   = pmem_pool_next;
                 pmem_pool_prev  = pmem_pool_next;
                 break;

            } else {
                pmem_seg_addr_start = (CPU_INT08U *)pmem_pool_next->SegAddr;
                pmem_seg_addr_end   = (CPU_INT08U *)pmem_pool_next->SegAddr + pmem_pool_next->SegSizeTot - 1;

                                                                    /* Seg not found.                                   */
                if (pmem_base_addr_end < pmem_seg_addr_start) {
                    break;

                                                                    /* New mem seg overlaps cur mem seg.                */
                } else if (((pmem_base_addr_start <= pmem_seg_addr_start)  &&
                            (pmem_base_addr_end   >= pmem_seg_addr_start)) ||
                           ((pmem_base_addr_start >= pmem_seg_addr_start)  &&
                            (pmem_base_addr_end   <= pmem_seg_addr_end  )) ||
                           ((pmem_base_addr_start <= pmem_seg_addr_end  )  &&
                            (pmem_base_addr_end   >= pmem_seg_addr_end  ))) {
                    CPU_CRITICAL_EXIT();
                   *perr = LIB_MEM_ERR_INVALID_SEG_OVERLAP;
                    return;
                }
            }
                                                                    /* If mem seg NOT found, adv to next mem seg.       */
            pmem_pool_prev = pmem_pool_next;
            pmem_pool_next = pmem_pool_next->SegNextPtr;
        }

        if (pmem_pool_blk == (MEM_POOL *)0) {                       /* If mem seg NOT found, add    new  mem seg.       */
            pmem_pool_blk               = pmem_pool;
            pmem_pool->SegAddr          = pmem_base_addr;
            pmem_pool->SegAddrNextAvail = pmem_base_addr;
            pmem_pool->SegSizeTot       = mem_size;
            pmem_pool->SegSizeRem       = mem_size;
        }

/*$PAGE*/
                                                                    /* Calc tot mem size for mem pool ptrs.             */
        pmem_addr_ptrs = (CPU_INT08U *)pmem_pool_heap->SegAddrNextAvail;
        size_tot_ptrs  =  Mem_PoolSegCalcTotSize((void     *)pmem_addr_ptrs,
                                                 (CPU_SIZE_T)blk_nbr,
                                                 (CPU_SIZE_T)sizeof(void *),
                                                 (CPU_SIZE_T)sizeof(void *));
        size_rem       =  pmem_pool_heap->SegSizeRem;

        if (size_tot_ptrs > size_rem) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_EMPTY;

            if (poctets_reqd != (CPU_SIZE_T *)0) {
               *poctets_reqd  =  size_tot_ptrs - size_rem;
            }
            return;
        }

                                                                    /* Calc tot mem size for mem blks.                  */
        pmem_addr_pool = (CPU_INT08U *)pmem_pool_blk->SegAddrNextAvail;
        size_tot_pool  =  Mem_PoolSegCalcTotSize((void     *)pmem_addr_pool,
                                                 (CPU_SIZE_T)blk_nbr,
                                                 (CPU_SIZE_T)blk_size,
                                                 (CPU_SIZE_T)blk_align);
        size_rem       =  pmem_pool_blk->SegSizeRem;

        if (size_tot_pool > size_rem) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_SEG_EMPTY;

            if (poctets_reqd != (CPU_SIZE_T *)0) {
               *poctets_reqd  =  size_tot_pool - size_rem;
            }
            return;
        }
    }


                                                                    /* ---------------- ALLOC MEM BLKs ---------------- */
    size_pool_ptrs =  blk_nbr * sizeof(void *);
                                                                    /* Alloc stk of ptrs for mem blks from heap.        */
    ppool_ptr      = (void **)Mem_PoolSegAlloc((MEM_POOL *)pmem_pool_heap,
                                               (CPU_SIZE_T)size_pool_ptrs,
                                               (CPU_SIZE_T)sizeof(void *));

    for (i = 0; i < blk_nbr; i++) {                                 /* Alloc mem blks from blk seg ptr.                 */
        pmem_blk = (void *)Mem_PoolSegAlloc(pmem_pool_blk, blk_size, blk_align);
        if (pmem_blk == (void *)0) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_SEG_EMPTY;
            return;
        }
        ppool_ptr[i] = pmem_blk;
    }


/*$PAGE*/
                                                                    /* ------------- UPDATE MEM POOL TBL -------------- */
    if (pmem_pool_prev == pmem_pool_next) {                         /* Add new mem seg  to list.                        */

        pmem_pool_next             = pmem_pool_blk->PoolNextPtr;
        pmem_pool->PoolPrevPtr     = pmem_pool_blk;
        pmem_pool->PoolNextPtr     = pmem_pool_next;
        pmem_pool_blk->PoolNextPtr = pmem_pool;
        if (pmem_pool_next != (MEM_POOL *)0) {
            pmem_pool_next->PoolPrevPtr = pmem_pool;
        }

    } else {                                                        /* Add new mem pool to mem seg.                     */

        pmem_pool->SegPrevPtr = pmem_pool_prev;
        pmem_pool->SegNextPtr = pmem_pool_next;

        if (pmem_pool_prev != (MEM_POOL *)0) {                      /* Update prev mem pool link.                       */
            pmem_pool_prev->SegNextPtr = pmem_pool;
        } else {
            Mem_PoolTbl                = pmem_pool;                 /* Update      mem pool head.                       */
        }

        if (pmem_pool_next != (MEM_POOL *)0) {                      /* Update next mem pool link.                       */
            pmem_pool_next->SegPrevPtr = pmem_pool;
        }
    }


                                                                    /* ----------------- CFG MEM POOL ----------------- */
    pmem_pool->Type          = (LIB_MEM_TYPE) LIB_MEM_TYPE_POOL;
    pmem_pool->PoolAddrStart = (void       *) pmem_addr_pool;
    pmem_pool->PoolAddrEnd   = (void       *)(pmem_addr_pool + size_tot_pool - 1);
    pmem_pool->PoolPtrs      = (void      **) ppool_ptr;
    pmem_pool->PoolSize      = (CPU_SIZE_T  ) size_tot_pool;
    pmem_pool->BlkAlign      = (CPU_SIZE_T  ) blk_align;
    pmem_pool->BlkSize       = (CPU_SIZE_T  ) blk_size;
    pmem_pool->BlkNbr        = (CPU_SIZE_T  ) blk_nbr;
    pmem_pool->BlkIx         = (MEM_POOL_IX ) blk_nbr;


    CPU_CRITICAL_EXIT();

   *perr = LIB_MEM_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolBlkGet()
*
* Description : Get a memory block from memory pool.
*
* Argument(s) : pmem_pool   Pointer to  memory pool to get memory block from.
*
*               size        Size of requested memory (in octets).
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                   Memory block successfully returned.
*                               LIB_MEM_ERR_NONE_AVAIL          NO memory blocks available in memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_BLK_SIZE    Invalid memory pool block size requested.
*                               LIB_MEM_ERR_INVALID_BLK_IX      Invalid memory pool block index.
*
* Return(s)   : Pointer to memory block, if NO errors.
*
*               Pointer to NULL,         otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
void  *Mem_PoolBlkGet (MEM_POOL    *pmem_pool,
                       CPU_SIZE_T   size,
                       LIB_ERR     *perr)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
    CPU_SR   cpu_sr;
#endif
    void    *pmem_blk;


    if (pmem_pool == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return ((void *)0);
    }

    CPU_CRITICAL_ENTER();
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return ((void *)0);
    }

    if (size > pmem_pool->BlkSize) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_SIZE;
        return ((void *)0);
    }

    if (pmem_pool->BlkIx < 1) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_NONE_AVAIL;
        return ((void *)0);
    }

    if (pmem_pool->BlkIx > pmem_pool->BlkNbr) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_IX;
        return ((void *)0);
    }

    pmem_pool->BlkIx--;
    pmem_blk = pmem_pool->PoolPtrs[pmem_pool->BlkIx];

    CPU_CRITICAL_EXIT();

   *perr =  LIB_MEM_ERR_NONE;

    return (pmem_blk);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolBlkFree()
*
* Description : Free a memory block to memory pool.
*
* Argument(s) : pmem_pool   Pointer to memory pool to free memory block.
*
*               pmem_blk    Pointer to memory block address to free.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                    Memory block successfully freed.
*                               LIB_MEM_ERR_POOL_FULL           ALL memory blocks already available in
*                                                                   memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool'/'pmem_blk' passed
*                                                                   a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_ADDR        Invalid memory pool address.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
void  Mem_PoolBlkFree (MEM_POOL  *pmem_pool,
                       void      *pmem_blk,
                       LIB_ERR   *perr)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
    CPU_SR       cpu_sr;
#endif
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    CPU_BOOLEAN  addr_valid;
    MEM_POOL_IX  i;
#endif


    if (pmem_pool == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }

    if (pmem_blk == (void *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }

    CPU_CRITICAL_ENTER();
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return;
    }

    if (pmem_pool->BlkIx >= pmem_pool->BlkNbr) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_POOL_FULL;
        return;
    }

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    addr_valid = Mem_PoolBlkIsValidAddr(pmem_pool, pmem_blk);
    if (addr_valid != DEF_OK) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_ADDR;
        return;
    }

    for (i = 0; i < pmem_pool->BlkIx; i++) {
        if (pmem_blk == pmem_pool->PoolPtrs[i]) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_INVALID_ADDR;
            return;
        }
    }
#endif

    pmem_pool->PoolPtrs[pmem_pool->BlkIx] = pmem_blk;
    pmem_pool->BlkIx++;

    CPU_CRITICAL_EXIT();

   *perr = LIB_MEM_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      Mem_PoolSegCalcTotSize()
*
* Description : (1) Calculates total memory segment size for number of blocks with specific size & alignment :
*
*
*                       -----                     ======================  ---
*                         ^       Mem Addr  --->  |  /  /  /  /  /  /  |   ^
*                         |    (see Note #1a)     | /  /  /  /  /  /  /|   |    Mem Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1e & #2a)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |     Mem Blk #1     |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         |                       |                    |   v
*                         |                       ----------------------  ---
*                         |                       |  /  /  /  /  /  /  |   ^
*                         |                       | /  /  /  /  /  /  /|   |    Blk Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1f & #2b)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                                                 |         .          |
*                     Total Size                  |         .          |
*                   (see Note #2c)                |         .          |
*                                                 ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |   Mem Blk #N - 1   |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         |                       |                    |   v
*                         |                       ----------------------  ---
*                         |                       |  /  /  /  /  /  /  |   ^
*                         |                       | /  /  /  /  /  /  /|   |    Blk Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1f & #2b)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |     Mem Blk #N     |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         v                       |                    |   v
*                       -----                     ======================  ---
*
*               where
*
*                   (a) Mem Addr            Memory address of the beginning of the memory block ('pmem_addr')
*
*                   (b) N                   Number of memory blocks to allocate ('blk_nbr')
*
*                   (c) Blk Size            Size   of memory block  to allocate ('blk_size')
*
*                   (d) Align               Required block memory alignment     ('blk_align')
*
*                   (e) Mem Align Offset    Offset required to align first memory block
*
*                   (f) Blk Align Offset    Offset required to align every memory block
*
*
*               (2) The total size is calculated based on the following equations :
*
*                                            { (1) Align - (Mem Addr % Align) , if memory address is not aligned
*                   (a) Mem Align Offset  =  {
*                                            { (2) 0                          , if memory address is     aligned
*
*
*                                            { (1) Align - (Size     % Align) , if memory block   is not aligned
*                   (b) Blk Align Offset  =  {
*                                            { (2) 0                          , if memory block   is     aligned
*
*
*                   (c) Total Size        =   Mem Align Offset
*                                         + ((Blk Size + Blk Align Offset) * (N - 1))
*                                         +   Blk Size
*
*$PAGE*
* Argument(s) : pmem_addr   Memory address of the beginning of the memory block.
*
*               blk_nbr     Number of memory blocks to allocate.
*
*               blk_size    Size   of memory block  to allocate.
*
*               blk_align   Required block memory alignment (in octets).
*               ---------   Argument validated in Mem_PoolCreate().
*
* Return(s)   : Total size of memory segment used to allocate the number of blocks.
*
* Caller(s)   : Mem_PoolCreate().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
static  CPU_SIZE_T  Mem_PoolSegCalcTotSize (void        *pmem_addr,
                                            CPU_SIZE_T   blk_nbr,
                                            CPU_SIZE_T   blk_size,
                                            CPU_SIZE_T   blk_align)
{
    CPU_SIZE_T  align_offset;
    CPU_SIZE_T  mem_align_offset;
    CPU_SIZE_T  blk_align_offset;
    CPU_SIZE_T  size_tot;

                                                                    /* Calc mem align (see Note #2a).                   */
    align_offset = (CPU_ADDR)pmem_addr % blk_align;
    if (align_offset != 0) {
        mem_align_offset = blk_align - align_offset;
    } else {
        mem_align_offset = 0;
    }
                                                                    /* Calc blk align (see Note #2b).                   */
    align_offset = blk_size % blk_align;
    if (align_offset != 0) {
        blk_align_offset = blk_align - align_offset;
    } else {
        blk_align_offset = 0;
    }
                                                                    /* Calc tot size  (see Note #2c).                   */
    size_tot = mem_align_offset + ((blk_size + blk_align_offset) * (blk_nbr - 1)) + blk_size;

    return (size_tot);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                      Mem_PoolBlkIsValidAddr()
*
* Description : Calculates if a given memory block address is valid for the memory pool.
*
* Argument(s) : pmem_pool   Pointer to memory pool structure to validate memory block address.
*               ---------   Argument validated in Mem_PoolBlkFree().
*
*               pmem_blk    Pointer to memory block address to validate.
*               --------    Argument validated in Mem_PoolBlkFree().
*
* Return(s)   : DEF_YES, if valid memory pool block address.
*
*               DEF_NO,  otherwise.
*
* Caller(s)   : Mem_PoolBlkFree().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if ((LIB_MEM_CFG_POOL_EN        == DEF_ENABLED) && \
     (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED))
static  CPU_BOOLEAN  Mem_PoolBlkIsValidAddr (MEM_POOL  *pmem_pool,
                                             void      *pmem_blk)
{
    CPU_INT08U   *ppool_addr_first;
    void         *ppool_addr_start;
    void         *ppool_addr_end;
    CPU_SIZE_T    align_offset;
    CPU_SIZE_T    blk_align;
    CPU_SIZE_T    blk_align_offset;
    CPU_SIZE_T    blk_size;
    CPU_SIZE_T    mem_align;
    CPU_SIZE_T    mem_align_offset;
    CPU_SIZE_T    mem_diff;
    CPU_BOOLEAN   addr_valid;


    ppool_addr_start = pmem_pool->PoolAddrStart;
    ppool_addr_end   = pmem_pool->PoolAddrEnd;

    if ((pmem_blk < ppool_addr_start) ||
        (pmem_blk > ppool_addr_end)) {
        return (DEF_NO);
    }

    blk_align      = (CPU_SIZE_T)pmem_pool->BlkAlign;
    align_offset   = (CPU_SIZE_T)((CPU_ADDR)ppool_addr_start % blk_align);
    if (align_offset != 0) {
        mem_align_offset = blk_align - align_offset;
    } else {
        mem_align_offset = 0;
    }

    blk_size     = pmem_pool->BlkSize;
    align_offset = blk_size % blk_align;
    if (align_offset != 0) {
        blk_align_offset = blk_align - align_offset;
    } else {
        blk_align_offset = 0;
    }

    ppool_addr_first = (CPU_INT08U *)((CPU_INT08U *)ppool_addr_start + mem_align_offset);
    mem_diff         = (CPU_SIZE_T  )((CPU_INT08U *)pmem_blk         - ppool_addr_first);
    mem_align        = (CPU_SIZE_T  )(              blk_size         + blk_align_offset);

    addr_valid       = ((mem_diff % mem_align) == 0) ? DEF_YES : DEF_NO;

    return (addr_valid);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Mem_PoolSegAlloc()
*
* Description : Allocates memory from specific segment.
*
* Argument(s) : pmem_pool   Pointer to memory pool structure containing segment information.
*               ---------   Argument validated in Mem_PoolCreate()
*
*               size        Size of memory to allocate.
*               ----        Argument validated in Mem_PoolCreate()
*
*               align       Required starting memory alignment (in octets).
*               -----       Argument validated in Mem_PoolCreate()
*
* Return(s)   : Pointer to allocated memory, if NO errors.
*
*               Pointer to NULL, otherwise.
*
* Caller(s)   : Mem_PoolCreate().
*
* Note(s)     : (1) Allocated memory from the specific segment is NEVER freed after allocation.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_POOL_EN == DEF_ENABLED)
static  void  *Mem_PoolSegAlloc  (MEM_POOL    *pmem_pool,
                                  CPU_SIZE_T   size,
                                  CPU_SIZE_T   align)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
    CPU_SR       cpu_sr;
#endif
    CPU_INT08U  *pmem_addr;
    CPU_SIZE_T   mem_align;
    CPU_SIZE_T   align_offset;
    CPU_SIZE_T   size_tot;
    CPU_SIZE_T   size_rem;


    CPU_CRITICAL_ENTER();
    pmem_addr = (CPU_INT08U *)pmem_pool->SegAddrNextAvail;

    mem_align = (CPU_SIZE_T  )((CPU_ADDR)pmem_addr % align);        /* Calc mem align.                                  */

    if (mem_align != 0) {
        align_offset = align - mem_align;
    } else {
        align_offset = 0;
    }

    size_tot = align_offset + size;
    size_rem = pmem_pool->SegSizeRem;

    if (size_tot > size_rem) {                                      /* If insufficiemt mem seg size rem, ...            */
        CPU_CRITICAL_EXIT();
        return ((void *)0);                                         /* ... rtn NULL.                                    */
    }

    pmem_addr                   += align_offset;                    /* Adj mem addr align.                              */

    pmem_pool->SegAddrNextAvail  = pmem_addr + size;                /* Adv next avail addr.                             */
    pmem_pool->SegSizeRem       -= size_tot;                        /* Adj rem mem seg size.                            */

    CPU_CRITICAL_EXIT();

    return ((void *)pmem_addr);
}
#endif

