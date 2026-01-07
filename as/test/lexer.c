/* SPDX-License-Identifier: Apache-2.0 */
#include "str.h"
#include <tokens.h>
#include <lexer.h>
#include <nurse.h>

test(symbol) {
    struct lexer l = { str("foo "), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, SYMBOL);
    assert_eq(tok.offset, 0);
}

test(label) {
    struct lexer l = { str("foo:"), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, LABEL_TOK);
    assert_eq(tok.offset, 0);
}

test(constant) {
    struct lexer l = { str("#7133876"), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, CONSTANT);
    assert_eq(tok.offset, 0);
}

test(valid_registers) {
    struct lexer l = { str("R0 SP BP"), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, REGISTER);
    assert_eq(tok.offset, 0);

    tok = lexer_next(&l);
    assert_eq(tok.type, REGISTER);
    assert_eq(tok.offset, 3);

    tok = lexer_next(&l);
    assert_eq(tok.type, REGISTER);
    assert_eq(tok.offset, 7);
}

test(comma) {
    struct lexer l = { str(","), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, COMMA);
    assert_eq(tok.offset, 0);
}

test(sample_code) {
    struct lexer l = { str("add:\n"
                           "  add R0, R1, R2\n"), 0 };

    struct token tok = lexer_next(&l);
    assert_eq(tok.type, LABEL_TOK);

    enum token_type types[] = {
        SYMBOL, REGISTER, COMMA, REGISTER, COMMA, REGISTER, END
    };

    for (int i = 0; i < 7; i++) {
        tok = lexer_next(&l);
        assert_eq(types[i], tok.type);
    }
}

suite(basic) {
    run_test(symbol);
    run_test(label);
    run_test(constant);
    run_test(valid_registers);
    run_test(comma);
    run_test(sample_code);
}
