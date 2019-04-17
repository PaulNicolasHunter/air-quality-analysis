import serial
import time
import json
import gspread
from datetime import datetime as dt
from oauth2client.service_account import ServiceAccountCredentials
import re

aud = serial.Serial("/dev/ttyACM1", 9600)
scopes = ["https://www.googleapis.com/auth/drive",
          "https://www.googleapis.com/auth/spreadsheets"]

goog_creds = ServiceAccountCredentials.from_json_keyfile_name(
    'airy.json', scopes=scopes)

gc = gspread.authorize(goog_creds)
sheet = gc.open('Air Quality1')
sheet.share('choudhary.vivek98@gmail.com', perm_type='user', role='writer')
work_sheet = sheet.worksheet('sheet')


def process_dat(dat):
    """
       The columns will be: TimeStamp, dust_reading, gas_reading_1, gas_reading_2, gas_reading_3
    """
    return [dt.now().strftime('%A-%d-%B-%Y-(%H-%M-%S-%f)-%Z'), dat]


while True:
    loaded = str(aud.read())
    
    print(loaded)
##    if not dat:
##        its_in_the_air = process_dat(float(loaded))
##        work_sheet.append_row(its_in_the_air)
