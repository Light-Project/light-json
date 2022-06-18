/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 Sanpe <sanpeqf@gmail.com>
 */

#ifndef _JSON_H_
#define _JSON_H_

#include "list.h"
#include "macro.h"
#include <errno.h>

enum json_flags {
    __JSON_IS_ARRAY     = 0,
    __JSON_IS_OBJECT    = 1,
    __JSON_IS_STRING    = 2,
    __JSON_IS_NUMBER    = 3,
    __JSON_IS_NULL      = 4,
    __JSON_IS_TRUE      = 5,
    __JSON_IS_FALSE     = 6,
};

#define JSON_IS_ARRAY   (1UL << __JSON_IS_ARRAY)
#define JSON_IS_OBJECT  (1UL << __JSON_IS_OBJECT)
#define JSON_IS_STRING  (1UL << __JSON_IS_STRING)
#define JSON_IS_NUMBER  (1UL << __JSON_IS_NUMBER)
#define JSON_IS_NULL    (1UL << __JSON_IS_NULL)
#define JSON_IS_TRUE    (1UL << __JSON_IS_TRUE)
#define JSON_IS_FALSE   (1UL << __JSON_IS_FALSE)

struct json_node {
    struct json_node *parent;
    struct list_head sibling;
    char *name;
    unsigned long flags;
    union {
        struct list_head child;
        long number;
        char *string;
    };
};

#define GENERIC_JSON_BITOPS(name, value)                    \
static inline void json_clr_##name(struct json_node *json)  \
{                                                           \
    json->flags &= ~value;                                  \
}                                                           \
                                                            \
static inline void json_set_##name(struct json_node *json)  \
{                                                           \
    json->flags |= value;                                   \
}                                                           \
                                                            \
static inline bool json_test_##name(struct json_node *json) \
{                                                           \
    return !!(json->flags & value);                         \
}

GENERIC_JSON_BITOPS(array, JSON_IS_ARRAY)
GENERIC_JSON_BITOPS(object, JSON_IS_OBJECT)
GENERIC_JSON_BITOPS(string, JSON_IS_STRING)
GENERIC_JSON_BITOPS(number, JSON_IS_NUMBER)
GENERIC_JSON_BITOPS(null, JSON_IS_NULL)
GENERIC_JSON_BITOPS(true, JSON_IS_TRUE)
GENERIC_JSON_BITOPS(false, JSON_IS_FALSE)

extern int json_parse(const char *buff, struct json_node **root);
extern int json_encode(struct json_node *root, char *buff, int size);
extern void json_release(struct json_node *root);

#endif  /* _JSON_H_ */
