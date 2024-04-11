import argparse
from pathlib import Path
import tests

from compiler import lexer, checker

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
            result = lexer.count_identifiers(code)
            for identifier, count in result.items():
                print(f"({identifier}, {count})")
        elif arg.experiment_name == "experiment2":
            result = lexer.get_tokens(code)
            for i in result:
                print(f"({i[0]}, {i[1]})")
        elif arg.experiment_name == "experiment3":
            print(checker.check(code))


if __name__ == "__main__":
    main()
