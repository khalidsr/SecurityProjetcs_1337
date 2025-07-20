import turtle

# Set up the screen
screen = turtle.Screen()
screen.setup(800, 600)  # Set window size to 800x600 pixels

# Set up the turtle
t = turtle.Turtle()
t.speed(0)  # Fastest speed
t.penup()
t.goto(0, 0)  # Start at the center of the screen
t.pendown()

# Scale factor for movements
scale = 0.25  # Divide distances by 4 to fit screen

# Initial sequence
t.left(90)
t.forward(50 * scale)
t.forward(1 * scale)
for _ in range(90):  # Loop for 90 repetitions of left 1 degree, forward 1
    t.left(1)
    t.forward(1 * scale)
for _ in range(90):  # Loop for 90 repetitions of right 1 degree, forward 1
    t.right(1)
    t.forward(1 * scale)

# Middle sequence
t.forward(50 * scale)
t.forward(210 * scale)
t.backward(210 * scale)
t.right(90)
t.forward(120 * scale)
t.right(10)
t.forward(200 * scale)
t.right(150)
t.forward(200 * scale)
t.backward(100 * scale)
t.right(120)
t.forward(50 * scale)

# Second repetitive sequence
t.left(90)
t.forward(50 * scale)
t.forward(1 * scale)
for _ in range(90):  # Loop for 90 repetitions of left 1 degree, forward 1
    t.left(1)
    t.forward(1 * scale)
for _ in range(90):  # Loop for 90 repetitions of right 1 degree, forward 1
    t.right(1)
    t.forward(1 * scale)

# Final sequence
t.forward(50 * scale)
t.forward(100 * scale)
t.backward(200 * scale)
t.forward(100 * scale)
t.right(90)
t.forward(100 * scale)
t.right(90)
t.forward(100 * scale)
t.backward(200 * scale)

# Keep the window open
turtle.done()
