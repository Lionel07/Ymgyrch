#include <ymgyrch/system.hpp>
#include <ymgyrch/cpu.hpp>
#include <ymgyrch/cpu/2A03.hpp>
#include <ymgyrch/state.hpp>
#include <logging.hpp>
#include <functional>

namespace Ymgyrch {

	Cpus::CPU2A03::opcode_t Cpus::CPU2A03::opcodes[] = {
		{ "BRK", &Cpus::CPU2A03::Opcode_brk, 0},  // 0x0
		{ "ORA ZPXI", &Cpus::CPU2A03::Opcode_ora_zpxi, 0},  // 0x1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4
		{ "ORA ZP", &Cpus::CPU2A03::Opcode_ora_zp, 0},  // 0x5
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x8
		{ "ORA", &Cpus::CPU2A03::Opcode_ora_im, 0},  // 0x9
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xa
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc
		{ "ORA AB", &Cpus::CPU2A03::Opcode_ora_ab, 0},  // 0xd
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x10
		{ "ORA ZXYI", &Cpus::CPU2A03::Opcode_ora_zpyi, 0},  // 0x11
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x12
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x13
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x14
		{ "ORA ZPX", &Cpus::CPU2A03::Opcode_ora_zpx, 0},  // 0x15
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x16
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x17
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x18
		{ "ORA ABY", &Cpus::CPU2A03::Opcode_ora_aby, 0},  // 0x19
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x1a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x1b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x1c
		{ "ORA ABX", &Cpus::CPU2A03::Opcode_ora_abx, 0},  // 0x1d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x1e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x1f
		{ "JSR", &Cpus::CPU2A03::Opcode_jsr, 0},  // 0x20
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x21
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x22
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x23
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x24
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x25
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x26
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x27
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x28
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x29
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x2f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x30
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x31
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x32
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x33
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x34
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x35
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x36
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x37
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x38
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x39
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x3f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x40
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x41
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x42
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x43
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x44
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x45
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x46
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x47
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x48
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x49
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4b
		{ "JMP", &Cpus::CPU2A03::Opcode_jmp, 2},  // 0x4c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x4f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x50
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x51
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x52
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x53
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x54
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x55
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x56
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x57
		{ "CLI", &Cpus::CPU2A03::Opcode_cli, 0},  // 0x58
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x59
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x5f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x60
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x61
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x62
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x63
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x64
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x65
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x66
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x67
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x68
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x69
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x6f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x70
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x71
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x72
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x73
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x74
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x75
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x76
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x77
		{ "SEI", &Cpus::CPU2A03::Opcode_sei, 0},  // 0x78
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x79
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7c
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x7f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x80
		{ "STA ZPXI", &Cpus::CPU2A03::Opcode_sta_zpxi, 0},  // 0x81
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x82
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x83
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x84
		{ "STA ZP", &Cpus::CPU2A03::Opcode_sta_zp, 0},  // 0x85
		{ "STX ZP", &Cpus::CPU2A03::Opcode_stx_zp, 0},  // 0x86
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x87
		{ "DEY", &Cpus::CPU2A03::Opcode_dey, 0},  // 0x88
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x89
		{ "TXA", &Cpus::CPU2A03::Opcode_txa, 0},  // 0x8a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x8b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x8c
		{ "STA AB", &Cpus::CPU2A03::Opcode_sta_ab, 0},  // 0x8d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x8e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x8f
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x90
		{ "STA ZPYI", &Cpus::CPU2A03::Opcode_sta_zpyi, 0},  // 0x91
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x92
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x93
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x94
		{ "STA ZP", &Cpus::CPU2A03::Opcode_sta_zpx, 0},  // 0x95
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x96
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x97
		{ "TYA", &Cpus::CPU2A03::Opcode_tya, 0},  // 0x98
		{ "STA ABY", &Cpus::CPU2A03::Opcode_sta_aby, 0},  // 0x99
		{ "TXS", &Cpus::CPU2A03::Opcode_txs, 0},  // 0x9a
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x9b
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x9c
		{ "STA ABX", &Cpus::CPU2A03::Opcode_sta_abx, 0},  // 0x9d
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x9e
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0x9f
		{ "LDY", &Cpus::CPU2A03::Opcode_ldy_im, 0},  // 0xa0
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xa1
		{ "LDX", &Cpus::CPU2A03::Opcode_ldx_im, 0},  // 0xa2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xa3
		{ "LDY ZP", &Cpus::CPU2A03::Opcode_ldy_zp, 0},  // 0xa4
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xa5
		{ "LDX ZP", &Cpus::CPU2A03::Opcode_ldx_zp, 0},  // 0xa6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xa7
		{ "TAY", &Cpus::CPU2A03::Opcode_tay, 0},  // 0xa8
		{ "LDA", &Cpus::CPU2A03::Opcode_lda_im, 0},  // 0xa9
		{ "TAX", &Cpus::CPU2A03::Opcode_tax, 0},  // 0xaa
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xab
		{ "LDY AB", &Cpus::CPU2A03::Opcode_ldy_ab, 0},  // 0xac
		{ "LDA AB", &Cpus::CPU2A03::Opcode_lda_ab, 0},  // 0xad
		{ "LDX AB", &Cpus::CPU2A03::Opcode_ldx_ab, 0},  // 0xae
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xaf
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb0
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb3
		{ "LDY ZPX", &Cpus::CPU2A03::Opcode_ldy_zpx, 0},  // 0xb4
		{ "LDA ZPX", &Cpus::CPU2A03::Opcode_lda_zpx, 0},  // 0xb5
		{ "LDX ZPY", &Cpus::CPU2A03::Opcode_ldx_zpy, 0},  // 0xb6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb7
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xb8
		{ "LDA ABY", &Cpus::CPU2A03::Opcode_lda_aby, 0},  // 0xb9
		{ "TSX", &Cpus::CPU2A03::Opcode_tsx, 0},  // 0xba
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xbb
		{ "LDY ABX", &Cpus::CPU2A03::Opcode_ldy_abx, 0},  // 0xbc
		{ "LDA ABX", &Cpus::CPU2A03::Opcode_lda_abx, 0},  // 0xbd
		{ "LDX ABY", &Cpus::CPU2A03::Opcode_ldx_aby, 0},  // 0xbe
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xbf
		{ "CPY", &Cpus::CPU2A03::Opcode_cpy_im, 0},  // 0xc0
		{ "CMP ZPX", &Cpus::CPU2A03::Opcode_cmp_zpx, 0},  // 0xc1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc3
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc4
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc5
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xc7
		{ "INY", &Cpus::CPU2A03::Opcode_iny, 0},  // 0xc8
		{ "CMP", &Cpus::CPU2A03::Opcode_cmp_im, 0},  // 0xc9
		{ "DEX", &Cpus::CPU2A03::Opcode_dex, 0},  // 0xca
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xcb
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xcc
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xcd
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xce
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xcf
		{ "BNE", &Cpus::CPU2A03::Opcode_bne, 0},  // 0xd0
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd3
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd4
		{ "CMP ZP", &Cpus::CPU2A03::Opcode_cmp_zp, 0},  // 0xd5
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd7
		{ "CLD", &Cpus::CPU2A03::Opcode_cld, 0},  // 0xd8
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xd9
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xda
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xdb
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xdc
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xdd
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xde
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xdf
		{ "CPX", &Cpus::CPU2A03::Opcode_cpx_im, 0},  // 0xe0
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe3
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe4
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe5
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe7
		{ "INX", &Cpus::CPU2A03::Opcode_inx, 0},  // 0xe8
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xe9
		{ "NOP", &Cpus::CPU2A03::Opcode_nop, 0},  // 0xea
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xeb
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xec
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xed
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xee
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xef
		{ "BEQ", &Cpus::CPU2A03::Opcode_beq, 0},  // 0xf0
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf1
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf2
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf3
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf4
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf5
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf6
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf7
		{ "SED", &Cpus::CPU2A03::Opcode_sed, 0},  // 0xf8
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xf9
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xfa
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xfb
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xfc
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xfd
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xfe
		{ "???", &Cpus::CPU2A03::Opcode_ukn, 0},  // 0xff
	};

