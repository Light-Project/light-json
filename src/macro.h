/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2022 Sanpe <sanpeqf@gmail.com>
 */

#ifndef _MACRO_H_
#define _MACRO_H_

#define ARRAY_SIZE(arr) ( \
    sizeof(arr) / sizeof((arr)[0]) \
)

#define max(a, b) ({ \
    typeof(a) _amax = (a); \
    typeof(a) _bmax = (b); \
    (void)(&_amax == &_bmax); \
    _amax > _bmax ? _amax : _bmax; \
})

#endif  /* _MACRO_H_ */
