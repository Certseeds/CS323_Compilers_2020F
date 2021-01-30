#include "mips32.hpp"

/* the output file descriptor, may not be explicitly used */
FILE *fd;

inline auto tac_kind(tac *tac_) {
    return tac_->code.kind;
}

inline auto reg_name(Register reg) {
    return regs[reg].name;
}

#define tac_quadruple(tac) (((tac)->code).tac)

Register get_register(tac_opd *opd) {
    assert(opd->kind == tac_opd::OP_VARIABLE);
    char *var = opd->char_val;
    /* COMPLETE the register allocation */
    return t0;
}

Register get_register_w(tac_opd *opd) {
    assert(opd->kind == tac_opd::OP_VARIABLE);
    char *var = opd->char_val;
    /* COMPLETE the register allocation (for write) */
    return s0;
}

void spill_register(Register reg) {
    /* COMPLETE the register spilling */
}


void mips_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(fd, fmt, args);
    va_end(args);
    fputs("\n", fd);
}

void _mips_iprintf(const char *fmt, ...) {
    va_list args;
    fputs("  ", fd); // `iprintf` stands for indented printf
    va_start(args, fmt);
    vfprintf(fd, fmt, args);
    va_end(args);
    fputs("\n", fd);
}


/* PARAM: a pointer to `struct tac_node` instance
   RETURN: the next instruction to be translated */
tac *emit_label(tac *label) {
    assert(tac_kind(label) == tac_inst::LABEL);
    mips_printf("label%d:", tac_quadruple(label).labelno->int_val);
    return label->next;
}

tac *emit_function(tac *function) {
    mips_printf("%s:", tac_quadruple(function).funcname);
    return function->next;
}

tac *emit_assign(tac *assign) {
    Register x, y;

    x = get_register_w(tac_quadruple(assign).left);
    if (tac_quadruple(assign).right->kind == tac_opd::OP_CONSTANT) {
        _mips_iprintf("li %s, %d", reg_name(x),
                      tac_quadruple(assign).right->int_val);
    } else {
        y = get_register(tac_quadruple(assign).right);
        _mips_iprintf("move %s, %s", reg_name(x), reg_name(y));
    }
    return assign->next;
}

tac *emit_add(tac *add) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(add).left);
    if (tac_quadruple(add).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(add).r2);
        _mips_iprintf("addi %s, %s, %d", reg_name(x),
                      reg_name(y),
                      tac_quadruple(add).r1->int_val);
    } else if (tac_quadruple(add).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(add).r1);
        _mips_iprintf("addi %s, %s, %d", reg_name(x),
                      reg_name(y),
                      tac_quadruple(add).r2->int_val);
    } else {
        y = get_register(tac_quadruple(add).r1);
        z = get_register(tac_quadruple(add).r2);
        _mips_iprintf("add %s, %s, %s", reg_name(x),
                      reg_name(y),
                      reg_name(z));
    }
    return add->next;
}

tac *emit_sub(tac *sub) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(sub).left);
    if (tac_quadruple(sub).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(sub).r2);
        _mips_iprintf("neg %s, %s", reg_name(y), reg_name(y));
        _mips_iprintf("addi %s, %s, %d", reg_name(x),
                      reg_name(y),
                      tac_quadruple(sub).r1->int_val);
    } else if (tac_quadruple(sub).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(sub).r1);
        _mips_iprintf("addi %s, %s, -%d", reg_name(x),
                      reg_name(y),
                      tac_quadruple(sub).r2->int_val);
    } else {
        y = get_register(tac_quadruple(sub).r1);
        z = get_register(tac_quadruple(sub).r2);
        _mips_iprintf("sub %s, %s, %s", reg_name(x),
                      reg_name(y),
                      reg_name(z));
    }
    return sub->next;
}

