/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xplot/xfigure.hpp"

namespace xpl
{
    TEST(xfigure, add_mark)
    {
        auto s = std::make_shared<linear_scale>();
        lines l1(s, s), l2(s, s);
        auto l3 = std::make_shared<lines>(s, s);
        figure f;
        f.add_mark(l1);
        f.add_mark(std::move(l2));
        f.add_mark(l3);
        EXPECT_EQ(f.marks().size(), 3);
    }

    TEST(xfigure, add_axis)
    {
        auto s = std::make_shared<linear_scale>();
        axis a1(s), a2(s);
        auto a3 = std::make_shared<axis>(s);
        figure f;
        f.add_axis(a1);
        f.add_axis(std::move(a2));
        f.add_axis(a3);
        EXPECT_EQ(f.axes().size(), 3);
    }
}