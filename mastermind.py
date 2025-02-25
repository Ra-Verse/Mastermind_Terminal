import random

COLORS = ["R", "B", "Y", "O", "G", "W"]
TRIES = 10
CODE_LENGTH = 4

def code_gen():
    code = []
    for i in range(CODE_LENGTH):
        code.append(random.choice(COLORS))
    return code

def guess_code():
    flag = False  # for outer loop

    while not flag:
        guess = input("Guess: ").upper().split(" ")

        flag = True 

        if len(guess) != CODE_LENGTH:
            print(f"You must guess {CODE_LENGTH} colors.")
            flag = False

        flag2 = False  # for inner loop

        for color in guess:
            if color not in COLORS:
                print(f"{color} is not a valid color. Choose from: R, B, Y, O, G, W")
                flag2 = True

        if flag2:
            flag = False

    return guess

def check_code(guess, code):
    color_count = {}
    correct_position = 0
    incorrect_position = 0

    for color in code:
        if color not in color_count:
            color_count[color] = 0
        color_count[color] += 1 

    for guess_color, real_color in zip(guess, code):
        if guess_color == real_color:
            correct_position += 1
            color_count[real_color] -=1

    for guess_color, real_color in zip(guess, code):
        if guess_color in real_color and color_count[guess_color] > 0:
            incorrect_position += 1
            color_count[guess_color] -= 1

    return correct_position, incorrect_position

def main():
    print(f"MasterMind")
    print(f"_________")
    print(f"")
    print("\nCorrect positions: Number of colors that are in the correct spot.")
    print("Incorrect positions: Number of correct colors but in the wrong spot.")
    print(f"")
    print(f"You have {TRIES} attempts to break the code")
    print(f"The valid colors are: ", *COLORS)
    code = code_gen()
    for attempts in range(1, TRIES + 1):
        guess = guess_code()
        correct_position, incorrect_position = check_code(guess, code)
        if correct_position == CODE_LENGTH:
            print(f"You cracked the code in {attempts} attempts!!")
            break
        print(f"Correct positions: {correct_position}       Incorrect positions: {incorrect_position}")

    else: 
        print("You ran out of tries, the code was ", *code)

if __name__ == "__main__":
    main()