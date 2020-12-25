#!/usr/bin/env python3

from argparse import ArgumentParser
from os import path, makedirs
from string import whitespace

LINE_BEGIN = 10
LINE_END = -3


def main():
    parser = ArgumentParser()
    parser.add_argument("--input", required=True)
    parser.add_argument("--output", required=True)
    parser.add_argument("--table_name", required=True)
    args = parser.parse_args()

    if not path.exists(path.dirname(args.output)):
        makedirs(path.dirname(args.output))

    with open(args.input) as inputFile, open(args.output, "w") as outputFile:
        outputFile.write('#include "syscall.h"\n')
        outputFile.write("syscall_t " + args.table_name + "[] = {\n")
        for line in inputFile:
            outputFile.write("    " + transform_line(line) + "\n")
        outputFile.write("};\n")


def transform_line(line):
    if line.startswith("#include"):
        return ""

    if not (line[0] == "[" and line[4] == "]"):
        return line[:-1]

    contents = line[LINE_BEGIN:LINE_END]
    for spaceChar in whitespace:
        contents = contents.replace(spaceChar, "")

    id, _, _, name = contents.split(",")

    return line[0:LINE_BEGIN] + ".nargs = " + id + ", .name = " + name + " },"


if __name__ == "__main__":
    main()
