import serial
import time
import json
import gspread
from datetime import datetime as dt

aud = serial.Serial("/dev/ttyACM0", 9600)
scopes = ["https://www.googleapis.com/auth/drive",
          "https://www.googleapis.com/auth/spreadsheets"]

goog_creds = ServiceAccountCredentials.from_json_keyfile_name(
    '<json-name>.json', scopes=scopes)

gc = gspread.authorize(goog_creds)
sheet = gc.open('Air Quality')
work_sheet = sheet.get_worksheet(0)


def process_dat(dat):
    """
       The columns will be: TimeStamp, dust_reading, gas_reading_1, gas_reading_2, gas_reading_3
    """
    return [dt.now().strftime('%A-%d-%B-%Y-(%H-%M-%S-%f)-%Z'), dat['dust'], dat['0']['reading'], dat['1']['reading'], dat['2']['reading']]


while True:
    loaded = json.loads(aud.read())
    its_in_the_air = process_dat(loaded)
    work_sheet = detail.append_row(its_in_the_air)
    print(f"dust reading => {loaded['dust']}, {loaded['0']['gas']} => {loaded['0']['reading']}, {loaded['1']['gas']} => {loaded['1']['reading']}, {loaded['2']['gas']} => {loaded['2']['reading']}")
