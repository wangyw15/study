import enum


type Token = tuple[TokenType, str]


class TokenType(enum.Enum):
    # operators
    PLUS = r"\+"
    MINUS = "-"
    TIMES = r"\*"
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
