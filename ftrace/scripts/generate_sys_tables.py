#!/usr/bin/env python3

from argparse import ArgumentParser
from contextlib import contextmanager
from os import path, makedirs
from string import whitespace
from requests import get


REPO_URL = "https://raw.githubusercontent.com/strace/strace/master/linux/"
FILE_URL_EXT = ".h"
FILE_EXT = ".data"

LINE_TAB = "    "
LINE_FEED = "\n"


def main():
    args = parse_args()

    dirname = path.dirname(path.abspath(args.output))
    if not path.exists(dirname):
        makedirs(dirname)

    with open(args.output, "w") as outputStream:
        outputStream.write('#include "syscall.h"' + (2 * LINE_FEED))
        outputStream.write("syscall_t " + args.table_name + "[] = {" + LINE_FEED)

        transform_file(args.file, outputStream, args.refetch)

        outputStream.write("};" + LINE_FEED)


def parse_args():
    parser = ArgumentParser()
    parser.add_argument("--file", required=True)
    parser.add_argument("--refetch", action="store_true")
    parser.add_argument("--output", required=True)
    parser.add_argument("--table_name", required=True)

    return parser.parse_args()


@contextmanager
def open_downloaded_file(filePath, mode="r", refetch=False):
    def yield_file(file):
        try:
            yield file
        finally:
            file.close()

    if not refetch:
        try:
            file = open(filePath + FILE_EXT, mode)
        except IOError:
            pass
        else:
            return yield_file(file)

    download_file(filePath)
    return yield_file(open(filePath + FILE_EXT, mode))


def download_file(filePath):
    response = get(REPO_URL + filePath.replace("~", "/") + FILE_URL_EXT)
    response.raise_for_status()

    with open(filePath + FILE_EXT, "wb") as outputStream:
        outputStream.write(response.content)


def transform_file(inputPath, outputStream, refetch):
    with open_downloaded_file(inputPath, "r", refetch) as inputStream:
        outputStream.write(LINE_FEED)
        for line in inputStream:
            if line.startswith("#include"):
                transform_file(line[10:-4], outputStream, refetch)
            else:
                outputStream.write(LINE_TAB + transform_line(line) + LINE_FEED)


def transform_line(line):
    line_begin = line.find("{") + 1

    if not (line[0] == "[" and line.count(",") == 4):
        return line[:-1]

    contents = line[line_begin:-3]
    for spaceChar in whitespace:
        contents = contents.replace(spaceChar, "")

    id, _, _, name = contents.split(",")

    return line[0:line_begin] + ".nargs = " + id + ", .name = " + name + " },"


if __name__ == "__main__":
    main()
