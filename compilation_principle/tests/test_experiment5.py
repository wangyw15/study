import pytest

from compiler.lexer import tokenize
from compiler.parser import ast
from compiler.interpreter import intermediate
from compiler.types import ExpressionType, IntermediateTuple
from . import code_helper


code_example = code_helper.get_test_code("experiment5_example")
code_division_by_zero = code_helper.get_test_code("expression_division_by_zero")
code_leading_minus = code_helper.get_test_code("expression_leading_minus")
code_long = code_helper.get_test_code("expression_long")
code_identifier = code_helper.get_test_code("experiment3_example")


def test_intermediate_example():
    expected = [
        IntermediateTuple(ExpressionType.ADD, "b", "c", "t1"),
        IntermediateTuple(ExpressionType.MULTIPLY, "a", "t1", "t2"),
    ]
    assert intermediate(ast(tokenize(code_example))) == expected


def test_intermediate_division_by_zero():
    with pytest.raises(ZeroDivisionError):
        intermediate(ast(tokenize(code_division_by_zero)))


def test_intermediate_leading_minus():
    expected = [
        IntermediateTuple(ExpressionType.MULTIPLY, "12", "9", "t1"),
        IntermediateTuple(ExpressionType.MINUS, "0", "t1", "t2"),
    ]
    assert intermediate(ast(tokenize(code_leading_minus))) == expected


def test_intermediate_long():
    expected = [
        IntermediateTuple(ExpressionType.ADD, "192", "98", "t1"),
        IntermediateTuple(ExpressionType.MULTIPLY, "t1", "09", "t2"),
        IntermediateTuple(ExpressionType.DIVIDE, "84", "21", "t3"),
        IntermediateTuple(ExpressionType.ADD, "t2", "t3", "t4"),
        IntermediateTuple(ExpressionType.ADD, "t4", "0", "t5"),
        IntermediateTuple(ExpressionType.MULTIPLY, "13", "100", "t6"),
        IntermediateTuple(ExpressionType.DIVIDE, "14", "2", "t7"),
        IntermediateTuple(ExpressionType.ADD, "t6", "t7", "t8"),
        IntermediateTuple(ExpressionType.DIVIDE, "t5", "t8", "t9"),
    ]
    assert intermediate(ast(tokenize(code_long))) == expected


def test_intermediate_identifier():
    expected = [
        IntermediateTuple(ExpressionType.ADD, "a", "15", "t1"),
        IntermediateTuple(ExpressionType.MULTIPLY, "t1", "b", "t2"),
    ]
    assert intermediate(ast(tokenize(code_identifier))) == expected
