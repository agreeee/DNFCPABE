#ifndef __INC_SM3_H__
#define __INC_SM3_H__


/// <summary>
/// 国密：SM3杂凑算法
/// </summary>
/// <param name="input">原文</param>
/// <param name="ilen">原文字节数</param>
/// <param name="output">输出32字节杂凑值</param>
void sm3(unsigned char *input, int ilen, unsigned char output[32]);


#endif // !__INC_SM3_H__