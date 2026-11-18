#include "gb/bus.hpp"

#include <gtest/gtest.h>

TEST(BusTest, readZero) {
    gb::Bus b{};
    uint8_t t = b.read(0x2300);
    EXPECT_EQ(t, 0x0000);
}

TEST(BusTest, readWriteRead) {
    gb::Bus b{};
    b.write(0xC311, 0x67);
    EXPECT_EQ(b.read(0xC311), 0x67);
}

TEST(BusTest, checkSpill) {
    gb::Bus b{};
    b.write(0xC10F, 0xC4); // sentinel below
    b.write(0xC111, 0xC4); // sentinel above
    b.write(0xC110, 0xAA);
    EXPECT_EQ(b.read(0xC10F), 0xC4);
    EXPECT_EQ(b.read(0xC110), 0xAA);
    EXPECT_EQ(b.read(0xC111), 0xC4);
}

TEST(BusTest, checkAtZero) {
    gb::Bus b{};
    uint8_t step1 = b.read(0x0000); // should hold 0x00
    b.write(0x0000, 0xCF);
    EXPECT_EQ(step1, 0x00);
    EXPECT_EQ(b.read(0x0000), 0xCF);
}

TEST(BusTest, checkAtFFFF) {
    gb::Bus b{};
    uint8_t step1 = b.read(0xFFFF); // should hold 0x00
    b.write(0xFFFF, 0x8E);
    EXPECT_EQ(step1, 0x00);
    EXPECT_EQ(b.read(0xFFFF), 0x8E);
}

TEST(BusTest, overwrite) {
    gb::Bus b{};
    uint8_t step1 = b.read(0xFDED); // should hold 0x00
    b.write(0xFDED, 0xB4);
    uint8_t step2 = b.read(0xFDED); // should hold 0xB4
    b.write(0xFDED, 0x52);
    uint8_t step3 = b.read(0xFDED); // should hold 0x52
    b.write(0xFDED, 0x00);
    EXPECT_EQ(step1, 0x00);
    EXPECT_EQ(step2, 0xB4);
    EXPECT_EQ(step3, 0x52);
    EXPECT_EQ(b.read(0xFDED), 0x00);
}