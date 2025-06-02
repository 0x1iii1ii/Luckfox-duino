//
// Created by 0x1iii1ii on 3/12/2025.
//

// * GPIO definition for Luckfox pico plus

#ifndef GPIO_DEF_H
#define GPIO_DEF_H

// Define group indexes for A, B, C, D
#define GROUP_A 0
#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3

// Macro to calculate the pin number from bank, group, and x
#define GPIO_PIN(bank, group, x) ((bank)*32 + ((group)*8 + (x)))

// Bank 0
#define GPIO0_A0 GPIO_PIN(0, GROUP_A, 0)  // 0*32 + (0*8+0) = 0
#define GPIO0_A1 GPIO_PIN(0, GROUP_A, 1)  // 1
#define GPIO0_A2 GPIO_PIN(0, GROUP_A, 2)  // 2
#define GPIO0_A3 GPIO_PIN(0, GROUP_A, 3)  // 3
#define GPIO0_A4 GPIO_PIN(0, GROUP_A, 4)  // 4
#define GPIO0_A5 GPIO_PIN(0, GROUP_A, 5)  // 5
#define GPIO0_A6 GPIO_PIN(0, GROUP_A, 6)  // 6
#define GPIO0_A7 GPIO_PIN(0, GROUP_A, 7)  // 7

#define GPIO0_B0 GPIO_PIN(0, GROUP_B, 0)  // 0*32 + (1*8+0) = 8
#define GPIO0_B1 GPIO_PIN(0, GROUP_B, 1)  // 9
#define GPIO0_B2 GPIO_PIN(0, GROUP_B, 2)  // 10
#define GPIO0_B3 GPIO_PIN(0, GROUP_B, 3)  // 11
#define GPIO0_B4 GPIO_PIN(0, GROUP_B, 4)  // 12
#define GPIO0_B5 GPIO_PIN(0, GROUP_B, 5)  // 13
#define GPIO0_B6 GPIO_PIN(0, GROUP_B, 6)  // 14
#define GPIO0_B7 GPIO_PIN(0, GROUP_B, 7)  // 15

#define GPIO0_C0 GPIO_PIN(0, GROUP_C, 0)  // 16
#define GPIO0_C1 GPIO_PIN(0, GROUP_C, 1)  // 17
#define GPIO0_C2 GPIO_PIN(0, GROUP_C, 2)  // 18
#define GPIO0_C3 GPIO_PIN(0, GROUP_C, 3)  // 19
#define GPIO0_C4 GPIO_PIN(0, GROUP_C, 4)  // 20
#define GPIO0_C5 GPIO_PIN(0, GROUP_C, 5)  // 21
#define GPIO0_C6 GPIO_PIN(0, GROUP_C, 6)  // 22
#define GPIO0_C7 GPIO_PIN(0, GROUP_C, 7)  // 23

#define GPIO0_D0 GPIO_PIN(0, GROUP_D, 0)  // 24
#define GPIO0_D1 GPIO_PIN(0, GROUP_D, 1)  // 25
#define GPIO0_D2 GPIO_PIN(0, GROUP_D, 2)  // 26
#define GPIO0_D3 GPIO_PIN(0, GROUP_D, 3)  // 27
#define GPIO0_D4 GPIO_PIN(0, GROUP_D, 4)  // 28
#define GPIO0_D5 GPIO_PIN(0, GROUP_D, 5)  // 29
#define GPIO0_D6 GPIO_PIN(0, GROUP_D, 6)  // 30
#define GPIO0_D7 GPIO_PIN(0, GROUP_D, 7)  // 31

