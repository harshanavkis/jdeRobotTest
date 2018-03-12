import unittest
from myConway import *

class myConwayTests(unittest.TestCase):
	def test_liveOrDie(self): 
		testGrid = Grid(100, 200)
		self.assertEqual(testGrid.liveOrDie(True, 1), False) #live cell dies if it has less than 2 liveneighbours
		self.assertEqual(testGrid.liveOrDie(True, 4), False) #live cell dies if it has more than 3 liveneighbours
		self.assertEqual(testGrid.liveOrDie(False, 3), True) #dead cell lives if it has exactly 3 liveneighbours
		self.assertEqual(testGrid.liveOrDie(True, 3), True) #live cell lives if it has 2 or 3 liveneighbours
		self.assertEqual(testGrid.liveOrDie(True, 2), True)