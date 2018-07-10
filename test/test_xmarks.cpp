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
    TEST(xmarks, constructor)
    {
        linear_scale sx1, sy1;
        sx1.mid_range = 0.9;
        sy1.mid_range = 0.87;
        lines l1(sx1, sy1);
        EXPECT_EQ(l1.scales()["x"].get<linear_scale>().mid_range(), 0.9);
        EXPECT_EQ(l1.scales()["y"].get<linear_scale>().mid_range(), 0.87);

        linear_scale sx2, sy2;
        sx2.mid_range = 0.9;
        sy2.mid_range = 0.87;
        lines l2(std::move(sx2), std::move(sy2));
        EXPECT_EQ(l2.scales()["x"].get<linear_scale>().mid_range(), 0.9);
        EXPECT_EQ(l2.scales()["y"].get<linear_scale>().mid_range(), 0.87);

        auto sx3 = std::make_shared<linear_scale>();
        sx3->mid_range = 0.9;
        lines l3(sx3, sx3);
        EXPECT_EQ(l3.scales()["x"].id(), l3.scales()["y"].id());
    }

    TEST(xmarks, lines)
    {
        linear_scale sx, sy;
        lines line(sx, sy);
        int res = line.marker_size();
        EXPECT_EQ(64, res);
    }
}
