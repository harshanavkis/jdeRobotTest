import turtle
import random

CELL_SIZE = 8 #size in pixels

class Grid:
	#x==>width y==>height
	def __init__(self, height, width):
		self.height, self.width = height, width #dimensions of the grid
		self.state = set() #state of the grid

	def isValidMove(self, x, y):
		return (0<=x<self.width) and (0<=y<self.height)

	def genGrid(self):
		self.clearGrid()
		for i in range(self.width):
			for j in range(self.height):
				if random.random() > 0.5:
					self.addToState(i,j)

	def clearGrid(self):
		self.state.clear()

	def addToState(self, x, y):
		if self.isValidMove(x, y):
			coord = (x, y)
			self.state.add(coord)
		else:
			raise ValueError("Coordinates {} and {} are not in range {} and {}".format(x, y, self.width, self.height))

	def revCellState(self, x, y):
		if self.isValidMove(x, y):
			coord = (x, y)
			if coord in self.state:
				self.state.remove(coord)
			else:
				self.state.add(coord)

		else:
			raise ValueError("Coordinates {} and {} are not in range {} and {}".format(x, y, self.width, self.height))

	def nextGen(self):
		nextGen = set()
		for i in range(self.width):
			posX = range(max(0, i-1), min(self.width, i+2))
			for j in range(self.height):
				liveNeighbours = 0
				cellState = ((i, j) in self.state)
				for iy in range(max(0, j-1), min(self.width, j+2)):
					for ix in posX:
						if (ix, iy) in self.state:
							liveNeighbours += 1

				liveNeighbours -= cellState

				if liveNeighbours==2 and cellState:
					nextGen.add((i, j))
				elif liveNeighbours==3:
					nextGen.add((i, j))
				elif cellState:
					pass
		self.state = nextGen

	def draw(self, x, y):
		turtle.penup()
		coord = (x, y)
		if coord in self.state:
			turtle.setpos(x*CELL_SIZE, y*CELL_SIZE)
			turtle.color("black")
			turtle.pendown()
			turtle.setheading(0)
			turtle.begin_fill()
			for i in range(4):
				turtle.forward(CELL_SIZE-1)
				turtle.left(90)

		turtle.end_fill()

	def drawGrid(self):
		turtle.clear()
		for i in range(self.width):
			for j in range(self.height):
				self.draw(i, j)
		turtle.update()

def display_instruction_window():
	from turtle import TK
	root = TK.TK()
	frame = TK.Frame()
	canvas = TK.Canvas(root, width=300, height=200, bg="white")
	canvas.pack()
	instr_screen = turtle.TurtleScreen(canvas)
	instr_t = turtle.RawTurtle(instr_screen)
	instr_t.penup()
	instr_t.hideturtle()
	instr_t.speed('fastest')

	width, height = instr_screen.screensize()
	line_height = 20
	y = height // 2 - 30

	for s in ("Click on cells to make them alive or dead.",
              "Keyboard commands:",
              " E)rase the board",
              " R)andom fill",
              " S)tep once or",
              " C)ontinuously -- use 'S' to resume stepping",
              " Q)uit"):
        instr_t.setpos(-(width / 2), y)
        instr_t.write(s, font=('sans-serif', 14, 'normal'))
        y -= line_height

