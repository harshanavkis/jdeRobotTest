import turtle
import sys
from myConway import *

def main():
	display_instruction_window()

	scr = turtle.Screen()
	turtle.mode('standard')
	width, height = scr.screensize()
	turtle.setworldcoordinates(0, 0, width, height)

	turtle.hideturtle()
	turtle.speed('fastest')
	turtle.tracer(0, 0)
	turtle.penup()

	grid = Grid(width//CELL_SIZE, 1 + height//CELL_SIZE)

	def toggle(x, y):
		cell_x = x/CELL_SIZE
		cell_y = y/CELL_SIZE
		if board.isValidMove(cell_x, cell_y):
		    board.revCellState(cell_x, cell_y)
		    board.drawGrid()

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