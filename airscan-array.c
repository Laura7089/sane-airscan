/* AirScan (a.k.a. eSCL) backend for SANE
 *
 * Copyright (C) 2019 and up by Alexander Pevzner (pzz@apevzner.com)
 * See LICENSE for license terms and conditions
 */

#include "airscan.h"

#include <glib.h>

/******************** Typed Arrays ********************/
/* Initial capacity of arrays
 */
#define ARRAY_INITIAL_CAPACITY  4

/* Initialize array of SANE_Word
 */
void
array_of_word_init (SANE_Word **a)
{
    *a = g_new0(SANE_Word, ARRAY_INITIAL_CAPACITY);
}

/* Cleanup array of SANE_Word
 */
void
array_of_word_cleanup (SANE_Word **a)
{
    g_free(*a);
    *a = NULL;
}

/* Get length of the SANE_Word array
 */
size_t
array_of_word_len (SANE_Word **a)
{
    return (size_t) (*a)[0];
}

/* Append word to array
 */
void
array_of_word_append(SANE_Word **a, SANE_Word w)
{
    size_t sz = array_of_word_len(a) + 1;

    /* If sz reached the power-of-2, reallocate the array, doubling its size */
    if (sz >= ARRAY_INITIAL_CAPACITY && (sz & (sz - 1)) == 0) {
        *a = g_renew(SANE_Word, (*a), sz + sz);
    }

    (*a)[sz] = w;
    (*a)[0] ++;
}

/* Compare function for array_of_word_sort
 */
int
array_of_word_sort_cmp(const void *p1, const void *p2)
{
    return *(SANE_Word*) p1 - *(SANE_Word*) p2;
}

/* Sort array of SANE_Word in increasing order
 */
void
array_of_word_sort(SANE_Word **a)
{
    SANE_Word len = (*a)[0];

    if (len) {
        qsort((*a) + 1, len, sizeof(SANE_Word), array_of_word_sort_cmp);
    }
}

/* Initialize array of SANE_String
 */
void
array_of_string_init (SANE_String **a)
{
    *a = g_new0(SANE_String, ARRAY_INITIAL_CAPACITY);
}

/* Cleanup array of SANE_String
 */
void
array_of_string_cleanup (SANE_String **a)
{
    g_free(*a);
    *a = NULL;
}

/* Get length of the SANE_Word array
 */
size_t
array_of_string_len (SANE_String **a)
{
    size_t sz;

    for (sz = 0; (*a)[sz]; sz ++)
        ;

    return sz;
}

/* Append string to array
 */
void
array_of_string_append(SANE_String **a, SANE_String s)
{
    size_t sz = array_of_string_len(a) + 1;

    /* If sz reached the power-of-2, reallocate the array, doubling its size */
    if (sz >= ARRAY_INITIAL_CAPACITY && (sz & (sz - 1)) == 0) {
        *a = g_renew(SANE_String, (*a), sz + sz);
    }

    /* Append string */
    (*a)[sz - 1] = s;
    (*a)[sz] = NULL;
}

/* vim:ts=8:sw=4:et
 */
