import numpy as np


def read_lines_up_to(file_path, line_number):
    # Initialize an empty list to store the lines
    lines = []

    # Open the file
    with open(file_path, "r") as file:
        for current_line_number, line in enumerate(file, start=1):
            if current_line_number > line_number:
                break
            lines.append(line.rstrip("\n") + "\n")

    return lines


def save_lines_to_new_file(lines, output_file_path):
    with open(output_file_path, "w") as file:
        file.writelines(lines)  # Writes all lines to the file


# main header information
line_number = 11  # Read up to line 11
lines_to_save = read_lines_up_to("0.pcd", line_number)
print(lines_to_save)
save_lines_to_new_file(lines_to_save, "test.pcd")

# data load and crop intensity up to 255
data = np.loadtxt("0.pcd", skiprows=11)
print(np.shape(data))
data[:, -1] = np.where(data[:, -1] > 255, 255, data[:, -1])

with open("test.pcd", "a") as f:
    np.savetxt(f, data, delimiter=" ")
