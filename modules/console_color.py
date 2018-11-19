class Color:
  BLACK = '\033[30m'
  RED = '\033[31m'
  GREEN = '\033[32m'
  YELLOW = '\033[33m'
  BLUE = '\033[34m'
  PURPLE = '\033[35m'
  CYAN = '\033[36m'
  WHITE = '\033[37m'
  _END = '\033[0m'
  BOLD = '\038[1m'
  UNDERLINE = '\033[4m'
  INVISIBLE = '\033[08m'
  REVERCE = '\033[07m'

def change_color(new_color):
  print(new_color)

def colored(msg, color):
  return color + msg + Color._END
