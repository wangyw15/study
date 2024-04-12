from compiler.types import ExpressionType, ExpressionNode, IntermediateTuple


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


_index = 0
_tuples: list[IntermediateTuple] = []


def _generate_intermediate(root: ExpressionNode) -> str:
    global _index

    if root.type in [ExpressionType.NUMBER, ExpressionType.IDENTIFIER]:
        return root.data

    left = _generate_intermediate(root.left)
    right = _generate_intermediate(root.right)

    # division by zero
    if root.type == ExpressionType.DIVIDE and right == "0":
        raise ZeroDivisionError("division by zero")

    if root.type in [
        ExpressionType.ADD,
        ExpressionType.MINUS,
        ExpressionType.MULTIPLY,
        ExpressionType.DIVIDE,
    ]:
        _index += 1
        _tuples.append(IntermediateTuple(root.type, left, right, f"t{_index}"))
        return f"t{_index}"

    raise ValueError("unknown expression type")


def intermediate(root: ExpressionNode) -> list[IntermediateTuple]:
    """
    Generate the intermediate representation of the expression tree
    :param root: the root of the expression tree
    :return: the intermediate representation of the expression tree
    """
    global _index, _tuples
    _index = 0
    _tuples = []
    _generate_intermediate(root)
    return _tuples
