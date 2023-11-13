#include "pbc-class.h"
#include <stdio.h>

/// <summary>
/// ȫ�ֱ���
/// </summary>
namespace PbcInit {
	/// <summary>
	/// ˫���Զ�
	/// </summary>
	pairing_t bilinear_pairing;
	bool inited = false;
}
/// <summary>
/// ͨ��cmd������ʼ��˫���ԶԲ���
/// <para>main��������д��ʽ����Ϊ</para>
/// <para>int main(int argc, char *argv[])</para>
/// <para>����������������������</para>
/// </summary>
/// <param name="argc"> : ����main����</param>
/// <param name="argv"> : ����main����</param>
void pbc_init(int argc, char *argv[]) {
	PbcInit::inited = true;
	pbc_demo_pairing_init(
		PbcInit::bilinear_pairing,
		argc, argv
	);
	return;
}
/// <summary>
/// �ͷ��ڴ棬����������֮ǰ�������
/// </summary>
void pbc_clear() {
	PbcInit::inited = false;
	pairing_clear(PbcInit::bilinear_pairing);
	return;
}

/*=========  ABEelement  =========*/
PBC_Element::~PBC_Element() {
#ifdef _CALL_DEBUG_
	printf("%s is called\n", __FUNCTION__);
#endif // _CALL_DEBUG_

	element_clear(this->val);
}
void PBC_Element::rand() {
	this->val->field->random(this->val);
	return;
}

void PBC_Element::set0() {
	this->val->field->set0(this->val);
	return;
}
void PBC_Element::set1() {
	this->val->field->set1(this->val);
	return;
}
void PBC_Element::set_si(signed long int i) {
	this->val->field->set_si(this->val, i);
	return;
}
int PBC_Element::size() {
	return element_length_in_bytes(this->val);
}
bool PBC_Element::isEqualTo(PBC_Element &X) {
	return !element_cmp(this->val, X.val);
}
void PBC_Element::print() {
	element_printf("%B\n", this->val);
	return;
}
void PBC_Element::print(const char *format) {
	printf(format);
	element_printf("%B\n", this->val);
	return;
}
void PBC_Element::copy(PBC_Element &n) {
	this->val->field->set(this->val, n.val);
	return;
}
int PBC_Element::toBytes(void *Buf) {
	return element_to_bytes(
		(unsigned char *)Buf, this->val
	);
}
int PBC_Element::setFromBytes(void *Buf) {
	return element_from_bytes(
		this->val, (unsigned char *)Buf
	);
}
/*=============  Zr  =============*/
Zr::Zr() {
#ifdef _CALL_DEBUG_
	printf("%s is called\n", __FUNCTION__);
#endif // _CALL_DEBUG_

	element_init_Zr(
		this->val,
		PbcInit::bilinear_pairing
	);
}
void Zr::add(Zr &X, Zr &Y) {
	this->val->field->add(
		this->val,
		X.val, Y.val
	);
	return;
}
void Zr::sub(Zr &X, Zr &Y) {
	this->val->field->sub(
		this->val,
		X.val, Y.val
	);
	return;
}
void Zr::mul(Zr &X, Zr &Y) {
	this->val->field->mul(
		this->val,
		X.val, Y.val
	);
	return;
}
void Zr::div(Zr &X, Zr &Y) {
	this->val->field->div(
		this->val,
		X.val, Y.val
	);
	return;
}
void Zr::inv(Zr& GX) {
	this->val->field->invert(
		this->val, GX.val
	);
	return;
}
void Zr::neg(Zr &X) {
	this->val->field->neg(
		this->val,
		X.val
	);
	return;
}

/*=============  G  =============*/
G::G() {
#ifdef _CALL_DEBUG_
	printf("%s is called\n", __FUNCTION__);
#endif // _CALL_DEBUG_

	element_init_G1(
		this->val,
		PbcInit::bilinear_pairing
	);
}
void G::add(G &aP, G &bP) {
	this->val->field->add(
		this->val,
		aP.val, bP.val
	);
	return;
}
void G::sub(G & X, G & Y) {
	this->val->field->sub(
		this->val,
		X.val, Y.val
	);
	return;
}
void G::DotPro(Zr &n, G &P) {
	element_pow_zn(
		this->val,
		P.val, n.val
	);
	return;
}

/*=============  GT  =============*/
GT::GT() {
#ifdef _CALL_DEBUG_
	printf("%s is called\n", __FUNCTION__);
#endif // _CALL_DEBUG_

	element_init_GT(
		this->val,
		PbcInit::bilinear_pairing
	);
}
void GT::add(GT& GX, GT& GY) {
	this->val->field->add(
		this->val,
		GX.val, GY.val
	);
	return;
}
void GT::pow(GT &GX, Zr &n) {
	element_pow_zn(
		this->val,
		GX.val, n.val
	);
	return;
}
void GT::E(G &P, G &Q) {
	pairing_apply(
		this->val, P.val, Q.val,
		PbcInit::bilinear_pairing
	);
	return;
}
void GT::inv(GT &GX) {
	this->val->field->invert(
		this->val, GX.val
	);
	return;
}
void GT::mul(GT &GX, GT &GY) {
	this->val->field->mul(
		this->val,
		GX.val, GY.val
	);
	return;
}
void GT::div(GT &GX, GT &GY) {
	this->val->field->div(
		this->val,
		GX.val, GY.val
	);
	return;
}
