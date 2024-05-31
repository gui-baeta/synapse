import os
import re
import subprocess
import numpy as np
import pandas as pd


def get_num_of_ops(rs_file: str) -> int:
    file_path = os.path.join("./src/bin/", "main_" + rs_file.split("_")[1] + ".rs")
    with open(file_path, 'r') as file:
        content = file.read()

    # Find the line containing the sum operations
    line_with_sums = re.search(r'let val10\s*=\s*(.+);', content)
    num_sums = 0
    if line_with_sums:
        # Extract the expression containing the sums
        sum_expression = line_with_sums.group(1)
        # Count the number of '+' characters in the expression
        num_sums = sum_expression.count('+')

    num_ops = content.count('*') - 1 + num_sums
    return int(num_ops)


def get_num_pbss(rs_file: str) -> (int, int, int):
    file_path = os.path.join("./src/bin/", "main_" + rs_file.split("_")[1] + ".rs")
    with open(file_path, 'r') as file:
        content = file.read()

    # Count the number of .map( and .bivariate_function( occurrences
    num_pbss = len(re.findall(r'(?<!//)\.map\(|(?<!//)\.bivariate_function\(', content))

    # Count the number of .bivariate_function( occurrences
    num_bivariate_pbss = len(re.findall(r'(?<!//)\.bivariate_function\(', content))

    # Count the number of .map( occurrences
    num_univariate_pbss = len(re.findall(r'(?<!//)\.map\(', content))

    return int(num_pbss), int(num_bivariate_pbss), int(num_univariate_pbss)


def get_num_of_ops_2(rs_file: str) -> int:
    file_path = os.path.join("./src/bin/", rs_file + ".rs")
    print(file_path)
    with open(file_path, 'r') as file:
        content = file.read()

    # Find the line containing the assignment of val10
    num_sums = 0
    num_multiplications = 0
    num_xors = 0
    assignment_lines = re.findall(r'let val10(_\d+)? = ([^;]*);', content)

    # Initialize counts for sums, multiplications, XORs, and shifts
    num_sums = 0
    num_multiplications = 0
    num_xors = 0

    # Loop through each assignment line
    for line in assignment_lines:
        # Extract the expression on the right-hand side of the assignment
        expression = line[1]
        # Count the number of '+' and '*' characters in the expression
        num_sums += expression.count('+')
        num_multiplications += expression.count('*')
        num_xors += expression.count('^')

    # Find all lines containing left shifts
    shift_lines = re.findall(r'let .+ = .+ << .+;', content)
    num_shifts = sum([line.count('<<') for line in shift_lines])

    num_ops = num_sums + num_multiplications + num_xors + num_shifts
    return int(num_ops)


def get_num_pbss_2(rs_file: str) -> (int, int, int):
    file_path = os.path.join("./src/bin/", rs_file + ".rs")
    with open(file_path, 'r') as file:
        content = file.read()

    # Count the number of .bivariate_function( occurrences
    exprs = re.findall(r'.+\.bivariate_function\(', content)
    num_bivariate_pbss = 0
    for expr in exprs:
        print(expr)
        if "//" not in expr:
            num_bivariate_pbss += 1

    # Count the number of .map( occurrences
    exprs = re.findall(r'.+\.map\(', content)
    num_univariate_pbss = 0
    for expr in exprs:
        if "//" not in expr:
            num_univariate_pbss += 1

    return int(num_bivariate_pbss + num_univariate_pbss), int(num_bivariate_pbss), int(num_univariate_pbss)


def main():
    # List of main files
    main_files = [i for i in range(0, 75)]
    main_files = sorted(main_files)
    main_files = [f"solution_{i}" for i in main_files]

    # CSV file
    csv_file = "all_solutions_number_of_ops_and_pbss.csv"


    # Check if file exists
    if not os.path.exists(csv_file):
        with open(csv_file, 'w') as file:
            file.write("")
        dict = {}
        for file in main_files:
            dict[file] = [np.nan for _ in range(2)]

        num_ops_df = pd.DataFrame(dict, index=['# Operations', '# PBSs', '# Bivariate PBSs', '# Univariate PBSs'], dtype=object)
        num_ops_df.to_csv(csv_file, index_label='op_kind')

    # Loop through each main file
    for solution_name in main_files:
        num_ops = get_num_of_ops(solution_name)
        num_pbss, num_bivariate_pbss, num_univariate_pbss = get_num_pbss(solution_name)
        df = pd.read_csv(csv_file, index_col='op_kind', dtype=object)

        df.loc['# Operations', solution_name] = int(num_ops)
        df.loc['# PBSs', solution_name] = int(num_pbss)
        df.loc['# Bivariate PBSs', solution_name] = int(num_bivariate_pbss)
        df.loc['# Univariate PBSs', solution_name] = int(num_univariate_pbss)

        df.to_csv(csv_file, index_label='op_kind')

    print(f"# of ops and PBSs saved to {csv_file}")


def num_ops_vs_optm_degree():
    solution_prefixes = ["main", "algebra_optimized_main", "lut_optimized_after_algebra_optm_main"]
    # optm_kind_column_label = ["SyNAPSE's Direct Solution", "Algebra Simplification", "LUT Optimization"]
    solution_nums = [0, 37, 74]

    solution_names = []
    for solution_prefix in solution_prefixes:
        for solution_num in solution_nums:
            solution_names.append(solution_prefix + "_" + str(solution_num))

    # CSV file
    csv_file = "num_ops_vs_optm_degree.csv"

    # Check if file exists
    if not os.path.exists(csv_file):
        with open(csv_file, 'w') as file:
            file.write("")
        dict = {}
        for col_label in solution_names:
            dict[col_label] = [np.nan for _ in range(4)]

        num_ops_df = pd.DataFrame(dict, index=['# Operations', '# PBSs', '# Bivariate PBSs', '# Univariate PBSs'],
                                  dtype=object)
        num_ops_df.to_csv(csv_file, index_label='op_kind')

    # Loop through each main file
    for solution_name in solution_names:
        num_ops = get_num_of_ops_2(solution_name)
        num_pbss, num_bivariate_pbss, num_univariate_pbss = get_num_pbss_2(solution_name)
        df = pd.read_csv(csv_file, index_col='op_kind', dtype=object)

        df.loc['# Operations', solution_name] = int(num_ops)
        df.loc['# PBSs', solution_name] = int(num_pbss)
        df.loc['# Bivariate PBSs', solution_name] = int(num_bivariate_pbss)
        df.loc['# Univariate PBSs', solution_name] = int(num_univariate_pbss)

        df.to_csv(csv_file, index_label='op_kind')

    print(f"# of ops and PBSs saved to {csv_file}")


if __name__ == "__main__":
    # main()

    num_ops_vs_optm_degree()