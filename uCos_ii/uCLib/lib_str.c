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
*                                       ASCII STRING MANAGEMENT
*
* Filename      : lib_str.c
* Version       : V1.25
* Programmer(s) : ITJ
*                 JDH
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

#define    LIB_STR_MODULE
#include  <lib_str.h>


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


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Len()
*
* Description : Calculate length of a string.
*
* Argument(s) : pstr        Pointer to string (see Note #1).
*
* Return(s)   : Length of string; number of characters in string before terminating NULL character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) String length calculation terminates when :
*
*                   (a) String pointer points to NULL.
*                       (1) String buffer overlaps with NULL address.
*                       (2) String length calculated for string up to but NOT beyond or including
*                           the NULL address.
*
*                   (b) Terminating NULL character found.
*                       (1) String length calculated for string up to but NOT           including
*                           the NULL character.
*********************************************************************************************************
*/

CPU_SIZE_T  Str_Len (CPU_CHAR  *pstr)
{
    CPU_SIZE_T  len;


    len = 0;
    while (( pstr != (CPU_CHAR *)0) &&                          /* Calc str len until NULL ptr (see Note #2a) ...       */
           (*pstr != (CPU_CHAR  )0)) {                          /* ... or NULL char found      (see Note #2b).          */
        len++;
        pstr++;
    }

    return (len);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Copy()
*
* Description : Copy source string to destination string buffer.
*
* Argument(s) : pdest       Pointer to destination string buffer to receive source string copy (see Note #1).
*
*               psrc        Pointer to source      string to copy into destination string buffer.
*
* Return(s)   : Pointer to destination string, if NO errors (see Note #2).
*
*               Pointer to NULL,               otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (a) Destination buffer size MUST be large enough to accommodate the entire source 
*                       string size including the terminating NULL character.
*
*               (2) String copy terminates when :
*
*                   (a) Destination/Source string pointer(s) are passed NULL pointers.
*                       (1) No string copy performed; NULL pointer returned.
*
*                   (b) Destination/Source string pointer(s) points to NULL.
*                       (1) String buffer(s) overlap with NULL address.
*                       (2) Source string copied into destination string buffer up to but NOT beyond or
*                           including the NULL address; destination string buffer properly terminated
*                           with NULL character.
*
*                   (c) Source string's terminating NULL character found.
*                       (1) Entire source string copied into destination string buffer.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Copy (CPU_CHAR  *pdest,
                     CPU_CHAR  *psrc)
{
    CPU_CHAR  *pstr;
    CPU_CHAR  *pstr_next;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #2a).          */
    if (pdest == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }
    if (psrc  == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }


    pstr      = pdest;
    pstr_next = pstr;
    pstr_next++;
    while (( pstr_next != (CPU_CHAR *)0) &&                     /* Copy str until NULL ptr(s) (see Note #2b) ...        */
           ( psrc      != (CPU_CHAR *)0) &&
           (*psrc      != (CPU_CHAR  )0)) {                     /* ... or NULL char found     (see Note #2c).           */
       *pstr = *psrc;
        pstr++;
        pstr_next++;
        psrc++;
    }

   *pstr = (CPU_CHAR)0;                                         /* Append NULL char (see Note #2b2).                    */


    return (pdest);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            Str_Copy_N()
*
* Description : Copy source string to destination string buffer, up to a maximum number of characters.
*
* Argument(s) : pdest       Pointer to destination string buffer to receive source string copy (see Note #1).
*
*               psrc        Pointer to source      string to copy into destination string buffer.
*
*               len_max     Maximum number of characters to copy (see Note #2d).
*
* Return(s)   : Pointer to destination string, if NO errors (see Note #2).
*
*               Pointer to NULL,               otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (a) Destination buffer size MUST be large enough to accommodate the entire source 
*                       string size including the terminating NULL character.
*
*               (2) String copy terminates when :
*
*                   (a) Destination/Source string pointer(s) are passed NULL pointers.
*                       (1) No string copy performed; NULL pointer returned.
*
*                   (b) Destination/Source string pointer(s) points to NULL.
*                       (1) String buffer(s) overlap with NULL address.
*                       (2) Source string copied into destination string buffer up to but NOT beyond or
*                           including the NULL address; destination string buffer properly terminated
*                           with NULL character.
*
*                   (c) Source string's terminating NULL character found.
*                       (1) Entire source string copied into destination string buffer.
*
*                   (d) 'len_max' number of characters copied.
*                       (1) 'len_max' number of characters does NOT include the terminating NULL character.
*
*                           See also Note #1a.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Copy_N (CPU_CHAR    *pdest,
                       CPU_CHAR    *psrc,
                       CPU_SIZE_T   len_max)
{
    CPU_CHAR    *pstr;
    CPU_CHAR    *pstr_next;
    CPU_SIZE_T   len_copy;

                                                                /* Rtn NULL if str ptr(s) NULL      (see Note #2a).     */
    if (pdest == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }
    if (psrc  == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }

    if (len_max == (CPU_SIZE_T)0) {                             /* Rtn NULL if copy len equals zero (see Note #2d).     */
        return  ((CPU_CHAR *)0);
    }


    pstr      = pdest;
    pstr_next = pstr;
    pstr_next++;
    len_copy  = 0;

    while (( pstr_next != (CPU_CHAR *)0) &&                     /* Copy str until NULL ptr(s)  (see Note #2b)  ...      */
           ( psrc      != (CPU_CHAR *)0) &&
           (*psrc      != (CPU_CHAR  )0) &&                     /* ... or NULL char found      (see Note #2c); ...      */
           ( len_copy  <  (CPU_SIZE_T)len_max)) {               /* ... or max nbr chars copied (see Note #2d).          */
       *pstr = *psrc;
        pstr++;
        pstr_next++;
        psrc++;
        len_copy++;
    }

   *pstr = (CPU_CHAR)0;                                         /* Append NULL char (see Note #2b2).                    */


    return (pdest);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Cat()
*
* Description : Append concatenation string to destination string.
*
* Argument(s) : pdest       Pointer to destination   string to append concatenation  string (see Note #1).
*
*               pstr_cat    Pointer to concatenation string to append to destination string.
*
* Return(s)   : Pointer to destination string, if NO errors (see Note #2).
*
*               Pointer to NULL,               otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Destination string buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (a) Destination buffer size MUST be large enough to accommodate the entire concatenated
*                       string size including the terminating NULL character.
*
*               (2) String concatenation terminates when :
*
*                   (a) Destination/Concatenation string pointer(s) are passed NULL pointers.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (b) Destination string overlaps with NULL address.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (c) Destination/Concatenation string pointer(s) points to NULL.
*                       (1) String buffer(s) overlap with NULL address.
*                       (2) Concatenation string appended into destination string buffer up to but NOT
*                           beyond or including the NULL address; destination string buffer properly
*                           terminated with NULL character.
*
*                   (d) Concatenation string's terminating NULL character found.
*                       (1) Entire concatenation string appended to destination string.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Cat (CPU_CHAR  *pdest,
                    CPU_CHAR  *pstr_cat)
{
    CPU_CHAR  *pstr;
    CPU_CHAR  *pstr_next;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #2a).          */
    if (pdest == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }
    if (pstr_cat == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }


    pstr = pdest;
    while (( pstr != (CPU_CHAR *)0) &&                          /* Adv to end of cur dest str until NULL ptr ...        */
           (*pstr != (CPU_CHAR  )0)) {                          /* ... or NULL char found..                             */
        pstr++;
    }
    if (pstr == (CPU_CHAR *)0) {                                /* If NULL str overrun, rtn NULL (see Note #2b).        */
        return ((CPU_CHAR *)0);
    }

    pstr_next = pstr;
    pstr_next++;
    while (( pstr_next != (CPU_CHAR *)0) &&                     /* Cat str until NULL ptr(s) (see Note #2c) ...         */
           ( pstr_cat  != (CPU_CHAR *)0) &&
           (*pstr_cat  != (CPU_CHAR  )0)) {                     /* ... or NULL char found    (see Note #2d).            */
       *pstr = *pstr_cat;
        pstr++;
        pstr_next++;
        pstr_cat++;
    }

   *pstr = (CPU_CHAR)0;                                         /* Append NULL char (see Note #2c2).                    */


    return (pdest);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Cat_N()
*
* Description : Append concatenation string to destination string, up to a maximum number of characters.
*
* Argument(s) : pdest       Pointer to destination   string to append concatenation  string (see Note #1).
*
*               pstr_cat    Pointer to concatenation string to append to destination string.
*
*               len_max     Maximum number of characters to concatenate (see Note #2e).
*
* Return(s)   : Pointer to destination string, if NO errors (see Note #2).
*
*               Pointer to NULL,               otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Destination string buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (a) Destination buffer size MUST be large enough to accommodate the entire concatenated
*                       string size including the terminating NULL character.
*
*               (2) String concatenation terminates when :
*
*                   (a) Destination/Concatenation string pointer(s) are passed NULL pointers.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (b) Destination string overlaps with NULL address.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (c) Destination/Concatenation string pointer(s) points to NULL.
*                       (1) String buffer(s) overlap with NULL address.
*                       (2) Concatenation string appended into destination string buffer up to but NOT
*                           beyond or including the NULL address; destination string buffer properly
*                           terminated with NULL character.
*
*                   (d) Concatenation string's terminating NULL character found.
*                       (1) Entire concatenation string appended to destination string.
*
*                   (e) 'len_max' number of characters concatenated.
*                       (1) 'len_max' number of characters does NOT include the terminating NULL character.
*
*                           See also Note #1a.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Cat_N (CPU_CHAR    *pdest,
                      CPU_CHAR    *pstr_cat,
                      CPU_SIZE_T   len_max)
{
    CPU_CHAR    *pstr;
    CPU_CHAR    *pstr_next;
    CPU_SIZE_T   len_cat;

                                                                /* Rtn NULL if str ptr(s) NULL     (see Note #2a).      */
    if (pdest == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }
    if (pstr_cat == (CPU_CHAR *)0) {
        return  ((CPU_CHAR *)0);
    }

    if (len_max == (CPU_SIZE_T)0) {                             /* Rtn NULL if cat len equals zero (see Note #2e).      */
        return  ((CPU_CHAR *)0);
    }


    pstr = pdest;
    while (( pstr != (CPU_CHAR *)0) &&                          /* Adv to end of cur dest str until NULL ptr ...        */
           (*pstr != (CPU_CHAR  )0)) {                          /* ... or NULL char found..                             */
        pstr++;
    }
    if (pstr == (CPU_CHAR *)0) {                                /* If NULL str overrun, rtn NULL (see Note #2b).        */
        return ((CPU_CHAR *)0);
    }

    pstr_next = pstr;
    pstr_next++;
    len_cat   = 0;

    while (( pstr_next != (CPU_CHAR *)0) &&                     /* Cat str until NULL ptr(s)  (see Note #2c)  ...       */
           ( pstr_cat  != (CPU_CHAR *)0) &&
           (*pstr_cat  != (CPU_CHAR  )0) &&                     /* ... or NULL char found     (see Note #2d); ...       */
           ( len_cat   <  (CPU_SIZE_T)len_max)) {               /* ... or max nbr chars cat'd (see Note #2d).           */
       *pstr = *pstr_cat;
        pstr++;
        pstr_next++;
        pstr_cat++;
        len_cat++;
    }

   *pstr = (CPU_CHAR)0;                                         /* Append NULL char (see Note #2c2).                    */


    return (pdest);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Cmp()
*
* Description : Determine if two strings are identical.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
* Return(s)   : 0,              if strings are identical             (see Notes #2a, #2e, & #2f).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #2b, #2g, & #2d).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #2c, #2h, & #2d).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) String comparison terminates when :
*
*                   (a) BOTH string pointer(s) are passed NULL pointers.
*                       (1) NULL strings identical; return 0.
*
*                   (b) 'p1_str' passed a NULL pointer.
*                       (1) Return negative value of character pointed to by 'p2_str'.
*
*                   (c) 'p2_str' passed a NULL pointer.
*                       (1) Return positive value of character pointed to by 'p1_str'.
*
*                   (d) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str'
*                           from the character pointed to by 'p1_str'.
*
*                   (e) Terminating NULL character found in both strings.
*                       (1) Strings identical; return 0.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (f) BOTH strings point to NULL.
*                       (1) Strings overlap with NULL address.
*                       (2) Strings identical up to but NOT beyond or including the NULL address; return 0.
*
*                   (g) 'p1_str_next' points to NULL.
*                       (1) 'p1_str' overlaps with NULL address.
*                       (2) Strings compared up to but NOT beyond or including the NULL address.
*                       (3) Return  negative value of character pointed to by 'p2_str_next'.
*
*                   (h) 'p2_str_next' points to NULL.
*                       (1) 'p2_str' overlaps with NULL address.
*                       (2) Strings compared up to but NOT beyond or including the NULL address.
*                       (3) Return  positive value of character pointed to by 'p1_str_next'.
*
*               (3) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_INT16S  Str_Cmp (CPU_CHAR  *p1_str,
                     CPU_CHAR  *p2_str)
{
    CPU_CHAR    *p1_str_next;
    CPU_CHAR    *p2_str_next;
    CPU_INT16S   cmp_val;


    if (p1_str == (CPU_CHAR *)0) {
        if (p2_str == (CPU_CHAR *)0) {
            return ((CPU_INT16S)0);                             /* If BOTH str ptrs NULL, rtn 0 (see Note #2a).         */
        }
        cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str);
        return (cmp_val);                                       /* If p1_str NULL, rtn neg p2_str val (see Note #2b).   */
    }
    if (p2_str == (CPU_CHAR *)0) {
        cmp_val = (CPU_INT16S)(*p1_str);
        return (cmp_val);                                       /* If p2_str NULL, rtn pos p1_str val (see Note #2c).   */
    }


    p1_str_next = p1_str;
    p2_str_next = p2_str;
    p1_str_next++;
    p2_str_next++;
    while ((*p1_str      == *p2_str)       &&                   /* Cmp strs until non-matching char (see Note #2d) ..   */
           (*p1_str      != (CPU_CHAR  )0) &&                   /* .. or NULL char(s)               (see Note #2e) ..   */
           ( p1_str_next != (CPU_CHAR *)0) &&                   /* .. or NULL ptr(s) found (see Notes #2f, #2g, & #2h). */
           ( p2_str_next != (CPU_CHAR *)0)) {
        p1_str_next++;
        p2_str_next++;
        p1_str++;
        p2_str++;
    }


    if (*p1_str != *p2_str) {                                           /* If strs NOT identical, ...                   */
         cmp_val = (CPU_INT16S)(*p1_str) - (CPU_INT16S)(*p2_str);       /* ... calc & rtn char diff  (see Note #2d1).   */

    } else if (*p1_str == (CPU_CHAR)0) {                                /* If NULL char(s) found, ...                   */
         cmp_val = 0;                                                   /* ... strs identical; rtn 0 (see Note #2e).    */

    } else {
        if (p1_str_next == (CPU_CHAR *)0) {
            if (p2_str_next == (CPU_CHAR *)0) {                         /* If BOTH next str ptrs NULL, ...              */
                cmp_val = (CPU_INT16S)0;                                /* ... rtn 0                   (see Note #2f).  */
            } else {                                                    /* If p1_str_next NULL, ...                     */
                cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str_next);   /* ... rtn neg p2_str_next val (see Note #2g).  */
            }
        } else {                                                        /* If p2_str_next NULL, ...                     */
            cmp_val = (CPU_INT16S)(*p1_str_next);                       /* ... rtn pos p1_str_next val (see Note #2h).  */
        }
    }


    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Cmp_N()
*
* Description : Determine if two strings are identical for up to a maximum number of characters.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
*               len_max     Maximum number of characters to compare  (see Notes #2i & #2j).
*
* Return(s)   : 0,              if strings are identical             (see Notes #2a, #2e, #2f, #2i, & #2j).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #2b, #2g, & #2d).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #2c, #2h, & #2d).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) String comparison terminates when :
*
*                   (a) BOTH string pointer(s) are passed NULL pointers.
*                       (1) NULL strings identical; return 0.
*
*                   (b) 'p1_str' passed a NULL pointer.
*                       (1) Return negative value of character pointed to by 'p2_str'.
*
*                   (c) 'p2_str' passed a NULL pointer.
*                       (1) Return positive value of character pointed to by 'p1_str'.
*
*                   (d) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str'
*                           from the character pointed to by 'p1_str'.
*
*                   (e) Terminating NULL character found in both strings.
*                       (1) Strings identical; return 0.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (f) BOTH strings point to NULL.
*                       (1) Strings overlap with NULL address.
*                       (2) Strings identical up to but NOT beyond or including the NULL address; return 0.
*
*                   (g) 'p1_str_next' points to NULL.
*                       (1) 'p1_str' overlaps with NULL address.
*                       (2) Strings compared up to but NOT beyond or including the NULL address.
*                       (3) Return  negative value of character pointed to by 'p2_str_next'.
*
*                   (h) 'p2_str_next' points to NULL.
*                       (1) 'p2_str' overlaps with NULL address.
*                       (2) Strings compared up to but NOT beyond or including the NULL address.
*                       (3) Return  positive value of character pointed to by 'p1_str_next'.
*
*                   (i) 'len_max' passed a zero length.
*                       (1) Zero-length strings identical; return 0.
*
*                   (j) First 'len_max' number of characters identical.
*                       (1) Strings identical; return 0.
*
*               (3) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_INT16S  Str_Cmp_N (CPU_CHAR    *p1_str,
                       CPU_CHAR    *p2_str,
                       CPU_SIZE_T   len_max)
{
    CPU_CHAR    *p1_str_next;
    CPU_CHAR    *p2_str_next;
    CPU_INT16S   cmp_val;
    CPU_SIZE_T   cmp_len;


    if (len_max == 0) {                                         /* If cmp len equals zero, rtn 0      (see Note #2i).   */
        return ((CPU_INT16S)0);
    }

    if (p1_str == (CPU_CHAR *)0) {
        if (p2_str == (CPU_CHAR *)0) {
            return ((CPU_INT16S)0);                             /* If BOTH str ptrs NULL,  rtn 0      (see Note #2a).   */
        }
        cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str);
        return (cmp_val);                                       /* If p1_str NULL, rtn neg p2_str val (see Note #2b).   */
    }
    if (p2_str == (CPU_CHAR *)0) {
        cmp_val = (CPU_INT16S)(*p1_str);
        return (cmp_val);                                       /* If p2_str NULL, rtn pos p1_str val (see Note #2c).   */
    }


    p1_str_next = p1_str;
    p2_str_next = p2_str;
    p1_str_next++;
    p2_str_next++;
    cmp_len     = 0;
    while ((*p1_str      == *p2_str)       &&                   /* Cmp strs until non-matching char (see Note #2d) ..   */
           (*p1_str      != (CPU_CHAR  )0) &&                   /* .. or NULL char(s)               (see Note #2e) ..   */
           ( p1_str_next != (CPU_CHAR *)0) &&                   /* .. or NULL ptr(s) found (see Notes #2f, #2g, & #2h); */
           ( p2_str_next != (CPU_CHAR *)0) &&
           ( cmp_len     <  (CPU_SIZE_T)len_max)) {             /* .. or len nbr chars cmp'd        (see Note #2j).     */
        p1_str_next++;
        p2_str_next++;
        p1_str++;
        p2_str++;
        cmp_len++;
    }


    if (cmp_len == len_max) {                                           /* If strs     identical for len nbr of chars,  */
        return ((CPU_INT16S)0);                                         /* ... rtn 0 (see Note #2j).                    */
    }

    if (*p1_str != *p2_str) {                                           /* If strs NOT identical, ...                   */
         cmp_val = (CPU_INT16S)(*p1_str) - (CPU_INT16S)(*p2_str);       /* ... calc & rtn char diff  (see Note #2d1).   */

    } else if (*p1_str == (CPU_CHAR)0) {                                /* If NULL char(s) found, ...                   */
         cmp_val = 0;                                                   /* ... strs identical; rtn 0 (see Note #2e).    */

    } else {
        if (p1_str_next == (CPU_CHAR *)0) {
            if (p2_str_next == (CPU_CHAR *)0) {                         /* If BOTH next str ptrs NULL, ...              */
                cmp_val = (CPU_INT16S)0;                                /* ... rtn 0                   (see Note #2f).  */
            } else {                                                    /* If p1_str_next NULL, ...                     */
                cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str_next);   /* ... rtn neg p2_str_next val (see Note #2g).  */
            }
        } else {                                                        /* If p2_str_next NULL, ...                     */
            cmp_val = (CPU_INT16S)(*p1_str_next);                       /* ... rtn pos p1_str_next val (see Note #2h).  */
        }
    }


    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Char()
*
* Description : Search string for first occurrence of specific character.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to first occurrence of search character in string, if any.
*
*               Pointer to NULL,                                           otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address.
*                       (2) String searched up to but NOT beyond or including the NULL address.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned.
*                       (2) Applicable ONLY IF search character is NOT the terminating NULL character.
*
*                   (d) Search character found.
*                       (1) Return pointer to first occurrence of search character in search string.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char (CPU_CHAR  *pstr,
                     CPU_CHAR   srch_char)
{
    CPU_CHAR  *pstr_next;


    if (pstr == (CPU_CHAR *)0) {                                /* Rtn NULL if srch str ptr NULL (see Note #2a).        */
        return ((CPU_CHAR *)0);
    }


    pstr_next = pstr;
    pstr_next++;
    while (( pstr_next != (CPU_CHAR *)0) &&                     /* Srch str until NULL ptr(s) (see Note #2b) ...        */
           (*pstr      != (CPU_CHAR  )0) &&                     /* ... or NULL char           (see Note #2c) ...        */
           (*pstr      != (CPU_CHAR  )srch_char)) {             /* ... or srch char found     (see Note #2d).           */
        pstr++;
        pstr_next++;
    }


    if (*pstr != srch_char) {                                   /* If srch char NOT found, str points to NULL; ...      */
        return ((CPU_CHAR *)0);                                 /* ... rtn NULL (see Notes #2b & #2c).                  */
    }

    return (pstr);                                              /* Else rtn ptr to found srch char (see Note #2d).      */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            Str_Char_N()
*
* Description : Search string for first occurrence of specific character, up to a maximum number of characters.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               len_max         Maximum number of characters to search (see Notes #2e & #3).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to first occurrence of search character in string, if any.
*
*               Pointer to NULL,                                           otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address.
*                       (2) String searched up to but NOT beyond or including the NULL address.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned.
*                       (2) Applicable ONLY IF search character is NOT the terminating NULL character.
*
*                   (d) Search character found.
*                       (1) Return pointer to first occurrence of search character in search string.
*
*                   (e) 'len_max' number of characters searched.
*                       (1) 'len_max' number of characters does NOT include terminating NULL character.
*
*               (3) Ideally, the 'len_max' parameter would be the last parameter in this function's
*                   paramter list for consistency with all other custom string library functions.
*                   However, the 'len_max' parameter is ordered to comply with the standard library
*                   function's parameter list.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char_N (CPU_CHAR    *pstr,
                       CPU_SIZE_T   len_max,
                       CPU_CHAR     srch_char)
{
    CPU_CHAR    *pstr_next;
    CPU_SIZE_T   len_srch;


    if (pstr == (CPU_CHAR *)0) {                                /* Rtn NULL if srch str ptr NULL    (see Note #2a).     */
        return ((CPU_CHAR *)0);
    }

    if (len_max == (CPU_SIZE_T)0) {                             /* Rtn NULL if srch len equals zero (see Note #2e).     */
        return ((CPU_CHAR *)0);
    }


    pstr_next = pstr;
    pstr_next++;
    len_srch  = 0;
    while (( pstr_next != (CPU_CHAR *)0)         &&             /* Srch str until NULL ptr(s)  (see Note #2b)  ...      */
           (*pstr      != (CPU_CHAR  )0)         &&             /* ... or NULL char            (see Note #2c)  ...      */
           (*pstr      != (CPU_CHAR  )srch_char) &&             /* ... or srch char found      (see Note #2d); ...      */
           ( len_srch  <  (CPU_SIZE_T)len_max)) {               /* ... or max nbr chars srch'd (see Note #2e).          */
        pstr++;
        pstr_next++;
        len_srch++;
    }


    if (*pstr != srch_char) {                                   /* If srch char NOT found, str points to NULL; ...      */
        return ((CPU_CHAR *)0);                                 /* ... rtn NULL (see Notes #2b & #2c).                  */
    }

    return (pstr);                                              /* Else rtn ptr to found srch char (see Note #2d).      */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Str_Char_Last()
*
* Description : Search string for last occurrence of specific character.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to last occurrence of search character in string, if any.
*
*               Pointer to NULL,                                          otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address.
*                       (2) String searched up to but NOT beyond or including the NULL address.
*                       (3) NULL address boundary handled in Str_Len().
*
*                   (c) String searched from end to beginning.
*                       (1) Search character NOT found in search string; NULL pointer returned.
*                       (2) Applicable ONLY IF search character is NOT the terminating NULL character.
*
*                   (d) Search character found.
*                       (1) Return pointer to first occurrence of search character in search string.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char_Last (CPU_CHAR  *pstr,
                          CPU_CHAR   srch_char)
{
    CPU_CHAR    *pstr_next;
    CPU_SIZE_T   str_len;


    if (pstr == (CPU_CHAR *)0) {                                /* Rtn NULL if srch str ptr NULL (see Note #2a).        */
        return ((CPU_CHAR *)0);
    }


    pstr_next  = pstr;
    str_len    = Str_Len(pstr);
    pstr_next += str_len;
    while (( pstr_next != pstr) &&                              /* Srch str from end until beg (see Note #2c) ...       */
           (*pstr_next != srch_char)) {                         /* ... until srch char found   (see Note #2d).          */
        pstr_next--;
    }


    if (*pstr_next != srch_char) {                              /* If srch char NOT found, str points to NULL; ...      */
        return ((CPU_CHAR *)0);                                 /* ... rtn NULL (see Notes #2b & #2c).                  */
    }

    return (pstr_next);                                         /* Else rtn ptr to found srch char (see Note #2d).      */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Str()
*
* Description : Search string for first occurence of a specific search string.
*
* Argument(s) : pstr            Pointer to        string (see Note #1).
*
*               psrch_str       Pointer to search string (see Note #1).
*
* Return(s)   : Pointer to first occurrence of search string in string, if any.
*
*               Pointer to NULL,                                        otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) Search string length greater than string length.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (c) Search string length equal to zero.
*                       (1) NULL search string at end of string returned.
*
*                   (d) Entire string has been searched.
*                       (1) Maximum size of the search is defined as the subtraction of the
*                           search string length from the string length.
*                       (2) Search string not found; NULL pointer returned.
*
*                   (e) Search string found.
*                       (1) Search string found according to Str_Cmp_N() return value.
*                       (2) Return pointer to first occurrence of search string in string.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Str (CPU_CHAR  *pstr,
                    CPU_CHAR  *psrch_str)
{
    CPU_SIZE_T    str_len;
    CPU_SIZE_T    srch_str_len;
    CPU_SIZE_T    srch_len;
    CPU_SIZE_T    srch_ix;
    CPU_BOOLEAN   srch_done;
    CPU_INT16S    srch_cmp;
    CPU_CHAR     *pstr_srch_ix;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #2a).          */
    if (pstr == (CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }
    if (psrch_str == (CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }


    str_len      = Str_Len(pstr);
    srch_str_len = Str_Len(psrch_str);
    if (srch_str_len > str_len) {                               /* If srch str len > str len, rtn NULL  (see Note #2b). */
        return ((CPU_CHAR *)0);
    }
    if (srch_str_len == 0) {                                    /* If srch str len = 0, srch str equal NULL str; ...    */
        pstr_srch_ix = (CPU_CHAR *)(pstr + str_len);            /* ... rtn ptr to NULL str found in str (see Note #2c). */
        return (pstr_srch_ix);
    }

    srch_len  = str_len - srch_str_len;                         /* Determine srch len (see Note #2d1).                  */
    srch_ix   = 0;
    srch_done = DEF_NO;
    while ((srch_done == DEF_NO) && (srch_ix <= srch_len)) {
        pstr_srch_ix = (CPU_CHAR *)(pstr + srch_ix);
        srch_cmp     =  Str_Cmp_N(pstr_srch_ix, psrch_str, srch_str_len);
        srch_done    = (srch_cmp == 0) ? DEF_YES : DEF_NO;
        srch_ix++;
    }


    if (srch_cmp != 0) {                                        /* If srch str NOT found, rtn NULL  (see Note #2d).     */
        return ((CPU_CHAR *)0);
    }

    return (pstr_srch_ix);                                      /* Rtn ptr to srch str found in str (see Note #2e).     */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Str_FmtNbr_32()
*
* Description : Format number into a multi-digit character string.
*
* Argument(s) : nbr             Number                          to format (see Note #1).
*
*               nbr_dig         Number of integer        digits to format (see Note #2).
*
*               nbr_dp          Number of decimal point  digits to format.
*
*               lead_zeros      Prepend leading zeros    option (DEF_YES/DEF_NO) [see Note #3].
*
*               nul             NULL-character terminate option (DEF_YES/DEF_NO) [see Note #4].
*
*               pstr_fmt        Pointer to character array to return formatted number string (see Note #5).
*
* Return(s)   : Pointer to formatted string, if NO errors (see Note #6).
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) The maximum accuracy for 32-bit floating-point numbers :
*
*
*                                 Maximum Accuracy            log [Internal-Base ^ (Number-Internal-Base-Digits)]
*                           32-bit Floating-point Number  =  -----------------------------------------------------
*                                                                             log [External-Base]
*
*                                                             log [2 ^ 24]
*                                                         =  --------------
*                                                               log [10]
*
*                                                         <  7.225  Base-10 Digits
*
*                               where
*                                       Internal-Base                   Internal number base of floating-
*                                                                           point numbers (i.e.  2)
*                                       External-Base                   External number base of floating-
*                                                                           point numbers (i.e. 10)
*                                       Number-Internal-Base-Digits     Number of internal number base
*                                                                           significant digits (i.e. 24)
*
*                   (b) Some compilers' floating-point routines MAY further reduce the maximum accuracy.
*
*                   (c) If the total number of digits to format ('nbr_dig + nbr_dp') is greater than the 
*                       maximum accuracy; digits following the first, significantly-accurate digits will
*                       be inaccurate.
*
*               (2) (a) If the number of digits to format ('nbr_dig') is less than the number of significant
*                       integer digits of the number to format ('nbr'); then the most-significant digits of
*                       the formatted number will be truncated.
*
*                           Example :
*
*                               nbr      = 23456.789
*                               nbr_dig  = 3
*                               nbr_dp   = 2
*
*                               pstr_fmt = "456.78"
*
*                   (b) If number to format ('nbr') is negative but the most-significant digits of the
*                       formatted number are truncated (see Note #2a); the negative sign still prefixes
*                       the truncated formatted number.
*
*                           Example :
*
*                               nbr      = -23456.789
*                               nbr_dig  =  3
*                               nbr_dp   =  2
*
*                               pstr_fmt = "-456.78"
*
*               (3) (a) Leading zeros option prepends leading '0's prior to the first non-zero digit.
*                       The number of leading zeros is such that the total number integer digits is
*                       equal to the requested number of integer digits to format ('nbr_dig').
*
*                   (b) (1) If leading zeros option DISABLED,                        ...
*                       (2) ... number of digits to format is non-zero,              ...
*                       (3) ... & the integer value of the number to format is zero; ...
*                       (4) ... then one digit of '0' value is formatted.
*
*                           This is NOT a leading zero; but a single integer digit of '0' value.
*
*               (4) (a) NULL-character terminate option DISABLED prevents overwriting previous character
*                       array formatting.
*
*                   (b) WARNING: Unless 'pstr_fmt' character array is pre-/post-terminated, NULL-character
*                       terminate option DISABLED will cause character string run-on.
*$PAGE*
*               (5) (a) Format buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (b) To prevent character buffer overrun :
*
*                           Character array size MUST be  >=  ('nbr_dig'         +
*                                                              'nbr_dp'          +
*                                                              1 negative sign   +
*                                                              1 decimal point   +
*                                                              1 'NUL' terminator)  characters
*
*               (6) String format terminates when :
*
*                   (a) Format string pointer is passed a NULL pointer.
*                       (1) No string format performed; NULL pointer returned.
*
*                   (b) Number successfully formatted into character string array.
*********************************************************************************************************
*/

#if (LIB_STR_CFG_FP_EN == DEF_ENABLED)
CPU_CHAR  *Str_FmtNbr_32 (CPU_FP32      nbr,
                          CPU_INT08U    nbr_dig,
                          CPU_INT08U    nbr_dp,
                          CPU_BOOLEAN   lead_zeros,
                          CPU_BOOLEAN   nul,
                          CPU_CHAR     *pstr_fmt)
{
    CPU_CHAR    *pstr;
    CPU_INT08U   i;
    CPU_INT32U   dig_nbr;
    CPU_INT32U   dig_val;
    CPU_FP32     dig_exp;
    CPU_FP32     dp_exp;

                                                                /* Rtn NULL if str ptr NULL (see Note #6a).             */
    if (pstr_fmt == (CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }


    pstr = pstr_fmt;

    if (nbr < 0.0) {                                            /* If nbr neg,             ...                          */
        if ((nbr_dig > 0) ||                                    /* ... &  at least one dig ...                          */
            (nbr_dp  > 0)) {                                    /* ... or at least one dp; ...                          */
             nbr     = -nbr;                                    /* ... negate nbr &        ...                          */
            *pstr++  = '-';                                     /* ... prefix with neg sign (see Note #2b).             */
        }
    }

    if (nbr_dig > 0) {
        dig_exp = 1.0;
        for (i = 1; i < nbr_dig; i++) {
            dig_exp *= 10.0;
        }
        for (i = nbr_dig; i > 0; i--) {                         /* Fmt str for desired nbr digs.                        */
            dig_nbr = (CPU_INT32U)(nbr / dig_exp);
            if ((dig_nbr >  0) ||                               /* If dig nbr > 0,                              ...     */
                (nbr_dig == 1) ||                               /* ... OR exactly 1 dig to fmt,                 ...     */
                (i       == 1) ||                               /* ... OR on one's  dig to fmt,                 ...     */
                (lead_zeros == DEF_YES)) {                      /* ... OR lead zeros opt ENABLED (see Note #3), ...     */
                                                                /* ... calc & fmt dig val.                              */
                 dig_val = (CPU_INT32U)(dig_nbr % 10 );
                *pstr++  = (CPU_CHAR  )(dig_val + '0');
            }
            dig_exp /= 10.0;                                    /* Shift to next least-significant dig.                 */
        }
    }

    if (nbr_dp > 0) {
       *pstr++ = '.';                                           /* Append dp prior to dp conversion.                    */
        dp_exp = 10.0;
        for (i = 0; i < nbr_dp; i++) {                          /* Fmt str for desired nbr dp.                          */
            dig_nbr  = (CPU_INT32U)(nbr * dp_exp );
            dig_val  = (CPU_INT32U)(dig_nbr % 10 );
           *pstr++   = (CPU_CHAR  )(dig_val + '0');
            dp_exp  *=  10.0;                                   /* Shift to next least-significant dp.                  */
        }
    }

    if (nul != DEF_NO) {                                        /* If NOT DISABLED, append NULL char (see Note #4).     */
       *pstr = (CPU_CHAR)0;
    }


    return (pstr_fmt);
}
#endif