// Bank 1
#define GPIO1_A0 GPIO_PIN(1, GROUP_A, 0)  // 1*32 + (0*8+0) = 32
#define GPIO1_A1 GPIO_PIN(1, GROUP_A, 1)  // 33
#define GPIO1_A2 GPIO_PIN(1, GROUP_A, 2)  // 34
#define GPIO1_A3 GPIO_PIN(1, GROUP_A, 3)  // 35
#define GPIO1_A4 GPIO_PIN(1, GROUP_A, 4)  // 36
#define GPIO1_A5 GPIO_PIN(1, GROUP_A, 5)  // 37
#define GPIO1_A6 GPIO_PIN(1, GROUP_A, 6)  // 38
#define GPIO1_A7 GPIO_PIN(1, GROUP_A, 7)  // 39

#define GPIO1_B0 GPIO_PIN(1, GROUP_B, 0)  // 40
#define GPIO1_B1 GPIO_PIN(1, GROUP_B, 1)  // 41
#define GPIO1_B2 GPIO_PIN(1, GROUP_B, 2)  // 42
#define GPIO1_B3 GPIO_PIN(1, GROUP_B, 3)  // 43
#define GPIO1_B4 GPIO_PIN(1, GROUP_B, 4)  // 44
#define GPIO1_B5 GPIO_PIN(1, GROUP_B, 5)  // 45
#define GPIO1_B6 GPIO_PIN(1, GROUP_B, 6)  // 46
#define GPIO1_B7 GPIO_PIN(1, GROUP_B, 7)  // 47

#define GPIO1_C0 GPIO_PIN(1, GROUP_C, 0)  // 48
#define GPIO1_C1 GPIO_PIN(1, GROUP_C, 1)  // 49
#define GPIO1_C2 GPIO_PIN(1, GROUP_C, 2)  // 50
#define GPIO1_C3 GPIO_PIN(1, GROUP_C, 3)  // 51
#define GPIO1_C4 GPIO_PIN(1, GROUP_C, 4)  // 52
#define GPIO1_C5 GPIO_PIN(1, GROUP_C, 5)  // 53
#define GPIO1_C6 GPIO_PIN(1, GROUP_C, 6)  // 54
#define GPIO1_C7 GPIO_PIN(1, GROUP_C, 7)  // 55

#define GPIO1_D0 GPIO_PIN(1, GROUP_D, 0)  // 56
#define GPIO1_D1 GPIO_PIN(1, GROUP_D, 1)  // 57
#define GPIO1_D2 GPIO_PIN(1, GROUP_D, 2)  // 58
#define GPIO1_D3 GPIO_PIN(1, GROUP_D, 3)  // 59
#define GPIO1_D4 GPIO_PIN(1, GROUP_D, 4)  // 60
#define GPIO1_D5 GPIO_PIN(1, GROUP_D, 5)  // 61
#define GPIO1_D6 GPIO_PIN(1, GROUP_D, 6)  // 62
#define GPIO1_D7 GPIO_PIN(1, GROUP_D, 7)  // 63

// Bank 2
#define GPIO2_A0 GPIO_PIN(2, GROUP_A, 0)  // 2*32 + 0 = 64
#define GPIO2_A1 GPIO_PIN(2, GROUP_A, 1)  // 65
#define GPIO2_A2 GPIO_PIN(2, GROUP_A, 2)  // 66
#define GPIO2_A3 GPIO_PIN(2, GROUP_A, 3)  // 67
#define GPIO2_A4 GPIO_PIN(2, GROUP_A, 4)  // 68
#define GPIO2_A5 GPIO_PIN(2, GROUP_A, 5)  // 69
#define GPIO2_A6 GPIO_PIN(2, GROUP_A, 6)  // 70
#define GPIO2_A7 GPIO_PIN(2, GROUP_A, 7)  // 71

#define GPIO2_B0 GPIO_PIN(2, GROUP_B, 0)  // 72
#define GPIO2_B1 GPIO_PIN(2, GROUP_B, 1)  // 73
#define GPIO2_B2 GPIO_PIN(2, GROUP_B, 2)  // 74
#define GPIO2_B3 GPIO_PIN(2, GROUP_B, 3)  // 75
#define GPIO2_B4 GPIO_PIN(2, GROUP_B, 4)  // 76
#define GPIO2_B5 GPIO_PIN(2, GROUP_B, 5)  // 77
#define GPIO2_B6 GPIO_PIN(2, GROUP_B, 6)  // 78
#define GPIO2_B7 GPIO_PIN(2, GROUP_B, 7)  // 79

