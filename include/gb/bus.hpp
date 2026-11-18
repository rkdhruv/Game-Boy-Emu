#pragma once
#include <cstdint>
#include <array>


namespace gb {
    struct Bus {
        std::array<uint8_t, 0x10000> memory{};

        uint8_t read(uint16_t address) const {
            return memory[address];
        }

        void write(uint16_t address, uint8_t value) {
            memory[address] = value;
        }
    };
}