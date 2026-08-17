#pragma once
#include <cstdint>

namespace gb {
    struct Registers {
        uint8_t a{};
        uint8_t f{};
        uint8_t b{};
        uint8_t c{};
        uint8_t d{};
        uint8_t e{};
        uint8_t h{};
        uint8_t l{};
        
        uint16_t sp{};
        uint16_t pc{};

        // Getter functions
        uint16_t af() const {
            return a * 256 + f;
        }

        uint16_t bc() const {
            return b * 256 + c;
        }

        uint16_t de() const {
            return d * 256 + e;
        }

        uint16_t hl() const {
            return h * 256 + l;
        }

        bool flag_z() const {
            return ((f & 0x80) != 0);
        }

        bool flag_n() const {
            return ((f & 0x40) != 0);
        }

        bool flag_h() const {
            return ((f & 0x20) != 0);
        }

        bool flag_c() const {
            return ((f & 0x10) != 0);
        }



        // Setter functions
        void set_af(uint16_t af) {
            a = static_cast<uint8_t>(af / 256);
            f = static_cast<uint8_t>((af % 256) & 0xF0);
        }

        void set_bc(uint16_t bc) {
            b = static_cast<uint8_t>(bc / 256);
            c = static_cast<uint8_t>(bc % 256);
        }

        void set_de(uint16_t de) {
            d = static_cast<uint8_t>(de / 256);
            e = static_cast<uint8_t>(de % 256);
        }

        void set_hl(uint16_t hl) {
            h = static_cast<uint8_t>(hl / 256);
            l = static_cast<uint8_t>(hl % 256);
        }

        void set_z(bool set) {
            if(set) {
                f = (f | 0x80) & 0xF0;
            } else {
                f = f & 0x70;
            }
        }

        void set_n(bool set) {
            if(set) {
                f = (f | 0x40) & 0xF0;
            } else {
                f = f & 0xB0;
            }
        }

        void set_h(bool set) {
            if(set) {
                f = (f | 0x20) & 0xF0;
            } else {
                f = f & 0xD0;
            }
        }

        void set_c(bool set) {
            if(set) {
                f = (f | 0x10) & 0xF0;
            } else {
                f = f & 0xE0;
            }
        }

    };
} // namespace gb