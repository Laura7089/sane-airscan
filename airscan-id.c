/* AirScan (a.k.a. eSCL) backend for SANE
 *
 * Copyright (C) 2019 and up by Alexander Pevzner (pzz@apevzner.com)
 * See LICENSE for license terms and conditions
 *
 * Routines for SANE options handling
 */

#include "airscan.h"

#include <string.h>

/******************** Generic functions for IDs ********************/
/* Name/value mapping entry
 */
typedef struct {
    int        id;
    const char *name;
} id_name_table;

/* Get name by ID. For unknown ID returns NULL
 */
static const char*
id_name (int id, const id_name_table *table)
{
    int i;

    for (i = 0; table[i].name != NULL; i ++) {
        if (table[i].id == id) {
            return table[i].name;
        }
    }

    return NULL;
}

/* Get ID by name. For unknown name returns -1
 */
static int
id_by_name (const char *name, int (*cmp) (const char *s1, const char *s2),
        const id_name_table *table)
{
    int i;

    for (i = 0; table[i].name != NULL; i ++) {
        if (!cmp(name, table[i].name)) {
            return table[i].id;
        }
    }

    return -1;
}

/******************** ID_PROTO ********************/
/* id_proto_name_table table represents name mapping for ID_PROTO
 */
static id_name_table id_proto_name_table[] = {
    {ID_PROTO_ESCL, "eSCL"},
    {ID_PROTO_WSD,  "WSD"},
    {-1, NULL}
};

/* id_proto_name returns protocol name
 * For unknown ID returns NULL
 */
const char*
id_proto_name (ID_PROTO proto)
{
    return id_name(proto, id_proto_name_table);
}

/* id_proto_by_name returns protocol identifier by name
 * For unknown name returns ID_PROTO_UNKNOWN
 */
ID_PROTO
id_proto_by_name (const char* name)
{
    return id_by_name(name, strcasecmp, id_proto_name_table);
}

/* vim:ts=8:sw=4:et
 */