#define GPIO2_C0 GPIO_PIN(2, GROUP_C, 0)  // 80
#define GPIO2_C1 GPIO_PIN(2, GROUP_C, 1)  // 81
#define GPIO2_C2 GPIO_PIN(2, GROUP_C, 2)  // 82
#define GPIO2_C3 GPIO_PIN(2, GROUP_C, 3)  // 83
#define GPIO2_C4 GPIO_PIN(2, GROUP_C, 4)  // 84
#define GPIO2_C5 GPIO_PIN(2, GROUP_C, 5)  // 85
#define GPIO2_C6 GPIO_PIN(2, GROUP_C, 6)  // 86
#define GPIO2_C7 GPIO_PIN(2, GROUP_C, 7)  // 87

#define GPIO2_D0 GPIO_PIN(2, GROUP_D, 0)  // 88
#define GPIO2_D1 GPIO_PIN(2, GROUP_D, 1)  // 89
#define GPIO2_D2 GPIO_PIN(2, GROUP_D, 2)  // 90
#define GPIO2_D3 GPIO_PIN(2, GROUP_D, 3)  // 91
#define GPIO2_D4 GPIO_PIN(2, GROUP_D, 4)  // 92
#define GPIO2_D5 GPIO_PIN(2, GROUP_D, 5)  // 93
#define GPIO2_D6 GPIO_PIN(2, GROUP_D, 6)  // 94
#define GPIO2_D7 GPIO_PIN(2, GROUP_D, 7)  // 95

// Bank 3
#define GPIO3_A0 GPIO_PIN(3, GROUP_A, 0)  // 96
#define GPIO3_A1 GPIO_PIN(3, GROUP_A, 1)  // 97
#define GPIO3_A2 GPIO_PIN(3, GROUP_A, 2)  // 98
#define GPIO3_A3 GPIO_PIN(3, GROUP_A, 3)  // 99
#define GPIO3_A4 GPIO_PIN(3, GROUP_A, 4)  // 100
#define GPIO3_A5 GPIO_PIN(3, GROUP_A, 5)  // 101
#define GPIO3_A6 GPIO_PIN(3, GROUP_A, 6)  // 102
#define GPIO3_A7 GPIO_PIN(3, GROUP_A, 7)  // 103

#define GPIO3_B0 GPIO_PIN(3, GROUP_B, 0)  // 104
#define GPIO3_B1 GPIO_PIN(3, GROUP_B, 1)  // 105
#define GPIO3_B2 GPIO_PIN(3, GROUP_B, 2)  // 106
#define GPIO3_B3 GPIO_PIN(3, GROUP_B, 3)  // 107
#define GPIO3_B4 GPIO_PIN(3, GROUP_B, 4)  // 108
#define GPIO3_B5 GPIO_PIN(3, GROUP_B, 5)  // 109
#define GPIO3_B6 GPIO_PIN(3, GROUP_B, 6)  // 110
#define GPIO3_B7 GPIO_PIN(3, GROUP_B, 7)  // 111

#define GPIO3_C0 GPIO_PIN(3, GROUP_C, 0)  // 112
#define GPIO3_C1 GPIO_PIN(3, GROUP_C, 1)  // 113
#define GPIO3_C2 GPIO_PIN(3, GROUP_C, 2)  // 114
#define GPIO3_C3 GPIO_PIN(3, GROUP_C, 3)  // 115
#define GPIO3_C4 GPIO_PIN(3, GROUP_C, 4)  // 116
#define GPIO3_C5 GPIO_PIN(3, GROUP_C, 5)  // 117
#define GPIO3_C6 GPIO_PIN(3, GROUP_C, 6)  // 118
#define GPIO3_C7 GPIO_PIN(3, GROUP_C, 7)  // 119

