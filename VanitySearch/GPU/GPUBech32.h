#pragma once

// ---------------------------------------------------------------------------------
// Bech32
// ---------------------------------------------------------------------------------

__device__ __constant__ char pszBech32Charset[] = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";
__device__ __constant__ char pszBech32HRP[] = "bc";

// 8位转5位
__device__ void ConvertBits5(const unsigned char* in, int inLen, unsigned char* out, int* outLen) {
    int acc = 0;
    int bits = 0;
    int outPos = 0;
    for (int i = 0; i < inLen; i++) {
        acc = (acc << 8) | in[i];
        bits += 8;
        while (bits >= 5) {
            out[outPos++] = (acc >> (bits - 5)) & 0x1F;
            bits -= 5;
        }
    }
    if (bits > 0) {
        out[outPos++] = (acc << (5 - bits)) & 0x1F;
    }
    *outLen = outPos;
}

// Bech32校验码（简化版，适合GPU环境）
__device__ uint32_t Bech32Polymod(const unsigned char* values, int length) {
    uint32_t chk = 1;
    for (int i = 0; i < length; ++i) {
        uint8_t top = chk >> 25;
        chk = ((chk & 0x1ffffff) << 5) ^ values[i];
        if (top & 1) chk ^= 0x3b6a57b2;
        if (top & 2) chk ^= 0x26508e6d;
        if (top & 4) chk ^= 0x1ea119fa;
        if (top & 8) chk ^= 0x3d4233dd;
        if (top & 16) chk ^= 0x2a1462b3;
    }
    return chk;
}

__device__ void Bech32CreateChecksum(const char* hrp, const unsigned char* data, int dataLen, unsigned char* checksum) {
    int hrpLen = 2; // "bc"
    unsigned char values[90];
    int v = 0;
    // Expand HRP
    for (int i = 0; i < hrpLen; ++i) values[v++] = hrp[i] >> 5;
    values[v++] = 0;
    for (int i = 0; i < hrpLen; ++i) values[v++] = hrp[i] & 0x1F;
    // Data
    for (int i = 0; i < dataLen; ++i) values[v++] = data[i];
    // 6 zeroes for checksum
    for (int i = 0; i < 6; ++i) values[v++] = 0;
    uint32_t polymod = Bech32Polymod(values, v) ^ 1;
    for (int i = 0; i < 6; ++i) {
        checksum[i] = (polymod >> (5 * (5 - i))) & 0x1F;
    }
}

// hash160: 20字节输入，bech32Add: 输出字符串
__device__ __noinline__ void _GetAddress_Bech32(const unsigned char* hash160, char* bech32Add) {
    unsigned char data[32];
    int dataLen = 0;
    // 版本字节0 + hash160
    data[0] = 0;
    for (int i = 0; i < 20; ++i) data[i + 1] = hash160[i];
    dataLen = 21;
    // 8位转5位
    unsigned char data5[40];
    int data5Len = 0;
    ConvertBits5(data, dataLen, data5, &data5Len);
    // 计算校验码
    unsigned char checksum[6];
    Bech32CreateChecksum(pszBech32HRP, data5, data5Len, checksum);
    // 拼接字符串
    int pos = 0;
    bech32Add[pos++] = pszBech32HRP[0];
    bech32Add[pos++] = pszBech32HRP[1];
    bech32Add[pos++] = '1';
    for (int i = 0; i < data5Len; ++i) bech32Add[pos++] = pszBech32Charset[data5[i]];
    for (int i = 0; i < 6; ++i) bech32Add[pos++] = pszBech32Charset[checksum[i]];
    bech32Add[pos] = 0;
}
