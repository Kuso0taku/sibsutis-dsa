import random
import sys
import time


def main():
    print("\n============================\n"
          "This program generates <n> random words with generator's seed <seed>\n"
          "from <min length> to <max length>, from <min ascii> to <max ascii>\n"
          "and writes them into <filename>;\n"
          "if generator's seed equals 0, then seed is the current time\n"
          "============================\n")

    try:
        n, min_length, max_length, min_ascii, max_ascii, seed = map(
            int,
            input("Input:\n<n> <min length> <max length> <min ascii> <max ascii> <seed>\n").split(),
        )
    except ValueError:
        print("Expected 6 integers separated by spaces.")
        sys.exit(1)

    if max_length < min_length or max_ascii < min_ascii:
        print("<max length> should be greater than or equal to <min length>\n"
              "<max ascii> should be greater than or equal to <min ascii>\n")
        sys.exit(1)

    if (n < 1 or min_length < 1 or max_length < 1
            or min_ascii < 32 or max_ascii < 32
            or min_ascii > 126 or max_ascii > 126):
        print("all numbers should be greater than 0;\n"
              "<max ascii> and <min ascii> should be less than 127 and greater than 31;\n")
        sys.exit(1)

    if n > 5_000_000:
        print("n > 5000000, exit\n")
        sys.exit(1)
    elif n >= 1_000_000:
        res = input(f"n = {n}, press <Y> to continue\n")
        if res != "Y":
            sys.exit(1)

    if seed == 0:
        seed = int(time.time())
    random.seed(seed)

    filename = input("Input <filename>:\n")

    with open(filename, "w") as f:
        for _ in range(n):
            word_len = random.randint(min_length, max_length)
            word = "".join(
                chr(random.randint(min_ascii, max_ascii))
                for _ in range(word_len)
            )
            f.write(word + "\n")

    print("Done\n")


if __name__ == "__main__":
    main()
