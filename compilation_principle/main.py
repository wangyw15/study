import argparse
from pathlib import Path
import tests

from compiler.lexer import count_identifiers, tokenize
from compiler.parser import ast
from compiler.interpreter import execute
import dataclasses
import json


class EnhancedJSONEncoder(json.JSONEncoder):
    def default(self, o):
        if dataclasses.is_dataclass(o):
            return dataclasses.asdict(o)
        return super().default(o)


arg_parser = argparse.ArgumentParser(description="Compilation principle experiment")
subparsers = arg_parser.add_subparsers(dest="subcommand")

test_parser = subparsers.add_parser("test", help="Run tests of experiments")
test_parser.add_argument(
    "test_name",
    help="Name of the test to run",
    type=str,
    choices=tests.get_test_names() + ["all"],
)

runner_parser = subparsers.add_parser("run", help="Run experiments")
runner_parser.add_argument(
    "experiment_name",
    help="Name of the experiment to run",
    type=str,
    choices=tests.get_test_names(),
)
runner_parser.add_argument("input", help="Input file path", type=str)


def main():
    arg = arg_parser.parse_args()

    if not arg.subcommand:
        arg_parser.print_help()
        return

    if arg.subcommand == "test":
        import pytest

        tests_path = Path(__file__).parent / "tests"
        if arg.test_name == "all":
            pytest.main([str(tests_path)])
            return
        pytest.main([str(tests_path / f"test_{arg.test_name}.py")])
    elif arg.subcommand == "run":
        input_path = Path(arg.input)
        if not input_path.exists():
            print(f"Input file {input_path} not found")
            return
        with input_path.open("r") as f:
            code = f.read()

        if arg.experiment_name == "experiment1":
            result = count_identifiers(code)
            for identifier, count in result.items():
                print(f"({identifier}, {count})")
        elif arg.experiment_name == "experiment2":
            result = tokenize(code)
            for i in result:
                print(f"({i.type.name}, '{i.data}')")
        elif arg.experiment_name == "experiment3":
            print(ast(tokenize(code)) is not None)
        elif arg.experiment_name == "experiment4":
            ast_tree = ast(tokenize(code))
            print("AST tree:")
            print(json.dumps(ast_tree, indent=2, ensure_ascii=False, cls=EnhancedJSONEncoder))
            print("Result:")
            print(execute(ast_tree))


if __name__ == "__main__":
    main()
