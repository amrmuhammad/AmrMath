class_name DoublyLinkedListNode
extends RefCounted

var data
var next_node: DoublyLinkedListNode = null
var prev_node: DoublyLinkedListNode = null

func _init(p_data):
	data = p_data
