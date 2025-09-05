class_name DoublyLinkedList
extends RefCounted

var head: DoublyLinkedListNode = null
var tail: DoublyLinkedListNode = null
var size: int = 0

func _init():
	pass

# Adds a new node to the end of the list
func append(p_data):
	var new_node = DoublyLinkedListNode.new(p_data)
	if head == null:
		head = new_node
		tail = new_node
	else:
		tail.next_node = new_node
		new_node.prev_node = tail
		tail = new_node
	size += 1

# Adds a new node to the beginning of the list
func prepend(p_data):
	var new_node = DoublyLinkedListNode.new(p_data)
	if head == null:
		head = new_node
		tail = new_node
	else:
		new_node.next_node = head
		head.prev_node = new_node
		head = new_node
	size += 1

# Removes a node with specific data
func remove(p_data):
	var current_node = head
	while current_node != null:
		if current_node.data == p_data:
			if current_node.prev_node != null:
				current_node.prev_node.next_node = current_node.next_node
			else:
				head = current_node.next_node

			if current_node.next_node != null:
				current_node.next_node.prev_node = current_node.prev_node
			else:
				tail = current_node.prev_node
			size -= 1
			return true # Node found and removed
		current_node = current_node.next_node
	return false # Node not found

# Prints the list from head to tail
func print_forward():
	var current_node = head
	var s = ""
	while current_node != null:
		s += str(current_node.data)
		if current_node.next_node != null:
			s += " <-> "
		current_node = current_node.next_node
	print("List (Forward): ", s)

# Prints the list from tail to head
func print_backward():
	var current_node = tail
	var s = ""
	while current_node != null:
		s += str(current_node.data)
		if current_node.prev_node != null:
			s += " <-> "
		current_node = current_node.prev_node
	print("List (Backward): ", s)
