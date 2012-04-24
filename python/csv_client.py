#!/usr/bin/env python
"""
Author: Chris Sauerwald(chris@afterfate.net)

VERY basic sample, YMMV.
"""

import sys
sys.path.append('lib/')
from charter_client import Chart

my_chart = Chart('CSV sample')

fd = open(sys.argv[1], 'r')

# This is more for readability than anything
# In my sample, the x values were the first element of the CSV, y values are
# second.
for line in fd:
   x = line.strip().split(',')[0]
   y = line.strip().split(',')[1]
   my_chart.append(x, y)

print "plot list: %s" % my_chart.plot_list
my_chart.ch.clear()
my_chart.plot()

fd.close()
