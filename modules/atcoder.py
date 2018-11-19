import html
import re
import os
from http import cookiejar
from urllib.request import build_opener, install_opener, HTTPCookieProcessor
from urllib.parse import urlencode
from modules import settings
from pyquery import PyQuery

class Language:
  cpp = 3003

def _get_csrf_token(url, cookie_jar):
  opener = build_opener(HTTPCookieProcessor(cookie_jar))
  install_opener(opener)
  with opener.open(url) as f:
    html_str = re.compile(r'([\r\n\t]|  )').sub('', f.read().decode('utf-8'))
    mc = re.compile(r'.*<input type="hidden" name="csrf_token" value=\'([^"]+)\' />').match(html_str)
    if not mc:
      raise RuntimeError("can't find csrf_token in {0}".format(url))
    csrf_token = html.unescape(mc.group(1))
  return csrf_token

def login(user_id, password):
  url = 'https://beta.atcoder.jp/login'
  cj = cookiejar.LWPCookieJar()
  csrf_token = _get_csrf_token(url, cj)
  opener = build_opener(HTTPCookieProcessor(cj))
  install_opener(opener)
  param = {
    "username": user_id,
    "password": password,
    "csrf_token": csrf_token,
    "User-Agent": settings.user_agent,
  }
  res = False
  with opener.open(url, data=urlencode(param).encode('ascii')) as fs:
    cj.save(settings.path_to_cookie)
    html_str = re.compile(r'([\r\n\t]|  )').sub('', fs.read().decode('utf-8'))
    if html_str.find('/login') >= 0:
      root = PyQuery(html_str)
      message = root.find('.alert').eq(0).text().replace('× ', '')
      raise Exception(message)
  return res

def _load_cookiejar():
  cj = cookiejar.LWPCookieJar()
  if not os.path.exists(settings.atcoder_cookie_file_path):
    raise Exception('run `./login atcoder` first')
  cj.load(settings.path_to_cookie)
  return cj

def submit(source_code, contest_name, task_name, language_id=Language.cpp):
  cj = _load_cookiejar()
  url = 'https://beta.atcoder.jp/contests/{0}/submit'.format(contest_name)
  csrf_token = _get_csrf_token(url, cj)
  opener = build_opener(HTTPCookieProcessor(cj))
  install_opener(opener)
  param = {
    "data.TaskScreenName": task_name,
    "data.LanguageId": language_id,
    "sourceCode": source_code.replace('\r\n', '\n').replace('\n', '\r\n'),
    "csrf_token": csrf_token,
    "User-Agent": settings.user_agent,
  }
  with opener.open(url, data=urlencode(param).encode('ascii')) as fs:
    cj.save(settings.path_to_cookie)

# def get_my_submissions(contest_name):
#   cj = _load_cookiejar()
#   url = 'https://beta.atcoder.jp/contests/{0}/submissions/me'.format(contest_name)
#   opener = build_opener(HTTPCookieProcessor(cj))
#   install_opener(opener)
#   res = []
#   with opener.open(url) as f:
#     cj.save(settings.atcoder_cookie_file_path)
#     html_str = f.read().decode('utf-8')
#     root = PyQuery(html_str)
#     for tr in root.find(".table-responsive > table > tbody > tr"):
#       res.push({
#         "id":
#         "date":
#         "task_name": tr.find(
#         "score":
#         "status":
#         "size_bytes":
#         "time_ms":
#         "memory_usage_kb":
#       })
#   return res
#
# <td class="no-break"><time class='fixtime fixtime-second'>2018-04-14 21:21:02+0900</time></td>
# <td><a href='/contests/arc095/tasks/arc095_b'>D - Binomial Coefficients</a></td>
# <td><a href='/users/drafear'>drafear</a> <a href='/contests/arc095/submissions?f.User=drafear'><span class='glyphicon glyphicon-search black' aria-hidden='true' data-toggle='tooltip' title='drafearさんの提出を見る'></span></a></td>
# <td>C&#43;&#43;14 (GCC 5.4.1)</td>
# <td class="text-right submission-score" data-id="2348877">400</td>
# <td class="text-right">1617 Byte</td>
# <td class='text-center'><span class='label label-success' aria-hidden='true' data-toggle='tooltip' data-placement='top' title="正解">AC</span></td><td class='text-right'>28 ms</td><td class='text-right'>3188 KB</td>
# <td class="text-center">
#   <a href='/contests/arc095/submissions/2348877'>詳細</a>
# </td>