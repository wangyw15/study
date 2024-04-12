import enum
from dataclasses import dataclass


class TokenType(enum.Enum):
    # operators
    PLUS = r"\+"
    MINUS = "-"
    ASTERISK = r"\*"
    SLASH = r"\/"
    # symbols
    LEFT_PARENTHESIS = r"\("
    RIGHT_PARENTHESIS = r"\)"
    EQUAL = "="
    PERIOD = r"\."
    BECOMES = ":="
    SEMICOLON = ";"
    COMMA = ","
    # keywords
    CONST = "const"
    VAR = "var"
    BEGIN = "begin"
    END = "end"
    # built-in functions
    READ = "read"
    WRITE = "write"
    # identifiers
    IDENTIFIER = r"[a-z_]\w*"
    NUMBER = r"\d+"
    UNKNOWN = ""


class ExpressionType(str, enum.Enum):
    ADD = "+"
    MINUS = "-"
    MULTIPLY = "*"
    DIVIDE = "/"
    IDENTIFIER = "identifier"
    NUMBER = "number"
    UNKNOWN = "unknown"


@dataclass
class Token:
    type: TokenType
    data: str


@dataclass
class ExpressionNode:
    type: ExpressionType = ExpressionType.UNKNOWN
    data: str = ""
    left: "ExpressionNode" = None
    right: "ExpressionNode" = None


@dataclass
class IntermediateTuple:
    operator: ExpressionType
    operand1: str
    operand2: str
    result: str
