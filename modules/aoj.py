import html
import re
import os
import json
import requests
from http import cookiejar
from modules import settings, judge_result
from pyquery import PyQuery
from time import sleep

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

class Language:
  cpp = 'C++14'

def api(path, method, param={}):
  url = 'https://judgeapi.u-aizu.ac.jp{0}'.format(path)
  session = requests.session()
  cookie_file_path = settings.path_to_cookie
  cj = cookiejar.LWPCookieJar()
  if os.path.exists(cookie_file_path):
    cj.load(cookie_file_path, ignore_discard=True)
  headers = {
    'content-type': 'application/json',
  }
  data = json.dumps(param).encode('utf-8')
  res = session.request(method, url, headers=headers, data=data, cookies=cj)
  if res.status_code == 200:
    for cookie in session.cookies:
      cj.set_cookie(cookie)
    cj.save(cookie_file_path, ignore_discard=True)
    return res.json()
  elif res.status_code == 400:
    result = res.json()[0]
    raise Exception('{0}: {1}: {2}'.format(path, result['code'], result['message']))
  else:
    raise Exception('{0}: HTTP Error {1}: {2}'.format(path, res.status_code, res.text))

def is_login():
  try:
    api('/self', 'GET')
    return True
  except Exception as e:
    if str(e).find('INVALID_REFRESH_TOKEN_ERROR: ') >= 0:
      return False
    raise e

def login(user_id, password):
  api('/session', 'POST', {
    "id": user_id,
    "password": password,
  })

# submit and return token for checking judge result
def submit(source_code, problem_id, language=Language.cpp):
  token = api('/submissions', 'POST', {
    "problemId": problem_id,
    "language": language,
    "sourceCode": source_code.replace('\r\n', '\n').replace('\n', '\r\n'),
  })['token']
  while True:
    status = get_judge_status(token)
    judge = status['status']
    if judge == JudgeType.STATE_RUNNING or judge == JudgeType.STATE_WAITING:
      sleep(1)
      continue
    result = api('/verdicts/{0}'.format(status['judgeId']), 'GET')['submissionRecord']
    return judge_result.JudgeResult(status=judge, time=result['cpuTime'], memory=result['memory'])

def get_user_id():
  return api('/self', 'GET')['id']

def get_judge_status(token):
  for result in api('/submission_records/recent', 'GET'):
    if result['token'] == token:
      return result
  raise Exception("can't find judge_id: {0}".format(token))
