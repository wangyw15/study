# 编译原理实验报告

# 实验一 识别标识符

## 实验内容

输入 PL/0 语言源程序，输出源程序中所有标识符的出现次数。

## 实验思路

根据PL/0语法，标识符是由字母和数字组成的字符串且不区分大小写，首字符必须是字母，并且标识符都在程序开头定义（begin关键字之前），所以只需要在begin关键字之前的字符中识别标识符即可。

定义变量的关键字有`const`和`var`，所以只需要在扫描到`const`和`var`之后，再通过正则表达式匹配标识符即可。

有些标识符会赋初值，因此编写正则表达式需要同样匹配赋值符号`:=`。

在识别到所有标识符后，赋初值的提取出标识符名称，并且去重即可。

由于赋值语句可能会跨越多行，因此用一个变量表示当前是否在赋值语句中，如果在赋值语句中，下一行也会继续匹配标识符。

计数则是通过正则表达式和取到的标识符列表进行匹配，如果匹配到了，就在计数器中加一，最后输出结果。

## 关键代码

```python
def get_defined_identifiers(code: str) -> list[str]:
    identifiers: list[str] = []
    lines = code.split("\n")

    # for multiline definition
    identifier_definition = False
    for line in lines:
        # skip empty line
        if not line.strip():
            continue
        # ignores case for now
        lower_line = line.lower()
        # define only occurs before "begin"
        if lower_line.strip() == "begin":
            break
        # define statement
        if lower_line.startswith("const"):
            identifier_definition = True
            lower_line = lower_line[5:].strip()
        elif lower_line.startswith("var"):
            identifier_definition = True
            lower_line = lower_line[3:].strip()
        # skip if not in define statement
        if not identifier_definition:
            continue
        # definition statement ends at semicolon
        if lower_line.endswith(";"):
            identifier_definition = False
            lower_line = lower_line[:-1]
        # multiple identifiers
        current_identifiers = lower_line.split(",")
        for current_identifier in current_identifiers:
            # comma at EOL
            if not current_identifier.strip():
                continue
            # with init value
            if "=" in current_identifier:
                current_identifier = current_identifier.split("=")[0].strip()
            else:
                current_identifier = current_identifier.strip()
            # test if the identifier is valid
            if re.fullmatch(
                TokenType.IDENTIFIER.value, current_identifier, re.IGNORECASE
            ):
                identifiers.append(current_identifier)
            else:
                raise SyntaxError("Invalid identifier: " + current_identifier)
    return identifiers

def count_identifiers(code: str) -> dict[str, int]:
    identifiers = get_defined_identifiers(code)
    # first appears in definition
    result: dict[str, int] = {i: 1 for i in identifiers}
    lines = code.split("\n")

    # define statement at start
    in_code_section = False
    for line in lines:
        # ignores case for now
        lower_line = line.lower().strip()
        # start code section
        if not in_code_section:
            if lower_line == "begin":
                in_code_section = True
            continue
        # end code section
        if re.fullmatch(_procedure_end_pattern, lower_line, re.IGNORECASE):
            in_code_section = False
            continue
        # find identifier
        for identifier in identifiers:
            if re.search(
                    _use_identifier_pattern.format(identifier), lower_line, re.IGNORECASE
            ):
                result[identifier] += 1
    return result
```

# 实验二 词法分析

## 实验内容

输入 PL/0 语言程序，输出程序中各个单词符号（关键字、专用符号以及其它标记）。

## 实验思路

预先定义各种可能出现的关键字和运算符等固定字符或字符串。以空白字符和运算符为分隔，对多字符的运算符做合并，将分割开的字符串与预定义的关键字、运算符和实验一所取到的标识符等，通过正则表达式进行匹配并输出。

## 关键代码

```python
def is_token_boundary(char: str, next_char: str) -> bool:
    boundary_chars = list("+-*/()=.:;,")
    return (
        re.fullmatch(TokenType.IDENTIFIER.value, char, re.IGNORECASE)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(TokenType.IDENTIFIER.value, next_char, re.IGNORECASE)
        or re.fullmatch(TokenType.NUMBER.value, char, re.IGNORECASE)
        and next_char in boundary_chars
        or char in boundary_chars
        and re.fullmatch(TokenType.NUMBER.value, next_char, re.IGNORECASE)
        or char in boundary_chars
        and next_char in boundary_chars
        or char.isspace()
        or next_char.isspace()
    )


def tokenize(code: str) -> list[Token]:
    result: list[Token] = []

    tokens: list[str] = []
    # spilt codes
    token_tmp = ""
    code = code + " "  # for enumerate
    for index, char in enumerate(code[:-1]):
        char: str
        if not char.isspace():
            token_tmp += char

        # detect word boundary
        if is_token_boundary(char, code[index + 1]):
            if token_tmp:
                tokens.append(token_tmp)
                token_tmp = ""

    # combine multi-char tokens
    tokens.append("")  # for last token
    processed_tokens: list[str] = []
    for index, token in enumerate(tokens[:-1]):
        if token + tokens[index + 1] == ":=":
            processed_tokens.append(":=")
            continue
        elif tokens[index - 1] + token == ":=":
            continue
        if token:
            processed_tokens.append(token)
    tokens = processed_tokens

    # detect tokens
    for token in tokens:
        token_type = None
        for t in TokenType:
            if re.fullmatch(t.value, token, re.IGNORECASE):
                token_type = t
                break
        if not token_type:
            if re.fullmatch(TokenType.IDENTIFIER.value, token, re.IGNORECASE):
                token_type = TokenType.IDENTIFIER
            else:
                token_type = TokenType.UNKNOWN
        if token_type:
            result.append(Token(token_type, token))

    return result
```

