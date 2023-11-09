def count_letters(text):
    # Compute the number of letters present in the text
    count_letters = 0

    for char in text:
        if char.isalpha():
            count_letters += 1

    return count_letters

def count_words(text):
    # Compute the number of words present in the text
    words = text.split()
    return len(words)

def count_sentences(text):
    # Compute the number of sentences in the text
    count_sentences = 0

    for char in text:
        if char in ['.', '!', '?']:
            count_sentences += 1

    return count_sentences

def get_grade(text):
    words = count_words(text)
    letters = count_letters(text)
    sentences = count_sentences(text)

    L_COEFF = 0.0588
    S_COEFF = 0.296
    COLEMAN_CONST = 15.8
    L = 0.0
    S = 0.0

    if words != 0:
        L = (letters / words) * 100
        S = (sentences / words) * 100

    index = (L_COEFF * L) - (S_COEFF * S) - COLEMAN_CONST

    return round(index)

if __name__ == "__main__":
    text = input("Text: ")
    grade = get_grade(text)

    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")
