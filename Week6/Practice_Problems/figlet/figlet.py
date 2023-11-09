from pyfiglet import Figlet
f = Figlet(font='slant')
text = input('input: ')
print(f.renderText(text))