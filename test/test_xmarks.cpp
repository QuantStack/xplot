/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xplot/xmarks.hpp"

namespace xpl
{
    TEST(xmarks, lines)
    {
        lines line;
        int res = line.marker_size();
        EXPECT_EQ(64, res);
    }
}