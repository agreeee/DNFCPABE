#ifndef __INC_SM3_H__
#define __INC_SM3_H__


/// <summary>
/// ���ܣ�SM3�Ӵ��㷨
/// </summary>
/// <param name="input">ԭ��</param>
/// <param name="ilen">ԭ���ֽ���</param>
/// <param name="output">���32�ֽ��Ӵ�ֵ</param>
void sm3(unsigned char *input, int ilen, unsigned char output[32]);


#endif // !__INC_SM3_H__