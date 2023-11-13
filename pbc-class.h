#ifndef __PBC_CLASS_H__
#define __PBC_CLASS_H__
#include <pbc.h>
#include <pbc_test.h>

//#define _CALL_DEBUG_	//打开函数调用检查

void pbc_init(int argc, char *argv[]);

void pbc_clear();

/// <summary>
/// 元素类
/// <para>所有KP-ABE需要的运算类的基类</para>
/// <para>由此类派生出其他对象</para>
/// <para>定义了公用的类方法</para>
/// </summary>
class PBC_Element {
public:
	/// <summary>
	/// 元素的值
	/// </summary>
	element_t val;
	/// <summary>
	/// 在元素的代数结构内随机赋值
	/// </summary>
	void rand();
	/// <summary>
	/// 将元素的数值打印出来
	/// </summary>
	void print();
	/// <summary>
	/// 将元素的值打印出来
	/// </summary>
	/// <param name="str">打印元素之前先打印该内容</param>
	void print(const char *str);
	/// <summary>
	/// 将元素设置为该代数结构中的零元素O
	/// </summary>
	void set0();
	/// <summary>
	/// 将元素设置为该代数结构中的幺元e
	/// </summary>
	void set1();
	/// <summary>
	/// 将元素设置为该代数结构中的有符号长整型i
	/// </summary>
	void set_si(signed long int i);
	/// <returns>该元素所占用的字节数</returns>
	int size();
	/// <returns>this == X ? true : false</returns>
	bool isEqualTo(PBC_Element &X);
	/// <summary>
	/// 复制元素
	/// <para>this = n</para>
	/// </summary>
	/// <param name="n"> : 要复制的元素</param>
	void copy(PBC_Element &n);
	/// <summary>
	/// 将元素写入内存中，并返回写入的字节数
	/// </summary>
	/// <param name="Buf">字节串</param>
	/// <returns>写入Buf的字节数</returns>
	int toBytes(void *Buf);
	/// <summary>
	/// 根据自身的数据种类，从内存中读取相应的字节数作为元素的值
	/// </summary>
	/// <param name="Buf">字节串</param>
	/// <returns>读入Buf的字节数</returns>
	int setFromBytes(void *Buf);
	PBC_Element() = default;
	/// <summary>
	/// 元素在程序结束或确定不再使用时自动删除内存
	/// </summary>
	~PBC_Element();
};

/// <summary>
/// 整数域类
/// <para>域中元素均在[0 ~ r-1]内</para>
/// <para>r为素数，且r为 G1 群，G2 群和 GT 群的阶</para>
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
/// 椭圆曲线群 G1
/// </summary>
class G : public PBC_Element {
public:
	G();
	/// <summary>
	/// 群加法运算
	/// <para> this = aP + bP = (a + b)P </para>
	/// </summary>
	/// <param name="aP">椭圆曲线群G1上的点</param>
	/// <param name="bP">椭圆曲线群G1上的点</param>
	void add(G &aP, G &bP);
	/// <summary>
	/// this = X - Y
	/// </summary>
	/// <param name="X"></param>
	/// <param name="Y"></param>
	void sub(G & X, G & Y);
	/// <summary>
	/// 点乘运算
	/// <para> this = n * P </para>
	/// </summary>
	/// <param name="n">Zr上的大数</param>
	/// <param name="P">椭圆曲线群G1上的点</param>
	void DotPro(Zr &n, G &P);
};

/// <summary>
/// 由椭圆曲线群配对映射的对象群 GT
/// <para>GT是个乘法域</para>
/// <para>GT = e(G1,G2)</para>
/// <para>有e(a*G1,b*G2) == e(G1,G2)^(a*b)</para>
/// </summary>
class GT : public  PBC_Element {
public:
	GT();
	/// <summary>
	/// 群加法运算
	/// <para> this = aP + bP = (a + b)P </para>
	/// </summary>
	/// <param name="aP">椭圆曲线群G2上的点</param>
	/// <param name="bP">椭圆曲线群G2上的点</param>
	void add(GT &GX, GT &GY);
	/// <summary>
	/// this = GX ^ n
	/// </summary>
	/// <param name="GX"> GT上的元素 </param>
	/// <param name="n"> Zr上的大整数 </param>
	void pow(GT &GX, Zr &n);
	/// <summary>
	/// this = E( P , Q )
	/// </summary>
	/// <param name="P"> 椭圆曲线群G1上的点 </param>
	/// <param name="Q"> 椭圆曲线群G1上的点 </param>
	void E(G &P, G &Q);
	/// <summary>
	/// this = inv(Gx)
	/// </summary>
	/// <param name="GX"> GT上的元素 </param>
	void inv(GT &GX);
	/// <summary>
	/// this = GX * GY
	/// </summary>
	/// <param name="GX"> GT上的元素 </param>
	/// <param name="GY"> GT上的元素 </param>
	void mul(GT &GX, GT &GY);
	/// <summary>
	/// this = GX / GY
	/// </summary>
	/// <param name="GX"> GT上的元素 </param>
	/// <param name="GY"> GT上的元素 </param>
	void div(GT &GX, GT &GY);
};

#endif // !__INC_KP_ABE_PBC_H__