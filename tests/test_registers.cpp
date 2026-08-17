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

TEST(RegisterPairs, flagGetters) {
    gb::Registers r{};
    r.f = 0xD0;
    EXPECT_EQ(r.flag_z(), true);
    EXPECT_EQ(r.flag_n(), true);
    EXPECT_EQ(r.flag_h(), false);
    EXPECT_EQ(r.flag_c(), true);

    r.f = 0x20;
    EXPECT_EQ(r.flag_z(), false);
    EXPECT_EQ(r.flag_n(), false);
    EXPECT_EQ(r.flag_h(), true);
    EXPECT_EQ(r.flag_c(), false);
}

TEST(RegisterPairs, flagSetters) {
    gb::Registers r{};
    r.f = 0x00;
    EXPECT_EQ(r.f, 0x00);
    r.set_z(true);
    EXPECT_EQ(r.f, 0x80);
    r.set_n(true);
    EXPECT_EQ(r.f, 0xC0);
    r.set_h(true);
    EXPECT_EQ(r.f, 0xE0);
    r.set_c(true);
    EXPECT_EQ(r.f, 0xF0);

    r.set_z(false);
    EXPECT_EQ(r.f, 0x70);
    r.set_n(false);
    EXPECT_EQ(r.f, 0x30);
    r.set_h(false);
    EXPECT_EQ(r.f, 0x10);
    r.set_c(false);
    EXPECT_EQ(r.f, 0x00);

}

TEST(RegisterPairs, fDirtyFlag) {
    gb::Registers r{};
    r.f = 0xF9;
    r.set_z(true);
    EXPECT_EQ(r.f, 0xF0);
    r.f = 0xBB;
    r.set_n(true);
    EXPECT_EQ(r.f, 0xF0);
    r.f = 0xE7;
    r.set_h(false);
    EXPECT_EQ(r.f, 0xC0);
    r.f = 0x4A;
    r.set_c(true);
    EXPECT_EQ(r.f, 0x50);

}