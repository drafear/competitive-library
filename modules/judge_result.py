import webbrowser
from modules.console_color import Color, colored

class JudgeType:
  STATE_COMPILEERROR = 0
  STATE_WRONGANSWER = 1
  STATE_TIMELIMIT = 2
  STATE_MEMORYLIMIT = 3
  STATE_ACCEPTED = 4
  STATE_WAITING = 5
  STATE_OUTPUTLIMIT = 6
  STATE_RUNTIMEERROR = 7
  STATE_PRESENTATIONERROR = 8
  STATE_RUNNING = 9

  @staticmethod
  def to_str(judge_type):
    if judge_type == JudgeType.STATE_COMPILEERROR:
      return colored("Compile Error", Color.RED)
    if judge_type == JudgeType.STATE_WRONGANSWER:
      return colored("Wrong Answer", Color.RED)
    if judge_type == JudgeType.STATE_TIMELIMIT:
      return colored("Time Limit Exceeded", Color.YELLOW)
    if judge_type == JudgeType.STATE_MEMORYLIMIT:
      return colored("Memory Limit Exceeded", Color.YELLOW)
    if judge_type == JudgeType.STATE_ACCEPTED:
      return colored("Accepted", Color.GREEN)
    if judge_type == JudgeType.STATE_WAITING:
      return "Waiting Judge"
    if judge_type == JudgeType.STATE_OUTPUTLIMIT:
      return colored("Output Limit Exceeded", Color.YELLOW)
    if judge_type == JudgeType.STATE_RUNTIMEERROR:
      return colored("Runtime Error", Color.YELLOW)
    if judge_type == JudgeType.STATE_PRESENTATIONERROR:
      return colored("Presentation Error", Color.CYAN)
    if judge_type == JudgeType.STATE_RUNNING:
      return "Running"
    return "Unknown"

class JudgeResult:
  def __init__(self, status, time, memory):
    self.type = status
    self.time = time
    self.memory = memory

  def output(self):
    print("""\
Result: {0}
Time:   {1} sec
Memory: {2} KB
""".format(JudgeType.to_str(self.type), self.time, self.memory))

class Browser:
  def __init__(self, url):
    self.url = url

  def output(self):
    webbrowser.open(self.url)
