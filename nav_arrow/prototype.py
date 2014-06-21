#!/usr/bin/env python

import time

# Hack the path to include our proto lib
import sys
sys.path.append('arduino-proto/')

from arduino import Arduino

b = '/dev/ttyUSB0'

# Read the directional data

# Mock directional array, maybe will only have one at a time
# GPS will update the distance. INF 

# Should there be a latlon in here for the Arduino to make this decision for us?
directions = [
        { 'direction': 'left', 'distance': 100 },
        { 'direction': 'left', 'distance': 50 },
        { 'direction': 'left', 'distance': 30 },
        { 'direction': 'left', 'distance': 20 },
        { 'direction': 'left', 'distance': 10 },
        { 'direction': 'left', 'distance': 5 },
        { 'direction': 'right', 'distance': 100 },
        ]

# Turn the directions into a servo update

def check_distance(distance, direction):
    if (distance < 5):
        print('Turn', direction, 'now')
    elif (distance < 15):
        print('Turn', direction, 'soon')
    elif (distance < 30):
        print('Turn', direction, 'later')

    return

def handle_update(next_dir):
    distance = next_dir['distance']
    direction = next_dir['direction']

    if (direction == 'left'):
        check_distance(distance, direction)
    elif (direction == 'right'):
        check_distance(distance, direction)

for direc in directions:
    handle_update(direc)
    sys.stdout.flush()
    time.sleep(30)

exit(0)



