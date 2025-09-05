extends Node2D

@onready var math_content_godot_node = $MathContent
	
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass


func _on_touch_screen_button_prev_released() -> void:
	if(math_content_godot_node.is_current_node_first_node() == true):
		# don't dispay next button
		pass
	else:
		math_content_godot_node.move_to_prev_node()
		
	var current_math_content_list_node = math_content_godot_node.current_math_content_list_node
	###
	
	math_content_godot_node.texture = current_math_content_list_node.data
	###


func _on_touch_screen_button_next_released() -> void:
	if(math_content_godot_node.is_current_node_last_node() == true):
		# don't dispay next button
		pass
	else:
		math_content_godot_node.move_to_next_node()
		
	var current_math_content_list_node = math_content_godot_node.current_math_content_list_node
	###
	
	math_content_godot_node.texture = current_math_content_list_node.data
	###