tac *emit_mul(tac *mul) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(mul).left);
    if (tac_quadruple(mul).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register_w(tac_quadruple(mul).r1);
        z = get_register(tac_quadruple(mul).r2);
        _mips_iprintf("lw %s, %d", reg_name(y),
                      tac_quadruple(mul).r1->int_val);
    } else if (tac_quadruple(mul).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(mul).r1);
        z = get_register_w(tac_quadruple(mul).r2);
        _mips_iprintf("lw %s, %d", reg_name(z),
                      tac_quadruple(mul).r2->int_val);
    } else {
        y = get_register(tac_quadruple(mul).r1);
        z = get_register(tac_quadruple(mul).r2);
    }
    _mips_iprintf("mul %s, %s, %s", reg_name(x),
                  reg_name(y),
                  reg_name(z));
    return mul->next;
}

tac *emit_div(tac *div) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(div).left);
    if (tac_quadruple(div).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register_w(tac_quadruple(div).r1);
        z = get_register(tac_quadruple(div).r2);
        _mips_iprintf("lw %s, %d", reg_name(y),
                      tac_quadruple(div).r1->int_val);
    } else if (tac_quadruple(div).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(div).r1);
        z = get_register_w(tac_quadruple(div).r2);
        _mips_iprintf("lw %s, %d", reg_name(z),
                      tac_quadruple(div).r2->int_val);
    } else {
        y = get_register(tac_quadruple(div).r1);
        z = get_register(tac_quadruple(div).r2);
    }
    _mips_iprintf("div %s, %s", reg_name(y), reg_name(z));
    _mips_iprintf("mflo %s", reg_name(x));
    return div->next;
}

tac *emit_addr(tac *addr) {
    Register x, y;

    x = get_register_w(tac_quadruple(addr).left);
    y = get_register(tac_quadruple(addr).right);
    _mips_iprintf("move %s, %s", reg_name(x), reg_name(y));
    return addr->next;
}

tac *emit_fetch(tac *fetch) {
    Register x, y;

    x = get_register_w(tac_quadruple(fetch).left);
    y = get_register(tac_quadruple(fetch).raddr);
    _mips_iprintf("lw %s, 0(%s)", reg_name(x), reg_name(y));
    return fetch->next;
}

tac *emit_deref(tac *deref) {
    Register x, y;

    x = get_register(tac_quadruple(deref).laddr);
    y = get_register(tac_quadruple(deref).right);
    _mips_iprintf("sw %s, 0(%s)", reg_name(y), reg_name(x));
    return deref->next;
}

tac *emit_goto(tac *goto_) {
    _mips_iprintf("j label%d", tac_quadruple(goto_).labelno->int_val);
    return goto_->next;
}

tac *emit_iflt(tac *iflt) {
    /* COMPLETE emit function */
    return iflt->next;
}

tac *emit_ifle(tac *ifle) {
    /* COMPLETE emit function */
    return ifle->next;
}

tac *emit_ifgt(tac *ifgt) {
    /* COMPLETE emit function */
    return ifgt->next;
}

tac *emit_ifge(tac *ifge) {
    /* COMPLETE emit function */
    return ifge->next;
}

tac *emit_ifne(tac *ifne) {
    /* COMPLETE emit function */
    return ifne->next;
}

tac *emit_ifeq(tac *ifeq) {
    /* COMPLETE emit function */
    return ifeq->next;
}

tac *emit_return(tac *return_) {
    /* COMPLETE emit function */
    return return_->next;
}

tac *emit_dec(tac *dec) {
    /* NO NEED TO IMPLEMENT */
    return dec->next;
}

tac *emit_arg(tac *arg) {
    /* COMPLETE emit function */
    return arg->next;
}

tac *emit_call(tac *call) {
    /* COMPLETE emit function */
    return call->next;
}

tac *emit_param(tac *param) {
    /* COMPLETE emit function */
    return param->next;
}

tac *emit_read(tac *read) {
    Register x = get_register(tac_quadruple(read).p);

    _mips_iprintf("addi $sp, $sp, -4");
    _mips_iprintf("sw $ra, 0($sp)");
    _mips_iprintf("jal read");
    _mips_iprintf("lw $ra, 0($sp)");
    _mips_iprintf("addi $sp, $sp, 4");
    _mips_iprintf("move %s, $v0", reg_name(x));
    return read->next;
}

