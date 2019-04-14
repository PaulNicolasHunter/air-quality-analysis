# Air quality analysis

The project consists of the following apparatus->
- Ardunio UNO
- MQ2 gas sensor
- sharp particle sensor
- Raspberry PI 3

Workflow ->

- The Arduino continously senses the air quality with the help of the sensors 
- if the concentration of particle or the gas increases to any point, then it triggers our air purifier, to ON state.
- The air purifier is a 12V DC fan attached to an filter.
- details about the air filer -> 

* Filters 99.97% of dust, pollen, smoke, odors, mold spores, and pet dander.
* Can as small as 0.3 microns and larger and filters air pollution of PM 2.5 (pollution rate) to help improve overall health
* True HEPA, Fine Preliminary, and Activated Carbon filters reduce unwanted odors in your living spaces. Perfect for pet owners, children,  elderly, or for anyone wanting to improve air quality
* Filters are sealed to protect their lifetime. It is recommended to replace air filters every 6 months. 

software requirements -> 

Python 3.x
- [gspread](https://github.com/burnash/gspread)
- [pyserial](erial.readthedocs.io/en/latest/shortintro.html)

buy links -> 
### - [fan](https://www.amazon.in/gp/product/B07M5LT81W/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
### - [filter](https://www.amazon.in/gp/product/B077NCJQY1/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)

_~peace_
