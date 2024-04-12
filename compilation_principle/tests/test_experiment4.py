import pytest

from compiler.lexer import tokenize
from compiler.parser import ast
from compiler.interpreter import execute
from . import code_helper

code_example = code_helper.get_test_code("experiment4_example")


def test_execute_example():
    assert execute(ast(tokenize(code_example))) == 17