tac *emit_write(tac *write) {
    Register x = get_register_w(tac_quadruple(write).p);

    _mips_iprintf("move $a0, %s", reg_name(x));
    _mips_iprintf("addi $sp, $sp, -4");
    _mips_iprintf("sw $ra, 0($sp)");
    _mips_iprintf("jal write");
    _mips_iprintf("lw $ra, 0($sp)");
    _mips_iprintf("addi $sp, $sp, 4");
    return write->next;
}

void emit_preamble() {
    mips_printf("# SPL compiler generated assembly");
    mips_printf(".data");
    mips_printf("_prmpt: .asciiz \"Enter an integer: \"");
    mips_printf(R"(_eol: .asciiz "\n")");
    mips_printf(".globl main");
    mips_printf(".text");
}

void emit_read_function() {
    mips_printf("read:");
    _mips_iprintf("li $v0, 4");
    _mips_iprintf("la $a0, _prmpt");
    _mips_iprintf("syscall");
    _mips_iprintf("li $v0, 5");
    _mips_iprintf("syscall");
    _mips_iprintf("jr $ra");
}

void emit_write_function() {
    mips_printf("write:");
    _mips_iprintf("li $v0, 1");
    _mips_iprintf("syscall");
    _mips_iprintf("li $v0, 4");
    _mips_iprintf("la $a0, _eol");
    _mips_iprintf("syscall");
    _mips_iprintf("move $v0, $0");
    _mips_iprintf("jr $ra");
}

static tac *(*emitter[])(tac *) = {
        emit_label, emit_function, emit_assign,
        emit_add, emit_sub, emit_mul, emit_div,
        emit_addr, emit_fetch, emit_deref, emit_goto,
        emit_iflt, emit_ifle, emit_ifgt, emit_ifge, emit_ifne, emit_ifeq,
        emit_return, emit_dec, emit_arg, emit_call, emit_param,
        emit_read, emit_write
};

tac *emit_code(tac *head) {
    tac *(*tac_emitter)(tac *);
    tac *tac_code = head;
    emit_preamble();
    emit_read_function();
    emit_write_function();
    while (tac_code != nullptr) {
        if (tac_kind(tac_code) != tac_inst::NONE) {
            tac_emitter = emitter[tac_kind(tac_code)];
            tac_code = tac_emitter(tac_code);
        } else {
            tac_code = tac_code->next;
        }
    }
}

/* translate a TAC list into mips32 assembly
   output the textual assembly code to _fd */
void mips32_gen(tac *head, FILE *_fd) {
    regs[zero].name = "$zero";
    regs[at].name = "$at";
    regs[v0].name = "$v0";
    regs[v1].name = "$v1";
    regs[a0].name = "$a0";
    regs[a1].name = "$a1";
    regs[a2].name = "$a2";
    regs[a3].name = "$a3";
    regs[t0].name = "$t0";
    regs[t1].name = "$t1";
    regs[t2].name = "$t2";
    regs[t3].name = "$t3";
    regs[t4].name = "$t4";
    regs[t5].name = "$t5";
    regs[t6].name = "$t6";
    regs[t7].name = "$t7";
    regs[s0].name = "$s0";
    regs[s1].name = "$s1";
    regs[s2].name = "$s2";
    regs[s3].name = "$s3";
    regs[s4].name = "$s4";
    regs[s5].name = "$s5";
    regs[s6].name = "$s6";
    regs[s7].name = "$s7";
    regs[t8].name = "$t8";
    regs[t9].name = "$t9";
    regs[k0].name = "$k0";
    regs[k1].name = "$k1";
    regs[gp].name = "$gp";
    regs[sp].name = "$sp";
    regs[fp].name = "$fp";
    regs[ra].name = "$ra";
    vars = new VarDesc();
    vars->next = nullptr;
    fd = _fd;
    emit_code(head);
}
