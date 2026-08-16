#include "gb/registers.hpp"

#include <gtest/gtest.h>

TEST(RegisterPairs, bcCombinesByte) {
    gb::Registers r{};
    r.b = 0xAF;
    r.c = 0x01;
    EXPECT_EQ(r.bc(), 0xAF01);
}

TEST(RegisterPairs, deSetBytes) {
    gb::Registers r{};
    r.set_de(0xC350);
    EXPECT_EQ(r.d, 0xC3);
    EXPECT_EQ(r.e, 0x50);
    EXPECT_EQ(r.de(), 0xC350);
}

TEST(RegisterPairs, hlIncBytes) {
    gb::Registers r{};
    r.set_hl(0x00FF);
    r.set_hl(r.hl() + 1);
    EXPECT_EQ(r.hl(), 0x0100);
}

TEST(RegisterPairs, afMaskTest) {
    gb::Registers r{};
    r.set_af(0x12AB);
    EXPECT_EQ(r.af(), 0x12A0);
}