#ifndef __PBC_CLASS_H__
#define __PBC_CLASS_H__
#include <pbc.h>
#include <pbc_test.h>

//#define _CALL_DEBUG_	//�򿪺������ü��

void pbc_init(int argc, char *argv[]);

void pbc_clear();

/// <summary>
/// Ԫ����
/// <para>����KP-ABE��Ҫ��������Ļ���</para>
/// <para>�ɴ�����������������</para>
/// <para>�����˹��õ��෽��</para>
/// </summary>
class PBC_Element {
public:
	/// <summary>
	/// Ԫ�ص�ֵ
	/// </summary>
	element_t val;
	/// <summary>
	/// ��Ԫ�صĴ����ṹ�������ֵ
	/// </summary>
	void rand();
	/// <summary>
	/// ��Ԫ�ص���ֵ��ӡ����
	/// </summary>
	void print();
	/// <summary>
	/// ��Ԫ�ص�ֵ��ӡ����
	/// </summary>
	/// <param name="str">��ӡԪ��֮ǰ�ȴ�ӡ������</param>
	void print(const char *str);
	/// <summary>
	/// ��Ԫ������Ϊ�ô����ṹ�е���Ԫ��O
	/// </summary>
	void set0();
	/// <summary>
	/// ��Ԫ������Ϊ�ô����ṹ�е���Ԫe
	/// </summary>
	void set1();
	/// <summary>
	/// ��Ԫ������Ϊ�ô����ṹ�е��з��ų�����i
	/// </summary>
	void set_si(signed long int i);
	/// <returns>��Ԫ����ռ�õ��ֽ���</returns>
	int size();
	/// <returns>this == X ? true : false</returns>
	bool isEqualTo(PBC_Element &X);
	/// <summary>
	/// ����Ԫ��
	/// <para>this = n</para>
	/// </summary>
	/// <param name="n"> : Ҫ���Ƶ�Ԫ��</param>
	void copy(PBC_Element &n);
	/// <summary>
	/// ��Ԫ��д���ڴ��У�������д����ֽ���
	/// </summary>
	/// <param name="Buf">�ֽڴ�</param>
	/// <returns>д��Buf���ֽ���</returns>
	int toBytes(void *Buf);
	/// <summary>
	/// ����������������࣬���ڴ��ж�ȡ��Ӧ���ֽ�����ΪԪ�ص�ֵ
	/// </summary>
	/// <param name="Buf">�ֽڴ�</param>
	/// <returns>����Buf���ֽ���</returns>
	int setFromBytes(void *Buf);
	PBC_Element() = default;
	/// <summary>
	/// Ԫ���ڳ��������ȷ������ʹ��ʱ�Զ�ɾ���ڴ�
	/// </summary>
	~PBC_Element();
};

/// <summary>
/// ��������
/// <para>����Ԫ�ؾ���[0 ~ r-1]��</para>
/// <para>rΪ��������rΪ G1 Ⱥ��G2 Ⱥ�� GT Ⱥ�Ľ�</para>
/// </summary>
class Zr : public PBC_Element {
public:
	Zr();
	/// <summary>
	/// this = X + Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void add(Zr &X, Zr &Y);
	/// <summary>
	/// this = X - Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void sub(Zr &X, Zr &Y);
	/// <summary>
	/// this = X * Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void mul(Zr &X, Zr &Y);
	/// <summary>
	/// this = X / Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void div(Zr &X, Zr &Y);
	/// <summary>
	/// this = X ^ (-1)
	/// </summary>
	/// <param name="X"></param>
	void inv(Zr &X);
	/// <summary>
	/// this = -X
	/// </summary>
	/// <param name="X"></param>
	void neg(Zr &X);
};

/// <summary>
/// ��Բ����Ⱥ G1
/// </summary>
class G : public PBC_Element {
public:
	G();
	/// <summary>
	/// Ⱥ�ӷ�����
	/// <para> this = aP + bP = (a + b)P </para>
	/// </summary>
	/// <param name="aP">��Բ����ȺG1�ϵĵ�</param>
	/// <param name="bP">��Բ����ȺG1�ϵĵ�</param>
	void add(G &aP, G &bP);
	/// <summary>
	/// this = X - Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void sub(G & X, G & Y);
	/// <summary>
	/// �������
	/// <para> this = n * P </para>
	/// </summary>
	/// <param name="n">Zr�ϵĴ���</param>
	/// <param name="P">��Բ����ȺG1�ϵĵ�</param>
	void DotPro(Zr &n, G &P);
};

/// <summary>
/// ����Բ����Ⱥ���ӳ��Ķ���Ⱥ GT
/// <para>GT�Ǹ��˷���</para>
/// <para>GT = e(G1,G2)</para>
/// <para>��e(a*G1,b*G2) == e(G1,G2)^(a*b)</para>
/// </summary>
class GT : public  PBC_Element {
public:
	GT();
	/// <summary>
	/// Ⱥ�ӷ�����
	/// <para> this = aP + bP = (a + b)P </para>
	/// </summary>
	/// <param name="aP">��Բ����ȺG2�ϵĵ�</param>
	/// <param name="bP">��Բ����ȺG2�ϵĵ�</param>
	void add(GT &GX, GT &GY);
	/// <summary>
	/// this = GX ^ n
	/// </summary>
	/// <param name="GX"> GT�ϵ�Ԫ�� </param>
	/// <param name="n"> Zr�ϵĴ����� </param>
	void pow(GT &GX, Zr &n);
	/// <summary>
	/// this = E( P , Q )
	/// </summary>
	/// <param name="P"> ��Բ����ȺG1�ϵĵ� </param>
	/// <param name="Q"> ��Բ����ȺG1�ϵĵ� </param>
	void E(G &P, G &Q);
	/// <summary>
	/// this = inv(Gx)
	/// </summary>
	/// <param name="GX"> GT�ϵ�Ԫ�� </param>
	void inv(GT &GX);
	/// <summary>
	/// this = GX * GY
	/// </summary>
	/// <param name="GX"> GT�ϵ�Ԫ�� </param>
	/// <param name="GY"> GT�ϵ�Ԫ�� </param>
	void mul(GT &GX, GT &GY);
	/// <summary>
	/// this = GX / GY
	/// </summary>
	/// <param name="GX"> GT�ϵ�Ԫ�� </param>
	/// <param name="GY"> GT�ϵ�Ԫ�� </param>
	void div(GT &GX, GT &GY);
};

#endif // !__INC_KP_ABE_PBC_H__