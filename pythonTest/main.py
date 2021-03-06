import turtle
import sys
import argparse
from myConway import *

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument('-width', type=int, help="enter the width of the grid in terms of the number of cells")
	parser.add_argument('-height', type=int, help="enter the height of the grid in terms of the number of cells")
	args = parser.parse_args()


	scr = turtle.Screen()
	turtle.mode('standard')
	turtle.bgcolor('lightblue')
	width, height = scr.screensize()
	turtle.setworldcoordinates(0, 0, width, height)

	turtle.speed(0)

	def square(size):
		turtle.color('grey')
		turtle.setheading(0)
		for i in range(5):
			turtle.forward(size)
			turtle.left(90)

	def row(size):
		r = size//CELL_SIZE
		for i in range(r):
			square(CELL_SIZE)

	def gridLines(height, width):
		r = height//CELL_SIZE
		for i in range(r):
			turtle.pendown()
			row(width)
			turtle.penup()
			turtle.setpos(0, (i+1)*CELL_SIZE)


	try:
		x = int(args.width)
		y = int(args.height)
	except:
		raise ValueError('Grid dimensions are not of type int')

	gridLines(y*CELL_SIZE, (x+1)*CELL_SIZE)
	display_instruction_window(width, height)

	turtle.hideturtle()
	turtle.speed('fastest')
	turtle.tracer(0, 0)
	turtle.penup()

	grid = Grid(x, 1 + y)

	def toggle(x, y):
		cell_x = x//CELL_SIZE
		cell_y = y//CELL_SIZE
		if grid.isValidMove(cell_x, cell_y):
		    grid.revCellState(cell_x, cell_y)
		    grid.drawGrid()

	turtle.onscreenclick(turtle.listen)
	turtle.onscreenclick(toggle)

	grid.genGrid()
	grid.drawGrid()

	def clear():
		grid.clearGrid()
		grid.drawGrid()
	turtle.onkey(clear, 'e')

	def randomize():
		grid.genGrid()
		grid.drawGrid()
	turtle.onkey(randomize, 'r')

	turtle.onkey(sys.exit, 'q')

	continuous = False
	def step_once():
	    nonlocal continuous
	    continuous = False
	    perform_step()

	def step_continuous():
	    nonlocal continuous
	    continuous = True
	    perform_step()

	def perform_step():
	    grid.nextGen()
	    grid.drawGrid()
	    if continuous:
	        turtle.ontimer(perform_step, 25)

	turtle.onkey(step_once, 's')
	turtle.onkey(step_continuous, 'c')

	turtle.listen()
	turtle.mainloop()

if __name__ == '__main__':
	main()