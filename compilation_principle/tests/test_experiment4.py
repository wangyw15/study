import pytest

from compiler.lexer import tokenize
from compiler.parser import ast
from compiler.interpreter import execute
from . import code_helper

code_example = code_helper.get_test_code("experiment4_example")
code_division_by_zero = code_helper.get_test_code("expression_division_by_zero")
code_leading_minus = code_helper.get_test_code("expression_leading_minus")
code_long = code_helper.get_test_code("expression_long")
code_identifier = code_helper.get_test_code("experiment3_example")


def test_execute_example():
    assert execute(ast(tokenize(code_example))) == 17


def test_execute_division_by_zero():
    with pytest.raises(ZeroDivisionError):
        execute(ast(tokenize(code_division_by_zero)))


def test_execute_leading_minus():
    assert execute(ast(tokenize(code_leading_minus))) == -108


def test_execute_long():
    assert execute(ast(tokenize(code_long))) == 2


def test_execute_identifier():
    with pytest.raises(ValueError, match="identifier not supported"):
        execute(ast(tokenize(code_identifier)))
