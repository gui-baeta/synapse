import os
import subprocess
import numpy as np
import pandas as pd


def run_and_capture_time(bin_file, runs=6):
    times = []
    for _ in range(runs):
        # Run the binary and capture the output
        result = subprocess.run(["cargo", "run", "--release", "--bin", bin_file], capture_output=True, text=True)
        output_lines = result.stdout.splitlines()

        # Find the line containing "Time taken:"
        time_line = next((line for line in output_lines if "Time taken:" in line), None)
        if time_line:
            # Extract the time from the line
            time_str = time_line.split()[-1]
            time_seconds = float(time_str)
            times.append(time_seconds)
        else:
            print(f"Time taken not found for {bin_file}")

    return times


def main():
    # List of main files
    main_files = [i for i in range(0, 75, 2)]
    main_files.append(37)
    main_files = sorted(main_files)
    main_files = [f"main_{i}" for i in main_files]

    # CSV file
    csv_file = "run_times.csv"


    # Check if file exists
    if not os.path.exists(csv_file):
        with open(csv_file, 'w') as file:
            file.write("")
        dict = {}
        for file in main_files:
            dict[file] = [np.nan for _ in range(10)]

        run_times = pd.DataFrame(dict)
        run_times.to_csv(csv_file, index_label='run')



    # df = pd.read_csv(csv_file)
    #
    # df.to_csv(csv_file)

    # Loop through each main file
    for main_file in main_files:
        times = run_and_capture_time(main_file)
        df = pd.read_csv(csv_file, index_col='run')
        for ix in range(0, len(times)):
            df.loc[ix, main_file] = times[ix]

        df.to_csv(csv_file, index_label='run')

    print(f"Run times saved to {csv_file}")


if __name__ == "__main__":
    main()