	void Cpus::CPU2A03::Init(Ymgyrch::System * sys) {
		this->name = "2A03";
		this->sys = sys;
		Reset();
		g_log->Debug("2A03", "Initialised");
	}

	void Cpus::CPU2A03::Update() {
		// Fetch opcode
		uint8_t opcode = sys->memController->ReadByte(registers.pc);
		std::invoke(opcodes[opcode].op, this);
		g_log->Debug("2A03", "Opcode 0x{0:X}, {1:s}", opcode, opcodes[opcode].dissassembly);
	}

	void Cpus::CPU2A03::Reset() {
		registers.a = 0x0;
		registers.x = 0x0;
		registers.y = 0x0;
		registers.p = 0x34;
		registers.s = 0xFD;
		registers.i = true;
		registers.pc = sys->memController->ReadShort(0xFFFC) ; //TODO:: SET TO 0xFFFC
		g_log->Debug("2A03", "Reset PC to {0:#04X}", registers.pc);
		registers.cycles = 0;
		registers.cyclesDelta = 0;
		g_log->Debug("2A03", "Reset");
	}

	std::vector<cpu_instruction_t> Ymgyrch::Cpus::CPU2A03::GetDissassembly()
	{
		opcode_t operation;
		cpu_instruction_t ins;
		std::vector<cpu_instruction_t> dis;
		float lim = (float)(State::disassembly.lines / 4);
		if ((int)(lim * 4) > State::disassembly.lines) { lim -= 2; }
		uint16_t location = registers.pc - 1;

		for (int i = 0; i < lim; i++) {
			operation = opcodes[sys->memController->ReadByte(location)];
			ins = { location, fmt::format("{0:02X} : ", sys->memController->ReadByte(location)) + operation.dissassembly, false, false };
			location -= 1;
			dis.push_back(ins);
		}
		std::reverse(dis.begin(), dis.end());

		location = registers.pc;
		operation = opcodes[sys->memController->ReadByte(location)];
		ins = { location,fmt::format("{0:02X} : ", sys->memController->ReadByte(location)) + operation.dissassembly, true, false };
		location += operation.operandSize + 1;
		dis.push_back(ins);

		for (int i = 0; i < (lim * 3) + 1; i++) {
			operation = opcodes[sys->memController->ReadByte(location)];
			ins = { location, fmt::format("{0:02X} : ", sys->memController->ReadByte(location)) + operation.dissassembly, false, false };
			location += operation.operandSize + 1;
			dis.push_back(ins);
		}
		return dis;
	}

	std::vector<cpu_info_t> Ymgyrch::Cpus::CPU2A03::GetStatus()
	{
		std::vector<cpu_info_t> status;
		cpu_info_t a = { "A", fmt::format("0x{0:02X}", registers.a) }; status.push_back(a);
		cpu_info_t x = { "X", fmt::format("0x{0:02X}", registers.x) }; status.push_back(x);
		cpu_info_t y = { "Y", fmt::format("0x{0:02X}", registers.y) }; status.push_back(y);
		cpu_info_t p = { "P", fmt::format("0x{0:02X}", registers.p) }; status.push_back(p);
		cpu_info_t pc = { "PC", fmt::format("0x{0:04X}", registers.pc) }; status.push_back(pc);
		cpu_info_t s = { "SP", fmt::format("0x{0:02X}", registers.s) }; status.push_back(s);
		return status;
	}
};