#define GPIO3_D0 GPIO_PIN(3, GROUP_D, 0)  // 120
#define GPIO3_D1 GPIO_PIN(3, GROUP_D, 1)  // 121
#define GPIO3_D2 GPIO_PIN(3, GROUP_D, 2)  // 122
#define GPIO3_D3 GPIO_PIN(3, GROUP_D, 3)  // 123
#define GPIO3_D4 GPIO_PIN(3, GROUP_D, 4)  // 124
#define GPIO3_D5 GPIO_PIN(3, GROUP_D, 5)  // 125
#define GPIO3_D6 GPIO_PIN(3, GROUP_D, 6)  // 126
#define GPIO3_D7 GPIO_PIN(3, GROUP_D, 7)  // 127

// Bank 4
#define GPIO4_A0 GPIO_PIN(4, GROUP_A, 0)  // 128
#define GPIO4_A1 GPIO_PIN(4, GROUP_A, 1)  // 129
#define GPIO4_A2 GPIO_PIN(4, GROUP_A, 2)  // 130
#define GPIO4_A3 GPIO_PIN(4, GROUP_A, 3)  // 131
#define GPIO4_A4 GPIO_PIN(4, GROUP_A, 4)  // 132
#define GPIO4_A5 GPIO_PIN(4, GROUP_A, 5)  // 133
#define GPIO4_A6 GPIO_PIN(4, GROUP_A, 6)  // 134
#define GPIO4_A7 GPIO_PIN(4, GROUP_A, 7)  // 135

#define GPIO4_B0 GPIO_PIN(4, GROUP_B, 0)  // 136
#define GPIO4_B1 GPIO_PIN(4, GROUP_B, 1)  // 137
#define GPIO4_B2 GPIO_PIN(4, GROUP_B, 2)  // 138
#define GPIO4_B3 GPIO_PIN(4, GROUP_B, 3)  // 139
#define GPIO4_B4 GPIO_PIN(4, GROUP_B, 4)  // 140
#define GPIO4_B5 GPIO_PIN(4, GROUP_B, 5)  // 141
#define GPIO4_B6 GPIO_PIN(4, GROUP_B, 6)  // 142
#define GPIO4_B7 GPIO_PIN(4, GROUP_B, 7)  // 143

#define GPIO4_C0 GPIO_PIN(4, GROUP_C, 0)  // 144
#define GPIO4_C1 GPIO_PIN(4, GROUP_C, 1)  // 145
#define GPIO4_C2 GPIO_PIN(4, GROUP_C, 2)  // 146
#define GPIO4_C3 GPIO_PIN(4, GROUP_C, 3)  // 147
#define GPIO4_C4 GPIO_PIN(4, GROUP_C, 4)  // 148
#define GPIO4_C5 GPIO_PIN(4, GROUP_C, 5)  // 149
#define GPIO4_C6 GPIO_PIN(4, GROUP_C, 6)  // 150
#define GPIO4_C7 GPIO_PIN(4, GROUP_C, 7)  // 151

#define GPIO4_D0 GPIO_PIN(4, GROUP_D, 0)  // 152
#define GPIO4_D1 GPIO_PIN(4, GROUP_D, 1)  // 153
#define GPIO4_D2 GPIO_PIN(4, GROUP_D, 2)  // 154
#define GPIO4_D3 GPIO_PIN(4, GROUP_D, 3)  // 155
#define GPIO4_D4 GPIO_PIN(4, GROUP_D, 4)  // 156
#define GPIO4_D5 GPIO_PIN(4, GROUP_D, 5)  // 157
#define GPIO4_D6 GPIO_PIN(4, GROUP_D, 6)  // 158
#define GPIO4_D7 GPIO_PIN(4, GROUP_D, 7)  // 159

#endif //GPIO_DEF_H
