#!/usr/bin/env python3

import argparse
import sys
import traceback
import getpass
from modules import atcoder

def parser():
  parser = argparse.ArgumentParser(description="Login to an online judge' and test it")
  parser.add_argument('target', metavar='target-online-judge', type=str, help='atcoder/aoj')
  return parser

def get_user_id():
  return input('User Id: ')

def get_password():
  return getpass.getpass()

def login_to_atcoder():
  user_id = get_user_id()
  password = get_password()
  atcoder.login_and_save_cookie(user_id=user_id, password=password)

def login_to_aoj():
  user_id = get_user_id()
  password = get_password()
  sys.stderr.write('未実装です')
  exit(1)

def main():
  args = parser().parse_args()
  target_online_judge = args.target
  try:
    if target_online_judge == 'atcoder':
      login_to_atcoder()
    elif target_online_judge == 'aoj':
      login_to_aoj()
    else:
      raise RuntimeError('unknown online judge: {0}'.format(target_online_judge))
    print('Logged in successfully!!')
  except Exception as e:
    # sys.stderr.write(traceback.format_exc()+'\n')
    sys.stderr.write(str(e)+'\n')
    exit(1)

main()
