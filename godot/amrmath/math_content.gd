extends Sprite2D

var texture1 = preload("res://algebraic_expression_definition.png") # Preload for efficiency

func _ready():
	# Example: Change the sprite when the scene is ready
	texture = texture1

func _input(event):
	if event is InputEventScreenTouch:
		if not event.pressed:  # Check if the touch is released
			# This code will execute when a screen touch is released
			print("Screen touch released at position: ", event.position)
			# Add your custom action here, e.g.,
			# do_something_on_touch_release()
			if texture == texture1:
				texture = preload("res://Components_of_an_algebraic_expression.png")
			else:
				texture = texture1
		
