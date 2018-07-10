/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xplot/xtoolbar.hpp"

namespace xpl
{
    TEST(xtoolbar, constructor)
    {
        figure f1;
        f1.title = "fig1";
        toolbar t1(f1);
        EXPECT_EQ(t1.figure().get<figure>().title(), "fig1");

        figure f2;
        f2.title = "fig2";
        toolbar t2(f2);
        EXPECT_EQ(t2.figure().get<figure>().title(), "fig2");

        auto f3 = std::make_shared<figure>();
        f3->title = "fig3";
        toolbar t3(f3);
        EXPECT_EQ(t3.figure().get<figure>().title(), "fig3");
    }
}
