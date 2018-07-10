/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xplot/xaxes.hpp"

namespace xpl
{
    TEST(xaxis, constructor)
    {
        linear_scale s1;
        s1.mid_range = 0.9;
        axis a1(s1);
        EXPECT_DOUBLE_EQ(a1.scale().get<linear_scale>().mid_range, s1.mid_range);

        linear_scale s2;
        s2.mid_range = 0.9;
        axis a2(std::move(s2));
        EXPECT_DOUBLE_EQ(a2.scale().get<linear_scale>().mid_range, s1.mid_range);

        auto s3 = std::make_shared<linear_scale>();
        s3->mid_range = 0.9;
        axis a3(s3);
        EXPECT_DOUBLE_EQ(a3.scale().get<linear_scale>().mid_range, s3->mid_range);
    }

    TEST(xcolor_axis, constructor)
    {
        linear_scale s1;
        s1.mid_range = 0.9;
        color_axis a1(s1);
        EXPECT_DOUBLE_EQ(a1.scale().get<linear_scale>().mid_range, s1.mid_range);

        linear_scale s2;
        s2.mid_range = 0.9;
        color_axis a2(std::move(s2));
        EXPECT_DOUBLE_EQ(a2.scale().get<linear_scale>().mid_range, s1.mid_range);

        auto s3 = std::make_shared<linear_scale>();
        s3->mid_range = 0.9;
        color_axis a3(s3);
        EXPECT_DOUBLE_EQ(a3.scale().get<linear_scale>().mid_range, s3->mid_range);
    }
}