# 实验三 语法分析

## 实验内容

已给 PL/0 语言文法，构造表达式部分的语法分析器。

## 实验思路

已知BNF，使用递归下降算法即可，匹配出错时抛出异常。

## 关键代码

```python
def _add_operator() -> ExpressionType:
    """
    <add_operator> ::= '+' | '-'
    :return: the type of the operator if the current token is an add operator, None otherwise
    """
    global _token_index
    # print("plus", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _tokens[_token_index].type == TokenType.PLUS:
        _token_index += 1
        return ExpressionType.ADD

    elif _tokens[_token_index].type == TokenType.MINUS:
        _token_index += 1
        return ExpressionType.MINUS

    return ExpressionType.UNKNOWN


def _multiply_operator() -> ExpressionType:
    """
    <multiply_operator> ::= '*' | '/'
    :return: the type of the operator if the current token is a multiply operator, None otherwise
    """
    global _token_index
    # print("multiply", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    if _tokens[_token_index].type == TokenType.ASTERISK:
        _token_index += 1
        return ExpressionType.MULTIPLY

    elif _tokens[_token_index].type == TokenType.SLASH:
        _token_index += 1
        return ExpressionType.DIVIDE

    return ExpressionType.UNKNOWN


def _factor() -> ExpressionNode:
    """
    <factor> ::= <identifier> | <unsigned int> | '(' <expression> ')'
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("factor", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for identifier
    if re.fullmatch(
        TokenType.IDENTIFIER.value,
        _tokens[_token_index].data,
        re.IGNORECASE,
    ):
        node = ExpressionNode(ExpressionType.IDENTIFIER, _tokens[_token_index].data)
        _token_index += 1
        return node

    # check for number
    if re.fullmatch(TokenType.NUMBER.value, _tokens[_token_index].data, re.IGNORECASE):
        node = ExpressionNode(ExpressionType.NUMBER, _tokens[_token_index].data)
        _token_index += 1
        return node

    # check for expression with parenthesis
    if not _tokens[_token_index].type == TokenType.LEFT_PARENTHESIS:
        raise SyntaxError("invalid syntax")
    _token_index += 1

    node = _expression()
    if not node:
        raise SyntaxError("invalid syntax")

    if (
        _token_index == len(_tokens)  # unexpected end of expression
        or not _tokens[_token_index].type == TokenType.RIGHT_PARENTHESIS
    ):
        raise SyntaxError("'(' was never closed")
    _token_index += 1

    return node


def _term() -> ExpressionNode:
    """
    <term> ::= <factor> { <multiply_operator> <factor> }
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("item", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for atomic expression
    node = _factor()
    if not node:
        raise SyntaxError("invalid syntax")

    while True:
        # end of expression
        if _token_index == len(_tokens):
            break

        operator = _multiply_operator()
        if operator == ExpressionType.UNKNOWN:
            break

        right_node = _factor()
        if not right_node:
            raise SyntaxError("invalid syntax")

        node = ExpressionNode(operator, "", node, right_node)

    return node


def _expression() -> ExpressionNode:
    """
    <expression> ::= [ +|- ] <term> { <plus_operator> <term> }
    :return: expression node if the current token is an expression, raise error otherwise
    """
    global _token_index
    # print("expr", end=" ")
    # print(_expression_index, end=" ")
    # print(_expression_tokens[_expression_index][1])

    # check for leading operators
    leading_sign = _add_operator()

    node = _term()
    if not node:
        raise SyntaxError("invalid syntax")

    while True:
        # end of expression
        if _token_index == len(_tokens):
            break

        operator = _add_operator()
        if operator == ExpressionType.UNKNOWN:
            break

        right_node = _term()
        if not right_node:
            raise SyntaxError("invalid syntax")

        node = ExpressionNode(operator, "", node, right_node)

    if leading_sign != ExpressionType.UNKNOWN:
        node = ExpressionNode(
            leading_sign, "", ExpressionNode(ExpressionType.NUMBER, "0"), node
        )

    return node
```

# 实验四 语义分析

## 实验内容

已给 PL/0 语言文法，在表达式的语法分析程序里，添加语义处理部分。

## 实验思路

修改实验三的代码，在递归下降算法的基础上，生成抽象语法树，并通过递归遍历树计算出表达式的值。

## 关键代码

```python
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
```

# 实验五 中间代码生成

## 实验内容

已给 PL/0 语言文法，在实验三的表达式语法分析程序里，添加语义处理部分输出表达式的中间代码，用四元式序列表示。

## 实验思路

将实验四生成的AST，通过递归遍历树转换为四元式。

## 关键代码

```python
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
```
