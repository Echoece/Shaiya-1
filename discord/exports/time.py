import datetime

time = str(datetime.datetime.now())
time_zone = str(datetime.datetime.now().astimezone().tzinfo)

x = slice(0, 19)
print(time[x] + " " + time_zone)
exit(0)
