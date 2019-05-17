import serial
import datetime
import json
import gspread
from datetime import datetime as dt
from oauth2client.service_account import ServiceAccountCredentials
import re


aud = serial.Serial("/dev/ttyACM0", 9600)
scopes = ["https://www.googleapis.com/auth/drive",
          "https://www.googleapis.com/auth/spreadsheets"]

goog_creds = ServiceAccountCredentials.from_json_keyfile_name(
    '<crediatial_used>.json', scopes=scopes) # private

gc = gspread.authorize(goog_creds)
sheet = gc.open('Air_Quality')
work_sheet = sheet.worksheet('sheet')

def process_dat(dat):
    """
       The columns will be: TimeStamp, dust_reading, gas_reading_1, gas_reading_2, gas_reading_3
    """
    return [round(datetime.datetime.utcnow().timestamp() * 1000), dat]

def read_line():
    loaded = re.findall('\d.\d\d', str(aud.readline()))
    if loaded:
        return process_dat(float(loaded[0]))

def update_sheet(its_in_the_air):
    work_sheet.append_row(its_in_the_air)

if __name__ == '__main__':

    while True:
        cool = read_line()    
        update_sheet(cool)
        
