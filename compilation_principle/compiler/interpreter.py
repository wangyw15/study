from compiler.types import ExpressionType, ExpressionNode
import math


def execute(root: ExpressionNode) -> float:
    """
    Execute the expression tree
    :param root: the root of the expression tree
    :return: the result of the expression
    """
    if root.type == ExpressionType.NUMBER:
        return float(root.data)

    if root.type == ExpressionType.IDENTIFIER:
        raise ValueError("identifier not supported")

    left = execute(root.left)
    right = execute(root.right)

    if root.type == ExpressionType.ADD:
        return left + right

    if root.type == ExpressionType.MINUS:
        return left - right

    if root.type == ExpressionType.MULTIPLY:
        return left * right

    if root.type == ExpressionType.DIVIDE:
        return left / right

    raise ValueError("unknown expression type")
