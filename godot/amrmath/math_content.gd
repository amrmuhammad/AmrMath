extends Sprite2D

var math_content_list = DoublyLinkedList.new()
var current_math_content_list_node = null

var textures = [
	preload("res://math_content_textures/algebraic_expression_definition.png"),
	preload("res://math_content_textures/Components_of_an_algebraic_expression.png"),
	preload("res://math_content_textures/Components_of_an_algebraic_expression_2.png"),
	preload("res://math_content_textures/Components_of_an_algebraic_expression_3.png"),
	preload("res://math_content_textures/Components_of_an_algebraic_expression_4.png"),
	preload("res://math_content_textures/Components_of_an_algebraic_expression_5.png"),
	preload("res://math_content_textures/Examples_of_algebraic_expressions.png"),
	preload("res://math_content_textures/Types_of_Algebraic_Expressions.png"),
	preload("res://math_content_textures/examples_of_monomials.png"),
	preload("res://math_content_textures/examples_of_binomials.png"),
	preload("res://math_content_textures/examples_of_trinomials.png"),
	preload("res://math_content_textures/examples_of_polynomials.png") ,
	preload("res://math_content_textures/common_operations_on_algebraic_expressions.png"),
	preload("res://math_content_textures/common_operations_on_algebraic_expressions2.png"),
	preload("res://math_content_textures/common_operations_on_algebraic_expressions3.png"),
	preload("res://math_content_textures/common_operations_on_algebraic_expressions4.png"),
	preload("res://math_content_textures/exponents.png"),
	preload("res://math_content_textures/exponents2.png"),
	preload("res://math_content_textures/exponents3.png")
]

func _ready():
	# Change the sprite when the scene is ready
	texture = textures[0]
	###
	# load the math content into the math_content_list
	for current_texture in textures:
		math_content_list.append(current_texture)
		
	###
	current_math_content_list_node = math_content_list.head

func move_to_next_node():
	current_math_content_list_node = current_math_content_list_node.next_node
	
func is_current_node_last_node():
	if(current_math_content_list_node == math_content_list.tail):
		return true
	else:
		return false
		
func move_to_prev_node():
	current_math_content_list_node = current_math_content_list_node.prev_node
	
func is_current_node_first_node():
	if(current_math_content_list_node == math_content_list.head):
		return true
	else:
		return false


			
#func _input(event):
	#if event is InputEventScreenTouch:
		#if not event.pressed:  # Check if the touch is released
			## This code will execute when a screen touch is released
			#print("Screen touch released at position: ", event.position)
			## Add your custom action here, e.g.,
			## do_something_on_touch_release()
			#if texture == texture1:
				#texture = preload("res://Components_of_an_algebraic_expression.png")
			#else:
				#texture = texture1
		
